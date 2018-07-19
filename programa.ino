#include <LiquidCrystal.h>

// Inicializo la libreria
//Rs, E,D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

//Contadores
int contador_bolsaCamion; //Bolsas totales cargadas en el camion
int contador_bolsaTotal; //Bolsas totales cargadas en todos los camiones
int numeroCamion; //Indica el camion actual

//Sensores
int sensor_bolsa = 2; //Pin del sensor que detecta las bolsas

//Botones
int boton_bolsaMas = A0; //Boton para agregar una bolsa al contador actual
int boton_bolsaMenos = A1; //Boton para restar una bolsa al contador actual
int boton_camionSiguiente = A3; //Boton para pasar al siguiente camion
int boton_reset = A4; //Boton para resetear los contadores y camiones

void setup() {
  //Configuración de Entrada/Salida
  //Botones
  pinMode(boton_bolsaMas,INPUT);
  pinMode(boton_bolsaMenos,INPUT);
  pinMode(boton_camionSiguiente,INPUT);
  pinMode(boton_reset,INPUT);
  //Sensores
  pinMode(sensor_bolsa,INPUT);

    // Declaro numero de columnas y filas:
  lcd.begin(16, 2);

  //Escribo fila de encabezados
  lcd.setCursor(0, 0);
  lcd.print("CAM BOLSAS TOTAL");

  //Valores iniciales de los contadores
  reset();
}

void loop() {
  displayLCD();
  botones();
  sensarBolsa();
  delay(200);
}

//Inicializa los contadores
void reset(){
  contador_bolsaTotal = 0;
  contador_bolsaCamion = 0;
  numeroCamion=1;
}

//Comprueba si se presiono un boton y realiza la acción pertinente en cada caso
void botones(){
  if( digitalRead(boton_bolsaMas) == HIGH ){
    contador_bolsaCamion++;
  }
  if( digitalRead(boton_bolsaMenos) == HIGH ){
    if( contador_bolsaCamion > 0 )
      contador_bolsaCamion--;
  }
  if( digitalRead(boton_camionSiguiente) == HIGH ){
    contador_bolsaTotal += contador_bolsaCamion;
    contador_bolsaCamion = 0;
    numeroCamion++;
  }
  if( digitalRead(boton_reset) == HIGH ){
    reset();
  }
}


//Comprueba si paso una bolsa por el sensor y la agrega al contador
void sensarBolsa(){
  int pulso_actual;
  static int pulso_anterior = LOW;
  static unsigned long tiempo_inicio;
  unsigned long tiempo_fin;
  unsigned long tiempo_total;

  pulso_actual = digitalRead(sensor_bolsa);
  if(pulso_actual != pulso_anterior){
    if(pulso_anterior == LOW){
      tiempo_inicio=millis();
    }
    if(pulso_anterior == HIGH){
      tiempo_fin=millis();
      tiempo_total = tiempo_fin - tiempo_inicio;
      if( tiempo_total >= 2000 ){
        contador_bolsaCamion++; 
      }
    }
    pulso_anterior = pulso_actual;
  }
}

//Muestra valores actuales en el LCD
void displayLCD(){
  //Borro fila 1
  lcd.setCursor(0, 1);
  lcd.print("                ");
  
  //Nro de camion
  lcd.setCursor(1, 1);
  lcd.print(numeroCamion);

  //Bolsas en camion
  lcd.setCursor(5, 1);
  lcd.print(contador_bolsaCamion);
  
  //Bolsas en totalion
  lcd.setCursor(11, 1);
  lcd.print(contador_bolsaTotal);
}
