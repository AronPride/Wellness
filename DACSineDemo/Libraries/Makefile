COMPILER=GCC
CC=arm-none-eabi-gcc
AR=arm-none-eabi-ar

BUILD_DIR=./Build
DRIVER_DIR=./MAX32600PeriphDriver
CMSIS_CORE=./CMSIS/Core
CMSIS_DEVICE=./CMSIS/Device/Maxim/MAX32600

LIB=libmax32600.a

_OBJS=adc.o \
	afe.o \
	clkman.o \
	dac.o \
	flc.o \
	gpio.o \
	heap.o \
	i2cm.o \
	icc.o \
	nvic_table.o \
	pmu.o \
	power.o \
	pt.o \
	rtc.o \
	spi.o \
	startup_max32600.o \
	system_max32600.o \
	systick.o \
	tmon.o \
	tmr.o \
	uart.o \
	wdt.o \
	lcd.o \
	aes.o \
	prng.o

OBJS=$(addprefix $(BUILD_DIR)/, $(_OBJS))

INCLUDE_PATHS=-I$(CMSIS_CORE)/Include -I$(CMSIS_DEVICE)/Include -I$(DRIVER_DIR)/Include
VPATH=$(DRIVER_DIR)/Source $(CMSIS_CORE)/Source $(CMSIS_DEVICE)/Source $(CMSIS_DEVICE)/Source/$(COMPILER)

DEFINE:=-D__Vendor_SysTickConfig=1

CFLAGS+= $(DEFINE)            \
	 $(INCLUDE_PATHS)     \
	 -mthumb              \
	 -mcpu=cortex-m3      \
	 -ffunction-sections  \
	 -fshort-wchar        \
	 -fdata-sections      \
	 -MD                  \
	 -Wno-unused-function \
	 -Wall                \
	 -fpack-struct=1      \
	 -g


.PHONY: clean subdirs

all: $(LIB)

$(LIB): Makefile $(OBJS)
	$(AR) rsc $(LIB) $(OBJS)

$(BUILD_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.S
	$(CC) -c $(CFLAGS) $< -o $@


$(OBJS): | $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf Build $(LIB)

-include $(BUILD_DIR)/*.d



