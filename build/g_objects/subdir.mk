################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../g_objects/Brick.cpp \
../g_objects/Bullet.cpp \
../g_objects/Concrete.cpp \
../g_objects/Enemy.cpp \
../g_objects/Flag.cpp \
../g_objects/Tank.cpp \
../g_objects/ally.cpp \
../g_objects/dgobject.cpp \
../g_objects/g_object.cpp 

OBJS += \
./g_objects/Brick.o \
./g_objects/Bullet.o \
./g_objects/Concrete.o \
./g_objects/Enemy.o \
./g_objects/Flag.o \
./g_objects/Tank.o \
./g_objects/ally.o \
./g_objects/dgobject.o \
./g_objects/g_object.o 

CPP_DEPS += \
./g_objects/Brick.d \
./g_objects/Bullet.d \
./g_objects/Concrete.d \
./g_objects/Enemy.d \
./g_objects/Flag.d \
./g_objects/Tank.d \
./g_objects/ally.d \
./g_objects/dgobject.d \
./g_objects/g_object.d 


# Each subdirectory must supply rules for building sources it contributes
g_objects/%.o: ../g_objects/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


