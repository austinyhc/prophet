CC = arm-none-eabi-gcc
CPU = -mcpu=cortex-m4

######################################
# CFLAGS
######################################
CPU = -mcpu=cortex-m4
FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=hard
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

CFLAGS = -c $(CPU) $(MCU) -std=gnu11 -Wall -O0
LDFLAGS = $(CPU) $(MCU) --specs=nano.specs -T stm32l4r9xx.ld -Wl,-Map=final.map
LDFLAGS_SH = $(CPU) $(MCU) --specs=rdimon.specs -T stm32l4r9xx.ld -Wl,-Map=final.map

all: main.o led.o startup_stm32l4r9xx.o syscalls.o final.elf

semi:main.o led.o stm32_startup.o syscalls.o final_sh.elf

main.o: main.c
	$(CC) $(CFLAGS) -o $@ $^

led.o: led.c
	$(CC) $(CFLAGS) -o $@ $^

stm32_startup.o: startup_stm32l4r9xx.c
	$(CC) $(CFLAGS) -o $@ $^

syscalls.o: syscalls.c
	$(CC) $(CFLAGS) -o $@ $^

final.elf: main.o led.o startup_stm32l4r9xx.o syscalls.o
	$(CC) $(LDFLAGS) -o $@ $^

final_sh.elf: main.o led.o startup_stm32l4r9xx.o
	$(CC) $(LDFLAGS_SH) -o $@ $^

clean:
	rm -rf *.o *.elf

load:
	openocd -f board/stm32f4discovery.cfg
