#include <Servo.h>

Servo myservo1;
Servo myservo2;

int pos = 0;
char num;
int val180=125;
//range=260[deg]
int preDeg1=0,preDeg2=0;;
void setup() {
  myservo1.attach(9);
  myservo2.attach(10);
  Serial.begin(9600);
  for(pos=260*val180/180; pos >= 0; pos-=1){
    myservo1.write(pos);
    delay(5);
  }
  for(pos=0*val180/180; pos <= 260; pos+=1){
    myservo2.write(pos);
    delay(5);
  }
}

int val[2];

void loop() {
  if(Serial.available() >= sizeof('H') + sizeof(int)){
    if(Serial.read()=='H'){
      delay(50);
      
      int buf[4];
     
      for (byte i = 0 ; i < 4; i++){
        buf[i] = Serial.read();
        if(buf[i] >= '0' && buf[i] <= '9'){
          buf[i] = buf[i] - 0x30;
        }else{
          buf[i] = buf[i] - 0x40 + 9;
        }
      }
      buf[0] = buf[0] << 4;
      buf[2] = buf[2] << 4;

      val[0] = buf[0] | buf[1];
      val[1] = buf[2] | buf[3];
    }
  }
  
  moveServo1(val[0]);
  moveServo2(val[1]);

}

void moveServo1(int deg){
  if(deg>preDeg1){
    //Serial.print("+move1 ");
    for (pos=preDeg1*val180/180; pos <= deg*val180/180; pos+=1) {
      myservo1.write(pos);
      //Serial.print("position1:");
      //Serial.println(pos);
      delay(3);
    }
    preDeg1=deg;
  }
  else if(deg<preDeg1){
    //Serial.print("-move1 ");
    for(pos=preDeg1*val180/180; pos >= deg*val180/180; pos-=1){
      myservo1.write(pos);
      //Serial.print("position1:");
      //Serial.println(pos);
      delay(3);
    }
    preDeg1=deg;
    
  }
  else{
    preDeg1=deg;
    //Serial.print("not move1 ");
  }
}

void moveServo2(int deg){
  if(deg>preDeg2){
    //Serial.print("+move2\n");
    for (pos=preDeg2*val180/180; pos <= deg*val180/180; pos+=1) {
      myservo2.write(pos);
      //Serial.print("position2:");
      //Serial.println(pos);
      delay(3);
    }
    preDeg2=deg;
  }
  else if(deg<preDeg2){
    //Serial.print("-move2\n");
    for(pos=preDeg2*val180/180; pos >= deg*val180/180; pos-=1){
      myservo2.write(pos);
      //Serial.print("position2:");
      //Serial.println(pos);
      delay(3);
    }
    preDeg2=deg;
    
  }
  else{
    preDeg2=deg;
    //Serial.print("not move2\n");
  }
}
