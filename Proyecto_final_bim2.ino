/*
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Quinto perito
   Quinto electronica
   Codigo Tecnico: EB5AV 
   Curso: Taller de electronica digital y reparacion de computadoras I
   Proyecto: Proyecto final
   Dev: Profe. Alejandro Lopez Navas
   Fecha:  27 de mayo
   link de la simulacion: https://www.tinkercad.com/things/4CQF20XuWoK-tremendous-densor-blad?sharecode=X12VNM9Bp9AHumwx_LJMSUuHYiBg0mKVI14HXhO2-80
*/

#include <Keypad.h>  
#include <Servo.h>
#include <LiquidCrystal_I2C.h> 
#include <Wire.h> 

#define filas_teclado 4        
#define columnas_teclado 4     
#define f1_teclado 9          
#define f2_teclado 8         
#define f3_teclado 7          
#define f4_teclado 6         
#define c1_teclado 5           
#define c2_teclado 4           
#define c3_teclado 3          
#define c4_teclado 2

#define ON(pin) digitalWrite(pin, HIGH)
#define OFF(pin) digitalWrite(pin, LOW)
#define salida(pin) pinMode(pin, OUTPUT)
#define entrada(pin) pinMode(pin, INPUT)

#define led_1 A0
#define led_2 A1
#define led_3 A2

#define pinServo 10 

#define direccion_lcd 0x20     
#define filas 2                
#define columnas 16 

const int A = 11;
const int B = 12;
const int F = 13;
const int G = A3;

byte pos_lcd = 0;

char keys[filas_teclado][columnas_teclado] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pines_filas[filas_teclado] = {f1_teclado,f2_teclado,f3_teclado,f4_teclado};
byte pines_columnas[columnas_teclado] = {c1_teclado,c2_teclado,c3_teclado,c4_teclado};

Keypad teclado = Keypad( makeKeymap(keys), pines_filas, pines_columnas, filas_teclado, columnas_teclado);
Servo ServoMovimiento;
LiquidCrystal_I2C lcdpresentacion(direccion_lcd, columnas, filas);

void config_outputs(void);
void config_HMI(void);
  
void setup() {
  Serial.begin(9600);
  Serial.println("Proyecto final");
  config_outputs();
  config_HMI();
  ServoMovimiento.write(0);
}

void loop() {
  char tecla = teclado.getKey();
  
  if(tecla == '1') {
    Serial.println("Contador de 0 a 99:");
    for(int a = 0; a < 100; a++) {
      Serial.println(a);
      delay(500);
    }
  }
      
  if(tecla == '2') {
    Serial.println("Contador de 99 a 0:");
    for(int b = 99; b >= 0; b--) {
      Serial.println(b);
      delay(500);
    }
  }
  
  if(tecla == '3') {
    Serial.println("Secuencia de auto fantastico:");
      for(int c = 0; c < 3; c++) {
        for(int d = 0; d <= 3; d++) {
          if(d == 0) {
            ON(led_1);
            delay(200);
          }
          
          if(d == 1) {
            OFF(led_1);
            ON(led_2);
            delay(200);
          }
          
          if(d == 2) {
            OFF(led_2);
            ON(led_3);
            delay(200);
          }
        }
        
        for(int d = 3; d >= 0; d--) {
          if(d == 2) {
            ON(led_3);
            delay(200);
          }
          
          if(d == 1) {
            OFF(led_3);
            ON(led_2);
            delay(200);
          }
          
          if(d == 0) {
            OFF(led_2);
            ON(led_1);
            delay(200);
          }
        }
      }
      
      for(int e = 0; e < 4; e++) {
        ON(led_1);
        ON(led_2);
        ON(led_3);
        delay(300);
        OFF(led_1);
        OFF(led_2);
        OFF(led_3);
        delay(300);
      }
    }
  
  if(tecla == '4') {
    Serial.println("Animacion con display de 7 segmentos:");
    for(int f = 0; f < 4; f++) {
        for(int g = 0; g <= 5; g++) {
          if(g == 0) {
            ON(A);
            delay(300);
          }
          
          if(g == 1) {
            OFF(A);
            ON(B);
            delay(300);
          }
          
          if(g == 2) {
            OFF(B);
            ON(G);
            delay(300);
          }
          
          if(g == 3) {
            OFF(G);
            ON(F);
            delay(300);
          }
          
          if(g == 4) {
            OFF(F);
            ON(A);
            delay(100);
          }
        }
      }
    
    for(int e = 0; e < 4; e++) {
      ON(A);
      ON(B);
      ON(G);
      ON(F);
      delay(300);
      OFF(A);
      OFF(B);
      OFF(G);
      OFF(F);
      delay(300);
      }
    }
  
  if(tecla == '5'){ 
    Serial.println("Movimiento de un Servomotor:");
    ServoMovimiento.write(45);
    delay(300);
    ServoMovimiento.write(90);
    delay(300);
    ServoMovimiento.write(135);
    delay(300);
    ServoMovimiento.write(180);
    delay(500);
    ServoMovimiento.write(0);
    delay(600);
  }
}
                                
void config_outputs(void) {
  salida(led_1);
  salida(led_2);
  salida(led_3);
  salida(pinServo);
}

void config_HMI(void) {
  ServoMovimiento.attach(pinServo);
  lcdpresentacion.init();
  lcdpresentacion.backlight();
  lcdpresentacion.setCursor(4,0);
  lcdpresentacion.print("Marito");
  lcdpresentacion.setCursor(1,1);
  lcdpresentacion.print("Proyecto final");
}
