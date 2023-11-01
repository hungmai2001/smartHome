################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-arm_20.2.6.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./tm4c123gh6pm_startup_ccs.obj" \
"./Application/freertos_demo.obj" \
"./Application/ledGreenStateMachine.obj" \
"./Application/ledRedStateMachine.obj" \
"./Application/led_task.obj" \
"./Application/switch_task.obj" \
"./FreeRTOSSource/croutine.obj" \
"./FreeRTOSSource/event_groups.obj" \
"./FreeRTOSSource/heap_2.obj" \
"./FreeRTOSSource/list.obj" \
"./FreeRTOSSource/port.obj" \
"./FreeRTOSSource/portasm.obj" \
"./FreeRTOSSource/queue.obj" \
"./FreeRTOSSource/stream_buffer.obj" \
"./FreeRTOSSource/tasks.obj" \
"./FreeRTOSSource/timers.obj" \
"./drivers/buttons.obj" \
"./drivers/led.obj" \
"./drivers/rgb.obj" \
"./drivers/switches.obj" \
"./drivers/uartstdio.obj" \
"../driverlib.lib" \
"../tm4c123gh6pm.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Application/subdir_vars.mk
-include FreeRTOSSource/subdir_vars.mk
-include drivers/subdir_vars.mk
-include subdir_rules.mk
-include Application/subdir_rules.mk
-include FreeRTOSSource/subdir_rules.mk
-include drivers/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
exampleQueue.out \

EXE_OUTPUTS__QUOTED += \
"exampleQueue.out" \

BIN_OUTPUTS += \
exampleQueue.hex \

BIN_OUTPUTS__QUOTED += \
"exampleQueue.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "exampleQueue.out"

# Tool invocations
exampleQueue.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-arm_20.2.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_BLIZZARD_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"exampleQueue.map" --heap_size=0 --stack_size=512 -i"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-arm_20.2.6.LTS/lib" -i"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-arm_20.2.6.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="exampleQueue_linkInfo.xml" --rom_model -o "exampleQueue.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

exampleQueue.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: Arm Hex Utility'
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-arm_20.2.6.LTS/bin/armhex" --diag_wrap=off -o "exampleQueue.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "tm4c123gh6pm_startup_ccs.obj" "Application\freertos_demo.obj" "Application\ledGreenStateMachine.obj" "Application\ledRedStateMachine.obj" "Application\led_task.obj" "Application\switch_task.obj" "FreeRTOSSource\croutine.obj" "FreeRTOSSource\event_groups.obj" "FreeRTOSSource\heap_2.obj" "FreeRTOSSource\list.obj" "FreeRTOSSource\port.obj" "FreeRTOSSource\portasm.obj" "FreeRTOSSource\queue.obj" "FreeRTOSSource\stream_buffer.obj" "FreeRTOSSource\tasks.obj" "FreeRTOSSource\timers.obj" "drivers\buttons.obj" "drivers\led.obj" "drivers\rgb.obj" "drivers\switches.obj" "drivers\uartstdio.obj" 
	-$(RM) "tm4c123gh6pm_startup_ccs.d" "Application\freertos_demo.d" "Application\ledGreenStateMachine.d" "Application\ledRedStateMachine.d" "Application\led_task.d" "Application\switch_task.d" "FreeRTOSSource\croutine.d" "FreeRTOSSource\event_groups.d" "FreeRTOSSource\heap_2.d" "FreeRTOSSource\list.d" "FreeRTOSSource\port.d" "FreeRTOSSource\queue.d" "FreeRTOSSource\stream_buffer.d" "FreeRTOSSource\tasks.d" "FreeRTOSSource\timers.d" "drivers\buttons.d" "drivers\led.d" "drivers\rgb.d" "drivers\switches.d" "drivers\uartstdio.d" 
	-$(RM) "FreeRTOSSource\portasm.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

