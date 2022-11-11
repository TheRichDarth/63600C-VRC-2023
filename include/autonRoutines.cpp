#include "vex.h"
#include "autonFunctions.cpp"

/* Push Preloads:
 * Drives forward and backward to push preload discs into the low goal.
 * Scores two points
 * 100% success rate
 */
void pushPreloads(){
    driveFwd(2,rotationUnits::rev,30,velocityUnits::pct);
    driveRev(2,rotationUnits::rev,30,velocityUnits::pct);
}
/* rollerSpinAuton:
 * Drives forward slightly into the roller on the left side and runs automatic roller spinning for the duration of the period
 * Scores ten points
 * 90% success rate
 * Parameters: bool onRedSide: which side the roller is scored for
 */
void rollerSpinAuton(bool onRedSide){
    
  topOptical.setLightPower(90,pct);
  bottomOptical.setLightPower(90,pct);
  

  driveTimeout(3,sec);
  driveFwd(0.5,rev,30,velocityUnits::pct, true);
  Controller1.rumble("...");
  for(int i = 0; i<15*1000/20;i++){
    if((topOptical.color()==red || topOptical.color()==blue) && (bottomOptical.color()==red || bottomOptical.color()==blue)){ //Automatic Roller Spinning Only works if both sensors have a color
      rollerSpin(onRedSide);
    }
    wait(20,msec);
  }
}
/* DEPRECATED: DO NOT USE
 * Old skills auton from before we moved the roller. This will not work. 
 */
void skillsAuton1(){
    rollerSpinAuton(true);
    turnRight(2.2,rev,30,velocityUnits::pct);
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
/*
 * Roller, roller, shoot preloads, pick up 3, shoot 3, pick up 2, roller, pick up 1, roller, shoot 3, pick up 2, shoot
 * See 11/12 entry in notebook
 *
 */
void skillsAuton2(){
    //Step 0.1: Drive into the roller
    driveTimeout(3,sec);
    driveRight(6,inches);
    driveFwd(2,inches);
    //Step 0.2: Spin roller
    autonRollerSpinning(true,2.5*1000);
    //Step 1.1: Drive to next roller
    driveRev(2.5*12,inches);
    turnRight(90);
    driveFwd(2.25*12,inches);
    //Step 1.2: Spin second roller
    autonRollerSpinning(true,2.5*1000);
    //Step 2.1 Spin up flywheel (haha pun)
    flywheelMotors.spin(fwd,100,velocityUnits::pct);
    //Step 2.2 Drive to launch position
    driveRev(24,inches);
    turnRight(90);
    //Step 3 launch Discs
    for(int i = 0; i<3; i++){
        indexPneumatic.set(true);
        wait(60,msec);
        indexPneumatic.set(false);
        wait(60,msec);
    }
    //flywheelMotors.stop(coast);
    //Step 4: Intake 3 and position to fire.
    driveFwd(24,inches);
    turnRight(45);
    driveFwd(6*12,inches);
    turnLeft(90);
    //Step 5: fire 3 discs
    for(int i = 0; i<3; i++){
        indexPneumatic.set(true);
        wait(60,msec);
        indexPneumatic.set(false);
        wait(60,msec);
    }
    flywheelMotors.stop(coast);
    turnRight(75);
    //Step 6: go to roller
    driveFwd(27,inches);
    turnRight(30);
    driveFwd(27,inches);
    //Step 7: Roller
    turnLeft(75);
    driveFwd(4,inches);
    autonRollerSpinning(true,2.5*1000);
    
}
void gameAutonRight1(bool onRedSide){
    //Step 1: Drive to the Roller
    driveTimeout(5,sec);
    driveLeft(24,inches,30,velocityUnits::pct);
    driveTimeout(2,sec);
    driveFwd(6,inches, false);

    //Step 2: Spin roller
    autonRollerSpinning(onRedSide,5000);
    rollerMotor.stop(brake);
    //Step 3: turn around and aim
    flywheelMotors.spin(fwd,12,volt);
    driveRev(6,inches);
    turnRight(830,degrees,15,velocityUnits::pct, true);
    wait(3,sec);
    driveFwd(5,inches,15,velocityUnits::pct);
    //Step 4: Fire 3 discs
    for(int i = 0; i<3; i++){
        indexPneumatic.set(true);
        wait(200,msec);
        indexPneumatic.set(false);
        wait(1500,msec);
    }
    flywheelMotors.stop(coast);

}

void skillsAdditionToGameAutonRight1(){
    gameAutonRight1(true);
    turnLeft(45);
    //Fire Endgame
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
 * 5: Game Auton Right RED
 * 6: Game Auton Right BLUE
 * 7 Skills Auton extended from game auton right
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
        skillsAuton2();
        break;
    case 5:
        gameAutonRight1(false);
        break;
    case 6:
        gameAutonRight1(false);
        break;
    case 7:
        skillsAdditionToGameAutonRight1();
        break;


    default:
        break;
    }
}