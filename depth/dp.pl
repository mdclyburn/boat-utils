#!/usr/bin/perl -w

use Getopt::Std;

# Switches
#
# -s        - Silences pretty output to the terminal.
# -o <file> - Send raw data to the file specified.
#
getopts('so:');

if(defined $opt_o) {
	open(LOGFILE, ">>", $opt_o) || die "Failed to open file to log to: $opt_o.\n";
}

open(TRANSDUCER, "<", $ARGV[-1]) || die "Failed to open $ARGV[0].\n";

# Define interrupt signal handler.
$SIG{INT} = $SIG{TERM} = sub {
	if(defined $opt_o) {
		close(LOGFILE) || warn "Failed to close log file.\n";
	}

	print "Exiting...\n";
	exit 0;
};

$depth_ft = 0;
$depth_m = 0;

while (<TRANSDUCER>) {
	if (/^\$SDDBT/) {
		# Capture data from the device.
		($depth_ft) = $_ =~ /(\d+\.\d),f/;
		($depth_m)  = $_ =~ /(\d+\.\d),M/;
		$depth_ft = $depth_m = "-" if ! defined $depth_ft;

		# Send data to terminal if we're not suppressing output.
		if(!defined $opt_s) {
			write;
		}

		# Write raw data to the specified file if desired.
		if(defined $opt_o) {
			print LOGFILE time() . " $depth_ft $depth_m\n";
		}
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
