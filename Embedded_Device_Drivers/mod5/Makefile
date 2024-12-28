obj-m  := mod51.o mod52.o
 
ifdef ARCH
  #You can update your Beaglebone path here.
  KSRC = ../linux
else
  KSRC = /lib/modules/$(shell uname -r)/build
endif
 
all:
	make -C $(KSRC)  M=$(shell pwd) modules
 
clean:
	make -C $(KSRC)  M=$(shell pwd) clean
