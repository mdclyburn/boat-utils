#!/usr/bin/perl -w

use Getopt::Std;

# Switches
#
# -s      - do not print data
# -o file - write raw data to specified file
getopts('hso:');

if(defined $opt_h) {
	print "Usage: wq.pl [-hs] [-o file] device\n\n";
	print "Options\n\n" .
		"  h - print help information and exit\n" .
		"  s - suppress formatted output\n\n" .
		"  o file - send raw, extracted data to the specified file";
	exit 0;
}

$SIG{INT} = $SIG{TERM} = sub {
	if(defined $opt_o) {
		close(LOG) || warn "Failed to close log file. Data may be lost.\n";
	}

	print "Exiting...\n";
	exit 0;
};

open(SENSOR, $ARGV[0]) || die "Failed to open $ARGV[0].\n";

if(defined $opt_o) {
	open(LOG, ">>", $opt_o) || die "Failed to open file to log to: $opt_o.\n";
}

while (<SENSOR>) {
	chomp;
	next if ($_ eq "");
	($wl_1, $sig_1, $wl_2, $sig_2) = $_ =~ /00\/00\/00\s+00:00:00\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)/;

	write if (!defined $opt_s);
	print LOG time() . " $wl_1 $sig_1 $wl_2 $sig_2\n" if (defined $opt_o);
}

format STDOUT_TOP =
 Time (sec.)   Wavelength   Signal   Wavelength   Signal
=========================================================
.

format STDOUT =
 @<<<<<<<<<<   @<<<<<<<<<   @<<<<<   @<<<<<<<<<   @<<<<<
time(), $wl_1, $sig_1, $wl_2, $sig_2
.
