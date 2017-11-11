#include <Servo.h>

Servo servo_bottom;      //initialize a servo object for the connected servo  
Servo servo_middle;

int servo_bottom_output = 9;
int servo_middle_output = 11;

int angle_bottom = 0;    
int angle_middle = 0;
    
int potentio_bottom = A0;      // initialize the A0analog pin for potentiometer
int potentio_middle = A5;      // initialize the A0analog pin for potentiometer

void setup() 
{
   
 Serial.begin(9600);
 
 servo_bottom.attach(servo_bottom_output);   // attach the signal pin of servo to pin9 of arduino
 servo_middle.attach(servo_middle_output);   // attach the signal pin of servo to pin9 of arduino

} 
 
void loop() 
{
   
 angle_bottom = map(analogRead(potentio_bottom), 0, 1023, 60, 120);     // scaling the potentiometer value to angle value for servo
 angle_middle = map(analogRead(potentio_middle), 0, 1023, 30, 150);     // scaling the potentiometer value to angle value for servo

 Serial.println(angle_middle);
 
 servo_bottom.write(angle_bottom);                   //command to rotate the servo to the specified angle 
 servo_middle.write(angle_middle);
 
 delay(5);             

}  
