CC = arm-none-eabi-gcc
CP = arm-none-eabi-objcopy

all: simple.bin

LIBS = -I../../drivers/cpu -I../../drivers/cmsis

simple.bin:
	$(CC) $(LIBS) -DSTM32L4R9xx -mcpu=cortex-m4 -mthumb -nostartfiles -c simple.c -o $@
	$(CP) -O binary -S $@ $@

clean:
	$(RM) simple.bin
