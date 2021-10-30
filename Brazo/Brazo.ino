#include <Servo.h>
//Tenemos 6 servos. El servo 0 funcionará con el joystick 2
Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

//Codigo pegado

float angulo0 = servo0.read() ;               // Empezamos en el centro
float angulo1 = servo1.read() ;
float angulo2 = servo2.read() ;
float angulo3 = servo3.read() ;
float angulo4 = servo4.read() ;
float angulo5 = servo5.read() ;
int salto = 1 ;                 // Controla el salto por movimiento
int salto0 = 1;
int Eje_X = A2 ;
int Eje_X2 = A0 ;

int contador = 1;
int pulsacion;
void setup(){
    Serial.begin(9600);
    servo0.attach(11);
    servo1.attach(10);
    servo2.attach(9);
    servo3.attach(6);
    servo4.attach(5);
    servo5.attach(3);
  
if (angulo0<=0){
  angulo0=0;
  }
else if (angulo0>=180){
  angulo0=180;
  } 
    servo0.write(angulo0);
    delay(1000);
    
if (angulo1<=0){
          angulo1=0;
       }else if (angulo1>=180){
          angulo1=180;
       }
    servo1.write(angulo1);
    delay(1000);


if (angulo2<=0){
    angulo2=0;
  }else if (angulo2>=180){
    angulo2=180;
  }    
    servo2.write(angulo2);
    delay(1000);

if (angulo3<=0){
    angulo3=0;
  }else if (angulo3>=180){
    angulo3=180;
  }
    servo3.write(angulo3);
    delay(1000);

if (angulo4<=0){
    angulo4=0;
  }else if (angulo4>=180){
    angulo4=180;
  }
    servo4.write(angulo4);
    delay(1000);

if (angulo5<=110){
    angulo5=110;
    }
  else if (angulo5>=180){
    angulo5=180;
    }
    servo5.write(angulo5);
    delay(1000);
    pinMode(4, INPUT_PULLUP);
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     void loop(){ 
      pulsacion=digitalRead(4);
      if (  pulsacion == LOW ){      
         contador++;               //Incrementa el contador
         if (contador == 6){
          contador=1;
         }
         
         Serial.println(contador); //Imprime el valor por consola
         delay (1000);           // Retardo
      }
      //Dependiendo del contador elegimos un servo distinto
     if (contador == 1){
       int p = analogRead(A2);
       if ( p < 400 )                    // Si la lectura es menor de 400
           angulo1 = angulo1 - (((400-p)/400)*salto);    // disminuimos el angulo
       else if (p>600)                   // Si mayor de 600
          angulo1 = angulo1 + (((p-600)/400)*salto) ;    // Aumentamos el angulo
       if (angulo1<=0){
          angulo1=0;
       }else if (angulo1>=180){
          angulo1=180;
       }
       
       servo1.write(angulo1);             // Y este es el que mueve el servo
       delay(10);                       // Este delay regula la velocidad del movimiento
    }


 if (contador == 2){
  int p = analogRead(A2);
  if ( p < 400 ){                    // Si la lectura es menor de 400
    angulo2 = angulo2 - salto ;    // disminuimos el angulo
  }else if (p>600){                   // Si mayor de 600
    angulo2 = angulo2 + salto ;    // Aumentamos el angulo
  }
  if (angulo2<=0){
    angulo2=0;
  }else if (angulo2>=180){
    angulo2=180;
  }
  servo2.write(angulo2);             // Y este es el que mueve el servo
  delay(10);                       // Este delay regula la velocidad del movimiento
}


 if (contador == 3){
  int p = analogRead(A2);
  if ( p < 400 )                    // Si la lectura es menor de 400
    angulo3 = angulo3 - salto ;    // disminuimos el angulo
  else if (p>600)                   // Si mayor de 600
    angulo3 = angulo3 + salto ;    // Aumentamos el angulo
  if (angulo3<=0){
    angulo3=0;
  }else if (angulo3>=180){
    angulo3=180;
  }
                      
  servo3.write(angulo3);             // Y este es el que mueve el servo
  delay(10);                       // Este delay regula la velocidad del movimiento
         }


 if (contador == 4){
  int p = analogRead(A2);
  if ( p < 400 )                    // Si la lectura es menor de 400
    angulo4 = angulo4 - salto ;    // disminuimos el angulo
  else if (p>600)                   // Si mayor de 600
    angulo4 = angulo4 + salto ;    // Aumentamos el angulo
  if (angulo4<=0){
    angulo4=0;
  }else if (angulo4>=180){
    angulo4=180;
  }
                      
  servo4.write(angulo4);             // Y este es el que mueve el servo
  delay(10);                       // Este delay regula la velocidad del movimiento
         }


 if (contador == 5){
  int p = analogRead(A2);
  if ( p < 400 )                    // Si la lectura es menor de 400
    angulo5 = angulo5 - salto ;    // disminuimos el angulo
  else if (p>600)                   // Si mayor de 600
    angulo5 = angulo5 + salto ;    // Aumentamos el angulo
  if (angulo5<=110){
    angulo5=110;
    }
  else if (angulo5>=180){
    angulo5=180;
    }               
  servo5.write(angulo5);             // Y este es el que mueve el servo
  delay(10);                       // Este delay regula la velocidad del movimiento
         }


//Ahora hacemos el control del servo 0 con el segundo joystick

int q = analogRead(A0);
if ( q < 400 )                    // Si la lectura es menor de 400
  angulo0 = angulo0 - (((400-q)/400)*salto0) ;    // disminuimos el angulo
else if (q>600)                   // Si mayor de 600
  angulo0 = angulo0 + (((q-600)/400)*salto0) ;
if (angulo0<=0){
  angulo0=0;
  }
else if (angulo0>=180){
  angulo0=180;
  }
servo0.write(angulo0);  
delay(10);
        }
