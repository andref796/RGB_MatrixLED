//
// Created by hyde on 19/06/22.
//
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include <i2c/smbus.h>
#include "i2c.h"

bool i2c::Open() {
    if( (_fd = open("/dev/i2c-1",O_RDWR)) < 0 ){
        return false;
    }
    if(ioctl(_fd, I2C_SLAVE, _addr) < 0){
        return false;
    }
    return true;
}

bool i2c::Close() {
    close(_fd);
    return true;
}

bool i2c::Init(){
    i2c_smbus_write_byte_data(_fd, CONFIGURE_CMD_PAGE, FUNCTION_PAGE);
    i2c_smbus_write_byte_data(_fd, SW_SHUT_DOWN_REG, 0x00);
    i2c_smbus_write_byte_data(_fd, PICTURE_DISPLAY_REG, 0x10);
    i2c_smbus_write_byte_data(_fd, STAGGERED_DELAY_REG, ((MSKSTD4 & CONST_STD_GROUP4)|(MSKSTD3 & CONST_STD_GROUP3)|(MSKSTD2 & CONST_STD_GROUP2)|(MSKSTD1 & CONST_STD_GROUP1)));
    i2c_smbus_write_byte_data(_fd, SLEW_RATE_CTL_REG, 0x01);
    i2c_smbus_write_byte_data(_fd, VAF_CTL_REG, (MSKVAF2 | MSKVAF1));
    i2c_smbus_write_byte_data(_fd, VAF_CTL_REG2, (MSKFORCEVAFCTL_DISABLE | MSKFORCEVAFTIME_CONST | MSKVAF3));
    i2c_smbus_write_byte_data(_fd, CURRENT_CTL_REG, (MSKCURRENT_CTL_EN | CONST_CURRENT_STEP_20mA));
    i2c_smbus_write_byte_data(_fd, CONFIGURE_CMD_PAGE, FRAME1_PAGE);
    //PENDING
    i2c_smbus_write_word_data(_fd,)
    i2c_smbus_write_byte_data(_fd, CONFIGURE_CMD_PAGE, FRAME2_PAGE);
    //PENDING
    i2c_smbus_write_byte_data(_fd, CONFIGURE_CMD_PAGE, LED_VAF_PAGE);
    //PENDING
    i2c_smbus_write_byte_data(_fd, CONFIGURE_CMD_PAGE, FUNCTION_PAGE);
    i2c_smbus_write_byte_data(_fd, SW_SHUT_DOWN_REG, 0x01);
    i2c_smbus_write_byte_data(_fd, CONFIGURE_CMD_PAGE, FRAME1_PAGE);
    //PENDING
    //PENDING
    i2c_smbus_write_byte_data(_fd, CONFIGURE_CMD_PAGE, FRAME2_PAGE);
    //PENDING
    //PENDING



    return true;
}

bool i2c::Write() {



    return true;
}

i2c::~i2c() {
    close(_fd);
}
