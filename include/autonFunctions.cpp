
#include "vex.h"

/* Configuration Variables for autonomous functions:
 *
 * defaultAutonDriveSpeed: default speed for driving in auton if no speed is specified. (See overloaded functions below.)
 * defaultAutonTurnSpeed: default speed for turning in auton if no speed is specified. (See overloaded functions below.)
 * defaultRotationUnits: default units for rotation if none are specified. (See overloaded functions below.)
 * defaultDistanceUnits: default units for distance if none are specified. (See overloaded functions below.)
 *
 * drivetrainRatio: the equivalent gear ratio in the drivetrain. For us, this is sqrt(2) because of X-drive
 * drivetrainGearRatio: the gear ratio on each wheel of the drivetrain. For us this is a 5:4 ratio meaning a factor of 5/4 or 1.25
 * 
 * wheelCircumference: circumference of each wheel (inches)
 * 
 * driveFactor: distance traveled for one revolution of the wheel. Used in distance based driving.
 */

const float defaultAutonDriveSpeed = 30;
const float defaultAutonTurnSpeed = 15;
vex::rotationUnits defaultRotationUnits = rotationUnits::rev;
vex::distanceUnits defaultDistanceUnits = distanceUnits::in;

const float drivetrainGearRatio =48/72;
const float wheelCircumference = 3.25*3.141592;

//Drive factor is the total distance traveled for one revolution of the motor. This is used to calculate distances for distance-based auton driving
const float driveFactor = wheelCircumference*drivetrainGearRatio;
/**
 * @brief Drives the robot forward for specified rotations at a specified velocity
 * 
 * @param distance The rotations to drive
 * @param distanceUnits Units for rotations
 * @param velocity The velocity to drive
 * @param velocityUnits Units for velocity
 * @param waitForCompletion Whether or not the function should wait for the drive to be completed before advancing
 */
void driveFwd(float distance, rotationUnits distanceUnits, float velocity, velocityUnits velocityUnits, bool waitForCompletion = true){
  leftDrivetrain.spinFor(forward,distance,distanceUnits,velocity,velocityUnits,false);
  rightDrivetrain.spinFor(forward,distance,distanceUnits,velocity,velocityUnits,waitForCompletion);
}
/**
 * @brief Drives the robot forward for specified rotations at a default velocity
 * 
 * @param distance The rotations to drive
 * @param distanceUnits Units for rotations
 * @param waitForCompletion Whether or not the function should wait for the drive to be completed before advancing
 */
void driveFwd(float distance,rotationUnits distanceUnits){
  driveFwd(distance,distanceUnits,defaultAutonDriveSpeed,velocityUnits::pct);
}
/**
 * @brief Drives the robot forward for a specified distance in wheel revolutions
 * @param distance The rotation to drive in revolutions

 * @param waitForCompletion Whether or not the function should wait for the drive to be completed before advancing
 */
void driveFwd(float distance){
  driveFwd(distance,defaultRotationUnits);
}
/**
 * @brief Drives the robot reverse for specified rotations at a specified velocity
 * 
 * @param distance The rotations to drive
 * @param distanceUnits Units for rotations
 * @param velocity The velocity to drive
 * @param velocityUnits Units for velocity
 * @param waitForCompletion Whether or not the function should wait for the drive to be completed before advancing
 */
void driveRev(float distance, rotationUnits distanceUnits, float velocity, velocityUnits velocityUnits, bool waitForCompletion = true){
  leftDrivetrain.spinFor(reverse,distance,distanceUnits,velocity,velocityUnits,false);
  rightDrivetrain.spinFor(reverse,distance,distanceUnits,velocity,velocityUnits,waitForCompletion);
}
/**
 * @brief Drives the robot reverse for specified rotations at a default velocity
 * 
 * @param distance The rotations to drive
 * @param distanceUnits Units for rotations
 * @param waitForCompletion Whether or not the function should wait for the drive to be completed before advancing
 */
void driveRev(float distance,rotationUnits distanceUnits){
  driveRev(distance,distanceUnits,defaultAutonDriveSpeed,velocityUnits::pct);
}
/**
 * @brief Drives the robot forward for a specified distance in wheel revolutions
 * @param distance The rotation to drive in revolutions

 * @param waitForCompletion Whether or not the function should wait for the drive to be completed before advancing
 */
void driveRev(float distance){
  driveRev(distance,defaultRotationUnits);
}

