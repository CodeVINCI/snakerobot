/*
 * Team ID: 3875
 * Author List: Tanay Agrawal, Abhishek Chauhan
 * Filename: slave.ino
 * Theme: Spotter Snake
 * Functions: setup(), buzz_start(), buzz_end(), attach_motor(), detach_motor(), 
 *            detach_y1_motor(), attach_y1_motor(), detach_x1_motor(), attach_x1_motor(), detection_buzzer()
 * Global Variables: x1,x2,y1,y2,z1,z2(values of jouysticks)
 *                   s1,s2,s3,s4,s5,s6,s7,s8,s9(servo motors)
 *                   m1,m2,m3,m4,m5,m6,m7,m8,m9(digital pins of motors)
 *                   arr(array receiving the values from romte)
 *                   buzzer(pin defined for buzzer)
 */


//======================setting up robot=====================
#include <Wire.h>
#include <Servo.h> 

int x1,y1,z1,x2,y2,z2;

int s8_err = 12;

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


int arr[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int flag = -1;
int buzzer = 11;

void setup() {
  Wire.begin(8);// join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output

  //buzzer
  pinMode(buzzer, OUTPUT);
}

//====================Buzzer Functions======================
/*
 * Function Name: buzz_start()
 * Input: Input coming from button, either 1 or 0
 * Logic: If button is pressed buzzer beeps for 
 *        2seconds two time with interval of 1second with frequency of 3000Hz
 * Example Call: buzz_start()
 */
void buzz_start()
{
  tone(buzzer,3000);
  delay(2000);
  noTone(buzzer);
  delay(1000);
  tone(buzzer,3000);
  delay(2000);
  noTone(buzzer);
  
}


/*
 * Function Name: buzz_end()
 * Input: Input coming from button, either 1 or 0
 * Logic: If button is pressed buzzer beeps for 
 *        1seconds five time with interval of 1second with frequency of 3000Hz
 * Example Call: buzz_end()
 */
void buzz_end()
{   int c=0;
    while(c<5)
      {
      tone(buzzer,3000);
      delay(1000);
      noTone(buzzer);
      delay(1000);
      c++;
      }
  
}


/*
 * Function Name: detection_buzzer()
 * Input: Input coming from button,value is either 1 or 0
 * Logic: If button is pressed buzzer beeps for 
 *        1/2 seconds 2 time with interval of 1second with frequency of 3000Hz
 * Example Call: detection_buzzer()
 */
void detection_buzzer()
{
   if(flag == 0)
   {
    tone(buzzer,3000);
    delay(500);
    noTone(buzzer);
    delay(1000);
    tone(buzzer,3000);
    delay(500);
    noTone(buzzer);
   }
   flag =flag+1;
  }

//================attach detach motor functions===============
/*
 * Function Name: attach_motor()
 * Input: None
 * Output: None
 * Logic: Attaches the motor at respective pins
 * Example Call: when one want to attach all the motors use attach_motor()
 */
void attach_motor() {
  s1.attach(m1);
  s2.attach(m2);
  s3.attach(m3);
  s4.attach(m4);
  s5.attach(m5);
  s6.attach(m6);
  s7.attach(m7);
  s8.attach(m8);
  s9.attach(m9);
  }


/*
 * Function Name: detach_motor()
 * Input: None
 * Output: None
 * Logic: Detaches the motor that were attahced to certain pins
 * Example Call: when one want to detach all the motors use detach_motor()
 */
void detach_motor(){
    s1.detach();
    s2.detach();
    s3.detach();
    s4.detach();
    s5.detach();
    s6.detach();
    s7.detach();
    s8.detach();
    s9.detach();
}


/*
 * Function Name: detach_y1_motor()
 * Input: None
 * Output: None
 * Logic: Detaches the motor that are placed horizontally, i.e they helps in the vertical motion of snake
 * Example Call: when one want to detach all horizontal motors use detach_y1_motor()
 */
void detach_y1_motor(){
    s1.detach();
    s3.detach();
    s5.detach();
    s7.detach();
    s9.detach();
  }


/*
 * Function Name: attach_y1_motor()
 * Input: None
 * Output: None
 * Logic: Attaches the motor that are placed horizontally, i.e they helps in the vertical motion of snake
 * Example Call: when one want to attach all horizontal motors use attach_y1_motor()
 */
void attach_y1_motor(){
    s1.attach(m1);
    s3.attach(m3);
    s5.attach(m5);
    s7.attach(m7);
    s9.attach(m9);
  }


/*
 * Function Name: detach_x1_motor()()
 * Input: None
 * Output: None
 * Logic: Detach the motor that are placed vertically, i.e they helps in the horizontal motion of snake
 * Example Call: when one want to detach all vertical motors use detach_x1_motor()
 */
void detach_x1_motor(){
    s2.detach();
    s4.detach();
    s6.detach();
    s8.detach();
  }


/*
 * Function Name: attach_x1_motor()
 * Input: None
 * Output: None
 * Logic: Attaches the motor that are placed vertically, i.e they helps in the horizontal motion of snake
 * Example Call: when one want to attach all vertical motors use attach_x1_motor()
 */
void attach_x1_motor(){
    s2.attach(m2);
    s4.attach(m4);
    s6.attach(m6);
    s8.attach(m8);
  }


/*
 * Function Name: snake_straight()
 * Input: None
 * Output: None
 * Logic: Attaches all the motor and give them angle 90deg, and makes the snake straight
 * Example Call: when one want to straighten the snake, snake_straight()
 */
void snake_straight() {
  attach_motor();
  
  s1.write(90);
  s2.write(90);
  s3.write(90);
  s4.write(90);
  s5.write(90);
  s6.write(90);
  s7.write(90);
  s8.write(90 + s8_err);
  s9.write(90);  
}

//==================Gait 1: CatterPillar Motion==================


/*
 * Function Name: catterpillar_turn()
 * Input: value of joystick x2
 * Output: None
 * Logic: Due to weight at the end because of battery, whereever we turn it, snake turns in same direction 
 * Example Call: catterpillar_turn(val_joystick)
 */
void catterpillar_turn(int x2)
{
  int angle;
   if(x2>=87 && x2<=94)
   {
    s2.detach();
    s4.detach();
    s6.detach();
    s8.detach();
    }
    else if(x2>94)
    {
      attach_x1_motor();
      angle = map(x2,94,180,5,40);
      s2.write(90+angle);
      s4.write(90+angle+5);
      s6.write(90-(angle+5));
      s8.write(90+(angle+10)+s8_err);
    }

    else if(x2<87)
    {
      attach_x1_motor();
      angle = map(x2,87,0,5,40);
      s2.write(90-angle);
      s4.write(90-(angle+5));
      s6.write(90+angle+5);
      s8.write(90-(angle+10)-s8_err);
    }
}


/*
 * Function Name: catterpillar_forward()
 * Input: value of joystick y1
 * Output: None
 * Logic: Gives a wave to whole body of snake.
 * Example Call: catterpillar_turn(val_joystick)
 */
void catterpillar_forward(int y1)
{
  
  int angle1 = (y1*0.5)+45;
  int angle2 = 180-angle1;

  float angle_addition;


    if(y1>=87 && y1<=94)
    {
      detach_y1_motor();
    }
    else if(y1>94)
    {
        attach_y1_motor();
        s9.write(90);
        s7.write(90-23-15);
        delay(300);
      
        s9.write(90-23-23-15-15);
        delay(400);
        
        s9.write(90-23-15);
        s5.write(90+23+15);
        s7.write(90+23+15);
        delay(300);
      
        s9.write(90+23+15);
        s7.write(90+23+23+15+15);
        s5.write(90+23+15);
        delay(300);
      
        s5.write(90-23-23-15-15);
        s3.write(90-23-15);
        s7.write(90-23-15);
        s9.write(90);
        delay(300);
      
        s7.write(90);
        s5.write(90+23+15);
        s3.write(90+23+23+15+15);
        s1.write(90+23+15);
        delay(300);
      
        s5.write(90+10+10);
        s3.write(90);
        s1.write(90);
        delay(300);
        
        snake_straight();
        delay(50);
        //s9.write(110);
      
    }   

    else if(y1<87)
    {
      attach_y1_motor();
        s9.write(90-23-15-23-10);
        s7.write(90-23-15-15);
        s1.write(110);
        s5.write(90-23-15);
        s3.write(90-23-20);
      delay(700);

      s7.write(90-23-23-15);
      s9.write(90-23-15);

      s5.write(90);
      s3.write(90);
      delay(300);

      s9.write(90);
      s7.write(90-23-15);

      s5.write(90-23);
      s3.write(90-23);
      delay(400);

      float k =0;
      for(int i=90-23; i<=90; i++)
      {
      s5.write(i);
      s3.write(i);
      delay(k);
      k=k+0.5;
      }
      k = 0;
      for(int i=90-23-23-15; i<=90; i++)
      {
        s7.write(i);
        delay(k);
        k = k+0.5;
        }
      s1.write(90);
      delay(20);
     /* s7.write(90-15);
      s9.write(90);
      delay(400);

      s7.write(90);
      s9.write(90);
      delay(300);*/
      
      /*s7.write(90-23-23-15);
      s9.write(90-23);
      delay(300);

      s7.write(90);
      s9.write(90);
      delay(300);*/
      
      
      }
}


/*
 * Function Name: catterpillar()
 * Input: value of joystick x1,y1 and z1
 * Output: None
 * Logic: Operates both forward and side motion simultaneously
 * Example Call: catterpillar(x1,y1,z1)
 */
void catterpillar(int x2, int y1, int z1)
{
    catterpillar_forward(y1);
    catterpillar_turn(x2);
    
}

//======================CatterPillar Gait Ends===============

//======================Gait2: Rotate About Center==================
/*
 * Function Name: sidewinding(x1)
 * Input: Value of joysticks
 * Output: None
 * Logic: Sidewinds the Snake
 * Example Call: Use turncenter(x1) to sidewind
 */
void turncenter(int x1)
{
    if(x1>=87 && x1<=94)
    {
      detach_motor();
    }
    else if(x1<87)
    {     attach_motor();  
          s3.write(90-20);
           s1.write(90);
           //s5.write(90+20);
          s9.write(90);
          s7.write(90-20);
          delay(600);
           
           /*s7.write(90-10);
           s9.write(90);
           s5.write(90+20);
           s3.write(90);
           s1.write(90);
           delay(300);*/
          
           s4.write(90-30);
           //s5.write(90+20);
           s3.write(90-20);
           s1.write(90); 
           s7.write(90-20);
           s9.write(90);
           s8.write(90+50);
           //s2.write(90);
           delay(600);
           
           s7.write(90);
           s9.write(90);
           //s5.write(90);
           s3.write(90);
           s1.write(90);
           s4.write(90-30);
           s8.write(90+50);
           delay(600);
          
           s4.write(90);
           
           s8.write(90);
           
           delay(500);
           }

     else if(x1>94)
      {
        attach_motor();  
          s3.write(90-20);
           s1.write(90);
           //s5.write(90+20);
          s9.write(90);
          s7.write(90-20);
          delay(600);
           
           /*s7.write(90-10);
           s9.write(90);
           s5.write(90+20);
           s3.write(90);
           s1.write(90);
           delay(300);*/
          
           s4.write(90+30);
           //s5.write(90+20);
           s3.write(90-20);
           s1.write(90); 
           s7.write(90-20);
           s9.write(90);
           s8.write(90-50);
           //s2.write(90);
           delay(600);
           
           s7.write(90);
           s9.write(90);
           //s5.write(90);
           s3.write(90);
           s1.write(90);
           s4.write(90+30);
           s8.write(90-50);
           delay(600);
          
           s4.write(90);
           s8.write(90);
           delay(500);
        }
     
}

//======================Gait3: Side Winding Gait Ends============


void loop() {
  //delay(1000);
  for(int val=0;val<14;val++)
  {
      Serial.print(arr[val]);
      Serial.println(" ");
    }
  Serial.println("===========================================");
  //delay(1000);  //to see vals uncomment

  if(arr[13])
  {
    detection_buzzer();
    }
    else
    {
      flag = 0;
      }

  if(arr[4])
  {
  buzz_start();}   //press 4th button to start buzzer

  if(arr[6])
  {buzz_end();}  //press 6th button to start buzzer
  
  x1 = arr[7];    
  y1 = arr[8];
  z1 = arr[9];
  x2 = arr[10];
  /*y2 = arr[11];
  z2 = arr[12];*/
       
    if(arr[5]==1  && arr[0]==0)
    {

      if(arr[1]==1)
       {
        snake_straight();
        }
        else
        {catterpillar(x2,y1,z1);
          }
       
       }
    if(arr[0]==1 && arr[5]==0)
      {

        if(arr[1]==1)
       {
        snake_straight();
        } 
       else
       {turncenter(x1);}
       
       
      }
  
}

/*
 * Function Name: receiveEvent
 * Input: 
 * Output: None
 * Logic: Sidewinds the Snake
 * Example Call: Use sidewinding(x1) to sidewind
 */
void receiveEvent(int howMany) {
  while (1 <= Wire.available()) { // loop through all but the last
    
    for(int val=0;val<14;val++)
    {
      arr[val] = Wire.read();
    }
    
    // print the character
  }
 
  //int x = Wire.read();    // receive byte as an integer
  //Serial.println(x);         // print the integer

  
}
