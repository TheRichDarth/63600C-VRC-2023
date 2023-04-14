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
/**
 * @brief Used to check whether the catapult is in the upper zone of its travel.
 * This zone is the highest point and a bit below to account for error.
 * 
 * @return true when the catapult is in this zone
 * @return false else
 */
bool acataZone1(){
  return catapultRotationSensor.angle(deg)>270;
  }
/**
 * @brief Used to check whether the catapult is in the hold zone of its travel
 * This zone is the point at which the catapult waits for firing.
 * 
 * @return true when the catapult is in this zone
 * @return false else
 */
bool acataZone2(){
  return catapultRotationSensor.angle(deg)<225.5;
}
/**
 * @brief PURPLE skills routine from volume 3 page 44.
 * 
 */
void catapultSkills1(){
    //Step 0: Prepare catapult
    //Lower catapult until limit switch is pressed
    driveTimeout(500,msec);
    // while(!acataZone2()){
    //     catapultMotor.spin(forward,catapultVelocity*3/4,velocityUnits::pct);
    // }
    // wait(2,sec);
    // catapultMotor.stop(brake);
    //Step 1: Spin first roller
    //1.1 Drive into roller
    rightDrivetrain.spinFor(180,deg,20,velocityUnits::pct);
    wait(200,msec);
    //1.2 Spin Roller
    rollerMotor.spinFor(forward, 4*87.75,rotationUnits::deg,80,velocityUnits::pct);
    wait(600,msec);
    //Step 2: Move to and spin second roller; Pick up disc.
    //2.1 Back up and turn right 90 degrees
    driveRev(12,inches);
    turnRight(5,rev);
    wait(200,msec);
    //2.2 Intake disc
    rollerMotor.spin(reverse,100,pct);
    //2.3 Drive into second roller
    driveFwd(30,inches);
    //2.4 Spin roller
    wait(2,sec);
    rollerMotor.stop(coast);
    wait(200,msec);
    driveFwd(6,inches);
    rollerMotor.spinFor(forward, 4*87.75,rotationUnits::deg,80,velocityUnits::pct);

    /*
    //Step 3: Move to and fire the catapult
    //3.1 back up and turn right 90 deg
    driveRev(2,inches);
    turnRight(3.1,rev);
    //3.2 drive towards high goal
    driveFwd(24*2+8,inches);
    //3.3 fire catapult
    while(!acataZone1()){
        catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    }
    wait(1,sec);
    //3.4 Reset catapult
    while(!acataZone2()){
        catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    }
    
    //Step 4: Pick up two discs and fire into the blue goal
    //Step 4.1:  Back up and turn 90 degrees right to be able to line up
    driveRev(6,inches);
    turnRight(3.1,rev);

    //Step 4.2 drive forward and turn right 45 degrees
    driveFwd(24,inches);
    turnRight(1.6,rev);

    //Step 4.3 Intake while driving forward
    intakeMotors.spin(fwd,100,pct);
    driveFwd(55,inches,20,velocityUnits::pct);

    //Step 4.4: Move to fire position:
    turnRight(1.6,rev);
    driveFwd(24,inches);
    turnLeft(3.1,rev);
    driveFwd(6,inches);

    //Step 4.5 Fire catapult
    while(!acataZone1()){
        catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    }
    wait(1,sec);
    //4.6 Reset catapult
    while(!acataZone2()){
        catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    }
    //Step 5: move and fire endgame

    */
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
 * 3: Catapult skills 1: Purple! (Roller-roller-fire-fire 5)
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
        catapultSkills1();
        break;
    default:
        break;
    }
}