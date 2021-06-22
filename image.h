#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>
#include <string>
#include <vector>
#include <bitset>

class Image
{
    unsigned size;
    char* header;
    char* data;
    std::vector<char> dibheader;

public:
    Image(): size(0), header(nullptr), data(nullptr) {}
    Image(const std::string& path): size(0), header(nullptr), data(nullptr) { scan(path); }
    ~Image() { delete[] header; delete[] data; }

    void scan(const std::string& path);
    void encode(const std::string& path);
    std::string decode();
};

#endif // IMAGE_H