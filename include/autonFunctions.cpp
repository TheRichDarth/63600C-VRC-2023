
#include "vex.h"



const float defaultAutonDriveSpeed = 30;
const float defaultAutonTurnSpeed = 15;
vex::rotationUnits defaultRotationUnits = rotationUnits::rev;
vex::distanceUnits defaultDistanceUnits = distanceUnits::in;

const float drivetrainRatio = 1.414213;
const float drivetrainGearRatio =1.2;
const float wheelCircumference = 3.25*3.141592;
const float wheelDistance = 7.5; // Distance between centers of each wheel and the center of the robot on each axis. (See Notebook)

//Drive factor is the total distance traveled for one revolution of the motor. This is used to calculate distances for distance-based auton driving
const float driveFactor = wheelCircumference*drivetrainRatio*drivetrainGearRatio;

void driveFwd(float distance, rotationUnits distanceUnits, float velocity, velocityUnits velocityUnits, bool waitForCompletion = true){
  frontLeftMotor.spinFor(reverse,distance,distanceUnits,velocity,velocityUnits, false);
  frontRightMotor.spinFor(reverse,distance,distanceUnits,velocity,velocityUnits, false);
  backLeftMotor.spinFor(reverse,distance,distanceUnits,velocity,velocityUnits, false);
  backRightMotor.spinFor(reverse,distance,distanceUnits,velocity,velocityUnits, waitForCompletion);
}
void driveFwd(float distance,rotationUnits distanceUnits){
  driveFwd(distance,distanceUnits,defaultAutonDriveSpeed,velocityUnits::pct);
}
void driveFwd(float distance){
  driveFwd(distance,defaultRotationUnits);
}

void driveRev(float distance, rotationUnits distanceUnits, float velocity, velocityUnits velocityUnits, bool waitForCompletion = true){
  frontLeftMotor.spinFor(forward,distance,distanceUnits,velocity,velocityUnits, false);
  frontRightMotor.spinFor(forward,distance,distanceUnits,velocity,velocityUnits, false);
  backLeftMotor.spinFor(forward,distance,distanceUnits,velocity,velocityUnits, false);
  backRightMotor.spinFor(forward,distance,distanceUnits,velocity,velocityUnits, waitForCompletion);
}
void driveRev(float distance,rotationUnits distanceUnits){
  driveRev(distance,distanceUnits,defaultAutonDriveSpeed,velocityUnits::pct);
}
void driveRev(float distance){
  driveRev(distance,defaultRotationUnits);
}
void driveLeft(float distance, rotationUnits distanceUnits, float velocity, velocityUnits velocityUnits, bool waitForCompletion = true){
  frontLeftMotor.spinFor(reverse,distance,distanceUnits,velocity,velocityUnits, false);
  frontRightMotor.spinFor(forward,distance,distanceUnits,velocity,velocityUnits, false);
  backLeftMotor.spinFor(forward,distance,distanceUnits,velocity,velocityUnits, false);
  backRightMotor.spinFor(reverse,distance,distanceUnits,velocity,velocityUnits,waitForCompletion);
}
void driveLeft(float distance,rotationUnits distanceUnits){
  driveLeft(distance,distanceUnits,defaultAutonDriveSpeed,velocityUnits::pct);
}
void driveLeft(float distance){
  driveLeft(distance,defaultRotationUnits);
}
void driveRight(float distance, rotationUnits distanceUnits, float velocity, velocityUnits velocityUnits, bool waitForCompletion = true){
  frontLeftMotor.spinFor(forward,distance,distanceUnits,velocity,velocityUnits, false);
  frontRightMotor.spinFor(reverse,distance,distanceUnits,velocity,velocityUnits, false);
  backLeftMotor.spinFor(reverse,distance,distanceUnits,velocity,velocityUnits, false);
  backRightMotor.spinFor(forward,distance,distanceUnits,velocity,velocityUnits,waitForCompletion);
}
void driveRight(float distance,rotationUnits distanceUnits){
  driveRight(distance,distanceUnits,defaultAutonDriveSpeed,velocityUnits::pct);
}
void driveRight(float distance){
  driveRight(distance,defaultRotationUnits);
}
void turnRight(float distance, rotationUnits distanceUnits, float velocity, velocityUnits velocityUnits, bool waitForCompletion = true){
  frontLeftMotor.spinFor(forward,distance,distanceUnits,velocity,velocityUnits, false);
  frontRightMotor.spinFor(reverse,distance,distanceUnits,velocity,velocityUnits, false);
  backLeftMotor.spinFor(forward,distance,distanceUnits,velocity,velocityUnits, false);
  backRightMotor.spinFor(reverse,distance,distanceUnits,velocity,velocityUnits,waitForCompletion);
}
void turnRight(float distance,rotationUnits distanceUnits){
  turnRight(distance,distanceUnits,defaultAutonTurnSpeed,velocityUnits::pct);
}
void turnRight(float distance){
  turnRight(distance,defaultRotationUnits);
}
void turnLeft(float distance, rotationUnits distanceUnits, float velocity, velocityUnits velocityUnits, bool waitForCompletion = true){
  frontLeftMotor.spinFor(reverse,distance,distanceUnits,velocity,velocityUnits, false);
  frontRightMotor.spinFor(forward,distance,distanceUnits,velocity,velocityUnits, false);
  backLeftMotor.spinFor(reverse,distance,distanceUnits,velocity,velocityUnits, false);
  backRightMotor.spinFor(forward,distance,distanceUnits,velocity,velocityUnits, waitForCompletion);
}
void turnLeft(float distance,rotationUnits distanceUnits){
  turnLeft(distance,distanceUnits,defaultAutonTurnSpeed,velocityUnits::pct);
}
void turnLeft(float distance){
  turnLeft(distance,defaultRotationUnits);
}
void driveTimeout(int time, timeUnits units){
  frontLeftMotor.setTimeout(time,units);
  frontRightMotor.setTimeout(time,units);
  backLeftMotor.setTimeout(time,units);
  backRightMotor.setTimeout(time,units);
}
void driveTimeout(int time){
  driveTimeout(time,seconds);
}



