/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         CarRun.c
* @author       liusen
* @version      V1.0
* @date         2017.07.25
* @brief        CarRun
* @details
* @par History  
*
*/


#define run_car     '1'
#define back_car    '2'
#define left_car    '3'
#define right_car   '4'
#define stop_car    '0'

#define ON 1          
#define OFF 0         

/*Enumeration of running state of car*/
enum {
  enSTOP = 0,
  enRUN,
  enBACK,
  enLEFT,
  enRIGHT,
  enTLEFT,
  enTRIGHT
} enCarState;

int CarSpeedControl = 150;
int IncomingByte = 0;            //Received data byte
String InputString = "";         //It is used to store received content
boolean NewLineReceived = false; //The previous data end flag
boolean StartBit  = false;       //Protocol start flag
String ReturnTemp = "";          //Store return value
/*状态机状态*/
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

  for(int i = 2; i < 14; i++)
  {
    pinMode(i, OUTPUT);
  }
 
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
void run()
{

  digitalWrite(3, LOW);    
  digitalWrite(2, HIGH);
  digitalWrite(4, LOW);   
  digitalWrite(5, HIGH);
  
  digitalWrite(7, LOW);    
  digitalWrite(6, HIGH);
  digitalWrite(8, LOW);    
  digitalWrite(9, HIGH);
  
  
  digitalWrite(11, LOW);    
  digitalWrite(10, HIGH);
  
  digitalWrite(12, LOW);    
  digitalWrite(13, HIGH);
}

/**
* Function       brake
* @author        liusen
* @date          2017.07.25
* @brief         brake
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   
*/
void brake()
{
 for(int i = 2; i < 14; i++)
  {
    digitalWrite(i, LOW);
  }
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
void left()
{
  digitalWrite(2, LOW);    
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);    
  digitalWrite(5, HIGH);
  
  digitalWrite(6, LOW);    
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);    
  digitalWrite(9, HIGH);
  
  
  digitalWrite(10, LOW);    
  digitalWrite(11, HIGH);
  
  digitalWrite(12, LOW);    
  digitalWrite(13, HIGH);
}

/**
* Function       right
* @author        liusen
* @date          2017.07.25
* @brief         turn right(left wheel advance,right wheel stop)
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   
*/
void right()
{
 digitalWrite(3, LOW);    
  digitalWrite(2, HIGH);
  digitalWrite(5, LOW);    
  digitalWrite(4, HIGH);
  
  digitalWrite(7, LOW);    
  digitalWrite(6, HIGH);
  digitalWrite(9, LOW);    
  digitalWrite(8, HIGH);
  
  
  digitalWrite(11, LOW);   
  digitalWrite(10, HIGH);
  
  digitalWrite(13, LOW);    
  digitalWrite(12, HIGH);

}

/**
* Function       spin_left
* @author        liusen
* @date          2017.07.25
* @brief         turn left in place(left wheel back,right wheel advance)
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   
*/
void spin_left()
{

}

/**
* Function       spin_right
* @author        liusen
* @date          2017.07.25
* @brief         turn right in place(left wheel adavnce,right wheel back)
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   
*/
void spin_right()
{
 
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
void back()
{
  digitalWrite(2, LOW);    
  digitalWrite(3, HIGH);
  digitalWrite(5, LOW);    
  digitalWrite(4, HIGH);
  
  digitalWrite(6, LOW);    
  digitalWrite(7, HIGH);
  digitalWrite(9, LOW);    
  digitalWrite(8, HIGH);
  
  
  digitalWrite(10, LOW);    
  digitalWrite(11, HIGH);
  digitalWrite(13, LOW);    
  digitalWrite(12, HIGH);
}
/**
* Function       serial_data_parse
* @author        liusen
* @date          2017.07.25
* @brief         The serial port data is parsed and the corresponding action is specified
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void serial_data_parse()
{

  //Analyze the general protocol instruction sent by the upper computer and perform corresponding actions
  //for exmaple:$1,0,0,0,0,0,0,0,0,0#    run
  if (InputString.indexOf("4WD") == -1)
  {
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

    if (InputString[7] == '1')     //accelerate
    {
      CarSpeedControl += 50;
      if (CarSpeedControl > 255)
      {
        CarSpeedControl = 255;
      }
    }
    if (InputString[7] == '2')//decelerate
    {
      CarSpeedControl -= 50;
      if (CarSpeedControl < 50)
      {
        CarSpeedControl = 100;
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
      case enRUN: run(); break;
      case enLEFT: left(); break;
      case enRIGHT: right(); break;
      case enBACK: back(); break;
      case enTLEFT: left(); break;
      case enTRIGHT: right(); break;
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
