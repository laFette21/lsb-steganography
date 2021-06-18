#include "image.h"

void Image::scan(const std::string& path)
{
    std::ifstream f(path);

    if(f.fail())
        throw std::runtime_error("Failed to open the BMP file!");
    else if(f.peek() == EOF)
        throw std::runtime_error("This BMP file is an empty file!");

    size = 0;
    delete[] header;
    delete[] data;

    char c;

    while(!f.fail())
    {
        f >> c;
        size++;
    }

    size -= 54; // TODO: Not sure if the size here contains the header or not.

    f.clear();
    f.seekg(0, std::ios::beg);

    header = new unsigned char[54];

    for(int i = 0; i < 54; ++i)
        f >> header[i];

    data = new unsigned char[size];

    for(int i = 0; !f.fail(); ++i) // TODO: Check if I could use the size variable instead of !f.fail()
        f >> data[i];

    f.close();
}