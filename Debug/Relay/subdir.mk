################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Relay/ImplementRelay.cpp \
../Relay/Relay.cpp \
../Relay/SimulationRelay.cpp 

OBJS += \
./Relay/ImplementRelay.o \
./Relay/Relay.o \
./Relay/SimulationRelay.o 

CPP_DEPS += \
./Relay/ImplementRelay.d \
./Relay/Relay.d \
./Relay/SimulationRelay.d 


# Each subdirectory must supply rules for building sources it contributes
Relay/%.o: ../Relay/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


