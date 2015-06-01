COMPILER=GCC
CC=arm-none-eabi-gcc

BUILD_DIR=./Build
DRIVER_DIR=./Libraries/MAX32600PeriphDriver
CMSIS_CORE=./Libraries/CMSIS/Core
CMSIS_DEVICE=./Libraries/CMSIS/Device/Maxim/MAX32600
LD_CMD=$(CMSIS_DEVICE)/Source/$(COMPILER)/max32600.ld
BLE_LIB_DIR=./BLE_Wicentric

ELF=MAXREFDES73.elf

_OBJS=	app_disc.o \
	app_main.o \
	app_server.o \
	app_slave.o \
	app_db.o \
	app_hw.o \
	app_ui.o \
	hci_cmd.o \
	hci_core.o \
	hci_evt.o \
	hci_tr.o \
	hci_vs.o \
	hci_drv.o \
	bas_main.o \
	hrps_main.o \
	svc_batt.o \
	svc_bps.o \
	svc_core.o \
	svc_dis.o \
	svc_gls.o \
	svc_hrs.o \
	svc_hts.o \
	svc_px.o \
	svc_wp.o \
	svc_wss.o \
	svc_hid.o \
	cfg_stack.o \
	hci_main.o \
	wsf_buf.o \
	wsf_msg.o \
	wsf_queue.o \
	wsf_sec.o \
	wsf_timer.o \
	wsf_assert.o \
	wsf_os.o \
	wsf_trace.o \
	MAXREFDES73.o \
	fit_main.o

DRIVER_LIB_DIR=Libraries
DRIVER_LIB=$(DRIVER_LIB_DIR)/libmax32600.a

LIBS=-lmax32600 -lc -lstacklib -lm

OBJS=$(addprefix $(BUILD_DIR)/, $(_OBJS))

INCLUDE_PATHS=-I./Include -I$(CMSIS_CORE)/Include -I$(CMSIS_DEVICE)/Include -I$(DRIVER_DIR)/Include \
	-I$(BLE_LIB_DIR) \
	-I$(BLE_LIB_DIR)/apps/app \
	-I$(BLE_LIB_DIR)/apps/app/include \
	-I$(BLE_LIB_DIR)/hci/dual_chip \
	-I$(BLE_LIB_DIR)/hci/include \
	-I$(BLE_LIB_DIR)/profiles/bas \
	-I$(BLE_LIB_DIR)/profiles/hrps \
	-I$(BLE_LIB_DIR)/services \
	-I$(BLE_LIB_DIR)/stack/cfg \
	-I$(BLE_LIB_DIR)/stack/hci \
	-I$(BLE_LIB_DIR)/stack/include \
	-I$(BLE_LIB_DIR)/util \
	-I$(BLE_LIB_DIR)/wsf/common \
	-I$(BLE_LIB_DIR)/wsf/generic \
	-I$(BLE_LIB_DIR)/wsf/include

VPATH=	$(BLE_LIB_DIR)/apps/app \
	$(BLE_LIB_DIR)/apps/app/generic \
	$(BLE_LIB_DIR)/hci/dual_chip \
	$(BLE_LIB_DIR)/hci/generic \
	$(BLE_LIB_DIR)/profiles/bas \
	$(BLE_LIB_DIR)/profiles/hrps \
	$(BLE_LIB_DIR)/services \
	$(BLE_LIB_DIR)/stack \
	$(BLE_LIB_DIR)/stack/cfg \
	$(BLE_LIB_DIR)/stack/hci \
	$(BLE_LIB_DIR)/wsf/common \
	$(BLE_LIB_DIR)/wsf/generic \
	$(BLE_LIB_DIR)/generic \
	$(DRIVER_DIR)/Source \
	$(CMSIS_CORE)/Source \
	$(CMSIS_DEVICE)/Source \
	$(CMSIS_DEVICE)/Source/$(COMPILER) \
	./Source

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
	 -nostartfiles        \
	 -g	

LDFLAGS=-Wl,--gc-sections -T $(LD_CMD) -Wl,-Map=MAXREFDES73.map -Wl,--no-wchar-size-warning --entry Reset_Handler

.PHONY: upload clean $(DRIVER_LIB)

all: $(ELF)

$(ELF): Makefile $(DRIVER_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -L$(DRIVER_LIB_DIR) -L$(BLE_LIB_DIR) -o $(ELF) -Wl,--start-group $(LIBS) -Wl,--end-group $(OBJS) -Wl,--start-group $(LIBS) -Wl,--end-group

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

upload:
	openocd -f interface/ftdi/olimex-arm-usb-tiny-h.cfg -f target/max32600.cfg -c "program MAXREFDES73.elf verify reset"

-include $(BUILD_DIR)/*.d
