# Project form nrf5240 MCU

# Project name
PROJECT_NAME	= retro_gamepad
# Folders which contains the build artifacts
RESULT_FOLDER 	= build
OBJECTS_FOLDER	= obj

# Compiler system
SYSTEM	=arm-none-eabi-
CXX		=$(SYSTEM)g++
CC		=$(SYSTEM)gcc
AS		=$(SYSTEM)as
OBJCOPY	=$(SYSTEM)objcopy
SIZE	=$(SYSTEM)size
LD		=$(SYSTEM)ld
OBJDUMP	=$(SYSTEM)objdump

# Defines for the different configurations (others can be added)
DEFINES =
DEFINES_DEBUG =
DEFINES_RELEASE = NDEBUG

# Flags for different configurations (others can be added)
ifeq ($(BUILD), release)
CONFIGURATION 	= release
DEFINES 		+= $(DEFINES_RELEASE)
OPTIMIZE		=-Os
else
CONFIGURATION 	= debug
DEFINES 		+= $(DEFINES_DEBUG)
OPTIMIZE		=-Os
endif

# Paths for build result folder
BIN_FOLDER 		= $(RESULT_FOLDER)\$(CONFIGURATION)
BUILD_FOLDER 	= $(RESULT_FOLDER)\$(CONFIGURATION)\$(OBJECTS_FOLDER)

# Warnings configuration
WARNINGS		= -Wall -Werror -Wextra -Wduplicated-branches -Wduplicated-cond -Wfloat-equal -Wshadow=compatible-local -Wcast-qual -Wconversion -Wsign-conversion -Wlogical-op
WARNINGS_CPP 	= -Wctor-dtor-privacy -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wextra-semi -Wnon-virtual-dtor

# Name of the Components folder and ThirdParty folder
COMPONENTS_FOLDER 	= components
THIRD_PARTY_FOLDER 	= ThirdParty

# Folders for the application code
APP_INCLUDES_FOLDER	= includes
APP_SOURCES_FOLDER	= sources
APP_SUB_FOLDERS		=

# Add your components folders here
COMPONENTS 	:= cpp_register hal hal\stm32f070f6\registers hal\stm32f070f6\hal meta_types led usb fifo
# Add third party folders here
THIRD_PARTY :=
# Add additional includes folder here
INCLUDES 	:= 

# Flag to use std library
STD_LIB 	:= 0
# Flag to add git commit and branch to the sources
GIT_DATA 	:= 1

# Compilation flags and linker script
COMMONFLAGS	= -ggdb -mcpu=cortex-m0 -mthumb -fmax-errors=5 $(OPTIMIZE) $(DEFINES) $(INCLUDES)
CFLAGS		=
CXXFLAGS 	= -std=c++20 -fdata-sections -ffunction-sections -fno-rtti -fno-exceptions -fno-threadsafe-statics -fconcepts-diagnostics-depth=5 -fno-builtin
LDFLAGS		= --specs=nano.specs --specs=nosys.specs
LDSCRIPT	= linker.ld