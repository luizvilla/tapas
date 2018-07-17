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
//! \file   one_phase_inverter.c
//! \brief
//! (C) Copyright 2011, Texas Instruments, Inc.

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
#define SIN_REF_FREQ_Hz 50 // define the frequency of the reference
#define SIN_REF_SIZE_ARRAY 250
#define SIN_REF_DECIMATION_Hz (SIN_REF_SIZE_ARRAY*SIN_REF_FREQ_Hz)  // define
#define Kp 1.0 // the proportional gain of the pi controller
#define Ki 0.01 // the integral gain of the pi controller
#define V_offset 1270466

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

PI_Obj   pi ;          // PI controller
PI_Handle   piHandle ;    // handle PI controller

long sinus_ref_array[SIN_REF_SIZE_ARRAY] = {50260,1.0049e+05,1.5065e+05,2.0072e+05,2.5067e+05,3.0045e+05,3.5005e+05,3.9942e+05,4.4854e+05,4.9738e+05,5.459e+05,5.9408e+05,6.4189e+05,6.8929e+05,7.3625e+05,7.8275e+05,8.2875e+05,8.7423e+05,9.1916e+05,9.6351e+05,1.0072e+06,1.0503e+06,1.0928e+06,1.1345e+06,1.1756e+06,1.2159e+06,1.2554e+06,1.2941e+06,1.332e+06,1.3691e+06,1.4053e+06,1.4406e+06,1.475e+06,1.5085e+06,1.541e+06,1.5726e+06,1.6031e+06,1.6327e+06,1.6612e+06,1.6887e+06,1.7151e+06,1.7404e+06,1.7646e+06,1.7877e+06,1.8097e+06,1.8305e+06,1.8502e+06,1.8687e+06,1.886e+06,1.9021e+06,1.917e+06,1.9308e+06,1.9433e+06,1.9545e+06,1.9646e+06,1.9734e+06,1.9809e+06,1.9872e+06,1.9923e+06,1.9961e+06,1.9986e+06,1.9998e+06,1.9998e+06,1.9986e+06,1.9961e+06,1.9923e+06,1.9872e+06,1.9809e+06,1.9734e+06,1.9646e+06,1.9545e+06,1.9433e+06,1.9308e+06,1.917e+06,1.9021e+06,1.886e+06,1.8687e+06,1.8502e+06,1.8305e+06,1.8097e+06,1.7877e+06,1.7646e+06,1.7404e+06,1.7151e+06,1.6887e+06,1.6612e+06,1.6327e+06,1.6031e+06,1.5726e+06,1.541e+06,1.5085e+06,1.475e+06,1.4406e+06,1.4053e+06,1.3691e+06,1.332e+06,1.2941e+06,1.2554e+06,1.2159e+06,1.1756e+06,1.1345e+06,1.0928e+06,1.0503e+06,1.0072e+06,9.6351e+05,9.1916e+05,8.7423e+05,8.2875e+05,7.8275e+05,7.3625e+05,6.8929e+05,6.4189e+05,5.9408e+05,5.459e+05,4.9738e+05,4.4854e+05,3.9942e+05,3.5005e+05,3.0045e+05,2.5067e+05,2.0072e+05,1.5065e+05,1.0049e+05,50260,0,-50260,-1.0049e+05,-1.5065e+05,-2.0072e+05,-2.5067e+05,-3.0045e+05,-3.5005e+05,-3.9942e+05,-4.4854e+05,-4.9738e+05,-5.459e+05,-5.9408e+05,-6.4189e+05,-6.8929e+05,-7.3625e+05,-7.8275e+05,-8.2875e+05,-8.7423e+05,-9.1916e+05,-9.6351e+05,-1.0072e+06,-1.0503e+06,-1.0928e+06,-1.1345e+06,-1.1756e+06,-1.2159e+06,-1.2554e+06,-1.2941e+06,-1.332e+06,-1.3691e+06,-1.4053e+06,-1.4406e+06,-1.475e+06,-1.5085e+06,-1.541e+06,-1.5726e+06,-1.6031e+06,-1.6327e+06,-1.6612e+06,-1.6887e+06,-1.7151e+06,-1.7404e+06,-1.7646e+06,-1.7877e+06,-1.8097e+06,-1.8305e+06,-1.8502e+06,-1.8687e+06,-1.886e+06,-1.9021e+06,-1.917e+06,-1.9308e+06,-1.9433e+06,-1.9545e+06,-1.9646e+06,-1.9734e+06,-1.9809e+06,-1.9872e+06,-1.9923e+06,-1.9961e+06,-1.9986e+06,-1.9998e+06,-1.9998e+06,-1.9986e+06,-1.9961e+06,-1.9923e+06,-1.9872e+06,-1.9809e+06,-1.9734e+06,-1.9646e+06,-1.9545e+06,-1.9433e+06,-1.9308e+06,-1.917e+06,-1.9021e+06,-1.886e+06,-1.8687e+06,-1.8502e+06,-1.8305e+06,-1.8097e+06,-1.7877e+06,-1.7646e+06,-1.7404e+06,-1.7151e+06,-1.6887e+06,-1.6612e+06,-1.6327e+06,-1.6031e+06,-1.5726e+06,-1.541e+06,-1.5085e+06,-1.475e+06,-1.4406e+06,-1.4053e+06,-1.3691e+06,-1.332e+06,-1.2941e+06,-1.2554e+06,-1.2159e+06,-1.1756e+06,-1.1345e+06,-1.0928e+06,-1.0503e+06,-1.0072e+06,-9.6351e+05,-9.1916e+05,-8.7423e+05,-8.2875e+05,-7.8275e+05,-7.3625e+05,-6.8929e+05,-6.4189e+05,-5.9408e+05,-5.459e+05,-4.9738e+05,-4.4854e+05,-3.9942e+05,-3.5005e+05,-3.0045e+05,-2.5067e+05,-2.0072e+05,-1.5065e+05,-1.0049e+05,-50260,-0
} ;

