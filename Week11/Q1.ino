#define PIN_DATA 11
#define PIN_CLK 13
#define PIN_LATCH_1 10
#define PIN_LATCH_2 9

#define BTN1 2
#define BTN2 3

#define LED 12

int map7seg[10] = {
  0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F
};
  
int TCNT_start = 3036;
int counter = 0;
bool isRunning = false;

#define MOTOR_D1_PIN 7 
#define MOTOR_D2_PIN 8 
#define MOTOR_PWM_PIN 6

int interruptChannelAPin = 2;
int interruptChannelBPin = 3;
volatile int encoderCount = 0;
volatile int encoderDir = 0;

int speedInput = 1;

void moveForward(int speed) {
    digitalWrite(MOTOR_D1_PIN,HIGH);
    digitalWrite(MOTOR_D2_PIN,LOW); 
    analogWrite(MOTOR_PWM_PIN,speed);
}

void moveBackward(int speed) {
    digitalWrite(MOTOR_D1_PIN,LOW);
    digitalWrite(MOTOR_D2_PIN,HIGH); 
    analogWrite(MOTOR_PWM_PIN,speed);
}

void setSpeed(int speed) { // Motor forward
  if (speed > 0) {
    if (speed > 255) {
    	speed = 255;
    }
  	moveForward(speed);
  } else if (speed < 0) {  // Motor backward
  	speed = speed*(-1);
    
    if (speed > 255) {
    	speed = 255;
    }
    moveBackward(speed);
  }
  else {                   // Motor stop
    moveForward(1);
  }
}

void setLED(){
  if(encoderCount < 0) digitalWrite(LED,HIGH);
  else digitalWrite(LED,LOW);
}

void setLed1(byte data){
  shiftOut(PIN_DATA, PIN_CLK, MSBFIRST, data);
  digitalWrite(PIN_LATCH_1,HIGH);
//  delayMicroseconds(2);
  digitalWrite(PIN_LATCH_1,LOW);
//  delayMicroseconds(2);
}

void setLed2(byte data){
  shiftOut(PIN_DATA, PIN_CLK, MSBFIRST, data);
  digitalWrite(PIN_LATCH_2,HIGH);
//  delayMicroseconds(2);
  digitalWrite(PIN_LATCH_2,LOW);
//  delayMicroseconds(2);
}

void write7Segemnt(unsigned char counter){
//  int num=counter/100;
//  if(num<=99){
    setLed1(map7seg[counter/10]);
    setLed2(map7seg[counter%10]);
//  }
}

/*void BTN1_callback(){
  isRunning = !isRunning;
  TCNT1 = TCNT_start;
}
void BTN2_callback(){
  counter = 0;
  setLed1(map7seg[counter]);
  setLed2(map7seg[counter]);
}*/

  
  
void setup(){
  Serial.begin(9600);
  pinMode(PIN_DATA,OUTPUT);
  pinMode(PIN_CLK,OUTPUT);
  pinMode(PIN_LATCH_1,OUTPUT);
  pinMode(PIN_LATCH_2,OUTPUT);

//  delay(100);
  	
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  
  TCNT1 = TCNT_start;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
  interrupts();
  
/*  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BTN1), BTN1_callback, RISING);
  attachInterrupt(digitalPinToInterrupt(BTN2), BTN2_callback, RISING);
*/
  
  pinMode(LED,OUTPUT); 
  
  pinMode(MOTOR_D1_PIN,OUTPUT); 
  pinMode(MOTOR_D2_PIN,OUTPUT); 
  pinMode(MOTOR_PWM_PIN,OUTPUT);  
  pinMode(interruptChannelAPin, INPUT_PULLUP);
  pinMode(interruptChannelBPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptChannelAPin), 
                  ChannelA_callback, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptChannelBPin), 
                  ChannelB_callback, RISING);
  
  digitalWrite(MOTOR_D1_PIN,LOW);
  digitalWrite(MOTOR_D2_PIN,HIGH);
  analogWrite(MOTOR_PWM_PIN,255);
}

  
void loop(){
/*  Serial.write(counter);
  Serial.println(String(isRunning?"Running":"Stoped")+" at "+String(counter));
  delay(1000);*/
  
  if(Serial.available()){
    String inString = Serial.readString();
    speedInput = inString.toInt();
   	Serial.println(speedInput);
  }
  
  setLED();
  setSpeed(speedInput);
  Serial.print(speedInput);
  Serial.print(":");
  Serial.println(encoderCount);
  delay(100);
}

  
ISR(TIMER1_OVF_vect){
  TCNT1 = TCNT_start;
  if(encoderCount>=0) write7Segemnt(encoderCount/100);
  else write7Segemnt(encoderCount/-100);
//  write7Segemnt(encoderCount/100);
  
//  counter++;
//  write7Segemnt(counter);
/*  if(isRunning){
    counter = (++counter);
    write7Segemnt(counter);
  }*/
}

void ChannelA_callback() {
  if (digitalRead(interruptChannelAPin)==1 && 
      digitalRead(interruptChannelBPin)==0) {
  	encoderCount--;
  }
}

void ChannelB_callback() {
  if (digitalRead(interruptChannelAPin)==0 && 
      digitalRead(interruptChannelBPin)==1) {
  	encoderCount++;
  }
}
