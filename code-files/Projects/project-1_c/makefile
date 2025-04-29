# This file is part of: **STM32F4 Template Stack**_
# Copyright (c) 2025 Nico Jan Eelhart_
# This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
# 
# Some header files in this project are © STMicroelectronics and used under their permissive license. See license notices in each file, and refer to:
# https://www.st.com/en/microcontrollers-microprocessors/stm32f4-series.html_



# This Makefile is used for building the STM32F4 embedded project. Below is an explanation of its structure and
# the commands available.
#
# - File Organization and Source Inclusions
#
# 	-	The Makefile automatically includes all C source files from the directory ROOT_SOURCE_DIR and its subdirectories 
#		up to 4 levels deep. This includes both C source files and header files, with ROOT_INCLUDE_DIR as the starting point 
#		for the header files.
# 	-	If your folder structure has more than 4 levels, you may need to add additional entries for source or include 
#		directories, but this is uncommon.
#
# - Customization:
#	-	Modify the `ROOT_SOURCE_DIR` and `ROOT_INCLUDE_DIR` to match your project’s source and include directories.
#	-	Add or remove directories from the search patterns if your project structure differs from the default.
#	-	The linker script used in this project can be found in `src\system\startup-code\stm32.ld`
#
# - Performance Considerations
#   -	Be careful with the number of files and the depth of subdirectories. A large number of files combined with deep
#     	directory structures (e.g., over 250,000 files across 150 folders with depth > 10) can lead to performance issues.
#   - 	Consider testing with parallel incremental builds (e.g., `make -j12`). Note that a **full build** must be executed
#     	first to create the required subdirectories, as they cannot be reliably created when using multiple threads.
#   - 	In case of performance problems, you can fall back to using **shell commands** (Linux/macOS only) in the Makefile
#     	to fetch files and folders instead of relying on Makefile wildcard matching.
#
# - Available Make Commands
#   - make              ->  Runs clean and build: full rebuild
#   - make build        ->  Incremental build
#   - make build -j12   ->  Uses all cores; for the first run, you may need to execute `make build` or `make`
#                           to ensure the directory structure is in place
#   - make size         ->  Prints memory sizes of the sections used by the program (defined in the linker script)
#                           Useful to monitor and manage your program's memory usage
#   - make disass       ->  Creates a disassembly listing of the program
#   - make debug        ->  Starts the local debugger — make sure `openocd` is running in another terminal:
#                           `openocd -f interface/stlink.cfg -f target/stm32f4x.cfg`
#   - make burn         ->  Flashes the program to the device
#   - make clean        ->  Cleans the project and removes all generated files
#
# - Toolchain and Dependencies (all installed in the Docker container):
#   - This Makefile assumes you are using the ARM GCC toolchain.
#   - You will also need `openocd` and `st-link` to interface with the STM32 device.
#   - This Makefile is designed for Linux-based (Docker Desktop) systems running on a Windows host.
#
#
#	Note 1: make output
#	I use the following construct to output information, during a makefile run. **Note** that I use:
#		-  @prinf instead of
#		-  @echo
#	because @printf is more portable, @echo works for bash but not fopr other shells 
#	Example:
# 				# Put dedicated variables close to the 'clean' target rule (inside the recipe is error)
#				CLEAN_CMD = rm -R ./bin
#				clean:
#				@printf "2Cleaning...\n  - Executing:\t%s\n" "$(CLEAN_CMD)"
#				@$(CLEAN_CMD) && printf "\n"
#
#
#   Notice: Yes, I had the audacity to indent less important output (see OUTPUT section, for example)
#           with spaces! (Using a tab there would cause a Makefile error.) Yes yes, I know — bad, bad boy!
#
# Version: 0.2 (March 2025)
#



# Display utility. Determine new line symbol based on OS
NEWLINE = $(shell if [ "$(OS)" = "Windows_NT" ]; then echo; else echo ""; fi)

