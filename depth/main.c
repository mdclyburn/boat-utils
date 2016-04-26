#include <assert.h>
#include <stdbool.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool running = true;

void interrupt_handler(int signal);

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

	// open device file
	FILE* const transducer = fopen(args[1], "r");
	if(transducer == NULL)
	{
	    printf("Failed to open transducer device file.\n");
	    printf("Please ensure that it is actually \'%s\'.\n", args[1]);
	    return 1;
	}

	// signal handling
	struct sigaction sa_spec;
	sa_spec.sa_handler = interrupt_handler;
	sa_spec.sa_flags = 0;
	sigfillset(&sa_spec.sa_mask);
	assert(sigaction(SIGINT, &sa_spec, 0) == 0);

	// main loop
	// simply read from the sensor and log when necessary
	// add proper response to SIGINT
	char buffer[50];
	while(running)
	{
	    const int read = fscanf(transducer, "%s", buffer);
	    if(read == EOF) continue;

	    // use only depth readings ('$SDDBT...')
	    if(buffer[4] != 'B') continue;

	    // write out reading to log
	    fprintf(log_file, "%lu ", time(NULL));
	    for(unsigned int i = 7; buffer[i] != ','; i++)
		fprintf(log_file, "%c", buffer[i]);
	    fprintf(log_file, "\n");
	}

	printf("\nStopping.\n");
	if(fclose(log_file) == EOF)
		printf("There was a problem properly closing the log file.\n");
	if(fclose(transducer) == EOF)
	    printf("There was a problem properly closing the device file.\n");

	return 0;
}

void interrupt_handler(int signal)
{
    if(signal == SIGTERM || signal == SIGABRT || signal == SIGINT)
	running = false;
    return;
}
