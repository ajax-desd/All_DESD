#!/bin/bash

## Shell script for controlling LEDs in 4-circuit ladder
## On a root shell:
## ./ctrl.sh 1 for on
## ./ctrl.sh 0 for off

set -x 

gpios=(47 48 49 60)
state=${1:-0}

echo "Usage: $0 0/1 for off/on"

for i in "${gpios[@]}"
do
	echo $state > /sys/class/gpio/gpio$i/value	
done
