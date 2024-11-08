#include "vex.h"
using namespace vex;
competition Competition;

int autonNumber = 3;

void drawGui()
{
  Brain.Screen.setFillColor(red);

  Brain.Screen.drawRectangle(1, 0, 500, 50);
  Brain.Screen.drawRectangle(1, 50, 500, 50);
  Brain.Screen.drawRectangle(1, 100, 500, 50);
  Brain.Screen.drawRectangle(1, 150, 500, 50);
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFont(mono20);
  Brain.Screen.printAt(50, 25, "Red WP");
  Brain.Screen.printAt(50, 75, "Blue WP");
  Brain.Screen.printAt(50, 125, "Red 4 Ring");
  Brain.Screen.printAt(50, 175, "Blue 4 Ring");
}
void selectDrive()
{

  int touchX = Brain.Screen.xPosition();
  int touchY = Brain.Screen.yPosition();

  if (touchY <= 49 && touchX >= 1)
  {
    autonNumber = 1;
    Brain.Screen.clearLine(200);
    Brain.Screen.setFont(mono12);
    Brain.Screen.setPenColor(green);
    Brain.Screen.printAt(50, 210, "Red WP");
    Brain.Screen.printAt(50, 230, "Number Selected: %d", autonNumber);
  }

  if (touchY >= 50 && touchY <= 99 && touchX >= 1)
  {
    autonNumber = 2;
    Brain.Screen.clearLine(200);
    Brain.Screen.setFont(mono12);
    Brain.Screen.setPenColor(green);
    Brain.Screen.printAt(50, 210, "Blue WP");
    Brain.Screen.printAt(50, 230, "Number Selected: %d", autonNumber);
  }

  if (touchY >= 100 && touchY <= 149 && touchX >= 1)
  {
    autonNumber = 3;
    Brain.Screen.clearLine(200);
    Brain.Screen.setFont(mono12);
    Brain.Screen.setPenColor(green);
    Brain.Screen.printAt(50, 210, "Red 4 Ring");
    Brain.Screen.printAt(50, 230, "Number Selected: %d", autonNumber);
  }

  if (touchY >= 150 && touchX >= 1)
  {
    autonNumber = 4;
    Brain.Screen.clearLine(200);
    Brain.Screen.setFont(mono12);
    Brain.Screen.setPenColor(green);
    Brain.Screen.printAt(50, 210, "Blue 4 Ring");
    Brain.Screen.printAt(50, 230, "Number Selected: %d", autonNumber);
  }
}

void pre_auton(void)
{
  op.setLightPower(25, percent);
  drawGui();
  Brain.Screen.pressed(selectDrive);
  liftAngle.resetPosition();
  imu.calibrate();
  resetDriveEncoders();
  driving.setStopping(coast);
}

// int autonSelected = 2;
float const drivekP = 0.69;
float const drivekD = 0.017;
float const drivekI = 0.03;
float const turnkP = 0.2;
float const turnkD = 1.05;
float const turnkI = 0.07;
float const rightArckP = 0.55;
float const rightArckD = 3.3;
float const rightArckI = 0.016;
float const leftArckP = 0.55;
float const leftArckD = 3.3;
float const leftArckI = 0.016;
float const liftkP = 1.2;
float const liftkD = 0.02;
float const driveIntegralTresh = 0;
float const turnIntegralTresh = 0;
float const driftIntegralTresh = 0;
float const arcIntegralTresh = 15;
float const drive_settle_error = 1.5;
float const turn_settle_error = 1;
float const arc_settle_error = 2;
float const drive_settle_time = 150;
float const turn_settle_time = 150;
float const arc_settle_time = 300;
float const default_settle_time = 100;
float const drive_timeout = 4000;
float const turntimeout = 2500;
float const arctimeout = 2500;

