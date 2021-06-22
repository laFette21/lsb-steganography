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
    dibheader.clear();

    header = new char[54];

    for(int i = 0; i < 54; ++i)
        f >> header[i];
    
    size = header[18] * header[22]; // header[18] -> x, header[22] -> y

    data = new char[size];

    for(int i = 0; i < size; ++i)
        f >> data[i];

    char c;

    for(int i = 0; !f.fail(); ++i)
    {
        f >> c;
        dibheader.push_back(c);
    }

    f.close();
}

void Image::encode(const std::string& path)
{
    std::ifstream f(path);

    if(f.fail())
        throw std::runtime_error("Failed to open the TXT file!");
    else if(f.peek() == EOF)
        throw std::runtime_error("This TXT file is an empty file!");

    char c;
    std::string binText = "";

    while(f.get(c))
        binText += std::bitset<8>(c).to_string();

    binText += "00000000";

    f.close();

    if(binText.length() > size)
        throw std::runtime_error("This TXT file is too long to be encoded in this BMP image!");
/*
    for(int i = 0; i < binText.size(); ++i)
        std::cout << binText[i];

    std::cout << std::endl;
*/
    unsigned char mask = 0b11111110;

    for(int i = 0; i < binText.size(); ++i)
    {
        data[i] &= mask;

        if(binText[i] == '1')
            data[i] += 1;
    }

    std::ofstream out("output.bmp");

    for(int i = 0; i < 54; ++i)
        out << header[i];

    for(int i = 0; i < size; ++i)
        out << data[i];

    for(int i = 0; i < dibheader.size(); ++i)
        out << dibheader[i];

    out.close();
}

std::string Image::decode()
{
    char* binText = new char[size];
    char temp;
    std::string res = "";

    for(int i = 0; i < size; ++i)
        binText[i] = (data[i] & 1);

    for(int i = 0; i < size; i += 8)
    {
        temp = 128 * binText[i] + 64 * binText[i + 1] + 32 * binText[i + 2] + 16 * binText[i + 3]
            + 8 * binText[i + 4] + 4 * binText[i + 5] + 2 * binText[i + 6] + binText[i + 7];

        res += temp;

        if(temp == 0)
            break;
    }

    delete[] binText;

    return res;
}