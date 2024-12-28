#!/bin/bash

# convert a decimal to LED binary lights!

set -x

echo "Usage: $0 <decimal_number < 16>"

num=${1:-15}

# MSB -> LSB
# 47 49 48 60
state60=$(( (num & 0x01) > 0 ))
state48=$(( (num & 0x02) > 0 ))
state49=$(( (num & 0x04) > 0 ))
state47=$(( (num & 0x08) > 0 ))

echo $state47 > /sys/class/gpio/gpio47/value
echo $state49 > /sys/class/gpio/gpio49/value
echo $state48 > /sys/class/gpio/gpio48/value
echo $state60 > /sys/class/gpio/gpio60/value

