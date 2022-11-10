/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */ 
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)] 
// frontLeftMotor       motor         9               
// backLeftMotor        motor         10              
// backRightMotor       motor         7               
// frontRightMotor      motor         8               
// Controller1          controller                    
// flywheelMotors       motor_group   1, 2            
// indexPneumatic       digital_out   H               
// bottomOptical        optical       20              
// topOptical           optical       19              
// rollerMotor          motor         16              
// intakeMotors         motor_group   4, 5            
// ---- END VEXCODE CONFIGURED DEVICES ----

// "vex.h" library is necessary for all VEXcode programs
#include "vex.h"
// "iostream" allows us to print to the terminal and use std::strings.
#include "iostream"
// "confic.cpp" has almost all configuration variables that we may want to adjust
#include "config.cpp"

// "autonRoutines.cpp" contains all the autonomous routines
#include "autonRoutines.cpp"
// "driverFunctions.cpp" contains all functions used in driving.
#include "driverFunctions.cpp"

//This includes all files from sylib. We haven't used this yet but plan to.
#include "sylib/sylib.hpp"

//This tells the code to default to interpreting all our code in the context of vex
using namespace vex;

// A global instance of competition
competition Competition;



/**
 * * 63600C 2023
 *
 * TODO: Create better X drive autonomous methods (maybe a class??)
 * TODO: Add air-saving code to limit index pneumatic actuation to allow enough air for the endgame.
 * TODO: Possibly change indexTime throughout the match to account for having less air pressure at the end of the match. 
 * 
 * !test
 * ?test
 * 
 * Example changes to a comment
 */

/* Pre auton runs when the code is paused by the field controller. 
 * This is where we run the brain screen auton selection.
 * The brain screen auton selector sets the variable 'autonSelect', declared and defined to a default value in "config.cpp" 
 */
void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  sylib::initialize();
  endgame.set(false);
  
  
  brainAutonSelect();
  //rollerSpin(true);


  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/* the autonomous function runs at the begining of our autonomous period. 
 * we call our own function here, 'runAuton' which references the variable from the brain screen auton selector to decide which auton routine to run
 *
 */
void autonomous(void) {
  runAuton(autonSelect); // References "autonRoutines.cpp"
  //rollerSpinAuton(true);
  //Test123456
}

/* 'usercontrol' is run during driver. Inside is a while loop that will run forever.
 * Before the while loop we initialize some things. We set a variable to false so the brain screen auton selector knows to stop running. (It is also in an infinite loop and will interphere with the driver if left running)
 * We also setup some code for displaying brain images and turn on the lights on the optical sensors.
 */
void usercontrol(void) {
  // User control code here, inside the loop
  driverStarted = true;
  endgame.set(false);
  
  const char * img = names[imgPos].c_str();    
  if(displayImages) Brain.Screen.drawImageFromFile(img, 0, 0);

  topOptical.setLightPower(90,pct);
  bottomOptical.setLightPower(90,pct);
  

  timer endgameTimer;
  endgameTimer.clear();

  while (1) {
    Controller2.Screen.clearScreen();
    if(!Controller2.ButtonA.pressing() && !Controller2.ButtonB.pressing() && !Controller2.ButtonX.pressing() && !Controller2.ButtonY.pressing() && !Controller2.ButtonUp.pressing() && !Controller2.ButtonDown.pressing() && !Controller2.ButtonLeft.pressing() && !Controller2.ButtonRight.pressing() && !Controller2.ButtonL1.pressing() && !Controller2.ButtonL2.pressing()){
      Controller2PressedLast = false;
    }
    Controller1.Screen.setCursor(4,1);
    Controller1.Screen.print("C2: %d", Controller2PressedLast);
    if(displayImages){
      //const char * img = names[imgPos].c_str();
      
      //Brain.Screen.drawImageFromFile(img, 0, 0);

      if(Brain.Screen.pressing() && Brain.Screen.xPosition() <=100 && Brain.Screen.yPosition() <=100 && displayImages){
        while(Brain.Screen.pressing()){}
        incrementImg();
        //const char * img = names[imgPos].c_str();
        Brain.Screen.drawImageFromFile(img, 0, 0);
      }

    }else{
    //Put Brain screen print code here to monitor values, etc.
    //Brain.Screen.printAt(20,20,"test1");
    }

    flywheelSpeedControl();  
    xDrive();

    if(!displayImages){
      Brain.Screen.newLine();
      Brain.Screen.print("Ready Press = %d",readyPress);
    }
    if((Controller1.ButtonX.pressing() || Controller2.ButtonL1.pressing())&& readyPress<=0){
      enableFlywheel = !enableFlywheel;
      readyPress = readyPressDelay;
    }

    if((Controller1.ButtonL1.pressing() || Controller1.ButtonL2.pressing())&& readyPress<=0){
      indexPneumatic.set(true);
      flywheelDelay = indexTime;
      readyPress = readyPressDelay;
    }
    

    // if(flywheelDelay<=0){
    //    indexPneumatic.set(false);
    // }

    //When flywheelDelay>0 cylinder is extended
    //When flywheelDelay is between 0 and -indexTimeBetweenDiscs the cylinder is retracted
    //When flywheelDelay is less than -indexTimeBetweenDiscs if the fire button is pressed flywheelDelay is set to index time.
    //If not pressed, then the cylinder is told to retract again.
  
    if(Controller1.ButtonL1.pressing() || Controller2.ButtonL2.pressing()){
      if(flywheelDelay<=-indexTimeBetweenDiscs) flywheelDelay = indexTime;
    }
    
    if(flywheelDelay>0) indexPneumatic.set(true);
    else indexPneumatic.set(false);
    
    readyPress--;
    flywheelDelay--;
    


    // if(enableFlywheel) {
    //   flywheelMotors.spin(fwd,flywheelSpeed,pct);
    // } else{
    //   flywheelMotors.stop(coast);
    // }
    if(enableFlywheel) {
      flywheelMotors.spin(fwd,flywheelSpeed,volt);
    } else{
      flywheelMotors.stop(coast);
    }
    
    if(!displayImages){
      Brain.Screen.newLine();
      Brain.Screen.print("Flywheel Efficiency (pct): %d",flywheelMotors.efficiency(percent));
      Brain.Screen.newLine();
      Brain.Screen.print("FlywheelDelay = %d",flywheelDelay);
    }
    if(Controller1.ButtonR1.pressing()){
      intakeMotors.spin(forward,100,pct);
      rollerMotor.spin(reverse);
    }else if(Controller1.ButtonR2.pressing()){
      intakeMotors.spin(reverse,60,pct);
      rollerMotor.spin(forward);
    }else{
      intakeMotors.stop(coast);
      if(!Controller1.ButtonX.pressing()){
        rollerMotor.stop(brake);
      }
    }


    //Actuates the cylinder controlling the endgame release
    if(Controller1.ButtonL2.pressing() && !Controller1.ButtonL1.pressing() && Controller1.ButtonR2.pressing() && Controller1.ButtonB.pressing()){
      endgame.set(true);
    }else{
      endgame.set(false);
    }


    runDriverRollerSpinning(true);
    
    if(endgameTimer.time()>((60+35)*1000)){
      Controller1.Screen.setCursor(4,10);
      Controller1.Screen.print("Endgame");
    } 

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
