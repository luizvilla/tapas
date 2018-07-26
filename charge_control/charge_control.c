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
#include "sw/modules/pi/src/32b/pi.h"


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

long gpwmvalue = _IQ(0.0);   //variable that holds the pwm value, starting at 50%
long gpwmvalue_charge = _IQ(0.0);   //variable that holds the pwm value, starting at 50%
long gpwmvalue_mppt = _IQ(0.0);   //variable that holds the pwm value, starting at 50%

long gpwmstep = _IQ(0.0001);          // defines the gpwmstep size

_iq equiv_V = 172414;        //the equivalence between voltage and the values
_iq gref = 1500000;              // defines the reference value to the followed by the tapas
_iq gmppt_ref = 1500000;              // defines the reference value to the followed by the tapas


//CHARGE CONTROLLER VARIABLES
int gchargecontrol = 0;     //variable that holds the value of the charge controller
int gchargemode_bulk = 0;   // variable that sets or clears the bulk mode during charging
int gchargemode_float = 0;   // variable that sets or clears the float mode during charging
int gcharge_case = 0;       //variable that holds the charge case for the charge controller
int gcharge_channel = 0;    //defines the PWM channel which will take the change controller
int gcharge_led_freq = 15;  // defines the led blinking frequency for the charge

_iq gchargeV_bulk = 14 * 172414;      //bulk voltage reference
_iq gchargeV_float = 12.2 * 172414;   //float voltage reference
long gchargeT_abs = 0;                  // absorption phase Timer
long gchargeT_bulk = 0;                 // bulk phase timer
long gchargeT_float = 0;                // float phase timer
long gchargeT_cycle = 432000000;        // defines the float period (4 hours = 30000 * 60 * 60 * 4 = frequency * second * minute * hour )
long gchargeT_max = 432000000;          // defines the maximum time (4 hours = 30000 * 60 * 60 * 4 = frequency * second * minute * hour )



// MPPT variables
_iq gmpptcurrent_now = 0;  //holds the mppt current value
_iq gmpptvoltage_now = 0;  // holds the mppt voltage value
_iq gmpptpower_now = 0;      //hotds the mppt power value
_iq gmppt_buffer = 0 ;  // buffers the mppt_powe_value
_iq gmpptpower_before = 0;  // holds the previous value of the mppt

int gmppt_cnt = 0;  // defines the counter for the mppt
int gmppt_on = 0;   //defines if the mppt is on
int gmppt = 0;   // mppt clear variable
int gmppt_sign = 1;    // initializes the mppt sign as 0
int gmppt_led_freq = 10;  // defines the led blinking frequency for the mppt

uint_least32_t gmppt_channel = 0;    //defines the PWM channel which will take the mppt
int gmppt_step = 0;    // initializes the mppt step as 0
_iq gmpptlim_max = 0; //initializes the maximum voltage reference as 0
_iq gmpptlim_min = 0; //initializes the maximum voltage reference as 0

