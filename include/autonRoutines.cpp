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
 * Drives forward slightly into the roller on the left side and spins the roller.
 */
void roller2(bool onRedSide = true){
    // driveFwd(1,rotationUnits::rev,30,velocityUnits::pct, true);
    rightDrivetrain.setTimeout(10,sec);
    rightDrivetrain.spinFor(300,rotationUnits::deg,100,velocityUnits::pct, false);
    wait(1,sec);
    //90 degrees times 3.25/
    rollerMotor.spinFor(forward, 2*87.75,rotationUnits::deg,80,velocityUnits::pct);
}

void catapultSkills1(){
    //Step 0: Prepare catapult
    //Lower catapult until limit switch is pressed
    while(!catapultLimitSwitch.pressing()){
        catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    }
    wait(2,sec);
    catapultMotor.stop(brake);
    //Step 1: Spin first roller
    //1.1 Drive into roller
    driveFwd(1,inches);
    //1.2 Spin Roller
    rollerMotor.spinFor(forward, 4*87.75,rotationUnits::deg,80,velocityUnits::pct);

    //Step 2: Move to and spin second roller; Pick up disc.
    //2.1 Back up and turn right 90 degrees
    driveRev(12,inches);
    turnRight(3,rev);
    //2.2 Intake disc
    rollerMotor.spin(reverse,100,pct);
    //2.3 Drive into second roller
    driveFwd(36,inches);
    //2.4 Spin roller
    rollerMotor.spinFor(forward, 4*87.75,rotationUnits::deg,80,velocityUnits::pct);
    //Step 3: Move to and fire the catapult
    //3.1 back up and turn right 90 deg
    driveRev(2,inches);
    turnRight(3.1,rev);
    //3.2 drive towards high goal
    driveFwd(24*2+8,inches);
    //3.3 fire catapult
    while(catapultLimitSwitch.pressing()){
        catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    }
    wait(4,sec);
    //Step 4: Endgame
    //4.1 Move to position
    driveRev(3*24,inches);
    turnLeft(4.5,rev);

    //4.2 fire endgame
}
const double rollerSpinSkills = 3.85*87.75;
void catapultSkills2(){
    //Step 1: Fire Catapult preloads
    //1.1: Preload catapult
    while(!catapultLimitSwitch.pressing()){
        catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    }
    wait(1,sec);
    //1.2 Fire catapult
    while(catapultLimitSwitch.pressing()){
        catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    }
    catapultMotor.stop(brake);
    wait(1,sec);
    //Step 2: Move to and score roller 1
    //Step 2.1 Back up 3 tiles 
    driveRev(7.5,rev);
    //Step 2.2 Turn right 90 degrees
    turnRight(1.19,rev);
    //Step 2.3 drive into roller
    driveTimeout(3,sec);
    driveFwd(1.31,rev);

    //Abridged Routine. 
    //Step 2.1 Drive 1 inch into roller
    Controller1.rumble("-.-.-");
    driveTimeout(1,sec);
    //driveFwd(1,inches);
    rollerMotor.setTimeout(2,sec);
    rightDrivetrain.spinFor(forward,1*360,rotationUnits::deg,30,velocityUnits::pct,true);
    //Step 2.4 turn roller
    rollerMotor.spinFor(forward, 4*87.75,rotationUnits::deg,80,velocityUnits::pct);
    wait(1,sec);
    //Step 3: Move to and score roller 2
    //Step 3.1 Back up 1 tile
    driveTimeout(4,sec);
    driveRev(4.21,rev);
    //Step 3.2 turn right 90 degrees
    turnRight(1.25,rev);
    //Step 3.3 drive one tile into roller
    driveTimeout(3,sec);
    driveFwd(4.1,rev);
    //Step 3.4 spin roller
    rollerMotor.spinFor(forward, 4*87.75,rotationUnits::deg,80,velocityUnits::pct);
    
    //Step 4: Turn and launch Endgame
    //Step 4.1 back up one tile
    turnRight(0.15,rev);
    //VERSION 1: LAUNCH ENDGAME::
    driveTimeout(4,sec);
    driveRev(4,rev);
    //Step 4.2 turn left 45 degrees
    turnLeft(0.7,rev);
    //Step 4.3 back up 0.5 tiles
    driveFwd(3,rev);
    //Step 4.4 fire endgame
    for(int i = 0; i<4; i++){
        endgameL.set(true);
        endgameR.set(true);
        
        wait(1,sec);
        endgameL.set(false);
        endgameR.set(false);
        
        wait(1,sec);
    }
    

    // //VERSION 2: MORE ROLLERS

    // //Step 4:Drive through low goal
    // //Step 4.1 back up 2 inches
    // driveRev(0.55,rev);
    // //Step 4.2 turn right 90 degrees
    // turnRight(1.21,rev);
    // //Step 4.2 drive forward through low goal
    // driveTimeout(15,sec);
    // driveFwd(16,rev);
    // //Step 4.3 align on front of robot
    // driveTimeout(3,sec);
    // driveFwd(1,rev);
    // //STep 4.4 back up and turn right 90 degrees
    // //Step 4.5 back up and align on the other wall
    // //Step 4.6 drive forward to rollers
    // //Step 5: Drive to roller 3
    // //Step 6: Drive to roller 4
}


/* Game Auton Routines
 * 0: Do Nothing
 * 1: Push preloads into low goal
 * 2: Spin Roller to US (Can be used in Skills
 * 
 * Skills Auton Routines:
 * 3: Catapult skills 2: SHoots preloads, 2 rollers and endgame
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
        catapultSkills2();
        break;
    default:
        break;
    }
}