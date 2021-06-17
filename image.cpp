#include "image.h"

Image::Image(const std::string& path)
{
    std::ifstream f(path);

    if(f.fail())
        throw std::runtime_error("Failed to open the BMP file!");
    else if(f.peek() == EOF)
        throw std::runtime_error("This BMP file is an empty file!");

    char c;

    while(!f.fail())
    {
        f >> c;
        size++;
    }

    size -= 54; // TODO: Not sure if the size here contains the header or not.

    f.clear();
    f.seekg(0, std::ios::beg);

    for(int i = 0; i < 54; ++i)
        f >> header[i];

    data = new unsigned char[size];

    for(int i = 0; !f.fail(); ++i)
        f >> data[i];

    f.close();
}