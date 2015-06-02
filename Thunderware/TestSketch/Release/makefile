################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include arduino/core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
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
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
arduino.ar \

ELF += \
TestSketch.elf \

EEP += \
TestSketch.eep \

FLASH_IMAGE += \
TestSketch.hex \


# All Target
all: TestSketch

# Tool invocations
TestSketch: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"/bin/avr-size" -A "/Users/mrogge/Filament_Extruder/Thunderware/Thunderware/TestSketch/Release/TestSketch.elf"
	@echo 'Finished building target: $@'
	@echo ' '

arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"/bin/avr-ar" rcs  "/Users/mrogge/Filament_Extruder/Thunderware/Thunderware/TestSketch/Release/arduino.ar"   $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

TestSketch.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"/bin/avr-gcc" -Os -Wl,--gc-sections -mmcu=atmega2560  -o "/Users/mrogge/Filament_Extruder/Thunderware/Thunderware/TestSketch/Release/TestSketch.elf"   $(LINK_OBJ) $(AR)  "/Users/mrogge/Filament_Extruder/Thunderware/Thunderware/TestSketch/Release/arduino.ar" "-L/Users/mrogge/Filament_Extruder/Thunderware/Thunderware/TestSketch/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

TestSketch.eep: $(ELF)
	@echo 'Create eeprom image'
	"/bin/avr-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "/Users/mrogge/Filament_Extruder/Thunderware/Thunderware/TestSketch/Release/TestSketch.elf" "/Users/mrogge/Filament_Extruder/Thunderware/Thunderware/TestSketch/Release/TestSketch.eep"
	@echo 'Finished building: $@'
	@echo ' '

TestSketch.hex: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"/bin/avr-objcopy" -O ihex -R .eeprom  "/Users/mrogge/Filament_Extruder/Thunderware/Thunderware/TestSketch/Release/TestSketch.elf" "/Users/mrogge/Filament_Extruder/Thunderware/Thunderware/TestSketch/Release/TestSketch.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(C_DEPS)$(AR)$(EEP)$(FLASH_IMAGE)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS) TestSketch
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
