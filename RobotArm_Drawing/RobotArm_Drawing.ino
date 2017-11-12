#include <Servo.h>

Servo servo_bottom;      //initialize a servo object for the connected servo  
Servo servo_middle;
Servo servo_top;

int servo_bottom_output = 9;
int servo_middle_output = 11;
int servo_top_output = 13;

double angle_bottom = 0;    
double angle_middle = 0;
double angle_top = 0;
    
int potentio_bottom = A0;      // initialize the pin for potentiometer
int potentio_middle = A2;      // initialize the pin for potentiometer
int potentio_top = A5;      // initialize the pin for potentiometer

double geo_height = 7.4;
double geo_arm_length = 5.7;
double geo_hand_length = 1.0 + 4.5;

double interval = 0.3;

void setup() 
{
   
 Serial.begin(9600);
 
 servo_bottom.attach(servo_bottom_output);   // attach the signal pin of servo to pin
 servo_middle.attach(servo_middle_output);   // attach the signal pin of servo to pin
 servo_top.attach(servo_top_output);   // attach the signal pin of servo to pin

 angle_bottom = map(analogRead(potentio_bottom), 0, 1023, 60, 120);     // scaling the potentiometer value to angle value for servo
 angle_middle = map(analogRead(potentio_middle), 0, 1023, 30, 150);     // scaling the potentiometer value to angle value for servo
 angle_top = map(analogRead(potentio_top), 0, 1023, 30, 150);  // scaling the potentiometer value to angle value for servo

} 


double armAngle (double dist){

  //Applying law of cosines

  // Angle between height and hypotenus
  double angle1 = atan(dist/geo_height) / M_PI * 180;
  //Serial.println(angle1);
  
  // Angle between hypotenus and arm
  double temp= (dist * dist + geo_height*geo_height + geo_arm_length*geo_arm_length - 
                geo_hand_length*geo_hand_length)/            
                (2*geo_arm_length*
                sqrt(dist * dist + geo_height*geo_height));
  double angle2 = acos(temp) / M_PI * 180;
  //Serial.println(angle2);
  
  return angle1+angle2;
  
}

double handAngle (double dist){

  //Applying law of cosines
  double temp= (geo_arm_length*geo_arm_length + geo_hand_length*geo_hand_length - 
                dist * dist - geo_height*geo_height)/            
                (2*geo_arm_length*geo_hand_length);
                
  double angle = 180 - (acos(temp) / M_PI * 180);
  //Serial.println(angle);
  return angle;

  
}
 
void loop() 
{
   
 angle_bottom = map(analogRead(potentio_bottom), 0, 1023, 60, 120);     // scaling the potentiometer value to angle value for servo
 

 //Serial.println(angle_middle);
 
 servo_bottom.write(angle_bottom);                   //command to rotate the servo to the specified angle 
 /*servo_middle.write(angle_middle);
 servo_top.write(angle_top);
 
 delay(5);             

 Serial.print(servo_bottom.read()); Serial.print(", ");
 Serial.print(servo_middle.read()); Serial.print(", ");
 Serial.println(servo_top.read());*/
 delay(1000);
 moveTo(6.5);
 delay(1000);
 moveTo(7.5);
}  

void moveTo(double dist){
  
  double arm = armAngle(dist);
  double hand = handAngle(dist);

  //angle_middle = arm;
  //angle_top = hand;
  
  Serial.println("-------");
  Serial.println("-------");
  Serial.println("Now, will move from");
  Serial.print(angle_middle);Serial.print(", "); Serial.println(angle_top);
  Serial.println("To the new position of");
  Serial.print(arm);Serial.print(", "); Serial.println(hand);
  Serial.println("-------");
  
  slowlyMoveTo(arm, hand);
}

void slowlyMoveTo(double armAngle, double handAngle){
  
  while(true){
    
    if(fabs(armAngle-angle_middle)>interval){
      if(armAngle > angle_middle){
        angle_middle += interval;
       }
       else{
        angle_middle -= interval;
       }
    }
    else{
      angle_middle = armAngle;
    }
    
    if(fabs(handAngle-angle_top)>interval){
      if(handAngle > angle_top){
        angle_top += interval;
       }
       else{
        angle_top -= interval;
       }
    }
    else{
      angle_top = handAngle;
    }

    Serial.println("...");
    Serial.print("Looping to move arm from "); Serial.print(angle_middle); Serial.print(" to "); Serial.println(armAngle);
    Serial.print("Looping to move hand from "); Serial.print(angle_top); Serial.print(" to "); Serial.println(handAngle);

    servo_middle.write(angle_middle);
    servo_top.write(angle_top);
  
    delay (5);

    if((armAngle == angle_middle) && (handAngle == angle_top)){
        Serial.println("-------");
        Serial.println("Well it looks like "); 
        Serial.print(angle_middle);Serial.print(" equals to "); Serial.println(armAngle);
        Serial.print(angle_top);Serial.print(" equals to "); Serial.println(handAngle);     
        return;
    }
  }
}