# 1) C FILES LOCATIONS
ROOT_SOURCE_DIR := ./src
TARGET = template
SRCS := $(wildcard $(ROOT_SOURCE_DIR)/*.c) 											# includes all C files from the root
SRCS += $(wildcard $(ROOT_SOURCE_DIR)/*/*.c) 	    								# includes all C files of the level 1 folder. i.e: ./system/*.c
SRCS += $(wildcard $(ROOT_SOURCE_DIR)/*/*/*.c) 										# includes all C files of the level 2 folder. i.e: ./system/l2/*.c
SRCS += $(wildcard $(ROOT_SOURCE_DIR)/*/*/*/*.c) 									# includes all C files of the level 3 folder. i.e: ./system/l2/l3/*.c
SRCS += $(wildcard $(ROOT_SOURCE_DIR)/*/*/*/*.c) 									# includes all C files of the level 4 folder. i.e: ./system/n2/n3/n4/*.c
# OPTIONAL (Linux only) use the shell command  find all C files
# SRCS := $(shell find ./src -name '*.c')
#
# OUTPUT C source files
    $(info $(NEWLINE) )$(info $(NEWLINE) )
    $(info These C files are build (same directory Layout is used, in output directory):)
    $(info ==============================================================================)
    $(info $(NEWLINE) )
    $(foreach src, $(SRCS), $(info $(src)))  								


## 2) 	INCLUDE FILE LOCATIONS frm the root folder and suport a 4 levels deep folder structure
#	   ‼️Also update the 'includePath' in the file: 'c_cpp_properties.json'‼️
#
ROOT_INCLUDE_DIR := ./src/_include

# Call these in your C files like:
# 	#include 'filename.c'
# 	#include 'directory/filename.c'
# 	#include 'directory/directory_2/filename.c
#
#   DEPENDENCY
#	Visual Studio Code(VSC) note:
#	You *can* include headers without their folder path (e.g., #include "syscalls.h") —
# 	Make will build fine. BUT IntelliSense will fail unless:
#   	- You install the Microsoft C/C++ extension
#   	- You create .vscode/c_cpp_properties.json
#   	- You define the includePath manually (matching what's defined here)
#
# 	⚠️ This setup is NOT DRY — the include structure must be maintained in both places.
# 	⚠️ For other IDE's you must probably do something similar
#		
SYSTEM_INCLUDE_DIRS := \
$(wildcard $(ROOT_INCLUDE_DIR)) \
$(wildcard $(ROOT_INCLUDE_DIR)/*/) \
$(wildcard $(ROOT_INCLUDE_DIR)/*/*/) \
$(wildcard $(ROOT_INCLUDE_DIR)/*/*/*/) \
$(wildcard $(ROOT_INCLUDE_DIR)/*/*/*/*/)
#
# Strip trailing slashes and convert to -I flags
SYSTEM_INCLUDE_DIRS := $(patsubst %/,%,$(SYSTEM_INCLUDE_DIRS))
INCLUDE_DIRS += $(patsubst %,-I%,$(SYSTEM_INCLUDE_DIRS))
#
#
# OPTIONAL (Linux only) use the shell command  find all include subfolders
# But curret version is more portable
# include files, that contains the sub directories automatically(Linux)
#	- Tip: Try the find command in your terminal
# INCLUDE_DIRS := $(shell find ./include -type d | sed 's/^/-I/')
#
# OUTPUT C header files
    $(info $(NEWLINE) )$(info $(NEWLINE) )								
    $(info These header files are used:)
    $(info ------------------------------------------------------------------------------)
    $(info $(NEWLINE) )
    $(foreach dir, $(INCLUDE_DIRS), $(info    $(dir)))						# Use to display (debug) include file locations
    $(info $(NEWLINE) )$(info $(NEWLINE) )


# 3) THE LINKER SCRIPT
LINKER_SCRIPT = ./src/system/startup-code/stm32.ld


# 4) Output directories and files
BINDIR  := ./bin
OBJDIR  := $(BINDIR)/obj
OBJS    := $(SRCS:%.c=$(OBJDIR)/%.o)
TARGET:=$(BINDIR)/template
$(shell mkdir -p $(BINDIR) $(OBJDIR))

# 5) Compiler flags
CFLAGS = -mcpu=cortex-m4 -mthumb 				# processor setup
CFLAGS += -O0 									# optimization is off
CFLAGS += -g2 									# -g3 generate debug info
CFLAGS += -fno-eliminate-unused-debug-types -fno-eliminate-unused-debug-symbols	# 
CFLAGS += -fno-common
CFLAGS += -Wall 								# turn on warnings
CFLAGS += -pedantic 							# more warnings
CFLAGS += -Wsign-compare
CFLAGS += -Wcast-align
CFLAGS += -Wconversion 							# neg int const implicitly converted to uint
CFLAGS += -fsingle-precision-constant
CFLAGS += -fomit-frame-pointer 					# do not use fp if not needed
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -mfloat-abi=soft 						# Chooses the relevant FPU optionNo FP
#CFLAGS += -mfloat-abi=softfp -mfpu=fpv4-sp-d16 # Soft FP
#CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16 # Hard FP


# 6) Linker flags
LDFLAGS += -march=armv7e-m # processor setup
#LDFLAGS += -mfloat-abi=softfp -mfpu=fpv4-sp-d16 # Soft FP
#LDFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16 # Hard FP
#
# !BAREBONE implementation no standard c startup code! 
# Were not using the standard C startup code (crt0.o, libc, libnosys, etc.) 
# but our own startup code via reset_handler(see startup.c)
LDFLAGS += -nostartfiles 	
#
# CHOICE ONE!
# For a fully standalone embedded application, use minimal stub implementations and provide 'syscalls.c' 
# to support malloc, printf, and other C standard functions. No semihosting is used. 'NewLib' is used. 
# Use:
LDFLAGS += --specs=nosys.specs  -u _sbrk  -lc -lm -lgcc
# Otherwise. Use semihosting instead. Standard I/O operations (e.g., printf) will be sent to the debugger on the host. 
# The debugger will halt the system for each operation (slow). No need for a 'syscalls.c' implementation.
# Uncomment the line below and comment out the one above if semihosting is desired.
# LDFLAGS += --specs=rdimon.specs -lc -lm -lgcc
#
LDFLAGS += -Wl,--gc-sections # linker garbage collector
LDFLAGS += -Wl,-Map=$(TARGET).map #generate map file
LDFLAGS += -T$(LINKER_SCRIPT)


# 7) Used compiler, linker and debugger
CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJDUMP = $(CROSS_COMPILE)objdump
OBJCOPY = $(CROSS_COMPILE)objcopy
SIZE = $(CROSS_COMPILE)size
#DBG = $(CROSS_COMPILE)gdb
DBG = gdb-multiarch


# 8) Build targets
#
all: clean $(SRCS) build size
	@echo "Successfully finished..."

build: $(TARGET).elf $(TARGET).hex $(TARGET).bin $(TARGET).lst

$(TARGET).elf: $(OBJS)
	@$(CC) $(OBJS) $(LDFLAGS) -o $@


# Compile all C files
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "\nBUILDING: %s \n----------------------------------------------------------------------------------------------------------------------------\n"  $<
	@$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# Compile all assembly files
$(OBJDIR)/%.o: %.s
	@mkdir -p $(dir $@)	
	@printf "\nBUILDING: %s \n----------------------------------------------------------------------------------------------------------------------------\n"  $<
	@$(CC) $(CFLAGS)  -c $< -o $@


# create (Hex) file 
#	- .Hex is ascii representation of the binary file
#	- for flashing to the device
$(BINDIR)/%.hex:$(BINDIR)/%.elf
	@$(OBJCOPY) -O ihex $< $@

# Binary representation of the executable program
# 	- Convert ELF to binary
#	- for flashing to the device
$(BINDIR)/%.bin: $(BINDIR)/%.elf
	@$(OBJCOPY) -O binary $< $@

# create listing file
$(BINDIR)/%.lst: $(BINDIR)/%.elf
	@$(OBJDUMP) -x -S $(TARGET).elf > $@

# make size
# -	Prints the memory sizes of the  section used by program (defined in the linker script)
# -	To monitor and manage your program's memory usage 
size: $(TARGET).elf
	@$(SIZE) $(TARGET).elf

# make disass
# -	Creates a disassembly listing of the program 
disass: $(TARGET).elf
	@$(OBJDUMP) -d  $(TARGET).elf

disass-all: $(TARGET).elf
	@$(OBJDUMP) -D $(TARGET).elf

# make debug
debug:
	@$(DBG) --eval-command="target  remote localhost:3333" \
	 $(TARGET).elf

# make burn
# - Flash to device
FLASH_CMD = st-flash write $(TARGET).bin 0x8000000
burn: $(TARGET).bin
	@printf "BURNING to device:  \n  - Executing:\t%s\n" "$(FLASH_CMD)"
	@$(FLASH_CMD) && printf "\n"

	
CLEAN_CMD = rm -R ./bin 
clean:
	@printf "CLEANING output directory:  \n  - Executing:\t%s\n" "$(CLEAN_CMD)"
	@$(CLEAN_CMD) && printf "\n"


.PHONY: all build size clean burn disass disass-all