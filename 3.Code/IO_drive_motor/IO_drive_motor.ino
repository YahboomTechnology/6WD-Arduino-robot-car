 /**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         CarRun.c
* @author       liusen
* @version      V1.0
* @date         2018.05.07
* @brief       
* @details
* @par History  
*
*/


/**
* Function       setup
* @author        liusen
* @date          2017.07.25
* @brief         
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
* @brief         advance
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   no
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
* @brief         
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
* Function       loop
* @author        liusen
* @date          2017.07.25
* @brief      
* @param[in]     void
* @retval        void
* @par History   
*/

void loop()
{
  run();
  delay(1000);
  brake();
  delay(1000);

}


