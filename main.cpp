#include <iostream>
#include "image.h"

using namespace std;

int main()
{
    try
    {
        Image img;
        Image eImg("eimg.bmp");
        Image neImg("neimg.bmp");
    }
    catch(const std::exception& e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}