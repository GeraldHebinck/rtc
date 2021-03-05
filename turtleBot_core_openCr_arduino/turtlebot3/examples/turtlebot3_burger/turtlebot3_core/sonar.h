// sonar.h
// edited 27.01.2021 by OJ
//--------------------------------------------
// Misst den Abstand mit dem SR04-Sonar-Sensor
// Version mit 2x Sonar
//
// die Funktionsaufrufe sind im File turtlebot3_core.ino 
// auszuführen 

// edited 03.03.2021 by HHT
//--------------------------------------------
// Aufruffrequenz erhoeht, max_dist und timeout reduziert.
// Abwechselndes lesen der Sensoren.
// Aufruf von pulseIn in Funktion gekapselt.


#include "turtlebot3_core_config.h"

const int UPDATE_INTERVALL=16; //ms
// Schallgeschwindigkeit 343,2 m/s 
  // 5800us pro m hin und zurück
  // Sonar < 2m => Timeout 11600 us
  // Sonar < 3m => Timeout 17400 us
const uint32_t TIMEOUT=6000; //us
// ...dazu passend der maximale Weg
const uint32_t  MAX_DIST=100; //cm

  //-- Abstands-Messung mit 2x SR04-Sonar durchfuehren --
  //so KLAPPTS => rostopic hz /tf ~28 Hz bei 35cm
  // uint-Version in ganzen cm => float vermeiden


float sonar_data_ ;//global
SONAR_PIN sonar_pin_; // Instanz 
float sonar_data2_ ;//global
SONAR_PIN sonar_pin2_; // Instanz 

// Funktion im setup() aufrufen
void initSonar(void)
{
  sonar_pin_.trig = BDPIN_GPIO_1;  //50
  sonar_pin_.echo = BDPIN_GPIO_2;  //51

  pinMode(sonar_pin_.trig, OUTPUT);
  pinMode(sonar_pin_.echo, INPUT);
  digitalWrite(sonar_pin_.trig, LOW);
}

void initSonar2(void)
{
   //diese Pins sind anscheined bislang NC 
   //$grep -r BDPIN_GPIO
  sonar_pin2_.trig = BDPIN_GPIO_3;  //52
  sonar_pin2_.echo = BDPIN_GPIO_4;  //53

  pinMode(sonar_pin2_.trig, OUTPUT);
  pinMode(sonar_pin2_.echo, INPUT);
  digitalWrite(sonar_pin2_.trig, LOW);
}

// Funktion wertet pulseIn für den sensor aus.
float measureSonar(SONAR_PIN sensor)
{
  uint32_t duration_uint, distance_uint;
  digitalWrite(sensor.trig, LOW);
  delayMicroseconds(2);
  digitalWrite(sensor.trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor.trig, LOW);

  //pulseIn mit Abbruch bei zu langer Wartezeit
  duration_uint = pulseIn(sensor.echo, HIGH, TIMEOUT);
  // ((340[m/s] * t[us]) * 100 [cm/m] / 1000000[us/s]) / 2  
  distance_uint = ((340 * duration_uint) / 10000) / 2;

  if (distance_uint <= MAX_DIST) /*cm*/
      return (float) distance_uint; //to global float Var
  else 
      return 0.0;
}

// Funktion in der Loop aufrufen
void updateSonar(uint32_t now)
{
  static uint32_t last_time = 0;
  static int last_sensor = 0;     
  
    if(now - last_time > UPDATE_INTERVALL)
    { // update nur alle xxx ms
      last_time = now; //aktuelle Zeit merken
      if(last_sensor)
      {
        sonar_data_ = measureSonar(sonar_pin_);
        last_sensor = 0;
      }
      else
      {
        sonar_data2_ = measureSonar(sonar_pin2_);
        last_sensor = 1;
      }
    }
}


 
// Funktion für die Konstruktion der Sensor-Msg des TurtleBots 
float getSonarData(void){
  return sonar_data_; //read global 
}

// Funktion für die Konstruktion der Sensor-Msg des TurtleBots 
float getSonarData2(void){
  return sonar_data2_; //read global 
}
