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
      if(Controller1.ButtonUp.pressing()){
        flywheelSpeed+=flywheelSpeedStep;
      }else if(Controller1.ButtonDown.pressing()){
        flywheelSpeed-=flywheelSpeedStep;
      }
      Controller1.Screen.setCursor(4,4);
      Controller1.Screen.print("Flywheel: ");
      Controller1.Screen.print(flywheelSpeed);
    }
}

void runDriverRollerSpinning(bool onRedSide){
    if(Controller1.ButtonX.pressing())autoRollerSpinning = false;
    // Roller Spinning (Nested Ifs galore)
    if(/*Controller1.ButtonX.pressing() &&*/ autoRollerSpinning){ //If roller button is being pressed
      if((topOptical.color()==red || topOptical.color()==blue) && (bottomOptical.color()==red || bottomOptical.color()==blue)){ //Automatic Roller Spinning Only works if both sensors have a color
        rollerSpin(onRedSide);
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

int s = 30; // slow drive speed (percent)

int deadZone(int min, int value){
    if(abs(value) > min){
      return value;
    }else return 0;
}

void xDrive(){

    power = deadZone(5,Controller1.Axis3.value());
    turn = -deadZone(30,Controller1.Axis1.value());
    strafe = deadZone(5,Controller1.Axis4.value());


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

