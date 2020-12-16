// Tyler Sverak 2020
#include <Servo.h>
// Servo for base, arm, and bucket attached to end of crane
Servo baseservo;
Servo armservo;
Servo handservo;
int repetitions = 10; //runs ten times before resetting

// Pin definition
#define basePin 3
#define armPin 8
#define handPin 9

void setup() {
  baseservo.attach(basePin);
  handservo.attach(handPin);
  armservo.attach(armPin);
  baseservo.write(10);
  delay(3000);
}

// takes a servo motor (assumes 360 degree) with a speed to run at, a direction, and a duration
// spins the motor at the speed given for the amount of time given in given direction
void timer(Servo ser, int speedd, bool counterclockwise, double seconds){
  if (counterclockwise){
    ser.write(90 + speedd);
  }else{
    ser.write(90 - speedd);
  }
  delay(seconds * 1000);
  ser.write(90);
}

// takes a servo motor (assumes 180 degree) and a direction (in or out) and slowly
// moves the servo to the other of the two positions
void moveBase(Servo base, bool going_out){
  int start = 10;
  int endofturn = 120;
  if (going_out){
    int spot = start;
    while (spot < endofturn){
      base.write(spot);
      delay(800);
      spot += 10;
    }
  }else{
    int spot = endofturn;
    while (spot > start){
      base.write(spot);
      delay(800);
      spot -= 10;
    }
  }
}

void loop() {
  // time needed to move both types of motors
  double armtiming = 1.75;
  double handtime = 1;
  // starts with bucket cast into reserve of water
  // 90 still, less turns clockwise, greater turns counter clockwise
  if (repetitions > 0){
    int ts = 30; // default speed to turn motors
    // pull up water
    timer(handservo, ts, true, 12 * handtime);
    timer(armservo, ts, false, armtiming);
    // move to other side and spill
    moveBase(baseservo, true);
    timer(handservo, ts, false, handtime);
    timer(armservo, ts, true, armtiming);
    delay(2000);
    // retrieve bucket and move back
    timer(handservo, ts, true, handtime);
    timer(armservo, ts, false, armtiming);
    moveBase(baseservo, false);
    // cast bucket out
    timer(armservo, ts, true, armtiming);
    timer(handservo, ts, false, 12 * handtime);
    delay(1000); //make more later, collecting water    
    //beginning again
    repetitions--;
  }
}
