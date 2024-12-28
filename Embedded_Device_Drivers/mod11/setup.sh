#!/bin/bash

# Setting up GPIOs for 4 LEDs at once

echo 60 > /sys/class/gpio/export
echo 60 > /sys/class/gpio/export
echo 48 > /sys/class/gpio/export
echo 48 > /sys/class/gpio/export
echo 49 > /sys/class/gpio/export
echo 49 > /sys/class/gpio/export
echo 47 > /sys/class/gpio/export
echo 47 > /sys/class/gpio/export

config-pin P9_12 out
config-pin P9_15 out
config-pin P9_23 out
config-pin P8_15 out