long sinus_ref ;    // holds the reference of the sine wave
int sin_refcnt ;
int decimator_cnt ;
_iq V_sin_out ;
_iq *controlOutput ;

MATH_vec3       gOffsets_V_pu = {1270466, 1270466, 1270466};  //!< contains the offsets for the voltage feedback



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

  // set the pre-determined voltage feeback offset values
//  gOffsets_V_pu.value[0] = _IQ(V_A_offset);
//  gOffsets_V_pu.value[1] = _IQ(V_B_offset);
//  gOffsets_V_pu.value[2] = _IQ(V_C_offset);

//  halHandle->adcBias.V.value[0] = V_offset ;
//  halHandle->adcBias.V.value[1] = V_offset ;
//  halHandle->adcBias.V.value[2] = V_offset ;


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

  HAL_enablePwm(halHandle);

  sin_refcnt = 0 ;
  decimator_cnt = 0 ;
  sinus_ref = sinus_ref_array[sin_refcnt] ;
  piHandle = PI_init(&pi,sizeof(pi));
  // The following instructions load the parameters for the PI controller.
  PI_setGains(piHandle,_IQ(Kp),_IQ(Ki));
  PI_setUi(piHandle,_IQ(0.0));  // Set the initial condition value
                                             // for the integrator output to 0
  PI_setMinMax(piHandle,_IQ(-0.5),_IQ(0.5));

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


  // generates a sinus waveform
  if(decimator_cnt++ > (uint_least32_t)(USER_ISR_FREQ_Hz / SIN_REF_DECIMATION_Hz) ){

      if (sin_refcnt++>= (SIN_REF_SIZE_ARRAY-1) ) // if we reach the end of the array
          sin_refcnt = 0 ; // go to the beginning of the array

      sinus_ref = sinus_ref_array[sin_refcnt] ; // take the next point of the array
      decimator_cnt = 0 ; // reset the decimator_cnt
  }

//   gAdcData.V.value[0] = gAdcData.V.value[0] - gOffsets_V_pu.value[0];
//   gAdcData.V.value[1] = gAdcData.V.value[1] - gOffsets_V_pu.value[1];
//   gAdcData.V.value[2] = gAdcData.V.value[2] - gOffsets_V_pu.value[2];
  V_sin_out = gAdcData.V.value[0] - gAdcData.V.value[1] ; // calculate the output voltage (Va - Vb)
  PI_run_parallel( piHandle,sinus_ref,V_sin_out,_IQ(0.0),controlOutput) ; // run the controller


  // Set the PWMs to 50% duty cycle
   gPwmData.Tabc.value[0] = _IQ(*controlOutput); // P1
   gPwmData.Tabc.value[1] = _IQ(-*controlOutput); // P2


  // write the PWM compare values
  HAL_writePwmData(halHandle,&gPwmData);


  return;
} // end of mainISR() function


//@} //defgroup
// end of file




