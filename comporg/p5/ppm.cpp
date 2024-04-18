#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ppm.hpp"

using std::string;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::getline;
using std::bad_alloc;
using std::endl;

/*  Rather than repeating this code 3 times (RGB), make a function out
    of it.
*/
void GetColorValue(ifstream & fin, int max_value, float * value) {
    string line;
    int v;

    getline(fin, line);
    stringstream ss(line);
    ss >> v;
    *value = float(v) / float(max_value);
}

/*  PPM Reading and Writing for an ARM NEON Project

    ARM Neon has a 4 float multiply but not a 3 float multiply. Due to
    this, image data is stored RGBx where x is always 0.

    Further, an integer buffer of the size width * height is allocated
    when the image is loaded. This serves as the destination for the
    conversion to Y as part of this project.
*/

bool PPM::Load(string file_name) {
    bool retval = false;
    ifstream fin(file_name);
    string line;
    long line_number = 1;

    if (fin.is_open()) {
        fin.exceptions(ifstream::failbit | ifstream::badbit);
        try {
            // Magic Number
            getline(fin, magic_number);
            line_number++;
			if (magic_number != "P3")
				throw "Bad magic number: " + magic_number;
			line_number++;

            // Comment
            getline(fin, comment);
            line_number++;
            
            // Width and Height
            getline(fin, line);
            {
                stringstream ss(line);
                ss >> width >> height;
            }
            if (width <= 0 || height <= 0)
                throw "Width or height is <= 0\n";
            data = new float[width * height * 4];
            gray_data = new int[width * height];
            line_number++;
            
            // Max Value
            getline(fin, line);
            {
                stringstream ss(line);
                ss >> max_value;
            }
            line_number++;
            
            // Allocate data
            if (width > 0 && height > 0) {
                long pc = 0; // short for pixel_counter
                float * ptr = data;
				// Load data. Must distinguish between good and bad EOF.
                for (; pc < width * height; pc++) {
                    GetColorValue(fin, max_value, ptr++);
                    line_number++;
                    GetColorValue(fin, max_value, ptr++);
                    line_number++;
					GetColorValue(fin, max_value, ptr++);
					line_number++;
                    *(ptr++) = 0.0;
				}
				retval = true;
			}
		} catch (ifstream::failure e) {
            stringstream ss;
            ss << "ifstream exception: " << e.what() << "\n";
            ss << "input line: " << line_number << "\n";
            ss << "failbit: " << fin.fail() << "\n";
            ss << "eofbit:  " << fin.eof() << "\n";
            ss << "badbit:  " << fin.bad() << "\n";
            throw ss.str();
		} catch (string e) {
            // This catch is currently unneeded. Here for future.
            throw;
        } catch (bad_alloc e) {
            throw "bad_alloc: " + string(e.what()) + "\n";
        }
	} else {
        throw "File: " + file_name + " could not be opened.";
    }
    return retval;
}

bool PPM::Store(string file_name) {
    bool retval = true;
    ofstream fout(file_name);

    if (fout.is_open()) {
        fout << magic_number << endl;
        fout << comment << endl;
        fout << width << " " << height << endl;
        fout << max_value << endl;
        for (int * ptr = gray_data; 
                   ptr < gray_data + width * height;
                   ptr++
        ) {
            fout << *ptr << endl;
			fout << *ptr << endl;
			fout << *ptr << endl;
		}
		fout.close();

    } else {
        throw "File: " + file_name + " could not be opened.";
    }

    return retval;
}

PPM::PPM() {
    width = height = max_value = 0;
    data = nullptr;
    gray_data = nullptr;
}

PPM::~PPM() {
    if (data)
        delete[] data;

    if (gray_data)
        delete[] gray_data;
}

PPM::PPM(const PPM & other) {
    width = other.width;
    height = other.height;
    max_value = other.max_value;
    data = nullptr;

    if (width > 0 && height > 0) {
        data = new float[width * height * 4];
        memcpy(data, other.data, sizeof(float) * width * height * 4);

        gray_data = new int[width * height];
        memcpy(gray_data, other.gray_data, sizeof(int) * width * height);
    }
}

PPM & PPM::operator=(const PPM & other) {
    if (this != &other) {
        delete[] data;
        delete[] gray_data;

        width = other.width;
        height = other.height;
        max_value = other.max_value;
        data = nullptr;
        gray_data = nullptr;
		if (width > 0 && height > 0) {
			data = new float[width * height * 4];
			memcpy(data, other.data, sizeof(float) * width * height * 4);
			gray_data = new int[width * height];
			memcpy(gray_data, other.gray_data, sizeof(int) * width * height);
		}
	}
    return *this;
}
