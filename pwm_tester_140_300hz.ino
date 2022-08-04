

/*------------------------------------------------------------
 * PWM Tester software, ~140hz and ~300hz. 
 * Author: Leevi Sulonen - ST Solutions
 * 
 * Used to test turbo actuators which use pwm as input signal.
 ------------------------------------------------------------*/
#include <StopwatchLib.h>
#include <avr/io.h>
#include <avr/delay.h>

Stopwatch stopwatch;
Stopwatch second_timer;

const int pulseduties[9] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
int time_on[9];
int time_off[9];
const int hz300_period_us = 3333;
const int hz140_period_us = 7143;
int dutyswitch = 1;

void init_times(int period_us)
{
    for(int i = 0; i < 9; i++)
  {
    time_on[i] = (pulseduties[i] * 0,001) * period_us;
  }

  for(int i = 9; i > 0; i--)
  {
    time_off[i] = time_on[i];     //times off are reverse values of times on  
  }
}

void pwm_output()
{
  stopwatch.Reset();
  
  while(stopwatch.GetElapsed() < 10000000)     //ten seconds
  {
    second_timer.Reset();

    while(second_timer.GetElapsed() < 500000)   //half of a second
    {
      PORTB = 0x02;
      delayMicroseconds(time_on[dutyswitch]);
      PORTB = 0x00;
      delayMicroseconds(time_off[dutyswitch]);
      second_timer.Update();
    }
    dutyswitch ++;
    if(dutyswitch > 8)
      dutyswitch = 1;

    stopwatch.Update();
  }
}
void setup()
{
  DDRB = 0x02;    //in build led is portb 5, d13 as output

  
}
void loop()
{  
  
  init_times(hz300_period_us);
  
  pwm_output();

  init_times(hz140_period_us);

  pwm_output();

    
}
