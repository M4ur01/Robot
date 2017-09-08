#include <unistd.h>    //Needed for I2C port
#include <fcntl.h>     //Needed for I2C port
#include <sys/ioctl.h> //Needed for I2C port
#include <linux/i2c-dev.h> //Needed for I2C port
#include <iostream>
#include "PCA9685.h" //PCA9685
#include <stdint.h>

using namespace std;

unsigned char buffer[60] = {0};

    
void Send(char add1,char  add2,int file_i2c)
{
  //----- write -----

  buffer[0] = add1;
  buffer[1] = add2;
  int length = 2;                 //<<< Number of bytes to write
//  cout<<"Buffer#1: "<<int(buffer[0])<<" Buffer#2: "<<int(buffer[1])<<endl;
  if (write(file_i2c, buffer, length) != length)              //write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
  {
    /* ERROR HANDLING: i2c transaction failed */
    cout<<"Failed to write to the i2c bus.\n";
  }
  //cout<<file_i2c<<endl;

}

void SetFreq(int freq,int file_i2c)
{
  uint8_t prescale_val = (CLOCK_FREQ / 4096 / freq)  - 1;
  Send(MODE1,0x10,file_i2c); //sleep
  Send(PRE_SCALE,prescale_val,file_i2c);
  Send(MODE1,0x80,file_i2c);
  Send(MODE2,0x04,file_i2c);
  //cout<<file_i2c<<endl;
}

void SetPWM(uint8_t led, int on_value, int off_value,int file_i2c)
{
  cout<<"Start"<<endl;
  Send(LED0_ON_L + LED_MULTIPLYER * (led - 1), on_value & 0xFF,file_i2c);
  Send(LED0_ON_H + LED_MULTIPLYER * (led - 1), on_value >> 8,file_i2c);
  Send(LED0_OFF_L + LED_MULTIPLYER * (led - 1), off_value & 0xFF,file_i2c);
  Send(LED0_OFF_H + LED_MULTIPLYER * (led - 1), off_value >> 8,file_i2c);
  //cout<<file_i2c<<endl;
}


int main()
{
  int file_i2c;
  int length;

  //----- OPEN THE I2C BUS -----
  char *filename = (char*)"/dev/i2c-1";
  if ((file_i2c = open(filename, O_RDWR)) <0)
  {
    //ERROR HANDLING: you can check errno to see what went wrong
    cout<<"Failed to open the i2c bus"<<endl;
  }

  int addr = 0x40;          //<<<<<The I2C address of the slave

  if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
  {
    cout<<"Failed to acquire bus access and/or talk to slave.\n";
    //ERROR HANDLING; you can check errno to see what went wrong
  }

    //----Set mode to 0----//
  Send(MODE1,0b00010000,file_i2c);
  Send(MODE1,0b00000000,file_i2c);
  usleep(5000);
  Send(MODE2,0b00000100,file_i2c);


  //----Set Freq to 60----//
  SetFreq(60,file_i2c);

  for(int a =0; a<=500; a++)
  {
    SetPWM(0,0,a,file_i2c);
    usleep(10000);
    cout<<150+a<<endl;
  }

}