################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../28069_RAM_lnk.cmd 

LIB_SRCS += \
/home/lflavado/ti/motorware_1_01_00_16/sw/modules/fast/lib/32b/f28x/f2806x/2806xRevB_FastSpinROMSymbols.lib \
/home/lflavado/ti/motorware_1_01_00_16/sw/modules/iqmath/lib/f28x/32b/IQmath.lib 

ASM_SRCS += \
/home/lflavado/ti/motorware_1_01_00_16/sw/modules/usDelay/src/32b/f28x/usDelay.asm 

C_SRCS += \
/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/mcbsp/SPImcBSP.c \
/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/adc/src/32b/f28x/f2806x/adc.c \
/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/clk/src/32b/f28x/f2806x/clk.c \
/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/cpu/src/32b/f28x/f2806x/cpu.c \
/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/dma/dma.c \
/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/drvic/drv8301/src/32b/f28x/f2806x/drv8301.c \
/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/flash/src/32b/f28x/f2806x/flash.c \
/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/gpio/src/32b/f28x/f2806x/gpio.c \
/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/hal.c \
/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/osc/src/32b/f28x/f2806x/osc.c \
/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/pie/src/32b/f28x/f2806x/pie.c \
/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/pll/src/32b/f28x/f2806x/pll.c \
/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/src/proj_lab01.c \
/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/pwm/src/32b/f28x/f2806x/pwm.c \
/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/pwr/src/32b/f28x/f2806x/pwr.c \
/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/spi/src/32b/f28x/f2806x/spi.c \
/home/lflavado/ti/motorware_1_01_00_16/sw/modules/spiCTRL/src/32b/spiCTRL.c \
/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/timer/src/32b/f28x/f2806x/timer.c \
/home/lflavado/ti/motorware_1_01_00_16/sw/modules/user/src/32b/user.c \
/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/wdog/src/32b/f28x/f2806x/wdog.c 

C_DEPS += \
./SPImcBSP.d \
./adc.d \
./clk.d \
./cpu.d \
./dma.d \
./drv8301.d \
./flash.d \
./gpio.d \
./hal.d \
./osc.d \
./pie.d \
./pll.d \
./proj_lab01.d \
./pwm.d \
./pwr.d \
./spi.d \
./spiCTRL.d \
./timer.d \
./user.d \
./wdog.d 

OBJS += \
./SPImcBSP.obj \
./adc.obj \
./clk.obj \
./cpu.obj \
./dma.obj \
./drv8301.obj \
./flash.obj \
./gpio.obj \
./hal.obj \
./osc.obj \
./pie.obj \
./pll.obj \
./proj_lab01.obj \
./pwm.obj \
./pwr.obj \
./spi.obj \
./spiCTRL.obj \
./timer.obj \
./usDelay.obj \
./user.obj \
./wdog.obj 

ASM_DEPS += \
./usDelay.d 

OBJS__QUOTED += \
"SPImcBSP.obj" \
"adc.obj" \
"clk.obj" \
"cpu.obj" \
"dma.obj" \
"drv8301.obj" \
"flash.obj" \
"gpio.obj" \
"hal.obj" \
"osc.obj" \
"pie.obj" \
"pll.obj" \
"proj_lab01.obj" \
"pwm.obj" \
"pwr.obj" \
"spi.obj" \
"spiCTRL.obj" \
"timer.obj" \
"usDelay.obj" \
"user.obj" \
"wdog.obj" 

C_DEPS__QUOTED += \
"SPImcBSP.d" \
"adc.d" \
"clk.d" \
"cpu.d" \
"dma.d" \
"drv8301.d" \
"flash.d" \
"gpio.d" \
"hal.d" \
"osc.d" \
"pie.d" \
"pll.d" \
"proj_lab01.d" \
"pwm.d" \
"pwr.d" \
"spi.d" \
"spiCTRL.d" \
"timer.d" \
"user.d" \
"wdog.d" 

ASM_DEPS__QUOTED += \
"usDelay.d" 

C_SRCS__QUOTED += \
"/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/mcbsp/SPImcBSP.c" \
"/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/adc/src/32b/f28x/f2806x/adc.c" \
"/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/clk/src/32b/f28x/f2806x/clk.c" \
"/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/cpu/src/32b/f28x/f2806x/cpu.c" \
"/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/dma/dma.c" \
"/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/drvic/drv8301/src/32b/f28x/f2806x/drv8301.c" \
"/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/flash/src/32b/f28x/f2806x/flash.c" \
"/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/gpio/src/32b/f28x/f2806x/gpio.c" \
"/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/hal.c" \
"/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/osc/src/32b/f28x/f2806x/osc.c" \
"/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/pie/src/32b/f28x/f2806x/pie.c" \
"/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/pll/src/32b/f28x/f2806x/pll.c" \
"/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/src/proj_lab01.c" \
"/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/pwm/src/32b/f28x/f2806x/pwm.c" \
"/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/pwr/src/32b/f28x/f2806x/pwr.c" \
"/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/spi/src/32b/f28x/f2806x/spi.c" \
"/home/lflavado/ti/motorware_1_01_00_16/sw/modules/spiCTRL/src/32b/spiCTRL.c" \
"/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/timer/src/32b/f28x/f2806x/timer.c" \
"/home/lflavado/ti/motorware_1_01_00_16/sw/modules/user/src/32b/user.c" \
"/home/lflavado/ti/motorware_1_01_00_16/sw/drivers/wdog/src/32b/f28x/f2806x/wdog.c" 

ASM_SRCS__QUOTED += \
"/home/lflavado/ti/motorware_1_01_00_16/sw/modules/usDelay/src/32b/f28x/usDelay.asm" 


