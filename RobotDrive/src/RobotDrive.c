#include "API.h"
#include "RobotDrive.h"

static int leftFrontMotor, rightFrontMotor, leftRearMotor, rightRearMotor;

static int clip(int value) {
  if (value < -127) value = -127;
  if (value > 127) value = 127;
  return value;
}

int max(int a, int b) {
  if (a > b) return a;
  return b;
}

void driveInit2(int leftMotor, int rightMotor) {
  driveInit4(leftMotor, 0, rightMotor, 0);
}

void driveInit4(int leftFront, int leftRear, int rightFront, int rightRear) {
  leftFrontMotor = leftFront;
  rightFrontMotor = rightFront;
  leftRearMotor = leftRear;
  rightRearMotor = rightRear;
}

void driveTank(int leftPower, int rightPower) {
  leftPower = clip(leftPower);
  rightPower = clip(rightPower);
  motorSet(leftFrontMotor, leftPower);
  if (leftRearMotor != 0) motorSet(leftRearMotor, leftPower);
  motorSet(rightFrontMotor, -rightPower);
  if (rightRearMotor != 0) motorSet(rightRearMotor, -rightPower);
}

void driveArcade(int moveValue, int rotateValue) {
  int leftMotorSpeed, rightMotorSpeed;
  moveValue = clip(moveValue);
  rotateValue = clip(rotateValue);
  if (moveValue > 0) {
    if (rotateValue > 0) {
      leftMotorSpeed = moveValue - rotateValue;
      rightMotorSpeed = max(moveValue, rotateValue);
    } else {
      leftMotorSpeed = max(moveValue, -rotateValue);
      rightMotorSpeed = moveValue + rotateValue;
    }
  } else {
    if (rotateValue > 0) {
      leftMotorSpeed = -max(-moveValue, rotateValue);
      rightMotorSpeed = moveValue + rotateValue;
    } else {
      leftMotorSpeed = moveValue - rotateValue;
      rightMotorSpeed = max(-moveValue, -rotateValue);
    }
    driveTank(leftMotorSpeed, rightMotorSpeed);
  }
}

void driveStop() {
  driveTank(0, 0);
}
