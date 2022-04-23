String a;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0) {
    a += char(Serial.read());//The serial data assignment
    //delay(200);
  }

if (a == "g") {    //Determines whether the keyword is the trigger , it is to start the game
   Serial.print("n0.val=500");
    off();
 for (int i = 0; i < 100; i++) {
  int c = 99 - i;//Reducing time progress bar
      Serial.print("j0.val=");
      Serial.print(c);
      off();
     
      delay(500);//Delay time, control the game difficulty
    
 }
 if(a == "f"){
  Serial.print("n0.val=200");
  off();
 }
 }
a = "";//Remove
}
 
 void off() {  //End code
  for (int i = 0; i < 3; i++) {
    Serial.write(0xff);
}
  }
  

