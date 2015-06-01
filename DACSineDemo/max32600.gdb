target remote | openocd -s $MAXIM_PATH/Toolchain/share/openocd/scripts -f interface/ftdi/olimex-arm-usb-tiny-h.cfg -f target/max32600.cfg -c "gdb_port pipe; log_output ./openocd.log"
