#!/bin/sh

if [ ! -f "/proc/cpuinfo" ]; then
        echo "WARNING: file not found: /proc/cpuinfo"
        exit 1
fi

str=$(grep -oP "^Revision\s*: [\da-f]*\K[\da-f]{4}$" /proc/cpuinfo)
processor=0x"$(echo "$(echo $str | cut -c 1)" | tr "[:lower:]" "[:upper:]")"
processor_decimal=$(printf "%d" $processor)
type="0x$(echo "$(echo $str | cut -c 2-3)" | tr "[:lower:]" "[:upper:]")"

if [ $processor_decimal -eq 0 ]; then
        peripheral_base="0x20000000"
elif [ $processor_decimal -ge 1 ] && [ $processor_decimal -le 2 ]; then
        peripheral_base="0x3F000000"
elif [ $processor_decimal -eq 3 ]; then
        peripheral_base="0xFE000000"
else
        echo "WARNING: processor not known: $processor"
        exit 1
fi

printf "$peripheral_base\n$type\n$processor\n"

exit 0
