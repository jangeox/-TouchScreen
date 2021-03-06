/*
  flexcable (upper side)
    
      |    |    |    |
      |    |    |    |
      |    |    |    |
      X1   Y1   X2   Y2
  
  X1 = left
  Y1 = bottom
  X2 = right
  Y2 = top
  
  (photo blog : X1 = brown, Y1 = red, X2 = orange, Y2 = yellow)
  
  !!!!!!!!!!!!
  xcoor leest YCOORDINAAT en omgekeerd !!!
  !!!!!!!!!!!!
  
*/



#include <Wire.h>
#include <Servo.h> 

Servo pan; 
Servo tilt;

int pinPan = 3;
int pinTilt = 5;

int panPos = 70;
int tiltPos = 80;
int panPosDelay;
int tiltPosDelay;

int speedPan;
int speedTilt;

int lijstx[] = {0,0,0,0,0,0,0,0,0,0};
int lijsty[] = {0,0,0,0,0,0,0,0,0,0};

int xcoor(){
  pinMode(A0,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A1,INPUT);
  pinMode(A3,INPUT);
  digitalWrite(A0,LOW);
  digitalWrite(A2,HIGH);
  return analogRead(A1);
    
}

int ycoor(){
  pinMode(A1,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A2,INPUT);
  digitalWrite(A1,LOW);
  digitalWrite(A3,HIGH);
  return analogRead(A2);
    
}

void setup(){



  Serial.begin(57600);
  
  
/*
  if (pan.attached() == 0){pan.attach(pinPan);};
  if (tilt.attached() == 0){tilt.attach(pinTilt);};
  pan.write(160);
  tilt.write(70);
  delay(500);


  for (int i = 70; i>=10; i--){
  tilt.write(i);
  delay(50);}
    
     pan.detach();
     tilt.detach();
*/



  
}


void loop(){

  int x = xcoor();
  if (x == 1023){x = 0;};

  int y = ycoor();
  if (y == 1023){y = 0;};  
  

  if ((x == 0) & (y == 0)){
    pan.detach();
    tilt.detach(); }
  else {

    if (pan.attached() == 0){pan.attach(pinPan);};
    if (tilt.attached() == 0){tilt.attach(pinTilt);};
    
    int y1 = 80 + (y / 14);
    int x1 = 10 + (70 - (x / 14));
    

    for (int i = 0; i<=8; i++){lijsty[i] = lijsty[i+1];};
    lijsty[9] = y1;
    int tot = 0;
    for (int i = 0; i<=9; i++){tot += lijsty[i];};
    tot = tot / 10;
    pan.write(tot);
    
    
    for (int i = 0; i<=8; i++){lijstx[i] = lijstx[i+1];};
    lijstx[9] = x1;
    tot = 0;
    for (int i = 0; i<=9; i++){tot += lijstx[i];};
    tot = tot / 10;
    tilt.write(tot);    
    
  };
 
  delay(50);
  
return;

}
