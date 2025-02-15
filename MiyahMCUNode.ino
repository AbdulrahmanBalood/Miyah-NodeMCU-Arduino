

//importing all the necessary libraries, the ESP8266 MCU node wifi support library, the software serial, and the firebase implementation libraries to establish the connection between the ESP8266 and the Firebase database
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <FirebaseHttpClient.h>

//set up firebase connection with link of the firebase databse  for FIREBASE_HOST and secret key authorization for FIREBASE_AUTH
#define FIREBASE_HOST "miyah-application-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "zVPxt4bgSASoD6hp5Z4eaYCVM8H0Uo9EJeHIYzAY" //firebase database seceret key
//set up wifi connection
#define WIFI_SSID "note20mhmd" //wifi network name 
#define WIFI_PASSWORD "20406080" //wifi password


//define pins for the ultrasonic sensor (trig and echo pins), and the variables for the water level calculations and data
String sensorData;
char rdata;
const int trigPin = D5;
const int echoPin = D6;
int firstVal;
 long duration;  
 int distance;  


void setup() { //setup method only runs code once

  //establish a wirelesss connection between the MCUNode ESP8266 to the wifi network

  pinMode(trigPin, OUTPUT); //define trigger pin as output
  pinMode(echoPin, INPUT); //define echo pin as input
    Serial.begin(9600);

  //source for setting up the firebase-arduino connection https://www.instructables.com/Firebase-Integrate-With-ESP8266/

  //establish the wifi and firebase connection
pinMode(16, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
    }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  //begin the  firebase connection
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("distance", 0);
}//end of setup method


//ultrasonic distance measurement logic
void loop() {//loop method is where the main code logic that's going to be repeated should be

//source for clearing trigPin and setting it HIGH http://electronoobs.com/eng_arduino_tut80.php

//clear the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

//set the trigPin on HIGH state for 10µs (microseconds unit)
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

//reads the echoPin and then returns the sound wave frequencies travel-time in microseconds 
duration = pulseIn(echoPin, HIGH);

//calculates the distance, source https://simple-circuit.com/arduino-hc-sr04-sensor-distance-meter/
distance= duration*0.034/2;  

//prints the distance on the Ardunio IDE's serial monitor 
Serial.print("Distance: ");
Serial.println(distance);
Firebase.setInt("distance",distance);
delay(2000);

}//end of loop method
