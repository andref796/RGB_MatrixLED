//
// Created by hyde on 19/06/22.
//
#include <unistd.h>				//Needed for I2C port
#include <iostream>
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
extern "C" {
    #include <linux/i2c-dev.h>		//Needed for I2C port
    #include <i2c/smbus.h>
}
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
    //std::cout << "Configure_Cmd_Page: " <<  i2c_smbus_read_byte_data(_fd,CONFIGURE_CMD_PAGE) << std::endl;
    i2c_smbus_write_byte_data(_fd, SW_SHUT_DOWN_REG, 0x0);
    i2c_smbus_write_byte_data(_fd, PICTURE_DISPLAY_REG, 0x10);
    i2c_smbus_write_byte_data(_fd, STAGGERED_DELAY_REG, ((MSKSTD4 & CONST_STD_GROUP4)|(MSKSTD3 & CONST_STD_GROUP3)|(MSKSTD2 & CONST_STD_GROUP2)|(MSKSTD1 & CONST_STD_GROUP1)));
    i2c_smbus_write_byte_data(_fd, SLEW_RATE_CTL_REG, 0x1);
    i2c_smbus_write_byte_data(_fd, VAF_CTL_REG, (MSKVAF2 | MSKVAF1));
    i2c_smbus_write_byte_data(_fd, VAF_CTL_REG2, (MSKFORCEVAFCTL_DISABLE | MSKFORCEVAFTIME_CONST | MSKVAF3));
    i2c_smbus_write_byte_data(_fd, CURRENT_CTL_REG, (MSKCURRENT_CTL_EN | CONST_CURRENT_STEP_20mA));
    i2c_smbus_write_byte_data(_fd, CONFIGURE_CMD_PAGE, FRAME1_PAGE);
    
    for (__u8 i = 0x00; i < 0xB3 ; i++) {
        i2c_smbus_write_byte_data(_fd, i, 0x00);
    }

    i2c_smbus_write_byte_data(_fd, CONFIGURE_CMD_PAGE, FRAME2_PAGE);

    for (__u8 i = 0x00; i < 0xB3 ; i++) {
        i2c_smbus_write_byte_data(_fd, i, 0x00);
    }

    i2c_smbus_write_byte_data(_fd, CONFIGURE_CMD_PAGE, LED_VAF_PAGE);

    for (__u8 i = 0x00; i < 0x40 ; ++i) {
        i2c_smbus_write_byte_data(_fd, i, Type3Vaf[i]);
    }

    i2c_smbus_write_byte_data(_fd, CONFIGURE_CMD_PAGE, FUNCTION_PAGE);
    i2c_smbus_write_byte_data(_fd, SW_SHUT_DOWN_REG, 0x1);
    i2c_smbus_write_byte_data(_fd, CONFIGURE_CMD_PAGE, FRAME1_PAGE);
    for (__u8 i = 0x00; i < 0x10 ; ++i) {
        i2c_smbus_write_byte_data(_fd, i, 0xFF);
    }
    for (__u8 i = 0x20; i < 0x80 ; ++i) {
        i2c_smbus_write_byte_data(_fd, i, 0x00);
    }
    i2c_smbus_write_byte_data(_fd, CONFIGURE_CMD_PAGE, FRAME2_PAGE);
    for (__u8 i = 0x00; i < 0x10 ; ++i) {
        i2c_smbus_write_byte_data(_fd, i, 0xFF);
    }
    for (__u8 i = 0x20; i < 0x80 ; ++i) {
        i2c_smbus_write_byte_data(_fd, i, 0x00);
    }
    return true;
}

bool i2c::ShowImage() {
    __u8 revert_image[3][64] = {};
    
    for(int i = 0; i<64;i++){
      revert_image[0][i] = rgb_test[i][1];
      revert_image[1][i] = rgb_test[i][0];
      revert_image[2][i] = rgb_test[i][2];
    }


    __u8 reg = 0x20;
    __u8 empty = 0;
    __u8 pos = 0;

    for (int i = 0; i < 15; i++)
    {
        if (i == 0){
            i2c_smbus_write_byte_data(_fd, CONFIGURE_CMD_PAGE, FRAME1_PAGE);
        }
        else if (reg == 0x20)
        {
            i2c_smbus_write_byte_data(_fd, CONFIGURE_CMD_PAGE, FRAME2_PAGE);
        }
    

    __u8 color = i % 3;

    __u8 pos_data = pos * 14;
      int data_left = 64-1 - (pos+1) * 14;

        __u8 data_lenth = 0;
        if (data_left > 0) {
          data_lenth = 14;
        }
        else{
          data_lenth = 8;
          pos_data = 56;
        }
        __u8 data[data_lenth] = {};
      for(int i = 0; i < data_lenth;i++){
        // data[i] = revert_image_data[pos_data+i];
        data[i] = revert_image[color][pos_data+i];

      }
        __u8 insert_data[data_lenth+2] = {0};
        for (int i=0; i<(data_lenth+2); i++)
        {
          if (i < empty){           
            insert_data[i] = data[i];
          }
          else if (i==empty || i== (empty+1)){
            insert_data[i] = 0;
            }
          
          else if (i > (empty+1)){
            insert_data[i] = data[i-2];
          }
    }
         if (data_lenth == 8){
          insert_data[8] = 0;
          insert_data[9] = 0;
          
         }
        
//        data.insert(empty,0)  //写入的数据补0
//        data.insert(empty + 1, 0)
//        bus._i2c_write_i2c_block_data(addr, reg, data)
      //  for(int i=0;i<data_lenth+2;i++){
      //    Serial.print(insert_data[i]);
      //    Serial.print(" ");
      //  }
      //  Serial.println(i);
        i2c_smbus_write_i2c_block_data(_fd, reg, data_lenth, insert_data);
        if (color == 2){
            empty += 3;
            pos += 1;
        }
        reg += 0x10;
        if (reg == 0xA0){
//          Serial.println("reg == 0xA0");
            reg = 0x20;
        }
        
//        Wire.endTransmission();    // stop transmitting

    
    
    }

    return true;
}

bool i2c::DrawPoint(__u8 coor[2],__u8 R,__u8 G,__u8 B){
    rgb_test[8*coor[1]+coor[0]][0] = B;
    rgb_test[8*coor[1]+coor[0]][1] = G;
    rgb_test[8*coor[1]+coor[0]][2] = R;
    return true;
}

i2c::~i2c() {
    close(_fd);
}
