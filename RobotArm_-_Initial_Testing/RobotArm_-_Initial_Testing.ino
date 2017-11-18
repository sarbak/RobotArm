#include <Servo.h>

Servo servo_bottom;      //initialize a servo object for the connected servo  
Servo servo_middle;
Servo servo_top;

int servo_bottom_output = 9;
int servo_middle_output = 11;
int servo_top_output = 13;

int angle_bottom = 0;    
int angle_middle = 0;
int angle_top = 0;
    
int potentio_bottom = A0;      // initialize the pin for potentiometer
int potentio_middle = A2;      // initialize the pin for potentiometer
int potentio_top = A5;      // initialize the pin for potentiometer



void setup() 
{
   
 Serial.begin(9600);
 
 servo_bottom.attach(servo_bottom_output);   // attach the signal pin of servo to pin
 servo_middle.attach(servo_middle_output);   // attach the signal pin of servo to pin
 servo_top.attach(servo_top_output);   // attach the signal pin of servo to pin

} 


 
void loop() 
{
   
 angle_bottom = map(analogRead(potentio_bottom), 0, 1023, 1, 180);     // scaling the potentiometer value to angle value for servo
 angle_middle = map(analogRead(potentio_middle), 0, 1023, 1, 180);     // scaling the potentiometer value to angle value for servo
 angle_top = map(analogRead(potentio_top), 0, 1023, 1, 240);  // scaling the potentiometer value to angle value for servo

 //Serial.println(angle_middle);

 // CONTROLS ARE MESSED UP FOR SOME TESTING PURPOSES
 servo_bottom.write(angle_bottom);                   //command to rotate the servo to the specified angle 
 servo_middle.write(angle_middle);
 servo_top.write(angle_top);            

 Serial.print(servo_bottom.read()); Serial.print(", ");
 Serial.print(servo_middle.read()); Serial.print(", ");
 Serial.println(servo_top.read());

 //armAngle(9);
}  
