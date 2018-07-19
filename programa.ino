//Contadores
int contador_bolsaCamion; //Bolsas totales cargadas en el camion
int contador_bolsaTotal; //Bolsas totales cargadas en todos los camiones
int numeroCamion; //Indica el camion actual

//Sensores
int sensor_bolsa = A7; //Pin del sensor que detecta las bolsas

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

  //Valores iniciales de los contadores
  reset();
}

void loop() {
  // put your main code here, to run repeatedly:

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
  static int pulso_anterior = HIGH;
  static int tiempo_inicio;
  int pulso_actual;
  int tiempo_fin;
  int tiempo_total;

  pulso_actual = digitalRead(sensor_bolsa);
  if(pulso_actual != pulso_anterior){
    if(pulso_anterior = HIGH){
      tiempo_inicio=millis();
    }else{
      tiempo_fin=millis();
      tiempo_total = tiempo_fin - tiempo_inicio;
      if( tiempo_total > 2000 ){
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
  lcd.setCursor(0, 1);
  lcd.print(numeroCamion);

  //Bolsas en curso
  lcd.setCursor(2, 1);
  lcd.print(contador_bolsaActual);

  //Bolsas en camion
  lcd.setCursor(6, 1);
  lcd.print(contador_bolsaCamion);
  
  //Bolsas en totalion
  lcd.setCursor(11, 1);
  lcd.print(contador_bolsaTotal);
}