//Distance-based auton functions:
//Distance driven = revolutions*circumference*sqrt(2)*gearRatio
//revolutions = distance/(circumference*sqrt(2)*gearRatio)


float convertToInch(float input, distanceUnits distUnits){
  // if(distUnits == inches || distUnits == distanceUnits::in){
  //   return input;
  // }else 
  if(distUnits==distanceUnits::mm) return 25.4*input;
  if(distUnits==distanceUnits::cm) return 2.54*input;
  return input;
  
}

void driveFwd(float distance, distanceUnits distUnits, float velocity, velocityUnits velUnits, bool waitForCompletion = true){
  driveFwd(convertToInch(distance,distUnits)/driveFactor,rotationUnits::rev,velocity,velUnits, waitForCompletion);
}
void driveFwd(float distance, distanceUnits distUnits, float velocity, bool waitForCompletion = true){
  driveFwd(distance, distUnits,velocity, velocityUnits::pct, waitForCompletion);
}
void driveFwd(float distance, distanceUnits distUnits, bool waitForCompletion = true){
  driveFwd(distance, distUnits, defaultAutonDriveSpeed, waitForCompletion);
}
void driveFwd(float distance, bool waitForCompletion = true){
  driveFwd(distance, defaultDistanceUnits, waitForCompletion);
}
void driveFwd(float distance, float velocity, velocityUnits velUnits, bool waitForCompletion = true){
  driveFwd(distance, defaultDistanceUnits, velocity, velUnits, waitForCompletion);
}
void driveFwd(float distance, float velocity, bool waitForCompletion = true){
  driveFwd(distance, velocity, velocityUnits::pct, waitForCompletion);
}

