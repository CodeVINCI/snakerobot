#include <Servo.h>

Servo s1;
Servo s2;
Servo s3;
Servo s4;
Servo s5;
Servo s6;
Servo s7;
Servo s8;
Servo s9;

int m1=9;
int m2=4;
int m3=2;
int m4=7;
int m5=10;
int m6=3;
int m7=5;
int m8=6;
int m9=8;

void setup() {
 
  //s1.attach(m1);
  //s2.attach(m2);
  //s3.attach(m3);
  //s4.attach(m4);
  //s5.attach(m5);
  //s6.attach(m6);
  //s7.attach(m7);
  //s8.attach(m8);
  s7.attach(m7); 
}



void loop()
{
  s7.write(90);
  }


/*void loop() {
  float c=0;
  for(float i=135;i>=45;i=i-2.5)
  {
    s8.write(i);
    delay(c+1);
    c=c+1;
    }
int d=0;
    for(float i=45;i<=135;i=i+2.5)
  {
    s8.write(i);
    delay(d+1);
    d=d+1;
    }
    
}*/
