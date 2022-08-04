/*------------------------------------------------------------
 * PWM Tester software, ~140hz and ~300hz. 
 * Author: Leevi Sulonen - ST Solutions
 * 
 * Used to test turbo actuators which use pwm as input signal.
 ------------------------------------------------------------*/

#include <StopwatchLib.h>

//Stopwatch stopwatch;
Stopwatch second_timer;
Stopwatch stopwatch;
const float pulseduties[9] = {10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0};
double time_on[9];
double time_off[9];
float hz300_period_us = 3333;
float hz140_period_us = 7143;
int dutyswitch = 0;

void init_times(int period_us)
{
  for(int i = 0; i < 9; i++)
  {
    time_on[i] = 0;
    time_off[i] = 0;   
  }
  
  for(int i = 0; i < 9; i++)
  {
    Serial.print("Ollaan inittimes \n");
    time_on[i] = (pulseduties[i] * 0.01) * period_us;
    
  }
  Serial.print("Vahan alempana \n ");
  for(int i = 9; i > 0; i--)
  {
    time_off[i] = time_on[i];     //times off are reverse values of times on  
    Serial.print("miinusta \n");
  }
 
  
/*  for(int i = 0; i < 9; i++)
  {
    Serial.print("Time on: ");
    Serial.print(time_on[i]);
    Serial.print("\n");
    
  }
  delay(2000);
*/
Serial.print("Just ennee\n");
}

void pwm_output()
{
  stopwatch.Reset();
  Serial.println("resetin jalkeen");
  
  while(stopwatch.GetElapsed() < 10000000)     //ten seconds
  {
    second_timer.Reset();
    Serial.print("second_timer: ");
    Serial.println(second_timer.GetElapsed());
  
    
    while(second_timer.GetElapsed() < 500000)   //half of a second
    {
      PORTB = 0x02;
      delayMicroseconds(time_on[dutyswitch]);
      PORTB = 0x00;
      delayMicroseconds(time_off[dutyswitch]);
      second_timer.Update();
    }
    Serial.println(time_on[dutyswitch]);
    dutyswitch ++;
    if(dutyswitch > 8)
      dutyswitch = 1;

    stopwatch.Update();
    Serial.println(stopwatch.GetElapsed());
  }
}
void setup()
{
  DDRB = 0x02;    //in build led is portb 5, d13 as output
  Serial.begin(9600);
}

Stopwatch testi;

void loop()
{ 
  testi.Update();
  
  Serial.println(testi.GetElapsed());
  testi.Reset();
  
  delay(1500);
  testi.Update();
  Serial.println(testi.GetElapsed());
  Serial.print("Enne ekaa init \n");
  init_times(hz300_period_us);
  Serial.print("Enne ekaa pwm output \n");
  pwm_output();
  Serial.print("Enne toista init \n");
  init_times(hz140_period_us);
  Serial.print("Enne toista pwm output \n ");
  pwm_output();
    
}
