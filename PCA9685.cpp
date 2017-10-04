#include <iostream>
#include <wiringPiI2C.h>
#include <unistd.h>
#include <stdint.h>
#include "PCA9685.h"

using namespace std;

int position[9];

//Sets up the frequency to 60Hz.
void PCA9685::Set_Freq(int fd){
  uint8_t prescale_val = (25000000/4096/60)-1;
  wiringPiI2CWriteReg8(fd, 0x00, 0x10);          //register mode1, Low power mode Turn off Oscillator
  wiringPiI2CWriteReg8(fd, 0xFE, prescale_val);  //Store the prescale_value(Frequency) into the Prescale register. 
  wiringPiI2CWriteReg8(fd, 0x00, 0x00);
  usleep(500);
  wiringPiI2CWriteReg8(fd, 0x00, 0x80);
  wiringPiI2CWriteReg8(fd, 0x01, 0x04);
//  cout<<"Setting up Freq.... Done" <<endl;
}

//Sets servos position using an array. 
void PCA9685::Set_Pwm(int fd, int degree[]){
//  cout<<"Start: "<<endl;
  for(int a = 0; a <= 9; a++)      //converts degrees to servo position.
  {
    position[a]= degree[a]*2.5;
    //cout<<position[a]<<endl;
  }

  for (int a=0; a< 9; a++)
  {
    wiringPiI2CWriteReg8(fd, 0x06+4*a, 0  &  0xFF);
    wiringPiI2CWriteReg8(fd, 0x07+4*a, 0  >> 8);
    wiringPiI2CWriteReg8(fd, 0x08+4*a,(150 + position[a]) &  0xFF);
    wiringPiI2CWriteReg8(fd, 0x09+4*a,(150 + position[a]) >> 8);
  //  cout << a<< endl;
  }
}

//Setting all servos to zero. Turning them all off. 


void PCA9685::Turn_off(int fd)
{
  for (int a = 0; a<9; a++)
  {
    wiringPiI2CWriteReg8(fd, 0x06+4*a, 0 &  0xFF);
    wiringPiI2CWriteReg8(fd, 0x07+4*a, 0 >> 8);
    wiringPiI2CWriteReg8(fd, 0x08+4*a, 0 &  0xFF);
    wiringPiI2CWriteReg8(fd, 0x09+4*a, 0 >> 8);

  }
}
