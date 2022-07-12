#include <iostream>
#include <errno.h>
#include "MatrixLed.h"


using namespace std;

int main()
{
    MatrixLed testI2c = MatrixLed(0x74);

    testI2c.Open();
    testI2c.Init();
    /*__u8 dot[2] = {0,0};
    __u8 dot1[2] = {4,4};
    testI2c.DrawPoint(dot, 243, 81, 0);
    testI2c.DrawPoint(dot1, 50, 100, 200);

    testI2c.ShowImage(); */
    __u8 heart[] = {0x00, 0x66, 0xff, 0xff, 0x7e, 0x3c, 0x18, 0x00};
    testI2c.ShowHex(heart, 255, 0, 0);
}
