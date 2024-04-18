#pragma once
#include <string>

struct PPM {
    std::string magic_number;
    std::string source_file_name;
    std::string comment;
    int width, height;
    int max_value;
    float * data;
    int   * gray_data;

    bool Load(std::string file_name);
    bool Store(std::string file_name);
    PPM();
    PPM(const PPM & other);
    PPM & operator=(const PPM & other);
    ~PPM();
};