void driveRev(float distance, distanceUnits distUnits, float velocity, velocityUnits velUnits, bool waitForCompletion = true){
  driveRev(convertToInch(distance,distUnits)/driveFactor,rotationUnits::rev,velocity,velUnits, waitForCompletion);
}
void driveRev(float distance, distanceUnits distUnits, float velocity, bool waitForCompletion = true){
  driveRev(distance, distUnits,velocity, velocityUnits::pct, waitForCompletion);
}
void driveRev(float distance, distanceUnits distUnits, bool waitForCompletion = true){
  driveRev(distance, distUnits, defaultAutonDriveSpeed, waitForCompletion);
}
void driveRev(float distance, bool waitForCompletion = true){
  driveRev(distance, defaultDistanceUnits, waitForCompletion);
}
void driveRev(float distance, float velocity, velocityUnits velUnits, bool waitForCompletion = true){
  driveRev(distance, defaultDistanceUnits, velocity, velUnits, waitForCompletion);
}
void driveFRev(float distance, float velocity, bool waitForCompletion = true){
  driveRev(distance, velocity, velocityUnits::pct, waitForCompletion);
}

void driveLeft(float distance, distanceUnits distUnits, float velocity, velocityUnits velUnits, bool waitForCompletion = true){
  driveLeft(convertToInch(distance,distUnits)/driveFactor,rotationUnits::rev,velocity,velUnits, waitForCompletion);
}
void driveLeft(float distance, distanceUnits distUnits, float velocity, bool waitForCompletion = true){
  driveLeft(distance, distUnits,velocity, velocityUnits::pct, waitForCompletion);
}
void driveleft(float distance, distanceUnits distUnits, bool waitForCompletion = true){
  driveLeft(distance, distUnits, defaultAutonDriveSpeed, waitForCompletion);
}
void driveLeft(float distance, bool waitForCompletion = true){
  driveLeft(distance, defaultDistanceUnits, waitForCompletion);
}
void driveLeft(float distance, float velocity, velocityUnits velUnits, bool waitForCompletion = true){
  driveLeft(distance, defaultDistanceUnits, velocity, velUnits, waitForCompletion);
}
void driveLeft(float distance, float velocity, bool waitForCompletion = true){
  driveLeft(distance, velocity, velocityUnits::pct, waitForCompletion);
}

