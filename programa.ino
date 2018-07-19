//Contadores
int contador_bolsaActual; //Bolsas de la tanda actual del camion
int contador_bolsaCamion; //Bolsas totales del camion
int contador_bolsaTotal; //Bolsas totales cargadas en todos los camiones
int numeroCamion; //Indica el camion actual

//Sensores
int sensor_bolsa = A7; //Pin del sensor que detecta las bolsas

//Botones
int boton_bolsaMas = A0; //Boton para agregar una bolsa al contador actual
int boton_bolsaMenos = A1; //Boton para restar una bolsa al contador actual
int boton_totalizador = A2; //Boton para pasar las bolsas del contador actual al contador del camion
int boton_camionSiguiente = A3; //Boton para pasar al siguiente camion
int boton_reset = A4; //Boton para resetear los contadores y camiones

void setup() {
  //Configuración de Entrada/Salida
  //Botones
  pinMode(boton_bolsaMas,INPUT);
  pinMode(boton_bolsaMenos,INPUT);
  pinMode(boton_totalizador,INPUT);
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
  contador_bolsaActual = 0;
  numeroCamion=1;
}

//Comprueba si se presiono un boton y realiza la acción pertinente en cada caso
void botones(){
  if( digitalRead(boton_bolsaMas) == HIGH ){
    contador_bolsaActual++;
  }
  if( digitalRead(boton_bolsaMenos) == HIGH ){
    if( contador_bolsaActual > 0 )
      contador_bolsaActual--;
  }
  if( digitalRead(boton_totalizador) == HIGH ){
    contador_bolsaCamion += contador_bolsaActual;
    contador_bolsaActual = 0;
  }
  if( digitalRead(boton_camionSiguiente) == HIGH ){
    contador_bolsaTotal += contador_bolsaCamion + contador_bolsaActual;
    contador_bolsaCamion = 0;
    contador_bolsaActual = 0;
    numeroCamion++;
  }
  if( digitalRead(boton_reset) == HIGH ){
    reset();
  }
}

//Comprueba si paso una bolsa por el sensor y la agrega al contador
void sensarBolsa(){
  static int pulso_anterior = 1;
  static int 
  int pulso actual;
}

