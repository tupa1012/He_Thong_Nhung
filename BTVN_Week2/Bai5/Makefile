TARGET = firmware

CC = arm-none-eabi-gcc
AS = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy


# =========================================================
# Compiler flags
# =========================================================

CFLAGS = -mcpu=cortex-m3 \
         -mthumb \
         -O2 \
         -Wall \
         -ffreestanding \
         -fdata-sections \
         -ffunction-sections \
         -DSTM32F10X_MD \
         -DUSE_STDPERIPH_DRIVER \
         -Ilib/inc \
         -Icmsis \
         -Idriver


# =========================================================
# Linker flags
# =========================================================

LDFLAGS = -T linker/LinkerScript.ld \
          -nostdlib \
          -Wl,--gc-sections \
          -Wl,-Map=build/$(TARGET).map


# =========================================================
# Source files
# =========================================================

SRC = src/main.c \
      driver/adc.c \
      driver/uart.c \
      driver/timer.c \
      cmsis/core_cm3.c \
      lib/src/stm32f10x_gpio.c \
      lib/src/stm32f10x_rcc.c \
      lib/src/system_stm32f10x.c

STARTUP = startup/startup_stm32f103xb.s


# =========================================================
# Object files
# =========================================================

OBJ = $(SRC:%.c=build/%.o)


# =========================================================
# Default target
# =========================================================

all: build/$(TARGET).bin


# =========================================================
# Compile .c -> .o
# =========================================================

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


# =========================================================
# Compile startup .s -> .o
# =========================================================

build/startup.o: $(STARTUP)
	@mkdir -p $(dir $@)
	$(AS) $(CFLAGS) -c $< -o $@


# =========================================================
# Link
# =========================================================

build/$(TARGET).elf: $(OBJ) build/startup.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@


# =========================================================
# ELF -> BIN
# =========================================================

build/$(TARGET).bin: build/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@


# =========================================================
# Flash STM32
# =========================================================

flash: build/$(TARGET).bin
	st-flash write $< 0x08000000


# =========================================================
# Clean
# =========================================================

clean:
	rm -rf build


# =========================================================
# Phony targets
# =========================================================

.PHONY: all flash clean
