#include <iostream>
#include <errno.h>
#include "i2c.h"


using namespace std;

int main()
{
    i2c testI2c = i2c(0x74);

    testI2c.Open();
    testI2c.Init();
    __u8 dot[2] = {3,1};
    testI2c.DrawPoint(dot, 255, 255, 0);

}