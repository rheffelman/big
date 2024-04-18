#include <arm_neon.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <sys/time.h>

#include "ppm.hpp"

extern "C" void ConvertToYNeon(PPM &);
extern "C" void ConvertToYCPU(PPM &);

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::fixed;
using std::setw;
using std::left;

int loops = 1024;

void DoConversion(PPM & ppm, void (* func)(PPM &), string label) {
	timeval start;
	timeval end;
	timeval elapsed;

	gettimeofday(&start, NULL);
	for (int counter = 0; counter < loops; counter++) {
		(*func)(ppm);
	}
	gettimeofday(&end, NULL);
	timersub(&end, &start, &elapsed);
	float e = float((long int)elapsed.tv_sec) + float((long int)elapsed.tv_usec) / 1000000.0;
	cout << left << setw(4) << label << " " << fixed << e / float(loops);
    cout << " per invocation." << endl;
}


int main(int argc, char ** argv) {
    int retval = 0;
	int loops = 1024;
	PPM ppm;

	if (argc != 2) {
		cerr << "Argument must be name of PPM file to load\n";
		retval = 1;
	} else {
		try {
			ppm.Load(string(argv[1]));
			cout << "File:      " << argv[1] << " loaded.\n";
			cout << "Size:      " << ppm.width << " x " << ppm.height << "\n";
			cout << "Max value: " << ppm.max_value << endl;
            DoConversion(ppm, ConvertToYCPU, "CPU");
            ppm.Store("CPU.ppm");
            DoConversion(ppm, ConvertToYNeon, "Neon");
			ppm.Store("NEON.ppm");
		} catch (string e) {
			cerr << "File: " << argv[1] << " load failed.\n";
			cerr << e << "\n";
			retval = 1;
		}
	}
	return retval;
}