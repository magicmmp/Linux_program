ifneq ($(KERNELRELEASE),)

obj-m :=hello_module.o

else

KDIR := /lib/modules/3.10.0-229.el7.x86_64/build
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers
endif