void autonomous(void)
{
  switch (autonNumber)

  {
  case 1:
    // Red WP

    /*
    Brain.Screen.clearScreen();
    setCoords(0, 0, 0.04);
    turntoPoint(24, 24, 0,  10, turn_settle_error, 50, 1000, turnkP, turnkI, turnkD, turnIntegralTresh);
    translate(24, 24, 0, 12, 10, drive_settle_error, 50, drive_timeout, drivekP, drivekI, drivekD, driveIntegralTresh, turnkP, turnkI, turnkD, turnIntegralTresh);
    translate(0, 0, 0, 12, 10, drive_settle_error, 50, drive_timeout, drivekP, drivekI, drivekD, driveIntegralTresh, turnkP, turnkI, turnkD, turnIntegralTresh);
    turnFor(0, turnkP, turnkD, turnkI, turnIntegralTresh, turn_settle_error, 100, 1000);
    */
    /*
    driveFor(-32.5, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, 300, 1000, 0, 9);
    clamp1.open();
    wait(100, msec);
    turnFor(90, turnkP, turnkD, turnkI, turnIntegralTresh, turn_settle_error, 100, 500); // 270 -> 360 - 270 = 90
    intake.spin(reverse, 12, voltageUnits::volt);
    driveFor(24.25, 0.35, drivekD, drivekI, driveIntegralTresh, drive_settle_error, 100, 1000, 0, 9);
    wait(500, msec);
    turnFor(302, turnkP, turnkD, turnkI, turnIntegralTresh, .75, 100, 1000); // 58 -> 360 - 58 = 302
    driveFor(30, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, 300, 1000, 0, 9);
    clamp1.close();
    driveFor(17, 0.4, drivekD, drivekI, driveIntegralTresh, drive_settle_error, 300, 1000, 0, 9);
    wait(500, msec);
    intake.stop(coast);
    driveFor(12, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, 300, 1000, 0, 9);
    intake.spinFor(reverse, .740, seconds, 87.5, vex::velocityUnits::pct);
    turnFor(35, turnkP, turnkD, turnkI, turnIntegralTresh, turn_settle_error, 100, 1000); // 325 -> 360 - 325 = 35
    driveFor(-37.5, 0.35, drivekD, drivekI, driveIntegralTresh, drive_settle_error, 200, 1000, 0, 9);
    clamp1.open();
    wait(320, msec);
    intake.spin(reverse, 12, vex::voltageUnits::volt);
    wait(300, msec);
    turnFor(270, turnkP, turnkD, turnkI, turnIntegralTresh, turn_settle_error, 150, 1000); // 90 -> 360 - 90 = 270
    driveFor(25, 0.35, drivekD, drivekI, driveIntegralTresh, drive_settle_error, 100, 1000, 0, 9);
    wait(400, msec);
    turnFor(90, turnkP, turnkD, turnkI, turnIntegralTresh, turn_settle_error, 200, 1000); // 270 -> 360 - 270 = 90
    intake.stop(coast);
    driveFor(42, 0.45, drivekD, drivekI, driveIntegralTresh, drive_settle_error, 200, 1000, 0, 9);
*/
    break;
  case 2:
    // Blue WP
    driveFor(-32.5, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, 300, 1000, 0, 9);
    clamp1.open();
    wait(100, msec);
    turnFor(270, turnkP, turnkD, turnkI, turnIntegralTresh, turn_settle_error, 100, 500);
    intake.spin(reverse, 12, voltageUnits::volt);
    driveFor(24.25, 0.35, drivekD, drivekI, driveIntegralTresh, drive_settle_error, 100, 1000, 0, 9);
    wait(500, msec);
    turnFor(58, turnkP, turnkD, turnkI, turnIntegralTresh, .75, 100, 1000);
    driveFor(30, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, 300, 1000, 0, 9);
    clamp1.close();
    driveFor(14, 0.35, drivekD, drivekI, driveIntegralTresh, drive_settle_error, 300, 1000, 0, 9);
    wait(500, msec);
    intake.stop(coast);
    driveFor(9, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, 300, 1000, 0, 9);
    intake.spinFor(reverse, .740, seconds, 82.5, vex::velocityUnits::pct);
    turnFor(325, turnkP, turnkD, turnkI, turnIntegralTresh, turn_settle_error, 100, 1000);
    driveFor(-37.5, 0.35, drivekD, drivekI, driveIntegralTresh, drive_settle_error, 200, 1000, 0, 9);
    clamp1.open();
    wait(320, msec);
    intake.spin(reverse, 12, vex::voltageUnits::volt);
    wait(300, msec);
    turnFor(90, turnkP, turnkD, turnkI, turnIntegralTresh, turn_settle_error, 150, 1000);
    driveFor(25, 0.35, drivekD, drivekI, driveIntegralTresh, drive_settle_error, 100, 1000, 0, 9);
    wait(400, msec);
    turnFor(270, turnkP, turnkD, turnkI, turnIntegralTresh, turn_settle_error, 200, 1000);
    intake.stop(coast);
    driveFor(42, 0.45, drivekD, drivekI, driveIntegralTresh, drive_settle_error, 200, 1000, 0, 9);

    break;
  case 3:

    /*
    Brain.Screen.clearScreen();
    setCoords(0, 0, 0.04);
    turntoPoint(24, 24, 0,  10, turn_settle_error, 50, 1000, turnkP, turnkI, turnkD, turnIntegralTresh);
    translate(24, 24, 0, 12, 10, drive_settle_error, 50, drive_timeout, drivekP, drivekI, drivekD, driveIntegralTresh, turnkP, turnkI, turnkD, turnIntegralTresh);
    translate(0, 0, 0, 12, 10, drive_settle_error, 50, drive_timeout, drivekP, drivekI, drivekD, driveIntegralTresh, turnkP, turnkI, turnkD, turnIntegralTresh);
    turnFor(0, turnkP, turnkD, turnkI, turnIntegralTresh, turn_settle_error, 100, 1000);
    */


    Brain.Screen.clearScreen();
    setCoords(0, 0, 180);
    translate(-5, 27, 0, 10, 10, drive_settle_error, 100, drive_timeout, drivekP, drivekI, drivekD, driveIntegralTresh, turnkP, turnkI, turnkD, turnIntegralTresh);
    // turntoPoint(-7, 24, 180,  10, turn_settle_error, 50, 1000, turnkP, turnkI, turnkD, turnIntegralTresh);
     wait(100, msec);
    clamp1.open();
    /*

    intake.spin(reverse, 12, volt);
    translate(0, 31, 0, 8, 10, drive_settle_error, 100, drive_timeout, drivekP, drivekI, drivekD, driveIntegralTresh, turnkP, turnkI, turnkD, turnIntegralTresh);
    translate(-18.8, 48, 0, 8, 10, drive_settle_error, 100, drive_timeout, drivekP, drivekI, drivekD, driveIntegralTresh, turnkP, turnkI, turnkD, turnIntegralTresh);
*/
    

  /*
    // red 4 Ring
    driveFor(-19, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, default_settle_time, 500, 0, 9);
    rightArcTurn(30, rightArckP, rightArckD, rightArckI, arcIntegralTresh, arc_settle_error, 150, 500);
    driveFor(-7, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, default_settle_time, 500, 0, 9);
    clamp1.open();
    wait(200, msec);
    turnFor(103, turnkP, turnkD, turnkI, turnIntegralTresh, turn_settle_error, default_settle_time, 500);
    intake.spin(reverse, 12, volt);
    wait(500, msec);
    driveFor(22, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, default_settle_time, 1000, 0, 7);
    turnFor(170, turnkP, turnkD, turnkI, turnIntegralTresh, turn_settle_error, 100, 500);
    driveFor(14.5, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, default_settle_time, 1000, 0, 4);
    wait(550, msec);
    driveFor(-13, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, default_settle_time, 1000, 0, 4);
    turnFor(200, turnkP, turnkD, turnkI, turnIntegralTresh, turn_settle_error, default_settle_time, 500);
    driveFor(12, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, default_settle_time, 1000, 0, 4);
    wait(650, msec);
    driveFor(-35, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, default_settle_time, 1000, 0, 9);
    turnFor(280, turnkP, turnkD, turnkI, turnIntegralTresh, turn_settle_error, default_settle_time, 500);
    // wait(4000, msec);
    // driveFor(100, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, default_settle_time, 3000, 0, 5);
    */

    break;
  case 4:
    // Blue 4 Ring
    driveFor(-19, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, default_settle_time, 500, 0, 9);
    leftArcTurn(330, rightArckP, rightArckD, rightArckI, arcIntegralTresh, arc_settle_error, 150, 500); // Changed 30 to 330
    driveFor(-7, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, default_settle_time, 500, 0, 9);
    clamp1.open();
    wait(200, msec);
    turnFor(257, turnkP, turnkD, turnkI, turnIntegralTresh, turn_settle_error, default_settle_time, 500); // Changed 103 to 257
    intake.spin(reverse, 12, volt);
    wait(500, msec);
    driveFor(22, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, default_settle_time, 1000, 0, 7);
    turnFor(190, turnkP, turnkD, turnkI, turnIntegralTresh, turn_settle_error, 100, 500); // Changed 170 to 190
    driveFor(16, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, default_settle_time, 1000, 0, 4);
    wait(550, msec);
    driveFor(-10, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, default_settle_time, 1000, 0, 4);
    turnFor(160, turnkP, turnkD, turnkI, turnIntegralTresh, turn_settle_error, default_settle_time, 500); // Changed 200 to 160
    driveFor(12, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, default_settle_time, 1000, 0, 4);
    wait(650, msec);
    driveFor(-35, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, default_settle_time, 1000, 0, 9);
    turnFor(80, turnkP, turnkD, turnkI, turnIntegralTresh, turn_settle_error, default_settle_time, 500); // Changed 280 to 80
    wait(4000, msec);
    driveFor(100, drivekP, drivekD, drivekI, driveIntegralTresh, drive_settle_error, default_settle_time, 3000, 0, 5);

    break;
  }
}

