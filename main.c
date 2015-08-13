#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** args)
{
	if(argc < 2)
	{
		printf("Usage: dp <device> <log file>\n");
		return 1;
	}

	// find out what device to read from
	const char* const dev = args[1];
	printf("Parsing readings from \'%s\'.\n", dev);

	// log file is optional; none specified means default
	char* log_file_name;
	if(argc >= 3) log_file_name = args[2];
	else log_file_name = "depth.log";
	printf("Logging to \'%s\'.\n", log_file_name);

	return 0;
}
