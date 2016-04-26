#!/usr/bin/perl -w

die "Usage: wq.pl <device>\n" if @ARGV < 1;

open(SENSOR, $ARGV[0]) || die "Failed to open $ARGV[0].\n";

while (<SENSOR>) {
	chomp;
	next if ($_ eq "");
	($wl_1, $sig_1, $wl_2, $sig_2) = $_ =~ /00\/00\/00\s+00:00:00\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)/;
	write;
}

format STDOUT_TOP =
 Time (sec.)   Wavelength   Signal   Wavelength   Signal
=========================================================
.

format STDOUT =
 @<<<<<<<<<<   @<<<<<<<<<   @<<<<<   @<<<<<<<<<   @<<<<<
time(), $wl_1, $sig_1, $wl_2, $sig_2
.
