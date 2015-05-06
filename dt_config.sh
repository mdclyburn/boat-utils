#!/bin/sh

# Script to configure the RadarSonics depth transducer.

if test "$(id -u)" != "0"
then
	printf "Cannot configure without root priveleges. Exiting.\n"
	exit 1
fi

if test -z $1
then
	printf "Error: no device specified.\n"
	exit 1
fi

device=$1
baud="4800"

printf "Configuring ${device}...\n"

# Communicates at 4800 baud, one stop bit, no parity.
printf "Stepping to $baud baud...\n"
stty -F $device $baud

printf "Disabling the stop bit...\n"
stty -F $device -cstopb

printf "Setting to use a single parity bit...\n"
stty -F $device -parenb

printf "Finished configuration.\n"

exit 0
