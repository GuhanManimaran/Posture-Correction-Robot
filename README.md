# Posture-Correction-Robot
An Arduino-based gesture detection system using the MPU6050 sensor to monitor pitch and roll. When significant motion is detected, two servo motors move to an active position, simulating actions like opening a lid or waving. Once stable, the servos return to their resting state.

# Gesture-Controlled Servo System using MPU6050 and Arduino

This project detects motion using the MPU6050 sensor and controls two servo motors accordingly. It calculates pitch and roll from the sensor data, and if the movement exceeds a defined threshold, the servos shift to an active position. When the motion stops, the servos return to their resting state. It’s ideal for gesture-triggered applications such as smart lids, robotic arms, or interactive installations.

##  Components Used

- Arduino Uno/Nano
- MPU6050 (IMU sensor)
- 2x Servo Motors
- Jumper Wires
- Breadboard or PCB

##   Features

- Motion detection using pitch and roll angles
- Threshold-based gesture activation
- Smooth servo movement transitions
- Uses Wire (I2C) and Servo libraries

##  File

- `main.ino`: Arduino sketch for MPU6050 initialization, motion detection, and servo control.


##  Setup Instructions

1. Connect MPU6050:
   - VCC → 5V, GND → GND, SDA → A4, SCL → A5
2. Connect ServoA to pin 8 and ServoB to pin 9.
3. Upload `main.ino` to Arduino via the Arduino IDE.
4. Open Serial Monitor (9600 baud) to view pitch and roll values.
5. Move the setup and watch the servos respond to orientation.

##  Configuration

- Adjust `ROLL_THRESHOLD` and `PITCH_THRESHOLD` for sensitivity.
- Modify `BASE_SERVO_A` and `BASE_SERVO_B` for different resting angles.

##  Circuit Connection

> ![image](https://github.com/user-attachments/assets/39b25795-d63d-48df-9f6e-5beb48aa7850)


##  License

Open-source for educational and hobby use.


