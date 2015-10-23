#!/usr/bin/perl -w

die "Usage: dp.pl <device>\n" if @ARGV < 1;

open(TRANSDUCER, "<", $ARGV[0]) || die "Failed to open $ARGV[0].\n";

$depth_ft = 0;
$depth_m = 0;

while (<TRANSDUCER>) {
	if (/^\$SDDBT/) {
		($depth_ft) = $_ =~ /(\d+\.\d),f/;
		($depth_m)  = $_ =~ /(\d+\.\d),M/;
		write;
	}
}

format STDOUT_TOP =
 Time (seconds)    Depth (ft.)  Depth (m.)
===========================================
.

format STDOUT =
 @<<<<<<<<<<<<     @<<<<<<<<<<  @<<<<<<<<<
time(), $depth_ft, $depth_m
.

exit;
