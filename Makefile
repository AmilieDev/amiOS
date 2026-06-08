# Toolchain
ASM     := nasm
CC      := i686-elf-gcc
LD      := i686-elf-ld

# Flags
CFLAGS  := -ffreestanding -Wall -Werror -MMD -MP
LDFLAGS := -T boot/linker.ld --oformat binary

# Sources and objects (mirror the kernel/ tree into build/)
C_SRCS  := $(shell find kernel -name '*.c')
C_OBJS  := $(patsubst %.c,build/%.o,$(C_SRCS))
ENTRY   := build/kernel_entry.o

MIN_BYTES := 8704          # 17 sectors * 512

.PHONY: all run clean
all: build/os-image.bin

run: build/os-image.bin
	qemu-system-i386 -drive format=raw,file=build/os-image.bin

build/boot.bin: boot/boot.asm
	@mkdir -p $(dir $@)
	$(ASM) -f bin $< -o $@

build/kernel_entry.o: boot/kernel_entry.asm
	@mkdir -p $(dir $@)
	$(ASM) -f elf32 $< -o $@

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# kernel_entry.o MUST be first so the entry sits at 0x1000
build/kernel.bin: $(ENTRY) $(C_OBJS) boot/linker.ld
	$(LD) $(LDFLAGS) -o $@ $(ENTRY) $(C_OBJS)

build/os-image.bin: build/boot.bin build/kernel.bin
	cat build/boot.bin build/kernel.bin > $@
	@if [ "$$(stat -c%s $@)" -lt $(MIN_BYTES) ]; then \
		truncate -s $(MIN_BYTES) $@; \
	fi

clean:
	rm -rf build

# auto header-dependency tracking (the .d files come from -MMD)
-include $(C_OBJS:.o=.d)