/**
 * @brief Turns the robot right in place for a specified wheel rotation at a specified velocity
 * 
 * @param distance The rotations for each wheel to move
 * @param distanceUnits Rotation units
 * @param velocity Wheel velocity
 * @param velocityUnits Velocity units
 * @param waitForCompletion Whether or not the function should wait for the drive to be completed before advancing
 */
void turnRight(float distance, rotationUnits distanceUnits, float velocity, velocityUnits velocityUnits, bool waitForCompletion = true){
  leftDrivetrain.spinFor(forward,distance,distanceUnits,velocity,velocityUnits, false);
  rightDrivetrain.spinFor(reverse,distance,distanceUnits,velocity,velocityUnits, waitForCompletion);
}
/**
 * @brief Turns the robot right in place for a specified wheel rotation at a specified velocity
 * 
 * @param distance The rotations for each wheel to move
 * @param distanceUnits Rotation units
 */
void turnRight(float distance,rotationUnits distanceUnits){
  turnRight(distance,distanceUnits,defaultAutonTurnSpeed,velocityUnits::pct);
}
/**
 * @brief Turns the robot left in place for a specified wheel rotation at a specified velocity
 * 
 * @param distance The rotations for each wheel to move
 * @param distanceUnits Rotation units
 * @param velocity Wheel velocity
 * @param velocityUnits Velocity units
 * @param waitForCompletion Whether or not the function should wait for the drive to be completed before advancing
 */
void turnLeft(float distance, rotationUnits distanceUnits, float velocity, velocityUnits velocityUnits, bool waitForCompletion = true){
  leftDrivetrain.spinFor(reverse,distance,distanceUnits,velocity,velocityUnits, false);
  rightDrivetrain.spinFor(forward,distance,distanceUnits,velocity,velocityUnits, waitForCompletion);
}
/**
 * @brief Turns the robot right in place for a specified wheel rotation at a specified velocity
 * 
 * @param distance The rotations for each wheel to move
 * @param distanceUnits Rotation units
 */
void turnLeft(float distance,rotationUnits distanceUnits){
  turnLeft(distance,distanceUnits,defaultAutonTurnSpeed,velocityUnits::pct);
}

/**
 * @brief Sets the timeout value for all drive motors
 * 
 * @param time Time for the motor timeout
 * @param units Time units
 */
void driveTimeout(int time, timeUnits units){
  leftDrivetrain.setTimeout(time,units);
  rightDrivetrain.setTimeout(time,units);
}
/**
 * @brief Sets the timeout value for all drive motors in seconds
 * 
 * @param time Time for the motor timeout
 */
void driveTimeout(int time){
  driveTimeout(time,seconds);
}

/**
 * @brief Converts a distance with specified units into a float quantity of inches
 * 
 * @param input Distance
 * @param distUnits Distance Units
 * @return Distance converted into inches
 */
float convertToInch(float input, distanceUnits distUnits){
  // if(distUnits == inches || distUnits == distanceUnits::in){
  //   return input;
  // }else 
  if(distUnits==distanceUnits::mm) return 25.4*input;
  if(distUnits==distanceUnits::cm) return 2.54*input;
  return input;
  
}
/**
 * @brief Drives the robot forward for specified distance at a specified velocity based on the configuration about the drivetrain
 * 
 * @param distance Distance to drive for
 * @param distUnits Distance Units
 * @param velocity Velocity to drive
 * @param velUnits Velocity Units
 * @param waitForCompletion Whether or not the function should wait for the drive to be completed before advancing
 */
void driveFwd(float distance, distanceUnits distUnits, float velocity, velocityUnits velUnits, bool waitForCompletion = true){
  driveFwd(convertToInch(distance,distUnits)/driveFactor,rotationUnits::rev,velocity,velUnits, waitForCompletion);
}
/**
 * @brief Drives the robot forward for specified distance at a specified velocity in percent based on the configuration about the drivetrain
 * 
 * @param distance Distance to drive for
 * @param distUnits Distance Units
 * @param velocity Velocity to drive
 * @param waitForCompletion Whether or not the function should wait for the drive to be completed before advancing
 */
void driveFwd(float distance, distanceUnits distUnits, float velocity, bool waitForCompletion = true){
  driveFwd(distance, distUnits,velocity, velocityUnits::pct, waitForCompletion);
}
/**
 * @brief Drives the robot forward for specified distance at a default velocity based on the configuration about the drivetrain
 * 
 * @param distance Distance to drive for
 * @param distUnits Distance Units
 * @param waitForCompletion Whether or not the function should wait for the drive to be completed before advancing
 */
