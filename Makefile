CC = arm-none-eabi-gcc
CPU = -mcpu=cortex-m4

BUILD_DIR = build

######################################
# CFLAGS
######################################
CPU = -mcpu=cortex-m4
FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=hard
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

CFLAGS = -c $(CPU) $(MCU) -std=gnu11 -Wall -O0 -g
LDFLAGS = $(CPU) $(MCU) --specs=nano.specs -T app/stm32l4r9xx.ld -Wl,-Map=$(BUILD_DIR)/final.map
LDFLAGS_SH = $(CPU) $(MCU) --specs=rdimon.specs -T app/stm32l4r9xx.ld -Wl,-Map=$(BUILD_DIR)/final.map

all: main.o led.o startup_stm32l4r9xx.o syscalls.o final.elf

semi: main.o led.o stm32_startup.o syscalls.o final_sh.elf

main.o: app/main.c $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(notdir $@) $<

led.o: app/led.c $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(notdir $@) $<

startup_stm32l4r9xx.o: app/startup_stm32l4r9xx.c $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(notdir $@) $<

syscalls.o: app/syscalls.c $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(notdir $@) $<

final.elf: $(BUILD_DIR)/main.o $(BUILD_DIR)/led.o $(BUILD_DIR)/startup_stm32l4r9xx.o $(BUILD_DIR)/syscalls.o
	$(CC) $(LDFLAGS) -o $(BUILD_DIR)/$@ $^

final_sh.elf: main.o led.o startup_stm32l4r9xx.o
	$(CC) $(LDFLAGS_SH) -o $@ $^

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf *.o *.elf *.map build

load:
	openocd -f board/stm32f4discovery.cfg
