/* --COPYRIGHT--,BSD
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
//! \file   solutions/instaspin_foc/src/proj_lab01.c
//! \brief CPU and Inverter Set-up and introduction to interfacing to the ROM library
//!
//! (C) Copyright 2011, Texas Instruments, Inc.

//! \defgroup PROJ_LAB01 PROJ_LAB01
//@{

//! \defgroup PROJ_LAB01_OVERVIEW Project Overview
//!
//! CPU and Inverter Set-up and introduction to interfacing to the ROM library
//!

//
// **************************************************************************
// the includes

// system includes
#include <math.h>


// modules
#include "sw/modules/math/src/32b/math.h"
#include "sw/modules/memCopy/src/memCopy.h"


// drivers


// platforms
#include "main.h"


// **************************************************************************
// the defines

#define LED_BLINK_FREQ_Hz   5

// **************************************************************************
// the globals

uint_least32_t gLEDcnt = 0;                   // Counter used to divide down the ISR rate for visually blinking an LED

#ifdef F2802xF
#pragma DATA_SECTION(halHandle,"rom_accessed_data");
#endif
HAL_Handle halHandle;                         // Handle to the Inverter hardware abstraction layer

#ifdef F2802xF
#pragma DATA_SECTION(gUserParams,"rom_accessed_data");
#endif
USER_Params gUserParams;                      // Contains the user.h settings

HAL_PwmData_t gPwmData = {0,0,0};             // Contains PWM duty cycles in global Q format

HAL_AdcData_t gAdcData = {0,0,0,0,0,0,0};     // Contains Current and Voltage ADC readings in global Q format

int gcnt = 0;  // global counter
int gmppt = 0;   // mppt clear variable

long gpwmvalue = _IQ(0.0);   //variable that holds the pwm value, starting at 50%
long gpwmstep = _IQ(0.0001);          // defines the gpwmstep size

_iq equiv_V = 172414;        //the equivalence between voltage and the values
_iq gref = 1500000;              // defines the reference value to the followed by the tapas


//CHARGE CONTROLLER VARIABLES
int gchargecontrol = 0;     //variable that holds the value of the charge controller
int gchargemode_bulk = 0;   // variable that sets or clears the bulk mode during charging
int gchargemode_float = 0;   // variable that sets or clears the float mode during charging
int gcharge_case = 0;       //variable that holds the charge case for the charge controller

_iq gchargeV_bulk = 14 * equiv_V;
_iq gchargeV_float = 12.2 * equiv_V;
long gchargeT_abs = 0;
long gchargeT_bulk = 0;
long gchargeT_float = 432000000; // defines the float period (4 hours = 30000 * 60 * 60 * 4 = frequency * second * minute * hour )
long gchargeT_cycle = 0;
long gchargeT_max = 0;



// MPPT variables
_iq gcurrent_now = 0;  //holds the mppt current value
_iq gvoltage_now = 0;  // holds the mppt voltage value
_iq gpower_now = 0;      //hotds the mppt power value
_iq gmppt_buffer = 0 ;  // buffers the mppt_powe_value
_iq gpower_before = 0;  // holds the previous value of the mppt

int gmppt_sign = 0;    // initializes the mppt sign as 0

volatile MOTOR_Vars_t gMotorVars = MOTOR_Vars_INIT;

#ifdef FLASH
// Used for running BackGround in flash, and ISR in RAM
extern uint16_t *RamfuncsLoadStart, *RamfuncsLoadEnd, *RamfuncsRunStart;

#ifdef F2802xF
extern uint16_t *econst_start, *econst_end, *econst_ram_load;
extern uint16_t *switch_start, *switch_end, *switch_ram_load;
#endif

#endif


#ifdef DRV8301_SPI
// Watch window interface to the 8301 SPI
DRV_SPI_8301_Vars_t gDrvSpi8301Vars;
#endif

#ifdef DRV8305_SPI
// Watch window interface to the 8305 SPI
DRV_SPI_8305_Vars_t gDrvSpi8305Vars;
#endif




// **************************************************************************
// the functions

void main(void)
{
  // Only used if running from FLASH
  // Note that the variable FLASH is defined by the project
  #ifdef FLASH
  // Copy time critical code and Flash setup code to RAM
  // The RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
  // symbols are created by the linker. Refer to the linker files.
  memCopy((uint16_t *)&RamfuncsLoadStart,(uint16_t *)&RamfuncsLoadEnd,(uint16_t *)&RamfuncsRunStart);

  #ifdef F2802xF
    //copy .econst to unsecure RAM
    if(*econst_end - *econst_start)
      {
        memCopy((uint16_t *)&econst_start,(uint16_t *)&econst_end,(uint16_t *)&econst_ram_load);
      }

    //copy .switch ot unsecure RAM
    if(*switch_end - *switch_start)
      {
        memCopy((uint16_t *)&switch_start,(uint16_t *)&switch_end,(uint16_t *)&switch_ram_load);
      }
  #endif

  #endif

  // initialize the hardware abstraction layer
  halHandle = HAL_init(&hal,sizeof(hal));


  // check for errors in user parameters
  USER_checkForErrors(&gUserParams);


  // store user parameter error in global variable
  gMotorVars.UserErrorCode = USER_getErrorCode(&gUserParams);


  // do not allow code execution if there is a user parameter error
  if(gMotorVars.UserErrorCode != USER_ErrorCode_NoError)
    {
      for(;;)
        {
          gMotorVars.Flag_enableSys = false;
        }
    }


  // initialize the user parameters
  USER_setParams(&gUserParams);


  // set the hardware abstraction layer parameters
  HAL_setParams(halHandle,&gUserParams);

#ifdef LAUNCHPAD
  // Setup GPIOs 0 and 1 as outputs for use in project lab1 only.
  // This is specific to the launchpad because its LEDs are also used by the PWM channels.
  HAL_setupLaunchPadGpio0and1(halHandle);
#endif

  // setup faults
  HAL_setupFaults(halHandle);


  // initialize the interrupt vector table
  HAL_initIntVectorTable(halHandle);


  // enable the ADC interrupts
  HAL_enableAdcInts(halHandle);


  // enable global interrupts
  HAL_enableGlobalInts(halHandle);


  // enable debug interrupts
  HAL_enableDebugInt(halHandle);


  // disable the PWM
  HAL_disablePwm(halHandle);

  // enable the PWM
  //HAL_enablePwm(halHandle);


#ifdef DRV8301_SPI
  // turn on the DRV8301 if present
  HAL_enableDrv(halHandle);
  // initialize the DRV8301 interface
  HAL_setupDrvSpi(halHandle,&gDrvSpi8301Vars);
#endif

#ifdef DRV8305_SPI
  // turn on the DRV8305 if present
  HAL_enableDrv(halHandle);
  // initialize the DRV8305 interface
  HAL_setupDrvSpi(halHandle,&gDrvSpi8305Vars);
#endif


  // For ever loop
  while(true);

} // end of main() function


interrupt void mainISR(void)
{

  // toggle status LED
  if(gLEDcnt++ > (uint_least32_t)(USER_ISR_FREQ_Hz / LED_BLINK_FREQ_Hz))
  {
    HAL_toggleLed(halHandle,(GPIO_Number_e)HAL_Gpio_LED2);
    gLEDcnt = 0;
  }


  // acknowledge the ADC interrupt
  HAL_acqAdcInt(halHandle,ADC_IntNumber_1);  //clear the flags


  // convert the ADC data
  HAL_readAdcData(halHandle,&gAdcData);


  if (gAdcData.V.value[0] < gref) {
      gpwmvalue++;  //if the value of my measurement is lower than the reference, the pwmvalue goes up
//      if(gpwmvalue > _IQ(0.49)) gpwmvalue = _IQ(0.49);
  } else {
      gpwmvalue--;  //if the value of my measurement is lower than the reference, the pwmvalue goes down
//      if(gpwmvalue < _IQ(-0.49)) gpwmvalue = _IQ(-0.49);
  }

  gchargecontrol = 0;
  if(gchargecontrol){// goes into the loop if the charge control is on

      switch(gcharge_case){

      case 1:  // initial bulk case after a float period

          if(gAdcData.V.value[0] < gchargeV_bulk){  //test if the battery is above bulk voltage and the time counter is zero
              gcharge_case = 2; //goes on to the next charge case
          } else {
              gpwmvalue++;  // increase the PWM (dump excess load) to control battery voltage
              if(gpwmvalue > _IQ(0.49)) gpwmvalue = _IQ(0.49);  //saturates the pwm just in case
          }// end of the case 1 if

          break; //gets out of case 1

      case 2:  // case after the bulk voltage has been achieved

          gchargeT_cnt = 0;
          HAL_disable_single_Pwm(HAL_Handle handle, 1); //disables the PWM 1 (to be changed by a variable)
          gcharge_case = 3; //goes on to the next charge case

          break;// gets out of case 2

      case 3:

          if(gAdcData.V.value[0] < gchargeV_bulk){  //test if the battery is above bulk voltage and the time counter is zero

              gchargeT_cnt++;  // adds to the counter

          } else {

              gchargeT_bulk = gchargeT_cnt;                 //saves the time that was counted during the first part of the bulk
              gchargeT_abs = 5*gchargeT_bulk;               //sets the absorption timer
              gcharge_case = 4; //goes on to the next charge case

          }// end of the case 3 if

          break;// gets out of case 3

      case 4:


          if(gAdcData.V.value[0] < gchargeV_bulk){  //tracks the bulk voltage

              gpwmvalue--;  //if the value of my measurement is lower than the reference, the pwmvalue goes down

          } else {
              gpwmvalue++;  // increase the PWM (dump excess load) to control battery voltage

          }// end of the case 1 if

          gchargeT_abs--;

          if(gchargeT_abs == 0) gcharge_case = 5; //goes on to the next charge case

          break;//gets out of case 4

      case 5:  //kicks off the float charge period






          break;

      }// end of switch case






          if(gAdcData.V.value[0] < gchargeV_bulk && gchargeT_cnt == 0 ){  //test if the battery is above bulk voltage and the time counter is zero

              gchargeT_cnt++;  // adds to the counter
              HAL_disable_single_Pwm(HAL_Handle handle, 1); //disables the PWM 1 (to be changed by a variable)


          } else if(gAdcData.V.value[0] < gchargeV_bulk && gchargeT_cnt > 0) {

              gchargeT_cnt++;  // adds to the counter

          } else if(gAdcData.V.value[0] > gchargeV_bulk && gchargeT_cnt > 0) {

              gchargeT_bulk = gchargeT_cnt;                 //saves the time that was counted during the first part of the bulk
              gchargeT_abs = 5*gchargeT_bulk;               //sets the absorption timer
              gchargeT_cnt = 0;                             //resets the counter

          } else if(gAdcData.V.value[0] > gchargeV_bulk && gchargeT_abs > 0) {



          } else {
              gpwmvalue++;  // increase the PWM (dump excess load) to control battery voltage
          }
      } else {


      }//end of the gchargemode_bulk if

  }//ed of the gchargecontrol if (global if)

  gmppt = 0;            //disables the MPPT
  if (gmppt){

      if (gcnt<32){
          gcurrent_now = gAdcData.I.value[0];  //reads the current
          gvoltage_now = gAdcData.V.value[0];  // reads the voltage
          gpower_now = gcurrent_now*gvoltage_now;       //calculates the new power value

          gmppt_buffer += gpower_now>>5;                // adds the value of the power divided by 32
          gcnt++;                                       //increments the global counter

      } else {
          /* MPPT sign estimation and toggle */
          if( gpower_before > gmppt_buffer )                         /* compare power values*/
          {
              gmppt_sign ^= 1 ; /* toggles the mppt_sign*/
          }
          gpower_before = gmppt_buffer;     // updates the power before with the current buffer
          gcnt = 0;                         //resets the global counter
          gmppt_buffer = 0;                 //resets the mppt buffer

          //reference update based on MPPT sign estimation
          if(gmppt_sign == 0){
              gref = gref + 256 ;  // if the sign is 0, the system adds to the mppt
          }else{
              gref = gref - 256 ;  // if the sign is 1, the system detracts from the mppt
          }

          //safety feature for the mppt - avoids going beyond a maximum reference
          if(gref > 10000000){
              gref = 10000000;
          }
      }
  }

//  if ( gpwmvalue > _IQ(0.4) ){
//      gpwmvalue = _IQ(0.4)
//  } else if ( gpwmvalue < _IQ(-0.4) ) {
//      gpwmvalue = _IQ(-0.4)
//  }

   //HAL_disablePwm(halHandle);

  // Set the PWMs to 50% duty cycle
   gPwmData.Tabc.value[0] = gpwmvalue;   // we need to understand how the values inside the parentheses change the PWM
   gPwmData.Tabc.value[1] = _IQ(-0.5);
   gPwmData.Tabc.value[2] = _IQ(-0.5);

   //HAL_enablePwm(halHandle);








  // write the PWM compare values
  HAL_writePwmData(halHandle,&gPwmData);


  return;
} // end of mainISR() function


//@} //defgroup
// end of file