void driveFwd(float distance, distanceUnits distUnits, bool waitForCompletion = true){
  driveFwd(distance, distUnits, defaultAutonDriveSpeed, waitForCompletion);
}
/**
 * @brief Drives the robot forward for specified distance with default units based on the configuration about the drivetrain
 * 
 * @param distance Distance to drive for
 * @param distUnits Distance Units
 * @param velocity Velocity to drive
 * @param velUnits Velocity Units
 * @param waitForCompletion Whether or not the function should wait for the drive to be completed before advancing
 */
void driveFwd(float distance, bool waitForCompletion = true){
  driveFwd(distance, defaultDistanceUnits, waitForCompletion);
}
/**
 * @brief Drives the robot forward for specified distance with default units and a specified velocity wih specified units based on the configuration about the drivetrain
 * 
 * @param distance Distance to drive for
 * @param velocity Velocity to drive
 * @param velUnits Velocity Units
 * @param waitForCompletion Whether or not the function should wait for the drive to be completed before advancing
 */
void driveFwd(float distance, float velocity, velocityUnits velUnits, bool waitForCompletion = true){
  driveFwd(distance, defaultDistanceUnits, velocity, velUnits, waitForCompletion);
}
/**
 * @brief Drives the robot forward for specified distance ad velocity, each with default units based on the configuration about the drivetrain
 * 
 * @param distance Distance to drive for
 * @param velocity Velocity to drive
 * @param waitForCompletion Whether or not the function should wait for the drive to be completed before advancing
 */
void driveFwd(float distance, float velocity, bool waitForCompletion = true){
  driveFwd(distance, velocity, velocityUnits::pct, waitForCompletion);
}

/**
 * @brief Drives the robot reverse for specified distance and velocity each with specified units based on the configuration about the drivetrain
 * 
 * @param distance Distance to drive for
 * @param distUnits Distance Units
 * @param velocity Velocity to drive
 * @param velUnits Velocity Units
 * @param waitForCompletion Whether or not the function should wait for the drive to be completed before advancing
 */
void driveRev(float distance, distanceUnits distUnits, float velocity, velocityUnits velUnits, bool waitForCompletion = true){
  driveRev(convertToInch(distance,distUnits)/driveFactor,rotationUnits::rev,velocity,velUnits, waitForCompletion);
}
/**
 * @brief Drives the robot reverse for specified distance with default units with specified units and velocity with default units based on the configuration about the drivetrain
 * 
 * @param distance Distance to drive for
 * @param distUnits Distance Units
 * @param velocity Velocity to drive
 * @param waitForCompletion Whether or not the function should wait for the drive to be completed before advancing
 */ 
void driveRev(float distance, distanceUnits distUnits, float velocity, bool waitForCompletion = true){
  driveRev(distance, distUnits,velocity, velocityUnits::pct, waitForCompletion);
}
/**
 * @brief Drives the robot reverse for specified distance with specified units and a default velocity based on the configuration about the drivetrain
 * 
 * @param distance Distance to drive for
 * @param distUnits Distance Units
 * @param waitForCompletion Whether or not the function should wait for the drive to be completed before advancing
 */
void driveRev(float distance, distanceUnits distUnits, bool waitForCompletion = true){
  driveRev(distance, distUnits, defaultAutonDriveSpeed, waitForCompletion);
}
/**
 * @brief Drives the robot reverse for specified distance with default units based on the configuration about the drivetrain
 * 
 * @param distance Distance to drive for
 * @param waitForCompletion Whether or not the function should wait for the drive to be completed before advancing
 */
void driveRev(float distance, bool waitForCompletion = true){
  driveRev(distance, defaultDistanceUnits, waitForCompletion);
}
/**
 * @brief Drives the robot reverse for specified distance with default units at a velocity with specified units based on the configuration about the drivetrain
 * 
 * @param distance Distance to drive for
 * @param velocity Velocity to drive
 * @param velUnits Velocity Units
 * @param waitForCompletion Whether or not the function should wait for the drive to be completed before advancing
 */
void driveRev(float distance, float velocity, velocityUnits velUnits, bool waitForCompletion = true){
  driveRev(distance, defaultDistanceUnits, velocity, velUnits, waitForCompletion);
}
/**
 * @brief Drives the robot reverse for specified distance with default units and a specified velocity with default units based on the configuration about the drivetrain
 * 
 * @param distance Distance to drive for
 * @param velocity Velocity to drive
 * @param waitForCompletion Whether or not the function should wait for the drive to be completed before advancing
 */
