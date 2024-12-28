#!/bin/bash

MODULE_PATH="./mod82.ko"

echo "inserting module $MODULE_PATH..."
sudo insmod $MODULE_PATH

if [$? -eq 0]; then
	echo "module inserted!"
        for i in {1..10}
        do
        	sudo dmesg | tail
	   	sudo su
		cd /dev
		cat cdac_dev
		dmesg | tail 
		echo 2 > cdac_dev
		dmesg | tail
	done
else
	sudo rmmod $MODULE_PATH
