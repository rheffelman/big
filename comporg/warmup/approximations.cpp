#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	for (int i = 1; i < 100; i++) {
		float g = 1.0f / (1.0f / float(i));
		if (g != i) { 
			cout << setw(3) << i << " yields: " << setprecision(20) << g << endl;
		}
	}
	return 0;
}
