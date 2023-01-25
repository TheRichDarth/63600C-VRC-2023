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
//DEPRECATED DO NOT USE
// void rollerSpinAuton(bool onRedSide){
    
//   topOptical.setLightPower(90,pct);
//   bottomOptical.setLightPower(90,pct);
//   driveTimeout(3,sec);
//   driveFwd(0.5,rev,30,velocityUnits::pct, true);
//   Controller1.rumble("...");
//   for(int i = 0; i<15*1000/20;i++){
//     if((topOptical.color()==red || topOptical.color()==blue) && (bottomOptical.color()==red || bottomOptical.color()==blue)){ //Automatic Roller Spinning Only works if both sensors have a color
//       rollerSpin(onRedSide);
//     }
//     wait(20,msec);
//   }
// }
void roller2(bool onRedSide = true){
    // driveFwd(1,rotationUnits::rev,30,velocityUnits::pct, true);
    rightDrivetrain.setTimeout(10,sec);
    rightDrivetrain.spinFor(300,rotationUnits::deg,100,velocityUnits::pct, false);
    wait(1,sec);
    //90 degrees times 3.25/
    rollerMotor.spinFor(forward, 2*87.75,rotationUnits::deg,80,velocityUnits::pct);
}
void rollerSpinAuton(bool t){

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
    turnRight(850,degrees,15,velocityUnits::pct, true);
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
    driveRight(4,inches);
    turnLeft(175,degrees,15,velocityUnits::pct, true);
    wait(10,sec);
    //Fire Endgame
    for(int i = 0; i<5; i++){
        endgame.set(true);
        wait(8,sec);
        endgame.set(false);
        wait(8,sec);
    }
}

/* Skills Auton 3
 * Shoots preloads, spins both rollers,drives through low goals to reach other side's rollers, scores them and launches endgame.
 *
 *
 */
void skillsAuton3(){
    //Step 1: Shoot preloads into the high goal
    flywheelMotors.spin(fwd,11.4,voltageUnits::volt);
    wait(5,sec);
    for(int i = 0; i<3; i++){
        indexPneumatic.set(true);
        wait(400,msec);
        indexPneumatic.set(false);
        wait(1000,msec);
    }
    //Step 2: Scores first roller
    driveRev(8,inches);
    turnRight(400,degrees,15,velocityUnits::pct);
    driveFwd(8,inches, false);
    autonRollerSpinning(true,4);
    //Step 3: Scores second roller
    driveRev(24,inches);
    turnRight(400,degrees,15,velocityUnits::pct);
    driveFwd(24,inches,false);
    autonRollerSpinning(true,6);

    //Step 4: Drive on route through blue low goal
    driveRev(3,inches);
    turnLeft(400,degrees);
    
    // float leftDistanceMin = 3;
    // float leftDistanceMax = 5;

    // while(leftDistance.value() <leftDistanceMin || leftDistance.value()>leftDistanceMax){
    //     if(){
    //         driveLeft(0.5,inches);
    //     }
    // }
    driveTimeout(8,sec);
    driveRev(108,inches);//Should run into the wall
    driveFwd(3,inches);
    turnLeft(400,degrees);
    driveTimeout(1,sec);

    //Step 5: Drive to next roller
    
}

void gameAutonLeft(bool onRedSide){
    //Spin the flywheel up to speed
    flywheelMotors.spin(forward, 12,voltageUnits::volt);
    wait(2,sec);
    //Launch 3 discs
    for(int i = 0; i<2; i++){
        wait(2000,msec);
        indexPneumatic.set(true);
        wait(500,msec);
        indexPneumatic.set(false);
    }
    wait(500,msec);
    flywheelMotors.stop(coast);
    // //drive forward 3 inches
    // driveFwd(3,inches);
    //turn 180 degrees
    turnRight(800,degrees);
    //drive forward 3 inches
    // wait(1,sec);
    driveFwd(4,inches);
    //drive right 3 inches
    //wait(1,sec);
    driveRight(7.5,inches);
    //drive forward 3 inches without waiting for completion
    //wait(1,sec);
    driveFwd(7,inches,false);
    //Run auto roller spinning
    autonRollerSpinning(onRedSide,5000);
    wait(1,sec);
    //Manually rotate roller
    //rollerMotor.spinFor(reverse, 90,rotationUnits::deg,70,velocityUnits::pct);
}

void five_right_game(bool onRedSide){
    gameAutonRight1(onRedSide);
    turnRight(850,30);

}

/* Game Auton Routines
 * 0: Do Nothing
 * 1: Push preloads into low goal
 * 2: Spin Roller to US (Can be used in Skills)
 *      -Starts on Left Side
 * 3: Spin Roller to US
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
        roller2();
        break;
    case 3:
        roller2();
        break;
    case 4:
        skillsAuton2();
        break;
    case 5:
        gameAutonRight1(true);
        break;
    case 6:
        gameAutonRight1(false);
        break;
    case 7:
        skillsAdditionToGameAutonRight1();
        break;
    case 8:
        gameAutonLeft(true);
        break;
    case 9:
        gameAutonLeft(false);
        break;


    default:
        break;
    }
}