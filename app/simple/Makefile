.PHONY: all flash-stlink clean

PREFIX = arm-none-eabi-

CC = $(PREFIX)gcc
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
BIN = $(CP) -O binary -S

all: simple.bin

LIBS = -I../../drivers/cpu -I../../drivers/cmsis

simple.bin: simple.elf
	$(BIN) $< $@

simple.elf:
	$(CC) $(LIBS) -DSTM32L4R9xx -mcpu=cortex-m4 -mthumb -nostartfiles -c simple.c -o $@
	$(SZ) $@

flash-stlink: all
	st-flash --reset write ./simple.bin 0x08000000

clean:
	$(RM) simple.elf
	$(RM) simple.bin
