COMPILER=GCC
CC=arm-none-eabi-gcc

BUILD_DIR=./Build
BOARD_DIR=./Boards/EVKIT_B2
DRIVER_DIR=./Libraries/MAX32600PeriphDriver
CMSIS_CORE=./Libraries/CMSIS/Core
CMSIS_DEVICE=./Libraries/CMSIS/Device/Maxim/MAX32600
LD_CMD=$(CMSIS_DEVICE)/Source/$(COMPILER)/max32600.ld

ELF=max32600.elf

_OBJS=dac_sine_demo.o
DRIVER_LIB_DIR=Libraries
DRIVER_LIB=$(DRIVER_LIB_DIR)/libmax32600.a

LIBS=-lmax32600 -lc

OBJS=$(addprefix $(BUILD_DIR)/, $(_OBJS))

INCLUDE_PATHS=-I./Include -I$(CMSIS_CORE)/Include -I$(CMSIS_DEVICE)/Include -I$(DRIVER_DIR)/Include -I$(BOARD_DIR)/Include
VPATH=./Source $(DRIVER_DIR)/Source $(CMSIS_CORE)/Source $(CMSIS_DEVICE)/Source $(CMSIS_DEVICE)/Source/$(COMPILER) $(BOARD_DIR)/Source

DEFINE=-D__Vendor_SysTickConfig=1

CFLAGS = $(DEFINE)            \
	 $(INCLUDE_PATHS)     \
	 -mthumb              \
	 -mcpu=cortex-m3      \
	 -ffunction-sections  \
	 -fshort-wchar        \
	 -fdata-sections      \
	 -MD                  \
	 -Wno-unused-function \
	 -Wall                \
	 -g	

LDFLAGS=-Wl,--gc-sections -T $(LD_CMD) -Wl,-Map=max32600.map -Wl,--no-wchar-size-warning --entry Reset_Handler

.PHONY: upload clean $(DRIVER_LIB)

all: $(ELF)

$(ELF): Makefile $(DRIVER_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -L$(DRIVER_LIB_DIR) -o $(ELF) -Wl,--start-group $(LIBS) -Wl,--end-group $(OBJS) -Wl,--start-group $(LIBS) -Wl,--end-group

$(BUILD_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.S
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJS): | $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(DRIVER_LIB):
	$(MAKE) -C $(DRIVER_LIB_DIR)

clean:
	rm -rf Build *.map *.log $(ELF)
	$(MAKE) -C $(DRIVER_LIB_DIR) clean

upload: $(ELF)
	openocd -f interface/ftdi/olimex-arm-usb-tiny-h.cfg -f target/max32600.cfg -c "program max32600.elf verify reset"

-include $(BUILD_DIR)/*.d
