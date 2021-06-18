#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>
#include <string>

class Image
{
    unsigned size;
    unsigned char* header;
    unsigned char* data;

public:
    Image(): size(0), header(nullptr), data(nullptr) {}
    Image(const std::string& path): size(0), header(nullptr), data(nullptr) { scan(path); }
    ~Image() { delete[] header; delete[] data; }

    void scan(const std::string& path);
};

#endif // IMAGE_H