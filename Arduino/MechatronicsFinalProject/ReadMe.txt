This was the code I wrote for a final project for Mechatronics

The problem we were seeking to solve, is the inability for a smart wheelchair to be able to detect the height and distance of a toilet from the user. This guidance 
system could later be used with a lifting mechanism to lift the user over the toilet, as well as a wheelchair seat which can open and close (which I designed during 
research with Dr. Yoon in the Smart Medical Devices Labratory at UWB https://nickdegrasse.wixsite.com/nicholasdegrasse/multifunction-wheelchair-seat), to autonomously
allow a wheelchair user to use the restroom.

The solution was to create a gimbal using two servo motors on perpendicular axis' with an ultrasound sensor attached, to feed distance and orientation data to an Arduino
Uno, which will start detecting distance automatically when the user is within a specific distance, then when the wheelchair is at a target range, the Arduino will use
that data to return the height of the toilet. All information is communicated over i2c to a screen mounted on the front of the wheelchair, and all components are wired
and attached to the wheelchair out of the users way.

We were able to return toilet height that was accurate within 5% for variable heights, and return real time distance to the tip of the toilet as well