void driveRight(float distance, distanceUnits distUnits, float velocity, velocityUnits velUnits, bool waitForCompletion = true){
  driveFwd(convertToInch(distance,distUnits)/driveFactor,rotationUnits::rev,velocity,velUnits, waitForCompletion);
}
void driveRight(float distance, distanceUnits distUnits, float velocity, bool waitForCompletion = true){
  driveFwd(distance, distUnits,velocity, velocityUnits::pct, waitForCompletion);
}
void driveRight(float distance, distanceUnits distUnits, bool waitForCompletion = true){
  driveRight(distance, distUnits, defaultAutonDriveSpeed, waitForCompletion);
}
void driveRight(float distance, bool waitForCompletion = true){
  driveRight(distance, defaultDistanceUnits, waitForCompletion);
}
void driveRight(float distance, float velocity, velocityUnits velUnits, bool waitForCompletion = true){
  driveRight(distance, defaultDistanceUnits, velocity, velUnits, waitForCompletion);
}
void driveRight(float distance, float velocity, bool waitForCompletion = true){
  driveRight(distance, velocity, velocityUnits::pct, waitForCompletion);
}
//Takes Degrees
void turnLeft(float angle,float velocity, velocityUnits velUnits){
  float distance = angle/(6.28318530717958*wheelDistance*1.414213*wheelCircumference*drivetrainRatio*drivetrainGearRatio);
  turnLeft(distance, rotationUnits::rev, velocity, velUnits);
}
void turnLeft(float angle, float velocity){
  turnLeft(angle, velocity, vex::velocityUnits::pct);
}
void turnLeft(angle){
  turnLeft(angle,defaultAutonTurnSpeed);
}
void turnRight(float angle,float velocity, velocityUnits velUnits){
  float distance = angle/(6.28318530717958*wheelDistance*1.414213*wheelCircumference*drivetrainRatio*drivetrainGearRatio);
  turnRight(distance, rotationUnits::rev, velocity, velUnits);
}
void turnRight(float angle, float velocity){
  turnRight(angle, velocity, vex::velocityUnits::pct);
}
void turnRight(angle){
  turnRight(angle,defaultAutonTurnSpeed);
}






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

    //int rollerVelocity = 90;
    vex::directionType preferredDirection = forward;
    const char * rumblePattern = ".";

    if(topOptical.color()==red){ //Red
      if(bottomOptical.color()==red){
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
      if(bottomOptical.color()==red){
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
  rollerSpin(onRedSide,90);
}





// float wheelDiameter = 3.25; //Units: inches
// float gearRatio = 5/4; //Ratio in form of driven/driving
// float drivetrainRatio = sqrt(2); // X drive makes robot drive sqrt(2) times faster and thus farther

// float convertUnits(float value, distanceUnits inputUnits){ //Converts all units to inches
//   if(inputUnits==inches || inputUnits==distanceUnits::in){
//     return value;
//   }else if(inputUnits==distanceUnits::cm){
//     return 2.54*value;
//   }else if(inputUnits==distanceUnits::mm){
//     return 25.4*value;
//   }
//   return 0;
// }

// void driveFwd(float distance, distanceUnits distUnits, float velocity, velocityUnits velUnits){
//   //distance = wheelRevolutions * pi * diameter * gear ratio * drivetrain Ratio
//   //wheelRevolutions = distance/(pi*diameter*gear ratio*drivetrain ratio)
  
// }



/*      Brain Auton Select
 *  Called once in preAuton();
 *  Has an infinite loop that will run until either auton starts or the loop is broken by 
 *  a final selection or preAuton ending.
 * 
//  */
// void brainAutonSelect(){ // Run in pre auton 
//     //Brain Screen is 480x272 pixels 

//     const int buttonMargin = 7;
//     const int bankButtonWidth = 130;
//     const int bankButtonHeight = 90;
//     const int routinesOnEachScreen = 4;

//     const int arrowSize = 30;
    
//     const fontType routineNameFont = vex::fontType::mono12;
//     const fontType routineDescriptionFont = vex::fontType::mono15;
//     const fontType routineConfirmNameFont = vex::fontType::mono40;
//     const fontType finalizeFont = vex::fontType::mono60;
//     const int routineNumberOffset = 3;
    
//     const int autonButtonWidth = (480-((1+routinesOnEachScreen)*buttonMargin))/routinesOnEachScreen;

//     //Colors: https://www.color-hex.com/color-palette/1019156
//     color backgroundColor = color(30);
//     color bankBackgroundColor = color(230);
//     //color autonButtonBackgroundColor = color(230);
//     color bankArrowColor = color(16,14,17);
//     color autonTextColor = color(16,14,17);
//     color backButtonColor = color(204,12,12);
//     color finalizeButtonColor = color(78,202,22);
//     color finalizeTextColor = color(16,14,17);


//     while(!finalAutonSelection){
//         Brain.Screen.setFillColor(backgroundColor);
//         Brain.Screen.drawRectangle(0,0,480,272);
//         switch (autonSelectScreen)
//         {
//         case 0: // Selection Screen (See page 1.111 in the Notebook)
//             //Bank 0 is auton select 0-3
            
//             //Drawing:
//             //Bank Buttons
//             Brain.Screen.setFillColor(bankBackgroundColor);
//             Brain.Screen.drawRectangle(buttonMargin,272-buttonMargin-bankButtonHeight,bankButtonWidth,bankButtonHeight);
//             Brain.Screen.drawRectangle(480-buttonMargin-bankButtonWidth,272-buttonMargin-bankButtonHeight,bankButtonWidth,bankButtonHeight);
//             //Bank Arrows
//             Brain.Screen.setFillColor(bankArrowColor);
//             Brain.Screen.drawRectangle(buttonMargin+bankButtonWidth/2-arrowSize,272-bankButtonHeight/2-arrowSize/2,arrowSize*3,arrowSize);
//             //Auton Buttons
//             for(int i = 0; i<routinesOnEachScreen; i++){
//                 //Draws the rectangle for each selection button
//                 Brain.Screen.setFillColor(routineColors[i+routinesOnEachScreen*autonSelectBank]);
//                 Brain.Screen.drawRectangle(buttonMargin+(buttonMargin+autonButtonWidth)*i,buttonMargin,autonButtonWidth,272-buttonMargin*3-bankButtonHeight);
                
//                 Brain.Screen.setFillColor(autonTextColor);
//                 Brain.Screen.setFont(routineNameFont);
//                 const char * name = autonRoutineNames[i+routinesOnEachScreen*autonSelectBank].c_str();
//                 Brain.Screen.printAt(buttonMargin+(buttonMargin+autonButtonWidth)*i+routineNumberOffset,buttonMargin+routineNumberOffset,name);
                
//             }
//             //Checking:
//             if(Brain.Screen.pressing()){
//                 if(Brain.Screen.xPosition()<=buttonMargin+bankButtonWidth && Brain.Screen.yPosition()>=272-bankButtonHeight-buttonMargin){
//                     autonSelectBank--;
//                     if(autonSelectBank<0)autonSelectBank = maxAutonBank;
//                 }else if(Brain.Screen.xPosition()>=(480-buttonMargin-bankButtonWidth) && Brain.Screen.yPosition()>=272-bankButtonHeight-buttonMargin){
//                     autonSelectBank++;
//                     if(autonSelectBank>maxAutonBank)autonSelectBank = 0;
//                 }else{
//                     for(int i = 0; i<routinesOnEachScreen; i++){
//                         if(Brain.Screen.yPosition()<=(480-bankButtonHeight-2*buttonMargin) && Brain.Screen.xPosition()>=i*(480/routinesOnEachScreen) && Brain.Screen.xPosition()<=(i+1)*(480/routinesOnEachScreen)){
                            
//                             autonSelect = i+autonSelectBank*routinesOnEachScreen;
//                             autonSelectScreen = 1;
//                         }                        
//                     }
//                 }
//             }


//             break;
//         case 1: // Final Confirmation (See page 1.111 in the Notebook)

//           //Drawing
//           //Back Button
//           Brain.Screen.setFillColor(backButtonColor);
//           Brain.Screen.drawRectangle(buttonMargin,buttonMargin,120-buttonMargin,100);
//           Brain.Screen.setFillColor(finalizeTextColor);
//           Brain.Screen.setFont(mono30);
//           Brain.Screen.printAt(buttonMargin+routineNumberOffset,buttonMargin+routineNumberOffset,"Back");
//           //Title
//           Brain.Screen.setFont(routineConfirmNameFont);
//           const char * name = autonRoutineNames[autonSelect].c_str();
//           Brain.Screen.printAt(120+buttonMargin*2,buttonMargin,name);

//           //Finalize Button
//           Brain.Screen.setFillColor(finalizeButtonColor);
//           Brain.Screen.drawRectangle(120,100+buttonMargin*2,240,150);
//           Brain.Screen.setFont(finalizeFont);
//           Brain.Screen.printAt(120+buttonMargin,100+3*buttonMargin,"Finalize");
//           //Checking
//           if(Brain.Screen.pressing()){
//             if(Brain.Screen.xPosition()<=120+buttonMargin && Brain.Screen.yPosition() <=100+buttonMargin){
//               //Back button Pressed
//               autonSelectScreen = 0;
//             }else if(Brain.Screen.xPosition()>=120 && Brain.Screen.xPosition()<=360){
//               //Finalize Button Pressed
//               finalAutonSelection = true;
//               autonSelectScreen = 2;
//               Controller1.rumble("- - -");
//             }
//           }
//           break;
//         case 2: // Locked on one routine. (See page 1.111 in the Notebook)
//           Brain.Screen.setFont(routineConfirmNameFont);
//           const char * name = autonRoutineNames[autonSelect].c_str();
//           Brain.Screen.printAt(120+buttonMargin*2,buttonMargin,name);
//           Brain.Screen.printAt(120+buttonMargin,100+3*buttonMargin,"Auton Finalized");
//           break;
//         default:
//         Brain.Screen.printAt(30,30,"Error: Bad value for autonSelectScreen");
//             break;
//         }
//         wait(20,msec);
//     }
// }
