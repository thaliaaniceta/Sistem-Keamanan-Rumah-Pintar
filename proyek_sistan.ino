// Kelompok 01 sistem tertanam
// 1. alexandro hutabarat
// 2. thalia
// 3. naek butarbutar
// 4. trisna lumbanraja
#include <Servo.h> // call library for dht11 sensor

#define gasSensorPin A0 // MQ2 sensor data pin connected to arduino uno A0 pin
#define apiSensorPin A1 // flame sensor data pin connected to arduino uno A1 pin
#define RELAY_ON 0 
#define RELAY_OFF 1 
#define RELAY_1 2 // pin IN1 in relay connected to arduino uno pin 2
#define RELAY_2 3 // pin IN2 in relay connected to arduino uno pin 3
#define trigPin 4 // trigg pin in ultrasonic sensor connected to arduino uno pin 4
#define echoPin 5 // echo pin in ultrasonic sensor connected to arduino uno pin 5

long duration;
int distance;

Servo myservo; // create servo object to control a servo
#define servoPin 6 // pin data servo terhubung ke pin 6 arduino uno

void setup() {
  pinMode(gasSensorPin, INPUT); //declared the MQ2 sensor as input
  pinMode(apiSensorPin, INPUT); //declared the flame sensor as input
  pinMode(trigPin, OUTPUT); //declared the trigg pin in sensor ultrasonic as output
  pinMode(echoPin, INPUT); //declared the echo pin in sensor ultrasonic as input
  myservo.attach(servoPin); 
  pinMode(RELAY_1, OUTPUT); //declared the RELAY_1 as output
  pinMode(RELAY_2, OUTPUT); //declared the RELAY_2 as output

  digitalWrite(RELAY_1, RELAY_ON); //use to control RELAY_1 and set the state to RELAY_ON
  digitalWrite(RELAY_2, RELAY_ON); //use to control RELAY_2 and set the state to RELAY_ON
  Serial.begin(9600); //used to initiate serial communication with a baud rate of 9600
}

void loop() {
  int gasLevel = analogRead(gasSensorPin); //membaca nilai analog dari sensor gas
  Serial.print("Gas Level: "); //untuk menampilkan data yang didapat ke serial monitor
  Serial.println(gasLevel);
  
  if (gasLevel>100) {
    digitalWrite(RELAY_1, RELAY_ON); 
  } else {
    digitalWrite(RELAY_1, RELAY_OFF); 
  }

  // Sensor Api
  int apiLevel = analogRead(apiSensorPin); //membaca nilai analog dari sensor api
  Serial.print("Api Level: "); // untuk menampilkan data yang didapat ke serial monitor
  Serial.println(apiLevel);
  
  if (apiLevel <500){
    digitalWrite(RELAY_2, RELAY_ON);    
  }else {
    digitalWrite(RELAY_2, RELAY_OFF);    
  }

  // Sensor Ultrasonic
  digitalWrite(trigPin, LOW); // set the trig pin to low
  delayMicroseconds(2); // wait for 2 microseconds
  digitalWrite(trigPin, HIGH); // set the trig pin to high
  delayMicroseconds(10); // wait for 10 microseconds
  digitalWrite(trigPin, LOW); // set the trig pin to low
  duration = pulseIn(echoPin, HIGH); // untuk mengukur durasi dari pulse bergema
  distance = duration * 0.034 / 2; // calculate the distance in cm
  
  if(distance < 8) { //objek akan terdeteksi ketika jaraknya kurang dar 8cm
    myservo.write(0); //
  } else {
    myservo.write(130); // servo bergerak ke 130 derajat
  }
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm"); // untuk menampilkan jarak di serial monitor
  
  delay(1000);
}

