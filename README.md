# Smart Car

## Brief Overview
The smart car application implements line tracking, obstacle avoidance, and manual drive control functionalities using infrared and ultrasonic sensors to drive the cars motors. The hardware used in this project comes from the Elegoo Smart Robot Car Kit 3.0 Plus and was purchased from them. The software written on the arduino to control the components and it's peripherals is custom written software by me. 

## Operation 
When the smart robot is powered on the robot will sit and wait for a drive mode to be selected. The infrared remote is used to switch the smart robot into one of three modes, line tracking, obstacle avoidance, and manual driving. Button "1" puts the car into manual drive, button "2" is obstacle avoidance, and button "3" line tracking. 

### Manual Drive
Manual drive provides the functionality to pilot the car using 5 keys to propel the car. The forward and back arrows drive the car forward and backwards and then the left and right arrows turn the car left and right respectively while the "OK" button is used to stop the car. Manual drive requires the use of an infrared sensor to receive the input from the infrared remote. The binary codes received from the remote are processed and then activate the motor control. When the car is switched into any other mode the car will initially stop and then begin carrying out its drive mode. 

### Obstacle Avoidance
The obstacle avoidance capabilities are limited but perform consistently. When the car gets within 60 centimeters of an object it should turn around about 150 degrees and continue in the forward direction. The cars ability to detect objects significantly drops when the obstacle is located at more of an angle in front of the car instead of perpendicular. The obstacle avoidance functionality utilizes the feedback from an ultrasonic sensor to calculate how far away an object is using the speed of sound. 

### Line Tracking
When the smart robot is placed  

## Video demonstration

