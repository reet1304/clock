#include <TM1637.h>

#define CLK 9//Pins for TM1637       
#define DIO 8
TM1637 tm1637(CLK,DIO);

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h" // с добавленной RTC_DS3231::getTemperature()
RTC_DS3231 rtc;
int hh, mm; 

unsigned int cnt = 0;

void setup()
{
  Serial.begin(9600);
  tm1637.init();
  tm1637.set(5); 
  //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;

  rtc.begin();
// manual adjust
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
// automatic adjust
  //  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

int disp(int i, int f) {
  // вывести на дисплей ii:ff
  tm1637.display(0,i/10);
  tm1637.display(1,i%10);
  tm1637.display(2,f/10);
  tm1637.display(3,f%10);
  return i+f; 
}

void loop(){
  cnt++;
  float t = rtc.getTemperature();
  int tt = (int)t;
  float d = t - tt;
  int dd = int(d * 100);
  DateTime now = rtc.now();
  hh = now.hour(), DEC;
  mm = now.minute(), DEC;
  int mod = cnt % 4;

  tm1637.point(POINT_OFF);

  bool is_clock = (mod == 2)||(mod == 3);
  
  if (is_clock) {
    disp(hh, mm);
  } else {
    disp(tt, dd);
  }
  
  delay(500);
  tm1637.point(POINT_ON);
  
  if (is_clock) {
    disp(hh, mm);
  } else {
    disp(tt, dd);
  }
    
  delay(500);

  Serial.print("Temperature: ");
  Serial.println(t);
   
}
