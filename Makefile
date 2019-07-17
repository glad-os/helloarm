#
# Copyright 2019 AbbeyCatUK
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
# http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  

#.SILENT:

# common
FIND     			= find
OPTIMIZE 			= 0

# 32-bit toolchain
GCC_PATH_32			= ~/Downloads/Software/ARM/32-bit/gcc-arm-8.2-2019.01-x86_64-arm-eabi
GCC_32      			= $(GCC_PATH_32)/bin/arm-eabi-gcc
AS_32       			= $(GCC_PATH_32)/arm-eabi/bin/as
AR_32       			= $(GCC_PATH_32)/arm-eabi/bin/ar
LD_32       			= $(GCC_PATH_32)/arm-eabi/bin/ld
OBJDUMP_32  			= $(GCC_PATH_32)/arm-eabi/bin/objdump
OBJCOPY_32  			= $(GCC_PATH_32)/arm-eabi/bin/objcopy

# 64-bit toolchain
GCC_PATH_64			= ~/Downloads/Software/ARM/64-bit/gcc-arm-8.2-2019.01-x86_64-aarch64-elf
GCC_64      			= $(GCC_PATH_64)/bin/aarch64-elf-gcc
AS_64       			= $(GCC_PATH_64)/aarch64-elf/bin/as
AR_64       			= $(GCC_PATH_64)/aarch64-elf/bin/ar
LD_64       			= $(GCC_PATH_64)/aarch64-elf/bin/ld
OBJDUMP_64  			= $(GCC_PATH_64)/aarch64-elf/bin/objdump
OBJCOPY_64  			= $(GCC_PATH_64)/aarch64-elf/bin/objcopy

# 32/64 bit flags for Assembler and Compiler
ARCH_64	 			= -march=armv8-a -mtune=cortex-a53
FLAGS_C_64  			= $(ARCH_64) -std=gnu99 -fsigned-char -Wno-psabi -O$(OPTIMIZE) -fno-builtin -nostartfiles -ffreestanding -D ISA_TYPE=$(ISA_TYPE)
FLAGS_A_64			= $(ARCH_64) -O$(OPTIMIZE) -D ISA_TYPE=$(ISA_TYPE)

ARCH_32	 			= -march=armv8-a -mtune=cortex-a53 -mfpu=neon-fp-armv8 -mfloat-abi=hard
FLAGS_C_32  			= $(ARCH_32) -std=gnu99 -fsigned-char -Wno-psabi -O$(OPTIMIZE) -fno-builtin -nostartfiles -ffreestanding -mapcs-frame -mno-thumb-interwork -D ISA_TYPE=$(ISA_TYPE)
FLAGS_A_32			= $(ARCH_32) -O$(OPTIMIZE) -D ISA_TYPE=$(ISA_TYPE)

# -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  

# 32-bit

32-bit: clean hello-32

32-bit: ISA_TYPE		= 32

32-bit: GCC			= $(GCC_32)
32-bit: AS			= $(AS_32)
32-bit: AR			= $(AR_32)
32-bit: LD			= $(LD_32)
32-bit: OBJDUMP			= $(OBJDUMP_32)
32-bit: OBJCOPY			= $(OBJCOPY_32)

32-bit: FLAGS_C			= $(FLAGS_C_32)
32-bit: FLAGS_A			= $(FLAGS_A_32)

32-bit: INCLUDE_DIR		= c/32-bit/include

# -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  

# 64-bit

64-bit: clean hello-64

64-bit: ISA_TYPE		= 64

64-bit: GCC			= $(GCC_64)
64-bit: AS			= $(AS_64)
64-bit: AR			= $(AR_64)
64-bit: LD			= $(LD_64)
64-bit: OBJDUMP			= $(OBJDUMP_64)
64-bit: OBJCOPY			= $(OBJCOPY_64)

64-bit: FLAGS_C			= $(FLAGS_C_64)
64-bit: FLAGS_A			= $(FLAGS_A_64)

64-bit: INCLUDE_DIR		= c/64-bit/include/

# -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  

# clean

clean:
	$(FIND) . -type f -name "*.o"    -delete
	$(FIND) . -type f -name "*.hex"  -delete
	$(FIND) . -type f -name "*.bin"  -delete
	$(FIND) . -type f -name "*.elf"  -delete
	$(FIND) . -type f -name "*.list" -delete

# -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  

# hello

HELLO_HOME 		= .
HELLO_INCLUDES		= -I $(HELLO_HOME)/ext/stdlib-$(ISA_TYPE)/include

HELLO_FLAGS_C		= $(FLAGS_C) $(HELLO_INCLUDES)
HELLO_FILES_C     	= $(patsubst %.c,%.o,$(shell find . -type f -name '*.c'))

hello-32: $(HELLO_FILES_C) $(STDLIB_FILES_C) hello
hello-64: $(HELLO_FILES_C) $(STDLIB_FILES_C) hello

hello: hello_c

	$(LD)  	linker.ld -o hello.elf c/common/main.o ext/stdlib-$(ISA_TYPE)/stdlib-$(ISA_TYPE).a

	$(OBJCOPY) -I elf32-little -O binary --strip-debug --strip-unneeded --verbose hello.elf hello.bin 
	$(OBJCOPY) hello.elf -O ihex hello.hex
	$(OBJDUMP) -D hello.elf > hello.list

hello_c: $(HELLO_FILES_C)

$(HELLO_HOME)/%.o : $(HELLO_HOME)/%.c
	$(GCC) -c $(HELLO_FLAGS_C) $< -o $@

