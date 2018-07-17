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

float sinus_ref_array[SIN_REF_SIZE_ARRAY] = {0.012565,0.025122,0.037663,0.050181,0.062667,0.075113,0.087512,0.099855,0.11214,0.12434,0.13648,0.14852,0.16047,0.17232,0.18406,0.19569,0.20719,0.21856,0.22979,0.24088,0.25181,0.26259,0.2732,0.28363,0.29389,0.30397,0.31385,0.32353,0.33301,0.34227,0.35132,0.36015,0.36876,0.37713,0.38526,0.39314,0.40078,0.40817,0.4153,0.42216,0.42876,0.43509,0.44115,0.44692,0.45241,0.45762,0.46254,0.46716,0.4715,0.47553,0.47926,0.48269,0.48582,0.48863,0.49114,0.49334,0.49523,0.49681,0.49807,0.49901,0.49964,0.49996,0.49996,0.49964,0.49901,0.49807,0.49681,0.49523,0.49334,0.49114,0.48863,0.48582,0.48269,0.47926,0.47553,0.4715,0.46716,0.46254,0.45762,0.45241,0.44692,0.44115,0.43509,0.42876,0.42216,0.4153,0.40817,0.40078,0.39314,0.38526,0.37713,0.36876,0.36015,0.35132,0.34227,0.33301,0.32353,0.31385,0.30397,0.29389,0.28363,0.2732,0.26259,0.25181,0.24088,0.22979,0.21856,0.20719,0.19569,0.18406,0.17232,0.16047,0.14852,0.13648,0.12434,0.11214,0.099855,0.087512,0.075113,0.062667,0.050181,0.037663,0.025122,0.012565,6.1232e-17,-0.012565,-0.025122,-0.037663,-0.050181,-0.062667,-0.075113,-0.087512,-0.099855,-0.11214,-0.12434,-0.13648,-0.14852,-0.16047,-0.17232,-0.18406,-0.19569,-0.20719,-0.21856,-0.22979,-0.24088,-0.25181,-0.26259,-0.2732,-0.28363,-0.29389,-0.30397,-0.31385,-0.32353,-0.33301,-0.34227,-0.35132,-0.36015,-0.36876,-0.37713,-0.38526,-0.39314,-0.40078,-0.40817,-0.4153,-0.42216,-0.42876,-0.43509,-0.44115,-0.44692,-0.45241,-0.45762,-0.46254,-0.46716,-0.4715,-0.47553,-0.47926,-0.48269,-0.48582,-0.48863,-0.49114,-0.49334,-0.49523,-0.49681,-0.49807,-0.49901,-0.49964,-0.49996,-0.49996,-0.49964,-0.49901,-0.49807,-0.49681,-0.49523,-0.49334,-0.49114,-0.48863,-0.48582,-0.48269,-0.47926,-0.47553,-0.4715,-0.46716,-0.46254,-0.45762,-0.45241,-0.44692,-0.44115,-0.43509,-0.42876,-0.42216,-0.4153,-0.40817,-0.40078,-0.39314,-0.38526,-0.37713,-0.36876,-0.36015,-0.35132,-0.34227,-0.33301,-0.32353,-0.31385,-0.30397,-0.29389,-0.28363,-0.2732,-0.26259,-0.25181,-0.24088,-0.22979,-0.21856,-0.20719,-0.19569,-0.18406,-0.17232,-0.16047,-0.14852,-0.13648,-0.12434,-0.11214,-0.099855,-0.087512,-0.075113,-0.062667,-0.050181,-0.037663,-0.025122,-0.012565,-1.2246e-16
} ;

int sinus_ref ;
int sin_refcnt ;
int decimator_cnt ;
_iq V_sin_out ;
_iq controlOutput ;


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


 // V_sin_out = gAdcData.V.value[0] - gAdcData.V.value[1] ; // calculate the output voltage (Va - Vb)
  //PI_run_parallel( piHandle,sinus_ref,V_sin_out,_IQ(0.0),(_iq *)controlOutput) ; // run the controller


  // Set the PWMs to 50% duty cycle
   gPwmData.Tabc.value[0] = _IQ(sinus_ref); // P1
   gPwmData.Tabc.value[1] = _IQ(-sinus_ref); // P2


  // write the PWM compare values
  HAL_writePwmData(halHandle,&gPwmData);


  return;
} // end of mainISR() function


//@} //defgroup
// end of file



