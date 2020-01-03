#!/bin/sh

if [ ! -f "/proc/cpuinfo" ]; then
        echo "WARNING: file not found: /proc/cpuinfo"
        exit 1
fi

str=$(grep -oP "^Revision\s*: [\da-f]*\K[\da-f]{4}$" /proc/cpuinfo)
processor=0x"$(echo "$(echo $str | cut -c 1)" | tr "[:lower:]" "[:upper:]")"
type="0x$(echo "$(echo $str | cut -c 2-3)" | tr "[:lower:]" "[:upper:]")"

printf "$type\n$processor\n"

exit 0
