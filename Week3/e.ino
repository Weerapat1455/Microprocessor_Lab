int clk_pin = 13;//SHCP
int latch_pin = 10;//STCP
int data_pin = 11;//DS

void setLed(uint8_t state){
  
  digitalWrite(latch_pin,LOW);
  for(int i=0;i<8;i++){
    digitalWrite(data_pin,(state>>(7-i))&0x01);
    digitalWrite(clk_pin,HIGH);
    digitalWrite(clk_pin,LOW);
    }
    digitalWrite(latch_pin,HIGH);
}
    
void setup(){
  pinMode(clk_pin,OUTPUT);
  pinMode(latch_pin,OUTPUT);
  pinMode(data_pin,OUTPUT);
  setLed(0x3F);
}

void loop(){
  delay(100);
}
