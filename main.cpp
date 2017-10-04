#include <string.h>
#include <iostream>
#include <wiringPiI2C.h>
//#include <unistd.h>
//#include <stdint.h>
#include "PCA9685.h"
#include <math.h>
using namespace std;

int stand[9]={20,100,90,20,100,90,20,100,90};
int value = 0;
int forward[9];
int fd = wiringPiI2CSetup(0x40);
int speed = 1000000;
PCA9685 PWM;


void walk()
{ 
  memcpy(forward, stand, sizeof(stand));
  cout<< "Enter a number: " <<endl;
  int user; 
  cin >> user;
  //1
  //forward[2] = 115;
  forward[1] = 150;
  forward[7] = 100;
  forward[4] = user;
  PWM.Set_Pwm(fd, forward);
  usleep(speed);
  //2
  //forward[2] = 140;
  forward[1] = 100;
  forward[7] = 100;
  forward[4] = 100;
  PWM.Set_Pwm(fd, forward);
  usleep(speed);
  //3
  //forward[2] = 120;
  PWM.Set_Pwm(fd, forward);
  usleep(speed);
  //4
  //forward[2] = 75;
  PWM.Set_Pwm(fd, forward);
  usleep(speed);
  //6
  //forward[2] = 30;
  forward[4] = 100;
  forward[7] = 120;
  PWM.Set_Pwm(fd, forward);
  usleep(speed);
  //7
  //forward[2] = 75;
  PWM.Set_Pwm(fd, forward);
  usleep(speed);

}



int main()
{
  //int fd;
  //int stand[9]={20,120,90,20,120,90,20,120,90}; 
  int value = 0;
    
  //fd = wiringPiI2CSetup(0x40);
  //PCA9685 PWM;
  PWM.Set_Freq(fd);
  
  while(value <=2)
  {
    PWM.Set_Pwm(fd, stand);
    sleep(1);
    walk();
    value++;
  }
  PWM.Turn_off(fd);
}
