#include "vex.h"
#include "iostream"


//Code to display images on the brain screen 

int imgPos = 0; // The initial image to display
void incrementImg(){
  imgPos++;
  if(imgPos>=(imageCount-1)) imgPos = 0;
  Brain.Screen.clearScreen(color::black);
}

void flywheelSpeedControl(){
  
  if(enableFlywheelSpeedControl){
    if(Controller2.ButtonUp.pressing() && !Controller2PressedLast){
      flywheelSpeed+=flywheelSpeedStep;
      Controller2PressedLast = true;
    }else if(Controller2.ButtonDown.pressing() && !Controller2PressedLast){
      flywheelSpeed-=flywheelSpeedStep;
      Controller2PressedLast = true;
    }
    Controller2.Screen.setCursor(4,1);
    Controller2.Screen.print("Flywheel: ");
    Controller2.Screen.print(flywheelSpeed);
    Controller2.Screen.print(" Volts");
  }
}
/* runDriverRollerSpinning:
 * Called in drive while loop
 * Runs automatic roller spinning while driving.
 * Will start moving the roller motor if both sensors see either red or blue
 * Parameter:
 * onRedSide: controls which side the code will score the roller for
 */
void runDriverRollerSpinning(bool onRedSide){
    if(Controller1.ButtonX.pressing())autoRollerSpinning = false;
    // Roller Spinning (Nested Ifs galore)
    if(/*Controller1.ButtonX.pressing() &&*/ autoRollerSpinning){ //If roller button is being pressed
      if((topOptical.color()==red || topOptical.color()==blue) && (bottomOptical.color()==red || bottomOptical.color()==blue)){ //Automatic Roller Spinning Only works if both sensors have a color
        rollerSpin(onRedSide, 30);
      }else{//Driver is trying to spin a roller but the sensors don't both have a reading
        //Controller1.rumble("-");
        if(!Controller1.ButtonR1.pressing() && !Controller1.ButtonR2.pressing()){
          rollerMotor.stop(brake);
        }
      }
    }
}

// * X drive Variables and Functions:
int power, strafe, turn;
int lfPower, lbPower, rfPower, rbPower;
float scaler = 1;

int s = 10; // slow drive speed (percent)

int deadZone(int min, int value){
    if(abs(value) > min){
      return value;
    }else return 0;
}

/* xDrive
 * runs x drive based on slow drive buttons and analog sticks
 * Function should be called in the drive while loop
 * Note the configuration variables in config.cpp:
 *
 * bool enableSlowDrive = true;
 * bool enableFwdRevSlowDrive = false;
 * bool enableLeftRightSlowDrive = true;
 * bool enableTurnSlowDrive = true;
 * bool enableXDriveBrainPrinting = true;
 * 
 * Also note the variables above and the deadZone function
 */
void xDrive(){

    power = deadZone(0,Controller1.Axis3.value());
    turn = -Controller1.Axis1.value()*0.8;
    strafe = deadZone(0,Controller1.Axis4.value());


    if(enableSlowDrive){
      if(Controller1.ButtonUp.pressing() && enableFwdRevSlowDrive){
        power = s;
      }else if(Controller1.ButtonDown.pressing() && enableFwdRevSlowDrive){
        power = -s;
      }
      if(Controller1.ButtonLeft.pressing() && enableLeftRightSlowDrive){
        strafe = -s;
      }else if(Controller1.ButtonRight.pressing() && enableLeftRightSlowDrive){
        strafe = s;
      }
      if(Controller1.ButtonY.pressing() && enableTurnSlowDrive){
        turn = s;
      }else if(Controller1.ButtonA.pressing() && enableTurnSlowDrive){
        turn = -s;
      }
    }
    power = -power;
    strafe = -strafe;

    if(!displayImages && enableXDriveBrainPrinting){
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.newLine();
      Brain.Screen.print("Power: ");
      Brain.Screen.print(power);
      Brain.Screen.newLine();
      Brain.Screen.print("Turn: ");
      Brain.Screen.print(turn);
      Brain.Screen.print(", ");
      Brain.Screen.print(Controller1.Axis4.value());
      Brain.Screen.newLine();
      Brain.Screen.print("Strafe: ");
      Brain.Screen.print(strafe);
    }
    lfPower = (power + turn + strafe) * (scaler);
    lbPower = (power + turn - strafe) * (scaler);
    rfPower = (power - turn - strafe) * (scaler);
    rbPower = (power - turn + strafe) * (scaler);

    frontLeftMotor.spin(fwd, lfPower, velocityUnits::pct);
    backLeftMotor.spin(fwd, lbPower, velocityUnits::pct);
    frontRightMotor.spin(fwd, rfPower, velocityUnits::pct);
    backRightMotor.spin(fwd, rbPower, velocityUnits::pct);

}

