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
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

#define run_car     '1'
#define back_car    '2'
#define left_car    '3'
#define right_car   '4'
#define stop_car    '0'

#define ON 1           
#define OFF 0          

enum {
  enSTOP = 0,
  enRUN,
  enBACK,
  enLEFT,
  enRIGHT,
  enTLEFT,
  enTRIGHT
} enCarState;

int CarSpeedControl = 2000;

int IncomingByte = 0;            //Received data byte
String InputString = "";         //It is used to store received content
boolean NewLineReceived = false; //The previous data end flag
boolean StartBit  = false;       //Protocol start flag
String ReturnTemp = "";          //Store return value

int g_CarState = enSTOP;         
int g_modeSelect = 0;  //0 default;  1:IR 2:tracking 3:ultrasonic  4:colorLED 5: light-seeking 6: Infrared follow
boolean g_motor = false;

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

  Serial.begin(9600);

//  for(int i = 2; i < 14; i++)
//  {
//    pinMode(i, OUTPUT);
//  }
  
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



void SetServoPos(int num, int value)
{
    // 50hz: 20,000 us
    long us = (value * 1800 / 180 + 600); // 0.6 ~ 2.4
    long pwmvalue = us * 4096 / 20000;
    pwm.setPWM(num, 0, pwmvalue);
}
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  //Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  //Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000;
  pulse /= pulselength;
  //Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

/**
* Function       serial_data_parse
* @author        liusen
* @date          2017.07.25
* @brief         The serial port data is parsed and the corresponding action is specified
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void serial_data_parse()
{

  //Analyze the general protocol instruction sent by the upper computer and perform corresponding actions
  //$4WD,PTZ180#
  if (InputString.indexOf("4WD") > 0)
  {
      //Analyze the control instruction from the upper servo and execute the steering gear rotation
      //for example:$4WD,PTZ180# servo turn 180°
      if (InputString.indexOf("PTZ") > 0)
      {
        int m_kp;
        int i = InputString.indexOf("PTZ"); 
        int ii = InputString.indexOf("#", i);
        if (ii > i)
        {
          String m_skp = InputString.substring(i + 3, ii);
          int m_kp = m_skp.toInt();        
          //Serial.print("PTZ:");
          //Serial.println(m_kp);
          
          SetServoPos(7, 180 - m_kp);
          //150 600   0-180
          //m_kp = map(180 - m_kp, 0, 180, SERVOMIN, SERVOMAX);
          // Serial.println(m_kp);
          //setServoPulse(7, SERVOMIN);
          
          InputString = "";                     //Clear serial port data
          NewLineReceived = false;
          return;
        }
      }
  }
  //如:$1,0,0,0,0,0,0,0,0,0#     run
  if (InputString.indexOf("4WD") == -1)
  {
    //小车原地左旋右旋判断
    if (InputString[3] == '1')      //turn left in place
    {
      g_CarState = enTLEFT;
    }
    else if (InputString[3] == '2') //turn right in place
    {
      g_CarState = enTRIGHT;
    }
    else
    {
      g_CarState = enSTOP;
    }
    
    if (InputString[9] == '1') //The servo rotates to 180°
    {
         SetServoPos(7, 180);
    }
    
    if (InputString[9] == '2') //The servo rotates to 0°
    {
       SetServoPos(7, 0);
    }
    
    
    if (InputString[17] == '1') 
    {
       SetServoPos(7, 90);
    }



    if (InputString[7] == '1')     //accelerate
    {
      CarSpeedControl += 1000;
      if (CarSpeedControl > 4095)
      {
        CarSpeedControl = 4095;
      }
    }
    if (InputString[7] == '2')//decelerate
    {
      CarSpeedControl -= 1000;
      if (CarSpeedControl < 0)
      {
        CarSpeedControl = 500;
      }
    }
    //run.back,turn left,turn right,stop
    if (g_CarState != enTLEFT && g_CarState != enTRIGHT)
    {
      switch (InputString[1])
      {
        case run_car:   g_CarState = enRUN;  break;
        case back_car:  g_CarState = enBACK;  break;
        case left_car:  g_CarState = enLEFT;  break;
        case right_car: g_CarState = enRIGHT;  break;
        case stop_car:  g_CarState = enSTOP;  break;
        default: g_CarState = enSTOP; break;
      }
    }

    InputString = "";         //clear serial port data
    NewLineReceived = false;

    switch (g_CarState)
    {
      case enSTOP: brake(); break;
      case enRUN: run(CarSpeedControl); break;
      case enLEFT: left(CarSpeedControl); break;
      case enRIGHT: right(CarSpeedControl); break;
      case enBACK: back(CarSpeedControl); break;
      case enTLEFT: spin_left(CarSpeedControl); break;
      case enTRIGHT: spin_right(CarSpeedControl); break;
      default: brake(); break;
    }
  }
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
  if (NewLineReceived)
  {
    serial_data_parse(); 
  }

}

/**
* Function       serialEvent
* @author        liusen
* @date          2017.07.25
* @brief         
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/

void serialEvent()
{
  while (Serial.available())
  {
    //Read one byte by byte, the next sentence is read into the string array to form a completed packet
    IncomingByte = Serial.read();
    if (IncomingByte == '$')
    {
      StartBit = true;
    }
    if (StartBit == true)
    {
      InputString += (char) IncomingByte;
    }
    if (IncomingByte == '#')
    {
      NewLineReceived = true;
      StartBit = false;
    }
  }
}
