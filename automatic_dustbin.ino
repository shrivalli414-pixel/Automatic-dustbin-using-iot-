#include <Servo.h> // includes the servo library
Servo myservo;

#define echopin 5   // Echo pin for ultrasonic sensor
#define trigpin 6   // Trigger pin for ultrasonic sensor
#define buzzerPin 11 // Buzzer pin

int set_cm = 30;
long ultra_time; 
long dis_cm;

void setup() { 
  Serial.begin(9600);

  // Attach the servo motor to pin 9
  myservo.attach(9);
  myservo.write(0);

  // Configure pins
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  delay(1000);
}

void loop() {
  // Read distance from ultrasonic sensor
  ultra_read();

  Serial.print("Distance: ");
  Serial.println(dis_cm); 

  // Control the servo based on the distance measured
  if (dis_cm < set_cm) {
    myservo.write(110);
    digitalWrite(buzzerPin, HIGH); // buzzer ON
    delay(3000); 
  } else {
    myservo.write(0);
    digitalWrite(buzzerPin, LOW); // buzzer OFF
  }

  delay(100);
}

// Function to read distance using the ultrasonic sensor
void ultra_read() {
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  
  ultra_time = pulseIn(echopin, HIGH);
  dis_cm = ultra_time / 29 / 2; 
}
