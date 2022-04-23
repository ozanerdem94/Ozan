//////////////////////////////////////

int frequenz = 50;//Wahle PWM Frequenz
int p = 0;
int e=0;
float f=0.0;
float g=0.0;
float h=0.0;
float w2 = 0.0;
int j = 0;
int a = 0;
int b = 0;
int c = 0;
int k = 0;
int momentan = 0;
int momentan2= 0;
int schalter = 0;
int potiPin = 0;//Potentiometer am analogen Eingang 0
int potiWert = 0;
int potigelagert = 0;

void setup() {
  // put your setup code here, to run once:

   


switch (frequenz){

case 25 :
frequenz = frequenz;
break;

case 30:
frequenz = frequenz;
break;

case 35:
frequenz = frequenz;
break;

case 40:
frequenz = frequenz;
break;

case 45:
frequenz = frequenz;
break;

case 50:
frequenz = frequenz;
break;

default :
frequenz = 30;//Standard frequenz 30kHZ
}

a = map(frequenz,25,50,640,320);
b = a/2;//50% duty cycle
c = a/1.333; // maximale Phasenverschiebung 90 Grad

Serial.begin(9600);
pinMode(6, OUTPUT); //OC4D
pinMode(9, OUTPUT); //OC1A
pinMode(12, OUTPUT); //OC1C
pinMode(11, OUTPUT);//#OC4D
pinMode(4,INPUT);//Schalter

GTCCR = (1<<TSM)|(1<<PSRASY)|(1<<PSRSYNC);//ALL TIMER STOP
TCCR4A = 0;
TCCR4B = 0;
TCCR4C = 0;
TCCR4D = 0;
//alle Register löschen
TCCR4C = _BV(COM4D0)
| _BV(PWM4D); // TIMER4 AUSGANG PIN 4
TCCR4B = _BV(CS40);//
TC4H = (a >> 8);// 8 Bit nach rechts verschieben
OCR4C = a & 0xff;// 320 entspricht 50 kHZ; 160 entspricht 100kHz; 266.666666667 entspricht 60 kHZ
TC4H = (b >> 8);
OCR4D = b & 0xff;
TC4H = 0;
TCNT4 = 0; 
TCCR1A = 0;//Timer1 Control Register1
TCCR1B = 0;
TCNT1 = 0;
TCCR1A = _BV(COM1A1)
| _BV(COM1C1)
| _BV(COM1C0)
| _BV(WGM11);
TCCR1B= _BV(WGM12)
| _BV(WGM13)//
| _BV(CS10);//
ICR1 = a;//60 kHz für TIMER1
OCR1A = b;// 50% Duty Cycle
OCR1C = b;//50% Duty Cycle
GTCCR = 0; // alle Timer laufen


  
}//void setup

void loop() {

 
    schalter = digitalRead(4);//Switch on or off
  //
  if(schalter == HIGH){
    //while(Serial.available()>0){
      Serial.print("PWM-Frequenz in kHz: ");
      Serial.println(frequenz);
      p = Serial.parseInt();//Empfang variable für phasenverschiebung
         
    //}//while loop
    if(k!=p){
      GTCCR = (1<<TSM)|(1<<PSRASY)|(1<<PSRSYNC);//Neustart der Timer bei Anderung
      TCNT1=p;
      TC4H = 0;
      TCNT4 = 0;
      GTCCR=0;
    
    }
    
    }//if schalter
    else{
    
      
    potigelagert=potiWert;
    delay(900);
    
    for(int i = 0; i<10; i++){
      Serial.println(momentan2);
      momentan = analogRead(potiPin);
      momentan2 += momentan;
    }

    potiWert =(momentan2/10);
    momentan2 = 0;
    e = map(potiWert,0,1023,-83,c);
    f = (float)e;
    w2 = float(a);
    g = w2/360;//Umrechnung zum Winkel
    h= (g*e);
    j= int(h);
    Serial.print("Phasenverschiebung: ");
    //Serial.println(e);
    Serial.print(h);
    Serial.println(" Grad");

   if(e!=p){
       GTCCR = (1<<TSM)|(1<<PSRASY)|(1<<PSRSYNC);//Restart Timer
       TCNT1 = e;
       TC4H = 0;
       TCNT4 = 0;
       GTCCR=0;
       p = e;
       }
       }//else
    
  }
  
