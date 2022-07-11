#include <iostream>
#include <errno.h>
#include "i2c.h"


using namespace std;

int main()
{
    i2c testI2c = i2c(0x74);

    testI2c.Open();
    testI2c.Init();
    __u8 dot[2] = {5,5};
    __u8 dot1[2] = {4,4};
    testI2c.DrawPoint(dot, 243, 81, 0);
    testI2c.DrawPoint(dot1, 255, 0, 0);

    testI2c.ShowImage();

}
