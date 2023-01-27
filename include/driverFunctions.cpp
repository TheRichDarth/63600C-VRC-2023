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
      if(flywheelSpeed>12.0) flywheelSpeed = 12.0;
      Controller2PressedLast = true;
      Controller2.Screen.setCursor(4,1);
      Controller2.Screen.clearLine();
      Controller2.Screen.print("Flywheel: ");
      Controller2.Screen.print(flywheelSpeed);
      Controller2.Screen.print(" Volts");
    }else if(Controller2.ButtonDown.pressing() && !Controller2PressedLast){
      flywheelSpeed-=flywheelSpeedStep;
      if(flywheelSpeed<flywheelMinSpeed)flywheelSpeed = flywheelMinSpeed;
      Controller2PressedLast = true;
      Controller2.Screen.setCursor(4,1);
      Controller2.Screen.clearLine();
      Controller2.Screen.print("Flywheel: ");
      Controller2.Screen.print(flywheelSpeed);
      Controller2.Screen.print(" Volts");
    }
    // if((Controller2.ButtonDown.pressing() || Controller2.ButtonUp.pressing())&& !Controller2PressedLast){
    //   Controller2.Screen.clearScreen();
    //   Controller2.Screen.setCursor(4,1);
    //   Controller2.Screen.clearLine();
    //   Controller2.Screen.print("Flywheel: ");
    //   Controller2.Screen.print(flywheelSpeed);
    //   Controller2.Screen.print(" Volts");
    // }
  }
}
/* runDriverRollerSpinning:
 * Called in drive while loop
 * Runs automatic roller spinning while driving.
 * Will start moving the roller motor if both sensors see either red or blue
 * Parameter:
 * onRedSide: controls which side the code will score the roller for
 */
void runDriverRollerSpinning(bool onRedSide, bool acceptGreenForBlue = true){
  if(Controller1.ButtonR1.pressing() || Controller1.ButtonR2.pressing()) return;
    if(Controller1.ButtonX.pressing())autoRollerSpinning = false;
    // Roller Spinning (Nested Ifs galore)
    if(/*Controller1.ButtonX.pressing() &&*/ autoRollerSpinning){ //If roller button is being pressed
      if((topRollerRed() || topRollerBlue()) && (bottomRollerRed() || bottomRollerBlue())){ //Automatic Roller Spinning Only works if both sensors have a color
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

void tankDrive(){
  float leftPower = Controller1.Axis3.value();
  float rightPower = Controller1.Axis2.value();

  leftDrivetrain.spin(fwd,leftPower,velocityUnits::pct);
  rightDrivetrain.spin(fwd,rightPower,velocityUnits::pct);
  
}

/**
 * @brief Updates the catapultState variable and runs the catapult motor when appropriate.
 * 
 * @param fireButton boolean input for whether the fire button is pressed
 */
void updateCatapult(bool fireButton){

  std::cout << "\n"/*updateCatapult run. State: "*/;
  std::cout << catapultDriverState;
  std::cout << ", Limit value: ";
  //std::cout << catapultLimitSwitch;
  std::cout << catapultLimitSwitch.pressing();
  std::cout << ", Timer: ";
  std::cout << catapultTimer.time(msec);


  switch (catapultDriverState){
  case 0:
    catapultMotor.stop(brake);
    //Catapult is raised after firing. Waiting for enough time to pass before automatically lowering if appropriate
    if(catapultTimer.time(sec)>1){
      //If enough time has elapsed after firing check if catapult should be lowered.
      if(catapultAutoLowering || fireButton){
        //Lower the catapult
        catapultDriverState = 1;
        catapultTimer.clear();
      }
    }
    break;
  case 1:
    //Lowering catapult into intake-position. Lowering is stopped when limit switch is pressed
    catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    if(catapultLimitSwitch.pressing()){
      //The catapult has reached it's rest position and the motor needs to stop moving.
      catapultMotor.stop(brake);
      catapultDriverState = 2;
      catapultTimer.clear();
    }else if(catapultTimer.time(msec)>catapultLowerMaxTime){
      //Catapult has been trying to lower for 7 seconds and has not progressed. An error must have occurred
      Controller1.rumble("---...---...");
      Controller1.Screen.setCursor(3,0);
      Controller1.Screen.print("Cata Lower Failed");
      std::cout << "Cata Main Lower Failed";
      catapultMotor.stop(coast);
      catapultDriverState = 0;
      catapultTimer.clear();
    }
    break;
  case 2:
    //Catapult is in ready-to-fire position and awaiting the fire button.
    catapultMotor.stop(brake);
    if(fireButton){
      //Fire the catapult
      catapultDriverState = 3;
      catapultTimer.clear();
    }
    break;
  case 3:
    //Catapult is in the process of moving downward to fire
    catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    if(!catapultLimitSwitch.pressing()){
      //Catapult has fired and the motor should stop.
      catapultMotor.stop(coast);
      catapultDriverState = 0;
      catapultTimer.clear();
    }
    if(catapultTimer.time(msec)>catapultFireMaxTime){
      //Catapult firing failed.
      Controller1.rumble("-.-.");
      std::cout << "Cata Main Lower Failed";

    }
    break;

  default:
    break;
  }

  //Manual Partner control:
  if(Controller2.ButtonA.pressing()){
    //Catapult Manual Control 1
    /**
     * In this mode, the partner controller can manually set the catapult to each state and it will automatically run as normal.
     * 
     */
    Controller2.Screen.clearScreen();
    Controller2.Screen.setCursor(0,0);
    Controller2.Screen.print("Mode:");
    Controller2.Screen.print(catapultDriverState);
    Controller2.Screen.print(" (D Resets)");
    Controller2.Screen.newLine();
    Controller2.Screen.print("(L-/R+) Vel: ");
    Controller2.Screen.print(catapultVelocity);
    Controller2.Screen.newLine();
    Controller2.Screen.print("(U) Auto: ");
    Controller2.Screen.print(catapultAutoLowering);
    // Controller2.Screen.
    if(Controller2.ButtonUp.pressing() && !Controller2PressedLast){
      //Toggle auto-lowering
      catapultAutoLowering = !catapultAutoLowering;
      Controller2PressedLast = true;
    }else if(Controller2.ButtonLeft.pressing() && !Controller2PressedLast){
      //Decrease speed
      catapultVelocity -=10;
      Controller2PressedLast = true;
    }else if(Controller2.ButtonRight.pressing() && !Controller2PressedLast){
      //Increase speed
      catapultVelocity +=10;
      Controller2PressedLast = true;
    }else if(Controller2.ButtonDown.pressing() && !Controller2PressedLast){
    catapultDriverState = 0;
    catapultMotor.stop(coast);
    Controller2PressedLast = true;
    }else if(Controller2.ButtonY.pressing()){
      catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    }else{
      Controller2PressedLast = false;
    }
  }

}
