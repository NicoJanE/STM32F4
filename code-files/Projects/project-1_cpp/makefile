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
# 	-	The Makefile automatically includes all C\C++ source files from the directory ROOT_SOURCE_DIR and its subdirectories 
#		up to 4 levels deep. This includes both source files and header files, with ROOT_INCLUDE_DIR as the starting point 
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
#   -	Be aware of the number of files and the depth of subdirectories. A large number of files combined with deep
#     	directory structures (e.g., over 250,000 files across 150 folders with depth > 10) can lead to performance issues.
#   - 	Consider testing with parallel incremental builds (e.g., `make -j12`). Note that a **full build** must be executed
#     	first to create the requiCOL_RED subdirectories, as they cannot be reliably created when using multiple threads.
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
#   - This Makefile assumes you are using the ARM GCC toolchain(C/C++).
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
# Version: 0.3 (April 2025)
#


# UTILITIES
current_dir := $(shell pwd)														# Display the current working directory
NEWLINE = $(shell if [ "$(OS)" = "Windows_NT" ]; then echo; else echo ""; fi) 	# Display utility. Determine new line symbol based on OS

# TEXT COLORS. Define some color escape sequences
COL_YELLOW 	= \033[1;33m
COL_LGREEN 	= \033[1;32m
COL_RED    	= \033[1;31m
COL_RESET  	= \033[0m
COL_LGRAY	= \033[1;30m
COL_WHITE	= \033[0;37m
COL_BLUE	= \033[0;36m

# 1.1) CPP FILES LOCATIONS
ROOT_SOURCE_DIR := ./src
EXT:=cpp
TARGET = template
SRCS_CPP := $(wildcard $(ROOT_SOURCE_DIR)/*.$(EXT)) 									# includes all C files from the root
SRCS_CPP += $(wildcard $(ROOT_SOURCE_DIR)/*/*.$(EXT)) 	    							# includes all C files of the level 1 folder. i.e: ./system/*.cpp
SRCS_CPP += $(wildcard $(ROOT_SOURCE_DIR)/*/*/*.$(EXT)) 								# includes all C files of the level 2 folder. i.e: ./system/l2/*.cpp
SRCS_CPP += $(wildcard $(ROOT_SOURCE_DIR)/*/*/*/*.$(EXT)) 								# includes all C files of the level 3 folder. i.e: ./system/l2/l3/*.cpp
SRCS_CPP += $(wildcard $(ROOT_SOURCE_DIR)/*/*/*/*.$(EXT)) 								# includes all C files of the level 4 folder. i.e: ./system/n2/n3/n4/*.cpp

# 1.2) C FILES LOCATIONS, some specific files to get the program started, C files are explicitly stated
SRCS_C += $(wildcard $(ROOT_SOURCE_DIR)/system/c-implementation/*.c)					# C Files for system function implementations
SRCS_C += $(wildcard $(ROOT_SOURCE_DIR)/system/startup-code/*.c)						# C Files for system starup (COL_RESET_Handler)
SRCS_C += $(wildcard $(ROOT_SOURCE_DIR)/main.c)											# C Files for system starup (COL_RESET_Handler)
# SRCS := $(shell find ./src -name '*.c')												# OPTIONAL (Linux only) use the shell command  find all C files

# 1.3) Throw everything(C and C++) on a pile
SRCS = $(SRCS_CPP) $(SRCS_C)

# Marco to displays the used source files and header directories at the top, invoked by target: header    
define print-header
	@printf "$(COL_RESET)Source Files to be build:$(COL_LGRAY)\n"
	@printf "%s\n" "$(SRCS)" | awk '{for(i=1;i<=NF;i++) print $$i}' # Remove extra spaces
	
	@printf "$(COL_RESET)\nHeader directories used:$(COL_LGRAY)\n"
	@printf "%s\n" "$(SYSTEM_INCLUDE_DIRS)" | awk '{for(i=1;i<=NF;i++) print $$i}' # Remove extra spaces

	@echo "\n\n$(COL_RESET)"
endef


# 2) 	INCLUDE FILE LOCATIONS from the root folder and suport a 4 levels deep folder structure
#	   ‼️Also update the 'includePath' in the file: 'c_cpp_properties.json'‼️
#
ROOT_INCLUDE_DIR := ./src/_include/
#
# Call these in your C files like:
# 	#include 'filename.c'							// okay
# 	#include 'directory/filename.c'					// okay, may use full path
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
#
SYSTEM_INCLUDE_DIRS := \
$(wildcard $(ROOT_INCLUDE_DIR)) \
$(wildcard $(ROOT_INCLUDE_DIR)/*/) \
$(wildcard $(ROOT_INCLUDE_DIR)/*/*/) \
$(wildcard $(ROOT_INCLUDE_DIR)/*/*/*/) \
$(wildcard $(ROOT_INCLUDE_DIR)/*/*/*/*/)
#
# Normalize paths to remove trailing slashes and double slashes
SYSTEM_INCLUDE_DIRS := $(patsubst %/,%,$(SYSTEM_INCLUDE_DIRS))
SYSTEM_INCLUDE_DIRS := $(abspath $(SYSTEM_INCLUDE_DIRS))
#
# Alternative, sdd the C linkage headers for the C++ Compiler, not used currently, we compile the headers conditional(C or C++ linkage)
#SYSTEM_INCLUDE_DIRS += /usr/lib/arm-none-eabi/include/c++/12.2.1
#
# Convert to -I flags
INCLUDE_DIRS += $(patsubst %,-I%,$(SYSTEM_INCLUDE_DIRS))
#
# OPTIONAL (Linux only) use the shell command  find all include subfolders
# But curret version is more portable
# include files, that contains the sub directories automatically(Linux)
#	- Tip: Try the find command in your terminal
# INCLUDE_DIRS := $(shell find ./include -type d | sed 's/^/-I/')
#


# 3) THE LINKER SCRIPT
LINKER_SCRIPT = ./src/system/startup-code/stm32.ld


# 4) Output directories and files
BINDIR  := ./bin
OBJDIR  := $(BINDIR)/obj
TARGET:=$(BINDIR)/template
$(shell mkdir -p $(BINDIR) $(OBJDIR))


# 5.1) Compiler flags for C compiler
CFLAGS = -mcpu=cortex-m4 -mthumb 				# processor setup
CFLAGS += -O0 									# optimization is off
CFLAGS += -g3 									# -g3 generate debug info
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
#CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16 	# Hard FP
CFLAGS +=  -std=c11 

# 5.2 Compiler flags for C++ compiler
# 📌 C++-specific
#
# See also **Remark 1** in the stm32.ld file
# fno-rtti: Disables runtime type information (optional for embedded systems). 
# -fno-exceptions: Disables exception handling (important because STM32 does not support exceptions unless you write custom handlers).
CXXFLAGS =  -fno-exceptions -fno-rtti
CXXFLAGS += -std=c++17
CXXFLAGS += -fno-use-cxa-atexit 	# No global destructors for globals/static C++
#
# Debug
# 📌 C++-specific
CXXFLAGS +=  -O0 -g3 				# -g3 for more verbose debug information
CXXFLAGS += -mcpu=cortex-m4			#‼️Absolutely critical for debugging, without a default profile will be used and debbuging fails for the CPP code (breakpoints, Step over/into instructions)
CXXFLAGS += -mthumb 				# 16 bit instruction set instead of 32
CXXFLAGS += -Wl,--trace-undefined -Wl,--warn-unresolved-symbols 	# This SHOULD helps should the location of liking errors like: `__dso_handle` but NOT on ARM :(


# 6) Linker flags
# processor setup
# Soft FP or Hard FP
LDFLAGS += -march=armv7e-m
#LDFLAGS += -mfloat-abi=softfp -mfpu=fpv4-sp-d16 
#LDFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16 # 
#
# !BAREBONE implementation no standard c startup code! 
# Were not using the standard C startup code (crt0.o, libc, libnosys, etc.) 
# but our own startup code via COL_RESET_handler(see startup.c)
LDFLAGS += -nostartfiles -ffreestanding
#
# CHOICE ONE!
# For a fully standalone embedded application, use minimal stub implementations and provide 'syscalls.c' 
# to support malloc, printf, and other C standard functions. No semihosting is used. 'NewLib' is used. 
# Use:
LDFLAGS += --specs=nosys.specs -u _sbrk  -lc -lm -lgcc
# Otherwise. Use semihosting instead. Standard I/O operations (e.g., printf) will be sent to the debugger on the host. 
# The debugger will halt the system for each operation (slow). No need for a 'syscalls.c' implementation.
# Uncomment the line below and comment out the one above if semihosting is desiCOL_RED.
# LDFLAGS += --specs=rdimon.specs -lc -lm -lgcc
#
# linker garbage collector
LDFLAGS += -Wl,--gc-sections				# EXPLAIN
LDFLAGS += -Wl,-Map=$(TARGET).map
LDFLAGS += -T$(LINKER_SCRIPT)
LDFLAGS += -lstdc++ -lc -lm


# 7) Tool Chain,  compilers, linker and debugger
CROSS_COMPILE 	= arm-none-eabi-
CC 				= $(CROSS_COMPILE)gcc
CCX 			= $(CROSS_COMPILE)g++
LD 				= $(CROSS_COMPILE)ld
OBJDUMP 		= $(CROSS_COMPILE)objdump
OBJCOPY			= $(CROSS_COMPILE)objcopy
SIZE			= $(CROSS_COMPILE)size
DBG 			= gdb-multiarch							# DBG = $(CROSS_COMPILE)gdb

# 7.1 Object files
OBJS_C  := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS_C))
OBJS_CPP:= $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS_CPP))
OBJS 	:= $(OBJS_C) $(OBJS_CPP)				# Throw everything on a pile 


# 8) Build targets/rules
#
# Default target
all: clean header  print-cflags print-cxxflags print-ldflags build size	
	@echo "\nSuccessfully finished!\n\n"

build:$(TARGET).elf $(TARGET).hex $(TARGET).bin $(TARGET).lst

compile-only: $(OBJS)
	@echo "Compilation done. Linking skipped."

# Linking
$(TARGET).elf: $(OBJS_C) $(OBJS_CPP)
	@printf "\n$(COL_BLUE)[CC] Linking C/C++ object files:\n$(COL_YELLOW)  $(OBJS_C) $(COL_WHITE) \n  $(OBJS_CPP) %s  $(COL_RESET)\n" $<
	@printf "\n\t$(COL_BLUE) Linking Result in: $(TARGET).elf\n\n $(COL_RESET)"
	@$(CCX) $(OBJS_C) $(OBJS_CPP) -o $@   $(LDFLAGS)


# Compile all C files
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)	
	@printf "$(COL_YELLOW)[CC] Compiling C source: %s  $(COL_RED)\n" $<
	@$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@


# Compile all CPP files
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@printf "$(COL_WHITE)[CC] Compiling C++ source: %s  $(COL_RED)\n" $<
	@$(CCX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@


# Compile all assembly files
$(OBJDIR)/%.o: %.s
	@mkdir -p $(dir $@)	
	@printf "\nCOMPILING, Assembly files: %s \n----------------------------------------------------------------------------------------------------------------------------\n"  $<
	@$(CC) $(CFLAGS)  -c $< -o $@


# create (Hex) file 
#	- .Hex is ascii representation of the binary file
#	- for flashing to the device
$(TARGET).hex:$(TARGET).elf
	@$(OBJCOPY) -O ihex $< $@

# Binary representation of the executable program
# 	- Convert ELF to binary
#	- for flashing to the device
$(TARGET).bin: $(TARGET).elf
	@$(OBJCOPY) -O binary $< $@

# create listing file
$(TARGET).lst: $(TARGET).elf
	@$(OBJDUMP) -x -S $(TARGET).elf > $@

# make size
# -	Prints the memory sizes of the  section used by program (defined in the linker script)
# -	To monitor and manage your program's memory usage 
size: $(TARGET).elf
	@printf "$(COL_BLUE)\nMemory locations:\n $(COL_LGRAY)"  $<
	@$(SIZE) $(TARGET).elf
	@echo "$(COL_RESET)"

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
burn: all $(TARGET).bin
	@printf "BURNING to device:  \n  - Executing:\t%s\n" "$(FLASH_CMD)"
	@$(FLASH_CMD) && printf "\n"

	
CLEAN_CMD = rm -R ./bin 
clean:
	@printf "\nCleaning output directory:$(COL_LGRAY) \n Executing:\t%s\n" "$(CLEAN_CMD)"
	@$(CLEAN_CMD) && printf "\n"
	
header:
	@$(call print-header)


# Print output. Special target to print CFLAGS once
print-cflags:
	@printf "$(COL_YELLOW)Used C-Compiler options:$(COL_LGRAY)\n[CC] CFLAGS:"
	@printf "%s\n " "$(CFLAGS)" | awk '{$$1=$$1; print}' 			 # Remove extra spaces
	@echo "$(COL_RESET)"
	
# Print output. Special target to print CXXFLAGS once
print-cxxflags:
	@printf "$(COL_WHITE)USed C++-Compiler options:$(COL_LGRAY)\n[CC] CXXFLAGS:"
	@printf "%s\n " "$(CXXFLAGS)" | awk '{$$1=$$1; print}' 			 # Remove extra spaces
	@echo "$(COL_RESET)"

# Print output. Special target to print LDFLAGS once
print-ldflags:
	@printf "$(COL_BLUE)Used Linking options:$(COL_LGRAY)\n[CC] LDFLAGS:"
	@printf "%s\n " "$(LDFLAGS)" | awk '{$$1=$$1; print}' 			 # Remove extra spaces
	@echo "$(COL_RESET)"

.PHONY: all build size clean burn disass disass-all print-cflags print-cxxflags print-ldflags header