obj-m  += mod6.o
 
ifdef ARCH
  #You can update your Beaglebone path here.
  KSRC = ../linux
else
  KSRC = /lib/modules/$(shell uname -r)/build
endif

mods:
	make -C $(KSRC)  M=$(shell pwd) modules
 
clean:
	make -C $(KSRC)  M=$(shell pwd) clean
