obj-m := hello.o
#obj-$(CONFIG_USB_SERIAL_GARMIN)         += garmin_gps.o
KERNEL_DIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all:
	make -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules
clean:
	rm *.o *.ko
