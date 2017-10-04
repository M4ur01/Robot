#ifndef _PCA9685_H
#define _PCA9685_H
#include <iostream>
#include <wiringPiI2C.h>
#include <unistd.h>
#include <stdint.h>

//Registers Definitions



//! Main class  for PCA9685 chip

class PCA9685{
public:
  void Set_Freq(int fd);
  void Set_Pwm(int fd, int degree[]);
  void Turn_off(int fd);
};
#endif
