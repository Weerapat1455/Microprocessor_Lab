int clk_pin = 13; //SHCP 
int latch_pin = 10; //STCP 
int data_pin = 11; //DS 
bool toggle;
void setup() {
// put your setup code here, to run once: 
  pinMode(clk_pin,OUTPUT); 
  pinMode(latch_pin,OUTPUT); 
  pinMode(data_pin,OUTPUT);
}
void loop() {
// put your mai;'n code here, to run repeatedly: 
  digitalWrite(latch_pin,LOW);
  
  for(int i = 0 ; i < 16 ; i++){
    digitalWrite(data_pin,toggle);
     
    digitalWrite(clk_pin,HIGH);
    if(){

       
    }
    digitalWrite(clk_pin,LOW); 
    toggle = !toggle;
  } 
  
  digitalWrite(latch_pin,HIGH);
  
  toggle = !toggle; 
  delay(1000);
}
