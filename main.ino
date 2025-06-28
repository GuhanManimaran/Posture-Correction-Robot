#include <SPI.h>
#include <Wire.h>
#include <Servo.h>
#define MPU 0x68 

Servo ServoA, ServoB;
double AcX, AcY, AcZ;
int Pitch, Roll;

const int ROLL_THRESHOLD = 15;   // Sensitivity: increase = less sensitive
const int PITCH_THRESHOLD = 15;

const int BASE_SERVO_A = 100;   // Resting position
const int BASE_SERVO_B = 175;

bool moved = false;

void setup() {
  Serial.begin(9600);
  ServoA.attach(8);
  ServoB.attach(9);
  init_MPU();

  ServoA.write(BASE_SERVO_A);
  ServoB.write(BASE_SERVO_B);
}

void loop() {
  FunctionsMPU();
  Roll = FunctionsPitchRoll(AcX, AcY, AcZ);   // Roll
  Pitch = FunctionsPitchRoll(AcY, AcX, AcZ);  // Pitch

  Serial.print("Roll: "); Serial.print(Roll);
  Serial.print(" | Pitch: "); Serial.println(Pitch);

  // Detect if current orientation is different from "resting"
  if (abs(Roll) > ROLL_THRESHOLD || abs(Pitch) > PITCH_THRESHOLD) {
    if (!moved) {
      moved = true;
      moveToActivePosition();
    }
  } else {
    if (moved) {
      moved = false;
      moveToRestingPosition();
    }
  }

  delay(200);
}

void init_MPU() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  delay(1000);
}

double FunctionsPitchRoll(double A, double B, double C) {
  double DatoB = sqrt(B * B + C * C);
  double angle = atan2(A, DatoB) * 180 / PI;
  return (int)angle;
}

void FunctionsMPU() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // ACCEL_XOUT_H
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // read 6 bytes

  AcX = Wire.read() << 8 | Wire.read(); // ACCEL_X
  AcY = Wire.read() << 8 | Wire.read(); // ACCEL_Y
  AcZ = Wire.read() << 8 | Wire.read(); // ACCEL_Z
}

void moveToActivePosition() {
  for (int i = 175; i >= 70; i--) {
    ServoB.write(i);
    int ll = map(i, 175, 70, 100, 50);
    ServoA.write(ll);
    delay(5);
  }
}

void moveToRestingPosition() {
  for (int i = 70; i <= 175; i++) {
    ServoB.write(i);
    int ll = map(i, 70, 175, 50, 100);
    ServoA.write(ll);
    delay(5);
  }
}
