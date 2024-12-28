obj-m  +=q2.o
 
ifdef ARCH
  
  KSRC = ../linux
else
  KSRC = /lib/modules/$(shell uname -r)/build
endif

mods:
	make -C $(KSRC)  M=$(shell pwd) modules
 
clean:
	make -C $(KSRC)  M=$(shell pwd) clean
