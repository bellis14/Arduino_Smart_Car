#include <Servo.h>
#include <NewPing.h>
#include <IRremote.h>

#define ENA 6
#define remoteInput 12
#define N1 11
#define N2 9
#define N3 8
#define N4 7
#define ENB 5
#define irR 10
#define irM 4
#define irL 2
#define servoPin 3
#define echo A4
#define trig A5
int rStatus = 0;
int lStatus = 0;
int mStatus = 0;
int servoPos = 0;
int driveMode = 0;
int startMode = 4;
bool objectFound = false;
unsigned long remoteReading;
Servo servo;
NewPing sonar(trig, echo);
IRrecv irrecv(remoteInput);
decode_results results;


void setup() {
  // initialize pins to motor shield 
  pinMode(ENA, OUTPUT);
  pinMode(N1, OUTPUT);
  pinMode(N2, OUTPUT);
  pinMode(N3, OUTPUT);
  pinMode(N4, OUTPUT);
  pinMode(ENB, OUTPUT);
 
  servo.attach(servoPin);
  
  //Initalize pins to ir sensor module for line tracking
  pinMode(irR, INPUT);
  pinMode(irM, INPUT);
  pinMode(irL, INPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() 
{
   if (irrecv.decode(&results))
   {
     remoteReading = results.value;
     Serial.println(remoteReading);
     irrecv.resume();
   }

   if (remoteReading == 16738455)
   {
     Serial.println("Manual 1");
     driveMode = 1;
   }
   else if (remoteReading == 16750695)
   {
     Serial.println("Obstacle Avoidance 2");
     driveMode = 2;
   }
   else if (remoteReading == 16756815)
   {
     Serial.println("Line Tracking 3");
     driveMode = 3;
   }

   if (driveMode == 1)
   {
      if (startMode != driveMode)
      {
        Stop();
        delay(1000);
        startMode = driveMode;
      }
      if (remoteReading == 16736925)
        forward();
      else if (remoteReading == 16761405)
        left();
      else if (remoteReading == 16720605)
        right();
      else if (remoteReading == 16754775)
        back();
      else if (remoteReading == 16712445)
        Stop();
   }
   else if (driveMode == 2)
   {
      if (startMode != driveMode)
      {
         Stop();
         delay(1000);
         startMode = driveMode;
      }
      obstacleAvoidance();
   }
   else if (driveMode == 3)
    {
       if (startMode != driveMode)
       {
          Stop();
          delay(1000);
          startMode = driveMode;
       }
       lineTracking();
    {   
}

void obstacleAvoidance()
{
   int distance = obstacleDetect();
   if (distance < 35)
   {
      turnAround();
      delay(1000);
   }
   else
   {
      forward();
   }
   delay(100);
}

void lineTracking()
{
   lStatus = digitalRead(irL);
   rStatus = digitalRead(irR);
   mStatus = digitalRead(irM);
   
   if (mStatus == HIGH)
   {
      Serial.print("Forward\n");
      forward();
   }
   else if (rStatus == HIGH)
   {
      Serial.print("turn left\n");
      left();
   }
   else if (lStatus == HIGH)
   {
      Serial.print("turn right\n");
      right();
   }
   
   delay(30);
}

int obstacleDetect()
{
   delay(70);
   int obstacle_distance = sonar.ping_cm();
   if (obstacle_distance == 0)
      obstacle_distance = 100;
   return obstacle_distance;
}

void servoRight()
{
  for (servoPos = 55; servoPos <= 125; servoPos++)
   {
     servo.write(servoPos);
     delay(15);
   }
}

void servoLeft()
{
  for (servoPos = 125; servoPos >= 55; servoPos--)
   {
     servo.write(servoPos);
     delay(15);
   }
}

// Turn the car around
void turnAround()
{
  // Turn left and right side motors on
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  // Configure the directional rotation of the tires
  digitalWrite(N1, HIGH);
  digitalWrite(N2, LOW);
  digitalWrite(N3, HIGH);
  digitalWrite(N4, LOW);
}

// Stop the car
void Stop()
{
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// Move the car forward
void forward()
{
  // Turn left and right side motors on
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);

  // Configure the directional rotation of the tires
  digitalWrite(N1, HIGH);
  digitalWrite(N2, LOW);
  digitalWrite(N3, LOW);
  digitalWrite(N4, HIGH);
}

// Move the car right
void right()
{
  // Turn off left side motors
  // and increase the motor speed of the 
  // motors on the right side
  analogWrite(ENA, 175);  //CALIBRATE LATER
  analogWrite(ENB, 0);

  // Configure the directional rotation of the tires
  digitalWrite(N1, HIGH);
  digitalWrite(N2, LOW);
  digitalWrite(N3, LOW);
  digitalWrite(N4, HIGH);
}

// Move the car left
void left()
{
  // Turn off right side motors
  // and increase the motor speed of the 
  // motors on the left side
  analogWrite(ENA, 0);
  analogWrite(ENB, 200); //CALIBRATE LATER

  // Configure the directional rotation of the tires 
  digitalWrite(N1, HIGH);
  digitalWrite(N2, LOW);
  digitalWrite(N3, LOW);
  digitalWrite(N4, HIGH);
}

// Move the car backwards
void back()
{
  // Turn left and right side motors on
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);

  // Configure the directional rotation of the tires
  digitalWrite(N1, LOW);
  digitalWrite(N2, HIGH);
  digitalWrite(N3, HIGH);
  digitalWrite(N4, LOW);
}
