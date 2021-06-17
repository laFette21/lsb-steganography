#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>
#include <string>

class Image
{
    unsigned size;
    unsigned char header[54];
    unsigned char* data;

public:
    Image(): data(nullptr) {}
    Image(const std::string& path);
    ~Image() { delete[] data; }
};

#endif // IMAGE_H