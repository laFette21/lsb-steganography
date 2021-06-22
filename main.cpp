#include <iostream>
#include "image.h"

using namespace std;

int main()
{
    try
    {
        //Image img;
        //Image eImg("img/eimg.bmp");
        Image neImg("img/neimg.bmp");

        neImg.encode("text.txt");

        cout << neImg.decode() << endl;
    }
    catch(const std::exception& e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}