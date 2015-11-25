################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../Visual\ Micro/ \
../__vm/


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../Heater.cpp \
../Buzzer.cpp \
../Caliper.cpp \
../Configuration.cpp \
../FastPWM.cpp \
../Key.cpp \
../Keypad.cpp \
../Menu.cpp \
../Nozzle.cpp \
../Outfeed.cpp \
../PID_v1.cpp \
../Safety.cpp \
../Spooler.cpp \
../StarveFeeder.cpp \
../StepperMotor.cpp \
../Thermistor.cpp


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
Heater.o \
Buzzer.o \
Caliper.o \
Configuration.o \
FastPWM.o \
Key.o \
Keypad.o \
Menu.o \
Nozzle.o \
Outfeed.o \
PID_v1.o \
Safety.o \
Spooler.o \
StarveFeeder.o \
StepperMotor.o \
Thermistor.o

OBJS_AS_ARGS +=  \
Heater.o \
Buzzer.o \
Caliper.o \
Configuration.o \
FastPWM.o \
Key.o \
Keypad.o \
Menu.o \
Nozzle.o \
Outfeed.o \
PID_v1.o \
Safety.o \
Spooler.o \
StarveFeeder.o \
StepperMotor.o \
Thermistor.o

C_DEPS +=  \
Heater.d \
Buzzer.d \
Caliper.d \
Configuration.d \
FastPWM.d \
Key.d \
Keypad.d \
Menu.d \
Nozzle.d \
Outfeed.d \
PID_v1.d \
Safety.d \
Spooler.d \
StarveFeeder.d \
StepperMotor.d \
Thermistor.d

C_DEPS_AS_ARGS +=  \
Heater.d \
Buzzer.d \
Caliper.d \
Configuration.d \
FastPWM.d \
Key.d \
Keypad.d \
Menu.d \
Nozzle.d \
Outfeed.d \
PID_v1.d \
Safety.d \
Spooler.d \
StarveFeeder.d \
StepperMotor.d \
Thermistor.d

OUTPUT_FILE_PATH +=Thunderware.elf

OUTPUT_FILE_PATH_AS_ARGS +=Thunderware.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler

































./%.o: .././%.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -D__AVR_ATmega2560__ -DARDUINO=161 -DARDUINO_MAIN -DF_CPU=16000000L -D__AVR__ -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR  -I"{runtime.tools.avr-gcc.path}/lib/gcc/avr/4.8.1/include" -I"{runtime.tools.avr-gcc.path}//avr/include/avr" -I"{runtime.tools.avr-gcc.path}/avr/include" -I"C:/Users/Matt Rogge/Documents/Arduino/libraries" -I"C:/Program Files (x86)/Atmel/Studio/7.0/Extensions/m2zu5bhx.ecj/Micro Platforms/default/debuggers" -I"C:/Program Files (x86)/Arduino/hardware/arduino/avr/libraries" -I"C:/Program Files (x86)/Arduino/libraries" -I"C:/Program Files (x86)/Arduino/hardware/arduino/avr/libraries/Wire/utility" -I"C:/Program Files (x86)/Arduino/hardware/arduino/avr/libraries/Wire" -I"C:/Program Files (x86)/Arduino/libraries/LiquidCrystal/src/utility" -I"C:/Program Files (x86)/Arduino/libraries/LiquidCrystal/src" -I"C:/Program Files (x86)/Arduino/hardware/arduino/avr/libraries/EEPROM/utility" -I"C:/Program Files (x86)/Arduino/hardware/arduino/avr/libraries/EEPROM" -I"../../Thunderware" -I"C:/Program Files (x86)/Arduino/hardware/arduino/avr/variants/mega" -I"C:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega2560 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\gcc\dev\atmega2560" -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR8/GNU Linker : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Thunderware.map" -Wl,--start-group  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega2560 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\gcc\dev\atmega2560"  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "Thunderware.elf" "Thunderware.hex"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Thunderware.elf" "Thunderware.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "Thunderware.elf" > "Thunderware.lss"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "Thunderware.elf" "Thunderware.srec"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "Thunderware.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "Thunderware.elf" "Thunderware.a" "Thunderware.hex" "Thunderware.lss" "Thunderware.eep" "Thunderware.map" "Thunderware.srec" "Thunderware.usersignatures"
	