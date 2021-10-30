#define DEBUG 1
#include <Servo.h>
//Tenemos 6 servos. El servo 0 funcionará con el joystick 2
char buff[50];
const int N_SERVOS = 6;
Servo servos[N_SERVOS];

const int servoPins[6] = {11, 10, 9, 6, 5, 3};
const float minAngleServo[6] = {0, 0, 0, 0, 0, 110};
const float maxAngleServo[6] = {180, 180, 180, 180, 180, 180};

//Codigo pegado

float salto = 1.0;                 // Controla el salto por movimiento
float salto0 = 1.0;
int Eje_X = A2 ;
int Eje_X2 = A0 ;

int counter = 0;
int pulsation;

volatile unsigned int timerIteration = 0;
bool serialWrite = false;

void setup() {
  Serial.begin(9600);

  // Initialization
  for (int i = 0; i < N_SERVOS; i++) {
    servos[i].attach(servoPins[i]);

    // Initial positioning
    float angleServo = servos[i].read() ;

    if (angleServo <= minAngleServo[i])
      angleServo = minAngleServo[i];
    else if (angleServo >= maxAngleServo[i])
      angleServo = maxAngleServo[i];

    servos[i].write(angleServo);

    if (DEBUG) {
      sprintf(buff, "Angle servo %i: %i.\n", i, int(angleServo));
      Serial.print(buff);
    }

    delay(1000);
  }
  // Joystick button configuration
  pinMode(4, INPUT_PULLUP);

  // Timer
  SREG = (SREG & 0b01111111); //Desabilitar interrupciones
  TIMSK2 = TIMSK2 | 0b00000001; //Habilita la interrupcion por desbordamiento
  TCCR2B = 0b00000111; //Configura preescala para que FT2 sea de 7812.5Hz
  SREG = (SREG & 0b01111111) | 0b10000000; //Habilitar interrupciones //Desabilitar interrupciones
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  // Counter servo update
  pulsation = digitalRead(4);
  if (  pulsation == LOW ) {
    counter = (counter + 1) % (N_SERVOS - 1);              //Incrementa el contador en 1
    sprintf(buff, "Moving servo %i.\n", counter);
    Serial.print(buff);
    delay (1000);           // Retardo
  }

  //Dependiendo del contador elegimos un servo distinto
  int p = analogRead(A2);
  float angleServo = servos[counter].read();
  if ( p < 400 )                    // Si la lectura es menor de 400
    angleServo = angleServo - (((400 - p) / 400) * salto); // disminuimos el angulo
  else if (p > 600)                 // Si mayor de 600
    angleServo = angleServo + (((p - 600) / 400) * salto) ; // Aumentamos el angulo

  // Restricting movement
  if (angleServo <= minAngleServo[counter]) {
    angleServo = minAngleServo[counter];
  } else if (angleServo >= maxAngleServo[counter]) {
    angleServo = maxAngleServo[counter];
  }

  servos[counter].write(angleServo);             // Y este es el que mueve el servo

  if (serialWrite && DEBUG) {
    sprintf(buff, "Angle servo %i: %i.\n", counter, int(angleServo));
    Serial.print(buff);
  }

  delay(10);                       // Este delay regula la velocidad del movimiento



  //Ahora hacemos el control del servo 0 con el segundo joystick

  int q = analogRead(A0);
  angleServo = servos[N_SERVOS - 1].read();
  if ( q < 400 )                    // Si la lectura es menor de 400
    angleServo = angleServo - (((400 - q) / 400) * salto0) ; // disminuimos el angulo
  else if (q > 600)                 // Si mayor de 600
    angleServo = angleServo + (((q - 600) / 400) * salto0) ;

  // Restricting movement
  if (angleServo <= minAngleServo[N_SERVOS - 1]) {
    angleServo = minAngleServo[N_SERVOS - 1];
  }
  else if (angleServo >= maxAngleServo[N_SERVOS - 1]) {
    angleServo = maxAngleServo[N_SERVOS - 1];
  }
  servos[N_SERVOS - 1].write(angleServo);

  if (serialWrite && DEBUG) {
    sprintf(buff, "Angle servo 5: %i.\n", int(angleServo));
    Serial.print(buff);
  }
  delay(10);
}

ISR(TIMER2_OVF_vect) {
  timerIteration++;
  if (timerIteration > 29) {
    serialWrite = true;
    timerIteration = 0;
  }else{
    serialWrite = false;
  }
}
