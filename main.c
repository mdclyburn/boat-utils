#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

	// open log file
	// always append, losing data is not fun
	FILE* const log_file = fopen(log_file_name, "a");
	if(log_file == NULL)
	{
		printf("Failed to open \'%s\'.", log_file_name);
		return 1;
	}
	else
		fprintf(log_file, "NEW SESSION @ %lu\n", time(NULL));

	// main loop
	// simply read from the sensor and log when necessary
	// add proper response to SIGINT
//	for(;;)
//	{
//	}

	if(fclose(log_file) == EOF)
		printf("There was a problem properly closing the log file.\n");

	return 0;
}
