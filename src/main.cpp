/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX Team 63600C                                           */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Code for Team 63600C                          */ 
/*                                                                            */
/*----------------------------------------------------------------------------*/

// "vex.h" library is necessary for all VEXcode programs
#include "vex.h"
//This includes all files from sylib. We haven't used this yet but plan to for addressable LED lights
#include "sylib/sylib.hpp"
// "iostream" allows us to print to the terminal and use std::strings.
#include "iostream"
// "config.cpp" has almost all configuration variables that we may want to adjust
#include "config.cpp"

// "autonRoutines.cpp" contains all the autonomous routines
#include "autonRoutines.cpp"
// "driverFunctions.cpp" contains all functions used in driving.
#include "driverFunctions.cpp"

//This tells the code to default to interpreting all our code in the context of vex
using namespace vex;

// A global instance of competition
competition Competition;



/* Pre auton runs when the code is paused by the field controller.
 * This is where we run the brain screen auton selection.
 * The brain screen auton selector sets the variable 'autonSelect'. Without the selector, this is declared and defined to a default value in "config.cpp" 
 */
void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  //Initializes the Sylib library. This controls the LEDs
  sylib::initialize();
  //Makes sure the end
  endgameL.set(false);
  endgameR.set(false);
  
  //Runs the brain screen auton selector
  brainAutonSelect();

}

/* the autonomous function runs at the beginning of our autonomous period.
 * we call our own function here, 'runAuton' which references the variable from the brain screen auton selector to decide which auton routine to run
 *
 */
void autonomous(void) {  
  runAuton(autonSelect); // References "autonRoutines.cpp"
}

//Vexcode has a habit of not downloading my code unless I change something in main.cpp. To ensure this doesn't happen, I comment or uncomment one of these functions before downloading. As stated in the function name, these do nothing.
void doNothing(){}
void alsoNothing(){}
// void thisIsNothingToo(){}

/* 'usercontrol' is run during driver. Inside is a while loop that will run forever.
 * Before the while loop we initialize some things. We set a variable to false so the brain screen auton selector knows to stop running. (It is also in an infinite loop and will interfere with the driver if left running)
 * We also setup some code for displaying brain images and turn on the lights on the optical sensors.
 */
void usercontrol(void) {

  driverStarted = true;
  //Makes sure the endgame doesn't activate
  endgameL.set(false);
  endgameR.set(false);
  
  //For displaying images on the brain screen. Generates a const char * with the image filepath we are using
  const char * img = names[imgPos].c_str();    
  if(displayImages) Brain.Screen.drawImageFromFile(img, 0, 0);

  //timer endgameTimer;
  //endgameTimer.clear();

  Brain.Screen.clearScreen();

  //This is the main drive loop. This loops infinitely every 20 ms to continuously run drive code
  while (1) {
    
    //Controller2.Screen.clearScreen();
    /* 
     * When we want something to be activated by pressing a button once we need to make sure the code doesn't activate multiple times on a single button press
     * Every time we want to look for a press on Controller2 (The partner controller) we need to also check if this boolean is false.
     * After accepting a press we also need to set it to true.
     */
    if(!Controller2.ButtonA.pressing() && !Controller2.ButtonB.pressing() && !Controller2.ButtonX.pressing() && !Controller2.ButtonY.pressing() && !Controller2.ButtonUp.pressing() && !Controller2.ButtonDown.pressing() && !Controller2.ButtonLeft.pressing() && !Controller2.ButtonRight.pressing() && !Controller2.ButtonL1.pressing() && !Controller2.ButtonL2.pressing()){
      Controller2PressedLast = false;
    }
    
    if(displayImages){
      if(Brain.Screen.pressing() && Brain.Screen.xPosition() <=100 && Brain.Screen.yPosition() <=100 && displayImages){
        while(Brain.Screen.pressing()){}
        incrementImg();
        //const char * img = names[imgPos].c_str();
        Brain.Screen.drawImageFromFile(img, 0, 0);
      }

    }else{
    //Put Brain screen print code here to monitor values, etc.
    //Brain.Screen.printAt(20,20,"test1");;
      // Brain.Screen.newLine();
      // Brain.Screen.print("Ready Press = %d",readyPress);
    }

    //Runs tank drive based on joystick inputs
    tankDrive();
    //Controls the catapult based on the fire button and configuration
    updateCatapult(Controller1.ButtonL1.pressing());

    //Delay between screen presses. When this is less than zero new inputs can be accepted
    // readyPress--;
    
    
    if(Controller1.ButtonR1.pressing()/* && catapultLimitSwitch.pressing()*/){
       rollerMotor.spin(reverse, 100,pct);
    }else if(Controller1.ButtonR2.pressing()){
      rollerMotor.spin(forward, 100,pct);
    }else{
      rollerMotor.stop(brake);
    }

    
    // Actuates the cylinder controlling the endgame release
    // To avoid accidental discharge multiple buttons must be pressed simultaneously to activate the endgame
    if(Controller1.ButtonL2.pressing() && !Controller1.ButtonL1.pressing() && Controller1.ButtonR2.pressing() && Controller1.ButtonB.pressing()){
      //Launch Endgame
      endgameR.set(true);
      endgameL.set(true);
    }else{
      //Do not launch endgame
      endgameR.set(false);
      endgameL.set(false);
    }

    wait(20, msec); // Sleep the task for a short amount of time to prevent wasted resources.
  }
}


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