// DC-DC variables
int gdc = 0;                 // dc-dc conversion flag
int gdc_channel = 0;         //defines the PWM channel which will take the mppt
int gdc_ref = 0;             // defines a dc-dc reference
int gpwmvalue_dc = _IQ(0.0);  //
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
//  HAL_disablePwm(halHandle);

  // enable the PWM
  HAL_enablePwm(halHandle);

  HAL_toggleLed(halHandle,(GPIO_Number_e)HAL_Gpio_LED2); // toggles the led at the start of the system


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
//  if(gLEDcnt++ > (uint_least32_t)(USER_ISR_FREQ_Hz / LED_BLINK_FREQ_Hz))
//  {
//    HAL_toggleLed(halHandle,(GPIO_Number_e)HAL_Gpio_LED2);
//    gLEDcnt = 0;
//  }


  // acknowledge the ADC interrupt
  HAL_acqAdcInt(halHandle,ADC_IntNumber_1);  //clear the flags


  // convert the ADC data
  HAL_readAdcData(halHandle,&gAdcData);



  gchargecontrol = 0;   // turns on or off the charge control
  gcharge_channel = 1;  // defines the channel where the charge controller will be implemented

  if(gchargecontrol){// goes into the loop if the charge control is on


      if(gcharge_case == 0){  // initializes the charge control
          HAL_enable_single_Pwm(halHandle, (gcharge_channel-1));
          gcharge_case = 1; // trigger the first charge case
      }

//-----------------------------------------------------------------------
//DESCRIPTION OF THE CASES
// CASE 1 - Tests if the bulk voltage if the battery is beyond the bulk voltage after the float period and dumps if needed
// CASE 2 - Sets all the variables once the the bulk voltage has been achieved
// CASE 3 - Tracks the time for the system to achieve bulk current
// CASE 4 - Track the bulk voltage during an absorption time calculated based on the bulk time
// CASE 5 - Kicks off the float charge period for a fixed total of 4 hours
//-----------------------------------------------------------------------

      switch(gcharge_case){

//-----------------------------------------------------------------------
// CASE 1 -
//-----------------------------------------------------------------------
      case 1:  // Tests if the bulk voltage if the battery is beyond the bulk voltage after the float period and dumps if needed

          if(gAdcData.dcBus < gchargeV_bulk){  //test if the battery is above bulk voltage and the time counter is zero
              gcharge_case = 2; //goes on to the next charge case
              HAL_toggleLed(halHandle,(GPIO_Number_e)HAL_Gpio_LED2); // toggles the led when I leave this state
          } else {
              gpwmvalue_charge++;  // increase the PWM (dump excess load) to control battery voltage
              if(gpwmvalue_charge > _IQ(0.49)) gpwmvalue_charge = _IQ(0.49);  //saturates the pwm just in case
          }// end of the case 1 if

          break; //gets out of case 1

//-----------------------------------------------------------------------
// CASE 2 -
//-----------------------------------------------------------------------
      case 2:  // sets all the variables once the the bulk voltage has been achieved

          gchargeT_bulk = 0;

          HAL_disable_single_Pwm(halHandle, gcharge_channel);
          gcharge_case = 3; //goes on to the next charge case

          break;// gets out of case 2

//-----------------------------------------------------------------------
// CASE 3 -
//-----------------------------------------------------------------------
      case 3: // Tracks the time for the system to achieve bulk current

          if(gAdcData.dcBus < gchargeV_bulk){  //test if the battery is above bulk voltage and the time counter is zero

              gchargeT_bulk++;  // adds to the counter

          } else {

              gchargeT_abs = 5*gchargeT_bulk;                               //sets the absorption timer
              if(gchargeT_abs > gchargeT_max) gchargeT_abs = gchargeT_max;  //if the bulk time is too long, then the charge time will still only be 4 hours
              gcharge_case = 4;                                             //goes on to the next charge case
              HAL_toggleLed(halHandle,(GPIO_Number_e)HAL_Gpio_LED2);        // toggles the LED when moving to the next state

          }// end of the case 3 if

          break;// gets out of case 3

//-----------------------------------------------------------------------
// CASE 4 -
//-----------------------------------------------------------------------
      case 4:  // Track the bulk voltage during an absorption time calculated based on the bulk time


          HAL_enable_single_Pwm(halHandle, gcharge_channel);

          if(gAdcData.dcBus < gchargeV_bulk){  //tracks the bulk voltage

              gpwmvalue_charge--;  //if the value of my measurement is lower than the reference, the pwmvalue goes down
              if(gpwmvalue_charge < _IQ(-0.49)) gpwmvalue_charge = _IQ(-0.49);  //saturates the pwm just in case

          } else {

              gpwmvalue_charge++;  // increase the PWM (dump excess load) to control battery voltage
              if(gpwmvalue_charge > _IQ(0.49)) gpwmvalue_charge = _IQ(0.49);  //saturates the pwm just in case

          }// end of the case 1 if

          gchargeT_abs--;   //decrements the absorption timer

          if(gchargeT_abs == 0){
              gcharge_case = 5; //goes on to the next charge case
              gchargeT_float = gchargeT_cycle; //loads up the cycle time onto the float timer
          }

          break;//gets out of case 4

//-----------------------------------------------------------------------
// CASE 5 -
//-----------------------------------------------------------------------
      case 5:  //kicks off the float charge period for a fixed total of 4 hours


          if(gAdcData.dcBus < gchargeV_float){  //tracks the float voltage

              gpwmvalue_charge--;  //if the value of my measurement is lower than the reference, the pwmvalue goes down
              if(gpwmvalue_charge < _IQ(-0.49)) gpwmvalue_charge = _IQ(-0.49);  //saturates the pwm just in case

          } else {

              gpwmvalue_charge++;  // increase the PWM (dump excess load) to control battery voltage
              if(gpwmvalue_charge > _IQ(0.49)) gpwmvalue_charge = _IQ(0.49);  //saturates the pwm just in case

          }// end of the case 1 if


          gchargeT_float--;  //decrements the float timer

          if(gchargeT_float == 0) gcharge_case = 1; //goes back to the beginning

          break;

      }// end of switch case
//-----------------------------------------------------------------------


  gPwmData.Tabc.value[gcharge_channel-1] = gpwmvalue_charge;   // uploads the pwm value onto the channel

  }//end of the gchargecontrol if

  gmppt = 1;            //disables the MPPT
  gmppt_step = 1;     // defines the mppt step size (fixed step)
  gmpptlim_max = 4000000; // defines the MPPT max voltage reference value
  gmpptlim_min = 4000000; // defines the MPPT min voltage reference value
  gmppt_channel = 2;    // defines the MPPT channel as 2
  //gmppt_sign = 1;    // initializes the mppt sign as 0

  if (gmppt){   //tests if the mppt is live
      if(gmppt_on==0) {
          HAL_enable_single_Pwm(halHandle, gmppt_channel);
          gmppt_on = 1; // defines the mppt as on
      }// end of the gmppt_on if

      if (gmppt_cnt<32){ // FIRST BLOCK THAT CALCULATES THE AVERAGE POWER

          gmpptcurrent_now = gAdcData.I.value[gmppt_channel-1];           //reads the current now
          gmpptvoltage_now = gAdcData.V.value[gmppt_channel-1];           // reads the voltage now
          gmpptpower_now = gmpptcurrent_now*gmpptvoltage_now;       //calculates the new power value

          gmppt_buffer += gmpptpower_now>>5;                // adds the value of the power divided by 32
          gmppt_cnt++;                                       //increments the global counter

      } else {     //SECOND BLOCK THAT CALCULATES THE CORRECTION OF THE VOTAGE REFERENCE ACCORDING TO POWER CHANGES

          if( gmpptpower_before > gmppt_buffer ) gmppt_sign ^= 1 ;                         //compares new power with old power and toggles the mppt sign
          gmpptpower_before = gmppt_buffer;                 // updates the power before with the current buffer
          gmppt_cnt = 0;                                     //resets the global counter
          gmppt_buffer = 0;                             //resets the mppt buffer

          //reference update based on MPPT sign estimation
          if(gmppt_sign == 0){

              gmppt_ref = gmppt_ref + gmppt_step ;  // if the sign is 0, the system adds a step to the mppt
              if(gmppt_ref > gmpptlim_max) gmppt_ref = gmpptlim_max; // saturates a maximum for the reference

          } else {

              gmppt_ref = gmppt_ref - gmppt_step ;  // if the sign is 1, the system detracts a step from the mppt
              if(gmppt_ref < gmpptlim_min) gmppt_ref = gmpptlim_min; // saturates a minimum for the reference

          }// end of gmppt_sign if
      }// end of the gcnt if

      // Tracks the global reference
      if (gAdcData.V.value[gmppt_channel-1] < gref) {
          gpwmvalue_mppt++;  //if the value of my measurement is lower than the reference, the pwmvalue goes up
      } else {
          gpwmvalue_mppt--;  //if the value of my measurement is lower than the reference, the pwmvalue goes down
      }

      gPwmData.Tabc.value[gmppt_channel-1] = gpwmvalue_mppt;   // we need to understand how the values inside the parentheses change the PWM

  }// end of the gmppt if



   gdc_channel = 1;    // activates the dc channel
   if(gdc_channel) {

//       if(gdc_ref == 0)  gdc_ref = gAdcData.dcBus; //sets the current DC bus as a reference
//       // Tracks the global reference
//       if (gAdcData.dcBus > gdc_ref) {
//           gpwmvalue_dc++;  //if the value of my measurement is lower than the reference, the pwmvalue goes up
//           if(gpwmvalue_dc > _IQ(0.49)) gpwmvalue_dc = _IQ(0.49);  //saturates the pwm just in case
//       } else {
//           gpwmvalue_dc--;  //if the value of my measurement is lower than the reference, the pwmvalue goes down
//           if(gpwmvalue_dc < _IQ(-0.49)) gpwmvalue_dc = _IQ(-0.49);  //saturates the pwm just in case
//       }

       gPwmData.Tabc.value[gdc_channel-1] = _IQ(0.49);   // we need to understand how the values inside the parentheses change the PWM

   }

   //HAL_enablePwm(halHandle);


  // write the PWM compare values
  HAL_writePwmData(halHandle,&gPwmData);


  return;
} // end of mainISR() function


//@} //defgroup
// end of file




