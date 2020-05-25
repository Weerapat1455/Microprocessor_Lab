#include <ThreeWire.h> 
#include <RtcDS1302.h>

ThreeWire myWire(4,5,2); // IO, SCLK, CE 
RtcDS1302<ThreeWire> 
Rtc(myWire);
int led = 13;
RtcDateTime now_ini;
int second = 0;

void printDateTime(const RtcDateTime& dt){ 
  Serial.print(dt.Year(), DEC);
  Serial.print('/');
  Serial.print(dt.Month(), DEC); 
  Serial.print('/');
  Serial.print(dt.Day(), DEC); 
  Serial.print(' '); 
  Serial.print(dt.Hour(), DEC); 
  Serial.print(':'); 
  Serial.print(dt.Minute(), DEC); 
  Serial.print(':'); 
  Serial.print(dt.Second(), DEC); 
  Serial.println();
  
  Serial.print("Total Seconds since 1/1/2000 : "); 
  Serial.print(dt.TotalSeconds());
  Serial.println();
  }
 
void setup() { 
  Serial.begin(57600);
  Rtc.Begin();
  RtcDateTime setting_time(2020,2,24,14,01,10);
  // year, month, dayOfMonth, hour, minute, second
  printDateTime(setting_time);
  //Try to comment This line
  Rtc.SetDateTime(setting_time); 

  pinMode(led, OUTPUT);
  now_ini = Rtc.GetDateTime();
  second = now_ini.Second();
  Serial.println("Start");
  printDateTime(now_ini);
}

void loop() {
  RtcDateTime now = Rtc.GetDateTime();

    if(now.TotalSeconds()>=now_ini.TotalSeconds()+120){
      Serial.println("END");
      printDateTime(now);
      digitalWrite(led,LOW);
    }
    else{
       if(now.Second()%2==0){
          digitalWrite(led, HIGH);
        }
        else{
          digitalWrite(led, LOW);
        }
    }
    delay(1000);
}
