/*------------------------------------------------------------
 * PWM Tester software, ~140hz and ~300hz. 
 * Author: Leevi Sulonen - ST Solutions
 * 
 * Used to test turbo actuators which use pwm as input signal.
 ------------------------------------------------------------*/


const float pulseduties[9] = {10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0};
double time_on_300hz[9] = {333, 666, 1000, 1333, 1666, 2000, 2333, 2666, 3000};               //microseconds for 10 ... 90 % pulse duty 
double time_on_140hz[9] = {714, 1428, 2142, 2857, 3571, 4285, 5000, 5714, 6428};

int halfSecondPeriods = 0;
float secondHalves = 0;
int dutyswitch = 0;

int frequency = 140;

void setup()
{
  Serial.begin(9600);
  DDRB = B00110001;       //d13 as indicator, d8 as pwm out

}


void loop()
{ 
    if(frequency == 140)
    {
      for(int i = 0; i < 2; i++)
      {
        PORTB = B00100000;      //indicator pin blip, also led. 2 blips => 140hhz, 3 blips -> 300hz 
        delay(150);
        PORTB = 0;
        delay(150);
        Serial.println("blip 140");
      }
    }
    
    if(frequency == 300)
    {
      for(int i = 0; i < 3; i++)
      {
        PORTB = B00100000;      //indicator pin blip, also led. 2 blips => 140hhz, 3 blips -> 300hz 
        delay(150);
        PORTB = 0;
        delay(150);
        Serial.println("blip 300hz");
      }
    }   


  
  while(secondHalves < 20)     //ten seconds
  { 
    Serial.println("Time on 300hz");   
    Serial.println(time_on_300hz[dutyswitch]);
    
    if(frequency == 300)
    {
      PORTB = B00010000;
      PORTB = 0;
      while(halfSecondPeriods < 150) //half of a second @ 300hz
      {
        PORTB = B00000001;
        delayMicroseconds(double(time_on_300hz[dutyswitch]));
        PORTB = 0;
        delayMicroseconds(double(time_on_300hz[8 - dutyswitch]));
        halfSecondPeriods++;
      }
    }
    
    if(frequency == 140)
    {
      PORTB = B00010000;
      PORTB = 0;
      Serial.print("Time on 140 ");
      Serial.println(dutyswitch);
      Serial.println(time_on_140hz[dutyswitch]);
      
      while(halfSecondPeriods < 70) //half of a second @ 140hz
      {
        PORTB = B00000001;
        delayMicroseconds( double(time_on_140hz[dutyswitch]));
        PORTB = 0;
        delayMicroseconds( double(time_on_140hz[8 - dutyswitch]));

        
        halfSecondPeriods++;
      }
    }
    
    halfSecondPeriods = 0;
    
    dutyswitch ++;
    if(dutyswitch > 8)
      dutyswitch = 0;

    secondHalves++;
  }
  secondHalves = 0;
  halfSecondPeriods = 0;
  dutyswitch = 0;
    
  delay(1000);
  
  if(frequency == 300)
  frequency = 140;
  else
  frequency = 300;
  
}
