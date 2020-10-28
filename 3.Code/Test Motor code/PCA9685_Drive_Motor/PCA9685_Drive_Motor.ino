/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         CarRun.c
* @author       liusen
* @version      V1.0
* @date         2017.07.25
* @brief       CarRun
* @details
* @par History  
*
*/
#include <Wire.h>
#include "./Adafruit_PWMServoDriver.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)


/**
* Function       setup
* @author        liusen
* @date          2017.07.25
* @brief         initialization configure
* @param[in]     void
* @retval        void
* @par History   
*/
void setup()
{
   pwm.begin();
   pwm.setPWMFreq(50);  // Analog servos run at ~60 Hz updates
}

/**
* Function       run
* @author        liusen
* @date          2017.07.25
* @brief         run
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   
*/
void run(int Speed)
{

    pwm.setPWM(8, 0, Speed);
    pwm.setPWM(9, 0, 0);
    pwm.setPWM(11, 0, Speed);
    pwm.setPWM(10, 0, 0);

    pwm.setPWM(0, 0, Speed);
    pwm.setPWM(1, 0, 0);
    pwm.setPWM(3, 0, Speed);
    pwm.setPWM(2, 0, 0);

    pwm.setPWM(12, 0, Speed);
    pwm.setPWM(13, 0, 0);
    pwm.setPWM(15, 0, Speed);
    pwm.setPWM(14, 0, 0);
}

/**
* Function       back
* @author        liusen
* @date          2017.07.25
* @brief         back
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   
*/
void back(int Speed)
{
    pwm.setPWM(8, 0, 0);
    pwm.setPWM(9, 0, Speed);
    pwm.setPWM(11, 0, 0);
    pwm.setPWM(10, 0, Speed);

    pwm.setPWM(0, 0, 0);
    pwm.setPWM(1, 0, Speed);
    pwm.setPWM(3, 0, 0);
    pwm.setPWM(2, 0, Speed);

    pwm.setPWM(12, 0, 0);
    pwm.setPWM(13, 0, Speed);
    pwm.setPWM(15, 0, 0);
    pwm.setPWM(14, 0, Speed);

}

/**
* Function       brake
* @author        liusen
* @date          2017.07.25
* @brief         brake
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   no
*/
void brake()
{

    pwm.setPWM(8, 0, 0);
    pwm.setPWM(9, 0, 0);
    pwm.setPWM(11, 0, 0);
    pwm.setPWM(10, 0, 0);

    pwm.setPWM(0, 0, 0);
    pwm.setPWM(1, 0, 0);
    pwm.setPWM(3, 0, 0);
    pwm.setPWM(2, 0, 0);

    pwm.setPWM(12, 0, 0);
    pwm.setPWM(13, 0, 0);
    pwm.setPWM(15, 0, 0);
    pwm.setPWM(14, 0, 0);
}

/**
* Function       left
* @author        liusen
* @date          2017.07.25
* @brief         turn left(left wheel stop,right wheel advance)
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   
*/
void left(int Speed)
{
    pwm.setPWM(8, 0, Speed);
    pwm.setPWM(9, 0, 0);
    pwm.setPWM(11, 0, 0);
    pwm.setPWM(10, 0, Speed);

    pwm.setPWM(0, 0, Speed);
    pwm.setPWM(1, 0, 0);
    pwm.setPWM(3, 0, 0);
    pwm.setPWM(2, 0, Speed);

    pwm.setPWM(12, 0, Speed);
    pwm.setPWM(13, 0, 0);
    pwm.setPWM(15, 0, 0);
    pwm.setPWM(14, 0, Speed);


}

/**
* Function       right
* @author        liusen
* @date          2017.07.25
* @brief         turn right(left wheel advance,right wheel stop)
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   no
*/
void right(int Speed)
{
    pwm.setPWM(8, 0, 0);
    pwm.setPWM(9, 0, Speed);
    pwm.setPWM(11, 0, Speed);
    pwm.setPWM(10, 0, 0);

    pwm.setPWM(0, 0, 0);
    pwm.setPWM(1, 0, Speed);
    pwm.setPWM(3, 0, Speed);
    pwm.setPWM(2, 0, 0);

    
    pwm.setPWM(12, 0, 0);
    pwm.setPWM(13, 0, Speed);
    pwm.setPWM(15, 0, Speed);
    pwm.setPWM(14, 0, 0);


}

/**
* Function       spin_left
* @author        liusen
* @date          2017.07.25
* @brief         turn left in place(left wheel back,right wheel advance)
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   no
*/
void spin_left(int Speed)
{
    pwm.setPWM(8, 0, Speed);
    pwm.setPWM(9, 0, 0);
    pwm.setPWM(11, 0, 0);
    pwm.setPWM(10, 0, Speed);

    pwm.setPWM(0, 0, Speed);
    pwm.setPWM(1, 0, 0);
    pwm.setPWM(3, 0, 0);
    pwm.setPWM(2, 0, Speed);


    pwm.setPWM(12, 0, Speed);
    pwm.setPWM(13, 0, 0);
    pwm.setPWM(15, 0, 0);
    pwm.setPWM(14, 0, Speed);

}

/**
* Function       spin_right
* @author        liusen
* @date          2017.07.25
* @brief         turn right in place(left wheel adavnce,right wheel back)
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   no
*/
void spin_right(int Speed)
{
    pwm.setPWM(8, 0, 0);
    pwm.setPWM(9, 0, Speed);
    pwm.setPWM(11, 0, Speed);
    pwm.setPWM(10, 0, 0);

    pwm.setPWM(0, 0, 0);
    pwm.setPWM(1, 0, Speed);
    pwm.setPWM(3, 0, Speed);
    pwm.setPWM(2, 0, 0);

    
    pwm.setPWM(12, 0, 0);
    pwm.setPWM(13, 0, Speed);
    pwm.setPWM(15, 0, Speed);
    pwm.setPWM(14, 0, 0);
}


/**
* Function       loop
* @author        liusen
* @date          2017.07.25
* @brief         delay 2s，run 1s，back 1s,turn left 2s,turn right 2s,
*                turn left in place 3s,turn right in place 3s,stop 0.5s
* @param[in]     void
* @retval        void
* @par History   
*/

void loop()
{
  run(1000);  //The speed range is: 0~4095
  delay(2000);
  back(1000);  //The speed range is: 0~4095
  delay(2000);
  spin_left(1000);  //The speed range is: 0~4095
  delay(2000);
  spin_right(1000);  //The speed range is: 0~4095
  delay(2000);
  brake();
  delay(2000);
}