void driveRev(float distance, float velocity, bool waitForCompletion = true){
  driveRev(distance, velocity, velocityUnits::pct, waitForCompletion);
}


//Deprecated methods used to check the optical sensor roller thresholds
bool topRollerRed(){
  return topOptical.hue()<=40 || topOptical.hue()>340;
}
bool topRollerBlue(){
  return topOptical.hue()<=290 && topOptical.hue()>=125;
}
bool bottomRollerRed(){
  return bottomOptical.hue()<=40 || topOptical.hue()>340;
}
bool bottomRollerBlue(){
  return bottomOptical.hue()<=290 && bottomOptical.hue()>=125;
}


//Deprecated method to spin rollers based on two optical sensors
void rollerSpin(bool onRedSide, int rollerVelocity){
    
    //Automatic Roller Code: We are RED
    //R/R: Rotate UP 
    //R/B: Correct Position
    //B/B: Rotate Down
    //B/R: Rotate Down (either way works)
    //We are BLUE:
    //R/R: Rotate Down
    //R/B: Rotate Down (either)
    //B/B: Rotate Up
    //B/R: Correct Position
    //Complete documentation in Engineering Notebook Volume 1, Page 90-91
    vex::directionType preferredDirection = forward;
    const char * rumblePattern = ".";
    rollerMotor.setStopping(coast);
    if(topRollerRed()){ //Red
      if(bottomRollerRed()){
        //R/R
        if(onRedSide){
          //Rotate Up
          rollerMotor.spin(reverse,rollerVelocity,percentUnits::pct);
        }else{
          //Rotate Down
          rollerMotor.spin(fwd,rollerVelocity,percentUnits::pct);
        }
      }else{
        //R/B
        if(onRedSide){
          //Correct Position; Vibrate Controller
          rollerMotor.stop(brake);
          Controller1.rumble(rumblePattern);
        }else{
          //Rotate Down (either)
          rollerMotor.spin(preferredDirection,rollerVelocity,percentUnits::pct);
        }
      }
    }else{ //Blue
      if(bottomRollerRed()){
        //B/R
        if(onRedSide){
          //Rotate Down (either)
          rollerMotor.spin(preferredDirection,rollerVelocity,percentUnits::pct);
        }else{
          //Correct Position; vibrate Controller
          rollerMotor.stop(brake);
          Controller1.rumble(rumblePattern);
        }
      }else{
        //B/B
        if(onRedSide){
          //Rotate Down
          rollerMotor.spin(fwd,rollerVelocity,percentUnits::pct);
        }else{
          //Rotate Up
          rollerMotor.spin(reverse,rollerVelocity,percentUnits::pct);
        }
      }
    }
}
void rollerSpin(bool onRedSide){
  rollerSpin(onRedSide,45);
}

void autonRollerSpinning(bool onRedSide, int timeDelay, bool acceptGreenForBlue = true){
  timer rollerSpinTimer;
    rollerSpinTimer.clear();
    //float rollerSpinTime = 2.5; //Units: seconds
    while(rollerSpinTimer<timeDelay){
        if((topRollerRed() || topRollerBlue()) && (bottomRollerRed() || bottomRollerBlue())){ //Automatic Roller Spinning Only works if both sensors have a color
            rollerSpin(onRedSide);
        }else{
          if(onRedSide){
            if(topRollerRed()){
              Controller1.rumble("- .");
            }else if(topRollerBlue()){
              rollerMotor.spin(fwd,60,velocityUnits::pct);
            }else{
              Controller1.rumble("...");
            }
          }else{
            if(topRollerBlue()){
              Controller1.rumble("- .");
            }else if(topRollerRed()){
              rollerMotor.spin(fwd,60,velocityUnits::pct);
            }else{
              Controller1.rumble("...");
            }
          }
        }
    }
}




/* Brain Screen Auton Select
 *  Called once in preAuton();
 *  Has an infinite loop that will run until either auton starts or the loop is broken by 
 *  a final selection or preAuton ending.
 * 
 */

int autonSelectScreen = 0;
int autonSelectBank = 0;
int maxAutonBank = 3;
bool finalAutonSelection = false;
bool pressedLast = false;
/* Game Auton Routines
 * 0: Do Nothing
 * 1: Push preloads into low goal
 * 2: Spin Roller to RED (Can be used in Skills)
 *      -Starts on Left Side
 * 3: Spin Roller to BLUE
 *      -Starts on Right Side
 * 
 * Skills Routines:
 * 4: Spin Roller, Shoot preloads into low goal and spins another roller (To RED for Skills)
 * 5: Game Auton Right RED
 * 6: Game Auton Right BLUE
 * 7 Skills Auton extended from game auton right
 */

