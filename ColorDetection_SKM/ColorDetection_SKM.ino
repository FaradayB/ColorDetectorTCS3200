#include <Servo.h>
#include <PID_v1.h>

#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define OUT 6

#define SERVO_PIN 9

Servo myServo;

int currentPos = 0;
int desiredPos = 0;

double Setpoint, Input, Output;
double Kp = 2.0, Ki = 5.0, Kd = 1.0;

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

int redfrequency = 0;
int greenfrequency = 0;
int bluefrequency = 0;

void setup() {
  Serial.begin(9600);

  myServo.attach(SERVO_PIN);

  Setpoint = desiredPos;
  Input = currentPos;
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-255, 255);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  pinMode(OUT, INPUT);
}

void loop() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redfrequency = pulseIn(OUT, LOW);

  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenfrequency = pulseIn(OUT, LOW);

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  bluefrequency = pulseIn(OUT, LOW);

  Serial.print("R = ");
  Serial.print(redfrequency);
  Serial.print(" G = ");
  Serial.print(greenfrequency);
  Serial.print(" B = ");
  Serial.println(bluefrequency);

  if (redfrequency > 210 && redfrequency < 255 && greenfrequency > 195 && greenfrequency < 235 && bluefrequency > 120 && bluefrequency < 160) {
    Serial.println("Color is DARK BLUE");
    desiredPos = 100;
  } else if (redfrequency > 60 && redfrequency < 90 && greenfrequency > 140 && greenfrequency < 170 && bluefrequency > 90 && bluefrequency < 120) {
    Serial.println("Color is PINK");
    desiredPos = 18;
  } else if (redfrequency > 150 && redfrequency < 205 && greenfrequency > 130 && greenfrequency < 175 && bluefrequency > 170 && bluefrequency < 210) {
    Serial.println("Color is BRIGHT GREEN");
    desiredPos = 90;
  } else if (redfrequency > 60 && redfrequency < 90 && greenfrequency > 140 && greenfrequency < 170 && bluefrequency > 125 && bluefrequency < 155) {
    Serial.println("Color is ORANGE");
    desiredPos = 126;
  } else if (redfrequency > 140 && redfrequency < 180 && greenfrequency > 110 && greenfrequency < 155 && bluefrequency > 85 && bluefrequency < 120) {
    Serial.println("Color is LIGHT BLUE");
    desiredPos = 72;
  } else if (redfrequency > 190 && redfrequency < 230 && greenfrequency > 130 && greenfrequency < 160 && bluefrequency > 160 && bluefrequency < 200) {
    Serial.println("Color is DARK GREEN");
    desiredPos = 162;
  } else if (redfrequency > 140 && redfrequency < 170 && greenfrequency > 225 && greenfrequency < 255 && bluefrequency > 190 && bluefrequency < 225) {
    Serial.println("Color is BROWN");
    desiredPos = 180;
  } else if (redfrequency > 85 && redfrequency < 116 && greenfrequency > 85 && greenfrequency < 120 && bluefrequency > 110 && bluefrequency < 130) {
    Serial.println("Color is YELLOW");
    desiredPos = 54;
  } else if (redfrequency > 110 && redfrequency < 130 && greenfrequency > 224 && greenfrequency < 240 && bluefrequency > 190 && bluefrequency < 210) {
    Serial.println("Color is RED");
    desiredPos = 0;
  } else if (redfrequency > 90 && redfrequency < 130 && greenfrequency > 150 && greenfrequency < 180 && bluefrequency > 160 && bluefrequency < 200) {
    Serial.println("Color is GOLD");
    desiredPos = 120;
  }

  Setpoint = desiredPos;
  Input = currentPos;
  myPID.Compute();

  if (Output > 0) {
    currentPos += min(Output, 1);
  } else {
    currentPos += max(Output, -1);
  }

  currentPos = constrain(Setpoint, 0, 180);
  myServo.write(currentPos);

  Serial.print("Current Position: ");
  Serial.print(currentPos);
  Serial.print(" Output: ");
  Serial.println(Output);

  delay(2000);
}