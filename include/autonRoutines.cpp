#include "vex.h"
#include "autonFunctions.cpp"



void pushPreloads(){
    driveFwd(2,rotationUnits::rev,30,velocityUnits::pct);
    driveRev(2,rotationUnits::rev,30,velocityUnits::pct);
}
void rollerSpinAuton(bool onRedSide){
    
  topOptical.setLightPower(90,pct);
  bottomOptical.setLightPower(90,pct);
  

  driveTimeout(3,sec);
  driveFwd(1,rev,30,velocityUnits::pct, false);
  for(int i = 0; i<15*1000/20;i++){
    if((topOptical.color()==red || topOptical.color()==blue) && (bottomOptical.color()==red || bottomOptical.color()==blue)){ //Automatic Roller Spinning Only works if both sensors have a color
      rollerSpin(onRedSide);
    }
    wait(20,msec);
  }
}
void skillsAuton1(){
    rollerSpinAuton(true);
    driveTimeout(10,sec);
    driveFwd(-0.5,rev,10,velocityUnits::pct, true);
    driveLeft(-0.8,rev,10,velocityUnits::pct);
    //turnLeft(-0.04,rev,30,velocityUnits::pct);
    flywheelMotors.spin(fwd,100,pct);
    wait(5,sec);

    for(int i = 0; i<4; i++){
    indexPneumatic.set(true);
    wait(1,sec);
    indexPneumatic.set(false);
    wait(1,sec);
    }

    driveFwd(-1.5,rev,30,velocityUnits::pct);
    driveRev(-0.6,rev,15,velocityUnits::pct, true);
    turnRight(-1.1,rev,15,velocityUnits::pct);
    driveTimeout(3,sec);
    driveRev(-1.5,rev,30,velocityUnits::pct, false);
    flywheelMotors.stop(coast);
    for(int i = 0; i<10*1000/20;i++){
    if((topOptical.color()==red || topOptical.color()==blue) && (bottomOptical.color()==red || bottomOptical.color()==blue)){ //Automatic Roller Spinning Only works if both sensors have a color
        rollerSpin(true);
    }
    wait(20,msec);
    }

}
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
 * 
 */
void runAuton(int autonSelect){
    switch (autonSelect){
    case 0:
        break;
    case 1:
        pushPreloads();
        break;
    case 2:
        rollerSpin(true);
        break;
    case 3:
        rollerSpin(false);
        break;
    case 4:
        skillsAuton1();
        break;


    default:
        break;
    }
}