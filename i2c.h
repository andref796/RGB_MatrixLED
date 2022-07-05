//
// Created by hyde on 19/06/22.
//

#ifndef RGB_I2C_H
#define RGB_I2C_H

#include <linux/i2c-dev.h>
#include <i2c/smbus.h>

const __u8 CONFIGURE_CMD_PAGE = 0xFD;
const __u8 FRAME1_PAGE = 0x00;
const __u8 FRAME2_PAGE = 0x01;
const __u8 FUNCTION_PAGE = 0x0B;
const __u8 LED_VAF_PAGE = 0x0D;

const __u8 CONFIGURATION_REG = 0x00;
const __u8 PICTURE_DISPLAY_REG = 0x01;
const __u8 DISPLAY_OPTION_REG = 0x05;
const __u8 BREATH_CTL_REG = 0x08;
const __u8 BREATH_CTL_REG2 = 0x09;
const __u8 SW_SHUT_DOWN_REG = 0x0A;

const __u8 AUDIO_GAIN_CTL_REG = 0x0B;
const __u8 STAGGERED_DELAY_REG = 0x0D;
const __u8 SLEW_RATE_CTL_REG = 0x0E;
const __u8 CURRENT_CTL_REG = 0x0F;
const __u8 VAF_CTL_REG = 0x14;
const __u8 VAF_CTL_REG2 = 0x15;

const __u8 MSKSTD1 = (0x03<<0);
const __u8 MSKSTD2 = (0x03<<2);
const __u8 MSKSTD3 = (0x03<<4);
const __u8 MSKSTD4 = (0x03<<6);
const __u8 CONST_STD_GROUP1 = 0x00;
const __u8 CONST_STD_GROUP2 = 0x55;
const __u8 CONST_STD_GROUP3 = 0xAA;
const __u8 CONST_STD_GROUP4 = 0xFF;

const __u8 MSKVAF1 = (0x04<<0);
const __u8 MSKVAF2 = (0x04<<4);
const __u8 MSKVAF3 = (0x04<<0);
const __u8 MSKFORCEVAFTIME_CONST= (0x00<<3);
const __u8 MSKFORCEVAFCTL_ALWAYSON = (0x00<<6);
const __u8 MSKFORCEVAFCTL_DISABLE = (0x02<<6);
const __u8 MSKCURRENT_CTL_EN = (0x01<<7);
const __u8 CONST_CURRENT_STEP_20mA = (0x19<<0);
const __u8 mskBLINK_FRAME_300 = (0x00<<6);
const __u8 mskBLINK_EN = (0x01<<3);
const __u8 mskBLINK_DIS = (0x00<<3);
const __u8 mskBLINK_PERIOD_TIME_CONST = (0x07<<0);



class i2c {
public:
    i2c(int &addr): _addr(addr);
    ~i2c();
    bool Open();
    bool Close();
    bool Init();
    bool Write();
    bool Read();

private:
    int _fd = 0;
    int _addr = 0;
};


#endif //RGB_I2C_H
