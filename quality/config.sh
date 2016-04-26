#!/bin/sh

# Script to configure the WETLabs water quality sensor.

set -u
set -e

if [ "$(id -u)" != "0" ]
then
	printf "Cannot configure without root priveleges. Exiting.\n"
	exit 1
fi

if [ -z $1 ]
then
	printf "Error: no device specified.\n"
	exit 1
fi

baud_rate="19200"

printf "Configuring %s...\n" "${device}"

printf "Stepping to %s baud...\n" "${baud_rate}"
stty -F ${device} ${baud_rate}

printf "Finished configuration.\n"

exit 0
