################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../net/AsynServer.cpp \
../net/ClientConnection.cpp \
../net/Connection.cpp \
../net/IConnection.cpp \
../net/IOServiceAgent.cpp \
../net/IServer.cpp \
../net/ServerConnection.cpp 

OBJS += \
./net/AsynServer.o \
./net/ClientConnection.o \
./net/Connection.o \
./net/IConnection.o \
./net/IOServiceAgent.o \
./net/IServer.o \
./net/ServerConnection.o 

CPP_DEPS += \
./net/AsynServer.d \
./net/ClientConnection.d \
./net/Connection.d \
./net/IConnection.d \
./net/IOServiceAgent.d \
./net/IServer.d \
./net/ServerConnection.d 


# Each subdirectory must supply rules for building sources it contributes
net/%.o: ../net/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/myron/workspace/TCPServer/net" -I"/home/myron/workspace/TCPServer/log" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


