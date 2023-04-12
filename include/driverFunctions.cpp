#include "vex.h"
#include "iostream"


//Code to display images on the brain screen 
int imgPos = 0; // The initial image to display
void incrementImg(){
  imgPos++;
  if(imgPos>=(imageCount-1)) imgPos = 0;
  Brain.Screen.clearScreen(color::black);
}

/**
 * @brief Updates drive motor tank drive based on controller inputs
 * @return * void 
 */
void tankDrive(){
  float leftPower = Controller1.Axis3.value();
  float rightPower = Controller1.Axis2.value();

  leftDrivetrain.spin(fwd,leftPower,velocityUnits::pct);
  rightDrivetrain.spin(fwd,rightPower,velocityUnits::pct);
  
}


//Lowest rotation 213
//Highest point where we can still intake discs 222.2
//High threshold: 270
//Highest point total: 275
//higher numbers are higher

/**
 * @brief Updates the catapultState variable and runs the catapult motor when appropriate.
 * @param fireButton boolean input for whether the fire button is pressed
 */

/**
 * @brief Used to check whether the catapult is in the upper zone of its travel.
 * This zone is the highest point and a bit below to account for error.
 * 
 * @return true when the catapult is in this zone
 * @return false else
 */
bool cataZone1(){
  return catapultRotationSensor.angle(deg)>270;
  }
/**
 * @brief Used to check whether the catapult is in the hold zone of its travel
 * This zone is the point at which the catapult waits for firing.
 * 
 * @return true when the catapult is in this zone
 * @return false else
 */
bool cataZone2(){
  return catapultRotationSensor.angle(deg)<221;
}

void updateCatapult(bool fireButton){
  // //When connected to the VS Code console this prints debug information. We keep this code commented to save processor time.
  // std::cout << "\n"/*updateCatapult run. State: "*/;
  // std::cout << catapultDriverState;
  // std::cout << ", L: ";//Limit
  // std::cout << catapultLimitSwitch.pressing();
  // std::cout << ", T: ";//Timer
  // std::cout << catapultTimer.time(msec);
  // std::cout << ", B: ";//Button
  // std::cout << fireButton;
  //Based on what state the catapult is in we tell it to move in certain ways and watch for certain things to happen
  switch (catapultDriverState){
  case 0:
    //Catapult is raised after firing. Waiting for enough time to pass before automatically lowering if appropriate
    catapultMotor.stop(brake);

    //If enough time has elapsed after firing for the catapult to bounce and release its energy.
    if(catapultTimer.time(sec)>1){
      //If either automatic lowering is enabled or the catapult fire button is pressed, lower the catapult
      if(catapultAutoLowering || fireButton){
        //Lower the catapult by incrementing the state
        catapultDriverState = 1;
        //Clears the timer so we know how long is spent in each state
        catapultTimer.clear();
      }
    }
    break;
  case 1:
    //Lowering catapult into intake-position. Lowering is stopped when limit switch is pressed
    catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);

    if(cataZone2()){
      //The catapult has reached it's rest position and the motor needs to stop moving.
      catapultMotor.stop(brake);
      //Increment catapult state
      catapultDriverState = 2;
      //Clears catapult timer so we know how long is spent in each state
      catapultTimer.clear();
    }else if(catapultTimer.time(msec)>catapultLowerMaxTime){
      //Catapult has been trying to lower for 7 seconds and has not progressed. An error must have occurred
      //Rumble controller to alert driver
      Controller1.rumble("---...---...");
      //Write text to controller to alert driver
      Controller1.Screen.setCursor(3,0);
      Controller1.Screen.print("Cata Lower Failed");
      //Outputs to console for debugging
      //std::cout << "Cata Main Lower Failed";
      
      //Let the motor coast and set it to its upwards state
      catapultMotor.stop(coast);
      catapultDriverState = 0;
      //Clears catapult timer so we know how long is spent in each state
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
    if(cataZone1()){
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