int autonSelect = 5;
const int numAutonRoutines = 12;
//The names of each routine
const std::string autonRoutineNames[numAutonRoutines] = {
    "0.Do Nothing",
    "1.PushPreload",
    "2.RED-Spin Roller",
    "3.BLUE-Spin Roller",

    "4.Skills-2",
    "5.RED-RightGame",
    "6.BLUE-RightGame",
    "7.Skills-rgEX",

    "8.RED-LeftGame",
    "9.BLU-LeftGame",
    "10.Xyz",
    "11.Xyz"
};
//The descriptions of each routine. (Not used at the moment)
const std::string autonRoutineDescriptions[numAutonRoutines] = {
    "0 points. Does nothing. Still nothing. Doesn't move; doesn't score. Just sits there. You can do better than this. Make a better choice.",
    "2 points. Pushes preloads into the low goal. Drives forward and then backward about 2 feet.",
    "10 points. Drives forward slightly and automatically spins roller for RED for the remainder of the auton period. It sometimes needs a second but it gets there in the end. Usually.",
    "10 points. Drives forward slightly and automatically spins roller for BLUE for the remainder of the auton period. It sometimes needs a second but it gets there in the end. Usually.",
    
    "?? points. New untested",
    "20 points",
    "20 points",
    "20+endgame points",
    
    "n points",
    "n points",
    "n points",
    "n points"
};
//The color of each button in the auton selector
const color routineColors[numAutonRoutines] = {
    color(230),
    color(69,232,80),
    color(232,80,69),
    color(80, 69, 232),

    color(161,69,232),
    color(232,80,69),
    color(80, 69, 232),
    color(80,232,69),

    color(252,80,80),
    color(80,69,232),
    color(156,89,209),
    color(44,44,44) 
};
/**
 * @brief Displays a menu on the brain screen to select autonomous routines. See Engineering Notebook Volume 1 pages 111-113 and Volume 2 pages 2-3 for complete description
 * 
 */
