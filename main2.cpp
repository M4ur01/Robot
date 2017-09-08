#define BOARD RASPBERRY_PI
 
#include "gnublin.h"
#include "PCA9685.h"
 
int main()
{
   gnublin_i2c i2c;
 
   i2c.setAddress(0x40); // set the address of the slave you want to read/write
 
   char buffer[8];
   char RxBuf[8];
 
   buffer[0]=0x00;

   i2c.send(MODE1, buffer, 1);   //send 2 bytes from buffer to register-address 0x1

   i2c.receive(MODE1, RxBuf, 8);  // read from  tegister-address 0x23 3 bytes and store them in RxBuf
 
}
