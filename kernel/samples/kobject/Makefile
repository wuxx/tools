#
#
# obj-$(CONFIG_SAMPLE_KOBJECT) += kobject-example.o kset-example.o

obj-m := kobject-example.o kset-example.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions  \
        *.order *.symvers        

.PHONY: modules modules_install clean
