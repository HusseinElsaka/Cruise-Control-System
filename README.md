# Cruise Control System

## System Descripition 
### Push Button Feature:
System is Ideal untill the Start button is pressed. 
Start with 10 % of total speed.
The system has two push Buttons. The Increment_Button will increase the speed of the car by 25% of the total speed. The Decrement_Button will decrease the speed of the car by 25% of the total speed.
If the speed of the car is on its max speed (100%). The Increment button signal neglected. 
If the speed of the car is on its min speed (0%) or (10%). The Decrement Button signal neglected. 
If the driver pressed the Increment Button and the Decrement Button at the same time. The Increment Button signal and Decrement Button Signal neglected. 
If the decrement button is pressed after the increment button is pressed by 1000msec. the software neglect the increment button. 
If the increment button is pressed after the decrement button is pressed by 1500msec. the software neglect the decrement button. 
The software handle the Button debouncing with accuracy 50msec. 
The system shall include a brake switch in case of the driver take_over mode. The driver take_over mode means that the driver will be in control of the car
The break decrement the speed of the car by 25%.
if push in break button twice within 1 second re-initialize the feature of the cruise control
### Ultrasonic Feature:
The system include an ultrasonic sensor for detecting any obstacles
If the obstacle is about 80cm or greater from the car && the Decrement Button signal is not pressed && the increment button is not pressed. The Car be on its max speed(100%). Note: Whatever the actual speed is. The speed signal has to reach it’s maximum.
If the obstacle is about 50cm or greater from the car && less than 80 && the Decrement Button signal is not pressed && the increment button is not pressed. The Car shall be on its max speed(75%).
If the obstacle is about 20cm or greater from the car && less than 50 && the Decrement Button signal is not pressed && the increment button is not pressed. The Car shall be on its max speed(50%). 
If the obstacle is less than 20cm from the car && the Decrement Button signal is not pressed && the increment button is not pressed. The system shall decrease the speed of the car by 5% of it’s total speed and reaches it’s zero speed before the obstacle is about 4cm of the car.
If there is an action needed to take related by the speed of the car through the ultrasonic feature. And the (Increment Button or the decrement Button is pressed). The system shall respond to the push button feature.
The whole of the feature of the cruise control system can be disabled by the brakes button. The meaning of the whole feature is disabled is that the software shall neglect the change in any of the signals related by the cruise control feature. (Ultrasonic signals).
If the decrement or the increment button is pressed. The ultrasonic feature can’t take any actions related by the speed control of the car. Until 5000 msec
### Communication Feature:
Once there is a new value is received by the Manin ECU for the speed. The partner ECU shall display the new value on the LCD. 
Communication between two ECU’s is based on UART Protcole
