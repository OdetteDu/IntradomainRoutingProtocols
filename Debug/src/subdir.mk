################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/Event.cc \
../src/Link.cc \
../src/Node.cc \
../src/RoutingProtocolImpl.cc \
../src/Simulator.cc 

OBJS += \
./src/Event.o \
./src/Link.o \
./src/Node.o \
./src/RoutingProtocolImpl.o \
./src/Simulator.o 

CC_DEPS += \
./src/Event.d \
./src/Link.d \
./src/Node.d \
./src/RoutingProtocolImpl.d \
./src/Simulator.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


