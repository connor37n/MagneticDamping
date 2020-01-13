# Magnetic Damping
Abstract
The goal of this lab is to investigate the effectiveness of measuring the damping constant of a magnetically damped oscillator. 
To investigate this, we measured displacement data for a mass on a spring undergoing underdamped oscillation using the
Ultrasound Sensor of an Arduino. From this data set, we developed a best fit function from which we calculated the damping constant 
and angular frequency of that distribution. We also calculated the angular frequency based on the damping constant. 
We compared these angular frequencies to see how accurate our damping constant is. In addition to this analysis, 
we also incorporated the Accelerometer by measuring and plotting the x-acceleration of the mass versus time and taking the 
second time derivative of our Ultrasound best fit function. Comparing the second derivative of the best fit and the x-acceleration
data shows that the Ultrasound and Accelerometer are consistent with each other. All analysis was done using Python in Google 
Colaboratory (code included in Appendix). As a result, it appears that using the best fit of the displacement curve is 
a reliable way to measure the damping constant of a damped oscillator based on the consistency of our values for angular frequency.
