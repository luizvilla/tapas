################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
SPImcBSP.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/drivers/mcbsp/SPImcBSP.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="SPImcBSP.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

adc.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/drivers/adc/src/32b/f28x/f2806x/adc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="adc.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

clk.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/drivers/clk/src/32b/f28x/f2806x/clk.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="clk.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

cpu.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/drivers/cpu/src/32b/f28x/f2806x/cpu.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="cpu.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

dma.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/drivers/dma/dma.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="dma.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

drv8301.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/drivers/drvic/drv8301/src/32b/f28x/f2806x/drv8301.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="drv8301.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

flash.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/drivers/flash/src/32b/f28x/f2806x/flash.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="flash.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

gpio.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/drivers/gpio/src/32b/f28x/f2806x/gpio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="gpio.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

hal.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/hal.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="hal.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

memCopy.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/modules/memCopy/src/memCopy.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="memCopy.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

osc.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/drivers/osc/src/32b/f28x/f2806x/osc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="osc.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

pie.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/drivers/pie/src/32b/f28x/f2806x/pie.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="pie.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

pll.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/drivers/pll/src/32b/f28x/f2806x/pll.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="pll.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

proj_lab01.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/src/proj_lab01.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="proj_lab01.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

pwm.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/drivers/pwm/src/32b/f28x/f2806x/pwm.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="pwm.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

pwr.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/drivers/pwr/src/32b/f28x/f2806x/pwr.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="pwr.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

spi.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/drivers/spi/src/32b/f28x/f2806x/spi.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="spi.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

spiCTRL.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/modules/spiCTRL/src/32b/spiCTRL.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="spiCTRL.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

timer.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/drivers/timer/src/32b/f28x/f2806x/timer.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="timer.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

usDelay.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/modules/usDelay/src/32b/f28x/usDelay.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="usDelay.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

user.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/modules/user/src/32b/user.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="user.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

wdog.obj: /home/lflavado/ti/motorware_1_01_00_16/sw/drivers/wdog/src/32b/f28x/f2806x/wdog.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/modules/hal/boards/TAPAS_V1.0/f28x/f2806x/src/" --include_path="/home/lflavado/ti/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/TAPAS__V1_0/f28x/f2806xF/src" --include_path="/home/lflavado/ti/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="wdog.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


