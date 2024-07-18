/*******************************************************************************
 * Nombre del Sketch: robot car con servo, escáner, LED RGB
 * Descripción: Robot coche evitador de obstáculos con LEDs parpadeantes
 * Creado: Julio 2024
 * Autor: Hernzum
 * Versión: 1.0
 *
 * Configuración:
 * - Conectar el servo al pin A1.
 * - Conectar el sensor de ultrasonidos: pin de eco a A2 y pin de trigger a A3.
 * - Conectar los LEDs: rojo al pin 10, verde al pin 12, azul al pin 13.
 * - Conectar los motores: ENA al pin 11, ENB al pin 3, IN1 al pin 8, IN2 al pin 7, IN3 al pin 6, IN4 al pin 5.
 * - Conectar el sensor táctil al pin 4.
 * - Asegurarse de tener instaladas las librerías Servo y NewPing.
 *
 * Uso:
 * - El robot se moverá hacia adelante mientras no haya obstáculos en su camino.
 * - Cada 3 segundos, el robot se detendrá y escaneará su entorno para decidir la dirección a tomar.
 * - Si detecta un obstáculo a menos de 10 cm, retrocederá, escaneará y girará hacia la dirección con más espacio.
 * - Si se activa el sensor táctil, el robot se detendrá, escaneará y avanzará hacia adelante, luego girará a la izquierda.
 ******************************************************************************/

#include <Servo.h>
#include <NewPing.h>

int redLED = 10;        // red LED pin
int greenLED = 12;        // green LED pin
int blueLED = 13;       // blue LED pin
int IN1 = 8;        // left motor forward pin
int IN2 = 7;        //     backward pin
int IN3 = 6;        // right motor forward pin
int IN4 = 5;        //       backward pin
int ENA = 11;       // left motor enable pin
int ENB = 3;        // right motor enable pin
int scanTime = 250;       // set time between scans (ms)
int turnTime = 500;       // time to make turn or move backward
int motorSpeed;
float bias = 0.95;        // bias speed of right motor
float leftDist, rightDist, frontDist, frontDistR, frontDistL;

void setup()
{
  servo.attach(servoPin);     // attach servo motor pin
  Serial.begin(9600); // baud rate
  
  pinMode(redLED, OUTPUT);  
  pinMode(greenLED, OUTPUT);    // define LED pins as OUTPUT
  pinMode(blueLED, OUTPUT);
  pinMode(trigPin, OUTPUT);       // define trigger pin as OUTPUT
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);     // define motor pins as OUTPUT
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop()
{
  servo.write(100);       // scan front left (100°), return distance
  frontDistL = (sonar.ping_median(5)/2.0)*0.0343;
  delay(50);
  servo.write(80);        // scan front right (80°), return distance
  frontDistR = (sonar.ping_median(5)/2.0)*0.0343;
  frontDist = min(frontDistL,frontDistR);   // minimum of front distances
  distance("front", frontDist);
  if(frontDist >20) direction("forward",100); // move forwad if clear
  else
  {
    direction("stop", 100);     // stop to start scanning
    digitalWrite(blueLED, HIGH);    // turn on blue LED to indicate scanning
    leftDist = scan(170, "left");     // scan 170° and return distance
    rightDist = scan(10, "right");      // scan 10° and return distance
    digitalWrite(blueLED, LOW);   // turn off blue LED
    if(rightDist <15 && leftDist <15)   // move back if clear distance <15cm
    {
      digitalWrite(greenLED, HIGH);   // turn on red and green LEDs
      turn(redLED, "backward");     //         for yellow colour
      digitalWrite(greenLED, LOW);
    }  
    else if(leftDist > rightDist) turn(greenLED, "left");   // turn left
    else if(rightDist > leftDist) turn(redLED, "right");    // turn right
  }

}


void turn (int LED, String direct)    // function to turn right or left
{
   digitalWrite(LED, HIGH);     // turn on LED
   direction(direct, turnTime);     // call function to control motors
   digitalWrite(LED, LOW);      // turn off LED
}

void direction(String direct, int runTime)    // function to set motor direction
{
         if(direct == "forward")     motor(1, 0, 1, 0, 1);    // both motors forward
  else if(direct == "backward") motor(0, 1, 0, 1, 1);   // both motors backward
  else if(direct == "right")         motor(1, 0, 0, 1, 0);    // left forward, right backward
  else if(direct == "left")           motor(0, 1, 1, 0, 0);    // left backward, right forward
  else if(direct == "stop")         motor(0, 0, 0, 0, 0);   // both motors stop
  delay(runTime);         // run time (ms) for motors
}

void motor(int leftF, int leftB, int rightF ,int rightB, int speed)        // motor function
{
  digitalWrite(IN1, leftF);     // control pin IN1 left motor forward
  digitalWrite(IN2, leftB);     // control pin IN2 left motor backward
  digitalWrite(IN3, rightF);      // control pin IN3 right motor forward
  digitalWrite(IN4, rightB);      // control pin IN4 right motor back
  if(speed == 1) motorSpeed = 100;   // higher speed when moving forward
  else motorSpeed = 80;     //       or backward than when turning
  analogWrite(ENA, motorSpeed);   // left motor speed
  motorSpeed = motorSpeed*bias;
  analogWrite(ENB, motorSpeed);   // right motor speed
}

float scan(int angle, String direct)    // function to scan distance at angle
{
  servo.write(angle);       // rotate servo motor
  delay(scanTime);        // delay between scans 
  float dist = (sonar.ping_median(5)/2.0)*0.0343; // check distance (cm)
  distance(direct, dist);     // display to distance on OLED
  servo.write(90);        // rotate servo motor
  delay(scanTime);        // delay between scans
  return dist;
}

void distance (String direct, float dist)   // function to display on OLED
{
 Serial.println("Robonito "); 
Serial.println(direct);
Serial.println(dist); 

}
