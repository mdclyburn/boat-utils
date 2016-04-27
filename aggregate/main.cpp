#include <cassert>
#include <cstdint>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		cout << "Usage: agg <depth log> <quality log>\n\n";
		return 1;
	}

	ifstream depth_log, quality_log;
	depth_log.open(argv[1]);
	quality_log.open(argv[2]);
	assert(depth_log.is_open() && quality_log.is_open());

	// Gotta see which log starts earlier.
	uint64_t time_depth, time_quality;
	depth_log >> time_depth;
	quality_log >> time_quality;

	if(time_depth < time_quality)
	{
		cout << "Fast-forwarding depth log to earliest quality log entry..." << endl;
		while(time_depth < time_quality)
		{
			double dm, df;
			depth_log >> dm;
			depth_log >> df;
			depth_log >> time_depth;
			cout << time_depth << " approaching " << time_quality << " (still " << time_quality - time_depth << "s behind...)" << endl;
			if(time_depth >= time_quality)
				break;
		}
	}
	else if(time_depth > time_quality)
	{
		cout << "Fast-forwarding quality log to earliest depth log entry..." << endl;
		while(time_quality < time_depth)
		{
			uint16_t a, b, c, d;
			quality_log >> a;
			quality_log >> b;
			quality_log >> c;
			quality_log >> d;
			cout << time_depth << " approaching " << time_quality << " (still " << time_quality - time_depth << "s behind...)" << endl;
			if(time_quality > time_depth)
				break;
		}
	}

	while(depth_log && quality_log)
	{
		double depth_ft, depth_m;
		uint32_t w1, w2, s1, s2;

		// Print out data from matching times.
		if(time_depth == time_quality)
		{
			depth_log >> depth_ft >> depth_m >> time_depth;
			cout << time_depth << " " << depth_ft << " " << depth_m;

			quality_log >> w1 >> s1 >> w2 >> s2 >> time_quality;
			cout << w1 << " " << s1 << " " << w2 << " " << s2 << endl;
		}
		else if(time_depth < time_quality)
		{
			depth_log >> depth_ft >> depth_m >> time_depth;
		}
		else
		{
			quality_log >> w1 >> s1 >> w2 >> s2 >> time_quality;
		}
	}

	return 0;
}
