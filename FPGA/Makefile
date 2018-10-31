
FPGA_BITSTREAM := $(shell ls *bin)

DTC := dtc -I dts -O dtb -o
DTSOURCE := $(shell ls *dts)
DTBLOB   := $(DTSOURCE:%.dts=%.dtbo)

setup: OVERLAYS

OVERLAYSPATH := /config/device-tree/overlays/uio-irq

OVERLAYS:$(DTBLOB)
	@cp -f $(FPGA_BITSTREAM) /lib/firmware/$(FPGA_BITSTREAM)
	@if [ -e $(OVERLAYSPATH) ];then rmdir $(OVERLAYSPATH); fi
	@mkdir $(OVERLAYSPATH)
	@cp $(DTBLOB) $(OVERLAYSPATH)/dtbo
	@rm $(DTBLOB)
	@echo 1 > $(OVERLAYSPATH)/status

$(DTBLOB): $(DTSOURCE)
	@$(DTC) $@ $<

.PHONY: clean
clean:
	@rm -f $(DTBLOB) $(OBJS)
	@if [ -e $(OVERLAYSPATH) ];then echo 0 > $(OVERLAYSPATH)/status; fi
	@if [ -e $(OVERLAYSPATH) ];then rmdir $(OVERLAYSPATH); fi

