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

#include "vex.h"
#include "iostream"

#include "config.cpp"

//#include "autonFunctions.cpp"
#include "autonRoutines.cpp"
#include "driverFunctions.cpp"

#include "sylib/sylib.hpp"

using namespace vex;

// A global instance of competition
competition Competition;



/**
 * * 63600C 2023
 *
 * TODO: Create better X drive autonomous methods (maybe a class??)
 * TODO: Add air-saving code to limit index pneumatic actuation to allow enough air for the endgame.
 * TODO: Possibly change indexTime throughout the match to account for having less air pressure at the end of the match. 
 * TODO: Add Partner Controller Support
 * TODO: Test auton select
 * 
 * !test
 * ?test
 * 
 * Example changes to a comment
 */



/* Game Auton Routines
 * 0: Do Nothing
 * 1: Push preloads into low goal
 * 2: Spin Roller to RED (Can be used in Skills)
 *      -Starts on Left Side
 * 3: Spin Roller to BLUE
 *      -Starts on Right Side
 * 
 * Skills Routines:
 * 11: Spin Roller, Shoot preloads into low goal and spins another roller (To RED for Skills)
 * 
 */

//bool onRedSide = true;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  sylib::initialize();
  
  
  brainAutonSelect();
  //rollerSpin(true);

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  //runAuton(autonSelect); // References "autonRoutines.cpp"
  //rollerSpinAuton(true);

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop

  
  const char * img = names[imgPos].c_str();    
  if(displayImages) Brain.Screen.drawImageFromFile(img, 0, 0);

  topOptical.setLightPower(90,pct);
  bottomOptical.setLightPower(90,pct);
  

  timer endgameTimer;
  endgameTimer.clear();

  while (1) {
    
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
    if(Controller1.ButtonL1.pressing() && readyPress<=0){
      enableFlywheel = !enableFlywheel;
      readyPress = readyPressDelay;
    }
    if(Controller1.ButtonB.pressing() && readyPress<=0){
      indexPneumatic.set(true);
      flywheelDelay = indexTime;
      readyPress = readyPressDelay;
    }
    
  
    
    readyPress--;
    flywheelDelay--;

    if(flywheelDelay<=0) indexPneumatic.set(false); 

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
    if(Controller1.ButtonL2.pressing() && !Controller1.ButtonL1.pressing() && Controller1.ButtonR2.pressing() && Controller1.ButtonX.pressing()){
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