void brainAutonSelect(){ // Run in pre auton 
    //Brain Screen is 480x272 pixels 

    const int buttonMargin = 7;
    const int bankButtonWidth = 130;
    const int bankButtonHeight = 90;
    const int routinesOnEachScreen = 4;

    const int arrowSize = 30;
    
    const fontType routineNameFont = vex::fontType::mono15;
    const fontType routineDescriptionFont = vex::fontType::mono15;
    const fontType routineConfirmNameFont = vex::fontType::mono40;
    const fontType finalizeFont = vex::fontType::mono60;
    const int routineNumberOffset = 3;
    
    const int autonButtonWidth = (480-((1+routinesOnEachScreen)*buttonMargin))/routinesOnEachScreen;

    //Colors: https://www.color-hex.com/color-palette/1019156
    color backgroundColor = color(30);
    color bankBackgroundColor = color(230);
    //color autonButtonBackgroundColor = color(230);
    color bankArrowColor = color(16,14,17);
    color autonTextColor = color(16,14,17);
    color backButtonColor = color(204,12,12);
    color finalizeButtonColor = color(78,202,22);
    color finalizeTextColor = color(16,14,17);


    while(!finalAutonSelection && !driverStarted){
        Brain.Screen.setFillColor(backgroundColor);
        Brain.Screen.drawRectangle(0,0,480,272);
        Brain.Screen.setPenWidth(0);

        if(!Brain.Screen.pressing()){
          pressedLast = false;
        }

        switch (autonSelectScreen)
        {
        case 0:{// Selection Screen (See page 1.111 in the Notebook)
            //Bank 0 is auton select 0-3
            
            //Drawing:
            //Bank Buttons
            Brain.Screen.setFillColor(bankBackgroundColor);
            Brain.Screen.drawRectangle(buttonMargin,272-buttonMargin-bankButtonHeight,bankButtonWidth,bankButtonHeight);
            Brain.Screen.drawRectangle(480-buttonMargin-bankButtonWidth,272-buttonMargin-bankButtonHeight,bankButtonWidth,bankButtonHeight);
            //Bank Arrows
            // Brain.Screen.setFillColor(bankArrowColor);
            // Brain.Screen.drawRectangle(buttonMargin+bankButtonWidth/2-arrowSize,272-bankButtonHeight/2-arrowSize/2,arrowSize*3,arrowSize);
            
            //Auton Buttons
            for(int i = 0; i<routinesOnEachScreen; i++){
                //Draws the rectangle for each selection button
                Brain.Screen.setFillColor(routineColors[i+routinesOnEachScreen*autonSelectBank]);
                Brain.Screen.drawRectangle(buttonMargin+(buttonMargin+autonButtonWidth)*i,buttonMargin,autonButtonWidth,272-buttonMargin*3-bankButtonHeight);
                
                Brain.Screen.setFillColor(autonTextColor);
                Brain.Screen.setFont(routineNameFont);
                const char * name = autonRoutineNames[i+routinesOnEachScreen*autonSelectBank].c_str();
                Brain.Screen.printAt(buttonMargin+(buttonMargin+autonButtonWidth)*i+routineNumberOffset,buttonMargin+routineNumberOffset+15,name);
                
            }
            //Checking:
            if(Brain.Screen.pressing() && !pressedLast){
              pressedLast = true;
              if(Brain.Screen.xPosition()<=buttonMargin+bankButtonWidth && Brain.Screen.yPosition()>=272-bankButtonHeight-buttonMargin){
                  autonSelectBank--;
                  if(autonSelectBank<0)autonSelectBank = maxAutonBank;
              }else if(Brain.Screen.xPosition()>=(480-buttonMargin-bankButtonWidth) && Brain.Screen.yPosition()>=272-bankButtonHeight-buttonMargin){
                  autonSelectBank++;
                  if(autonSelectBank>maxAutonBank)autonSelectBank = 0;
              }else{
                  for(int i = 0; i<routinesOnEachScreen; i++){
                      if(Brain.Screen.yPosition()<=(480-bankButtonHeight-2*buttonMargin) && Brain.Screen.xPosition()>=i*(480/routinesOnEachScreen) && Brain.Screen.xPosition()<=(i+1)*(480/routinesOnEachScreen)){
                          
                          autonSelect = i+autonSelectBank*routinesOnEachScreen;
                          autonSelectScreen = 1;
                      }                        
                  }
              }
            }
            


            break;
        }
        case 1: {// Final Confirmation (See page 1.111 in the Notebook)

          //Drawing
          //Back Button
          Brain.Screen.setFillColor(backButtonColor);
          Brain.Screen.drawRectangle(buttonMargin,buttonMargin,120-buttonMargin,100);
          Brain.Screen.setFillColor(finalizeTextColor);
          Brain.Screen.setFont(mono30);
          Brain.Screen.printAt(buttonMargin+routineNumberOffset,buttonMargin+routineNumberOffset+20,"Back");
          //Title
          Brain.Screen.setFont(routineConfirmNameFont);
          const char * nameTest = autonRoutineNames[autonSelect].c_str();
          Brain.Screen.printAt(120+buttonMargin*2,buttonMargin*3,nameTest);

          //Finalize Button
          Brain.Screen.setFillColor(finalizeButtonColor);
          Brain.Screen.drawRectangle(120,100+buttonMargin*2,240,150);
          Brain.Screen.setFont(finalizeFont);
          Brain.Screen.printAt(120+buttonMargin,100+3*buttonMargin+30,"Finalize");
          //Checking
          if(Brain.Screen.pressing() && !pressedLast){
            pressedLast = true;
            if(Brain.Screen.xPosition()<=120+buttonMargin && Brain.Screen.yPosition() <=100+buttonMargin){
              //Back button Pressed
              autonSelectScreen = 0;
            }else if(Brain.Screen.xPosition()>=120 && Brain.Screen.xPosition()<=360){
              //Finalize Button Pressed
              finalAutonSelection = true;
              autonSelectScreen = 2;
              Controller1.rumble("- - -");
            }
          }
          break;
        }
        case 2: {// Locked on one routine. (See page 1.111 in the Notebook)
          Brain.Screen.setFont(routineConfirmNameFont);
          //const char * name = autonRoutineNames[autonSelect].c_str();
          Brain.Screen.printAt(120+buttonMargin*2,buttonMargin,"null");
          Brain.Screen.printAt(120+buttonMargin,100+3*buttonMargin,"Auton Finalized");
          break;
        }
        default:
        Brain.Screen.printAt(30,30,"Error: Bad value for autonSelectScreen");
            break;
        }
        wait(20,msec);
    }
}
