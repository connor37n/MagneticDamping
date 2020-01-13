#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include<Wire.h>


RF24 radio(7, 8); // Pins for CE, CSN
const byte address[6] = "00001"; //Any address that has to match with the reciever

const int MPU_addr=0x68;  // I2C address of the MPU-6050
long elapsedTime;

float AcX, AcY, AcZ; 

float Xoffset=1100;  
float Yoffset=100;
float Zoffset=2400;

float Xscale=16384;
float Yscale=16384;
float Zscale=18384;

float sound_speed= 343000; // sound speed (mm/s)
float g=980;  // gravity acceleration cm/s^2 


int trigPin = 3;    // Trigger
int echoPin = 2;    // Echo
float duration;
 

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.setChannel(70);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);

  radio.stopListening();
  
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
}
void loop() {  

    
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH)*sound_speed/2000000;

  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,8,true);  // request a total of 14 registers
  AcX=float((Wire.read()<<8|Wire.read())-Xoffset)*g/Xscale;  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L) 
  AcY=float((Wire.read()<<8|Wire.read())-Yoffset)*g/Yscale;  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=float((Wire.read()<<8|Wire.read())-Zoffset)*g/Zscale;  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  elapsedTime = millis();
  long dataArray[5] = {elapsedTime, AcX, AcY, AcZ,duration} ;

  for(int i = 0; i < (sizeof(dataArray) / sizeof(dataArray[0])-1); i++)
  {
    Serial.print(dataArray[i]);
    Serial.print(",");  
   }
   Serial.print(dataArray[4]);
   Serial.println();
   
  radio.write(&dataArray, sizeof(dataArray));  

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
}