void usercontrol(void)
{

  Right.stop(coast);
  Left.stop(coast);
  liftAngle.setPosition(360, degrees);
  master.ButtonR1.pressed(liftUp);
  master.ButtonR1.pressed(liftDown);
  master.ButtonRight.pressed(doinkerClose);
  master.ButtonRight.pressed(doinkerOpen);
  master.ButtonY.pressed(clampOpen);
  master.ButtonY.pressed(clampClose);
  master.ButtonR2.pressed(liftScore1);
  // master.ButtonB.pressed(liftHangUp);
  // master.ButtonB.pressed(liftHangDown);
  // master.ButtonUp.pressed(intakeOne);
  // master.ButtonUp.pressed(intakeBoth);
  // odom_test();
  Brain.Screen.clearScreen();

  while (1)
  {

     Brain.Screen.printAt(5, 20, "X: %f", positionX());
      Brain.Screen.printAt(5, 40, "Y: %f", positionY());

    /*
  Brain.Screen.printAt(1, 50, "leftEncoders: %f \n", Left.position(deg) * (0.75/360.0*M_PI*2.75));//converted into inches
  Brain.Screen.printAt(1, 70, "rawleftEncoders: %f \n", Left.position(deg));
  Brain.Screen.printAt(1, 90, "rightEncoders: %f \n",  Right.position(deg) * (0.75/360.0*M_PI*2.75));
  Brain.Screen.printAt(1, 110, "rawleftEncoders: %f \n", Right.position(deg));
  Brain.Screen.printAt(1, 130, "RobotPose: %f \n", (Right.position(deg) * (0.75/360.0*M_PI*2.75) + Left.position(deg) * (0.75/360.0*M_PI*2.75) ) / 2);
  Brain.Screen.printAt(1, 150, "Theta %f", imu.heading(degrees));b
  */

    driveMove(master.Axis3.value(), master.Axis2.value(), 2);
    // tankDrive(master.Axis3.value(), master.Axis2.value(), 0);
    intakeCode();
    liftScore1();
    // liftControl();
    wait(20, msec);
  }
}

int main()
{

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true)
  {
    wait(100, msec);
  }
}
