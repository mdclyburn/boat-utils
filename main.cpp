#include <cassert>
#include <fstream>
#include <iostream>
#include <thread>
using namespace std;

#include "TransducerBuffer.h"

int main(int numberOfArgs, char** args)
{
    if(numberOfArgs < 2)
    {
	cout << "Usage: dp <device>" << endl;
	return 1;
    }

    ifstream file;
    file.open(args[1]);
    cout << "Reading from " << args[1] << "..." << endl;

    TransducerBuffer* buffer = new TransducerBuffer();
    // spin off new thread to asynchronously read from device
    std::thread dev_reader = std::thread([buffer](){
	cout << "Started device reader thread." << endl;
	return;
    });

    dev_reader.join();
 
    return 0;
}
