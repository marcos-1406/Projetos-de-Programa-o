/* **** -CONFIGURAÇÃO PARA PLACA DE SENSORES- **** */

//DECLARANDO O PINO PARA CADA SENSOR
int sensor0 = 51;
int sensor1 = 49;
int sensor2 = 47;
int sensor3 = 45;
int sensor4 = 43;
int sensor5 = 41;
int sensor6 = 39;
int sensor[7]; //VETOR PARA ARMAZENAR INFORMAÇÃO DA PLACA

/* **** ---------------------------------------------------------- **** */

/* **** -CONFIGURAÇÃO PARA A PONTE H- **** */

int IN1 = 24;//PINOS PARA CONTROLAR O SENTIDO DOS DOIS MOTORES
int IN2 = 26; 
int IN3 = 30;
int IN4 = 28;

int PWM_A = 6; //PINOS PARA CONTROLE DA VELOCIDADE
int PWM_B = 7;

int vel_A = 150; //VELOCIDADES MÁXIMO DOS MOTORES 
int vel_B = 255;

/* **** ---------------------------------------------------------- **** */

int Ki = 0;
int Kp = 35;
int Kd = 35;
int I = 0, P = 0, D = 0, PID = 0;
int velesq = 0, veldir = 0;
int erro = 0, erro_anterior = 0;

void setup() {
  /* **** DECLARAÇÃO DE CADA PINO COMO ENTRADA E SAÍDA **** */
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (PWM_A, OUTPUT);
  pinMode (PWM_B, OUTPUT);
  pinMode (sensor0, INPUT);
  pinMode (sensor1, INPUT);
  pinMode (sensor2, INPUT);
  pinMode (sensor3, INPUT);
  pinMode (sensor4, INPUT);
  pinMode (sensor5, INPUT);
  pinMode (sensor6, INPUT);
  delay(2000);
  Serial.begin(9600);
}

void ler_sensores(){
  sensor[0] = digitalRead (sensor0);
  sensor[1] = digitalRead (sensor1);
  sensor[2] = digitalRead (sensor2);
  sensor[3] = digitalRead (sensor3);
  sensor[4] = digitalRead (sensor4);
  sensor[5] = digitalRead (sensor5);
  sensor[6] = digitalRead (sensor6);
}

void curva90_direita(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(PWM_A, 0.10*vel_A);
  analogWrite(PWM_B, 0.80*vel_B);
  delay(850);
}

void curva90_esquerda(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(PWM_A, 0.90*vel_A);
  analogWrite(PWM_B, 0.05*vel_B);
  delay(850);
}

void parada(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

void calcula_erro(){
  if ((sensor[0]==1) && (sensor[1]==1) && (sensor[2]==1) && (sensor[3]==1) && (sensor[4]==1) && (sensor[5]==1) && (sensor[6]==1)){ erro = 0;}
  else if ((sensor[0]==1) && (sensor[1]==1) && (sensor[2]==1) && (sensor[3]==0) && (sensor[4]==0) && (sensor[5]==1) && (sensor[6]==1)){ erro = 1;}
  else if ((sensor[0]==1) && (sensor[1]==1) && (sensor[2]==0) && (sensor[3]==0) && (sensor[4]==1) && (sensor[5]==1) && (sensor[6]==1)){ erro = -1;}
  else if ((sensor[0]==1) && (sensor[1]==1) && (sensor[2]==1) && (sensor[3]==1) && (sensor[4]==0) && (sensor[5]==1) && (sensor[6]==1)){ erro = 1.5;}
  else if ((sensor[0]==1) && (sensor[1]==1) && (sensor[2]==0) && (sensor[3]==1) && (sensor[4]==1) && (sensor[5]==1) && (sensor[6]==1)){ erro = -1.5;}
  else if ((sensor[0]==1) && (sensor[1]==1) && (sensor[2]==1) && (sensor[3]==1) && (sensor[4]==0) && (sensor[5]==0) && (sensor[6]==1)){ erro = 1.75;}
  else if ((sensor[0]==1) && (sensor[1]==0) && (sensor[2]==0) && (sensor[3]==1) && (sensor[4]==1) && (sensor[5]==1) && (sensor[6]==1)){ erro = -1.75;}
  else if ((sensor[0]==1) && (sensor[1]==1) && (sensor[2]==1) && (sensor[3]==1) && (sensor[4]==1) && (sensor[5]==0) && (sensor[6]==1)){ erro = 2;}
  else if ((sensor[0]==1) && (sensor[1]==0) && (sensor[2]==1) && (sensor[3]==1) && (sensor[4]==1) && (sensor[5]==1) && (sensor[6]==1)){ erro = -2;}
}

void calcula_PID(){
  if (erro==0){
    I = 0;
  }
  P = erro;
  I = I + erro;

  if (I > 255){
    I = 255;
  }

  else if (I < -255){
    I = -255;
  }

  D = erro - erro_anterior;
  PID = (Kp*P) + (Ki*I) + (Kd*D);
  erro_anterior = erro;
}

void controle_motor(){
  if (PID >= 0){
    velesq = vel_B;
    veldir = vel_A - PID;
  }
  else{
    velesq = vel_B + PID;
    veldir = vel_A
    ;
  }
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  analogWrite (PWM_A, veldir);
  analogWrite (PWM_B, velesq);
  
}

void loop() {

  calcula_erro();
  calcula_PID();
  controle_motor();
  ler_sensores();
  
  /*LINHA RETA
  if(sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==0 && sensor[4]==1 && sensor[5]==1 && sensor[6]==1){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(PWM_A, vel_A*(0.8));
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(PWM_B, vel_B*(0.8));

  }

  //CURVA LEVE À DIREITA
  else if(sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==0 && sensor[4]==0 && sensor[5]==1 && sensor[6]==1){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(PWM_A, vel_A*(0.5)); 
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(PWM_B, vel_B*(0.8));
  }

  //CURVA LEVE À ESQUERDA
  else if(sensor[0]==1 && sensor[1]==1 && sensor[2]==0 && sensor[3]==0 && sensor[4]==1 && sensor[5]==1 && sensor[6]==1){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(PWM_A, vel_A*(0.8));
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(PWM_B, vel_B*(0.5));
  }
  //CURVA À DIREITA
  else if(sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==0 && sensor[5]==1 && sensor[6]==1){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(PWM_A, vel_A*(0.1)); // mudei de 0,2 para 0,1
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(PWM_B, vel_B*(0.8));
  }

  //CURVA À ESQUERDA
  else if(sensor[0]==1 && sensor[1]==1 && sensor[2]==0 && sensor[3]==1 && sensor[4]==1 && sensor[5]==1 && sensor[6]==1){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(PWM_A, vel_A*(0.8));
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(PWM_B, vel_B*(0.2));
  }

  //CURVA ACENTUADA À DIREITA
  else if(sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==0 && sensor[5]==0 && sensor[6]==1){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(PWM_A, vel_A*(0.1));
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(PWM_B, vel_B*(0.8));
  }

  //CURVA ACENTUADA À ESQUERDA
  else if(sensor[0]==1 && sensor[1]==0 && sensor[2]==0 && sensor[3]==1 && sensor[4]==1 && sensor[5]==1 && sensor[6]==1){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(PWM_A, vel_A*(0.8));
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(PWM_B, vel_B*(0.1));
  }

  //CURVA MUITO ACENTUADA À DIREITA
  else if(sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==1 && sensor[5]==0 && sensor[6]==1){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(PWM_A, vel_A*0);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(PWM_B, vel_B*0.8);
  }

  //CURVA MUITO ACENTUADA À ESQUERDA
  else if(sensor[0]==1 && sensor[1]==0 && sensor[2]==1 && sensor[3]==1 && sensor[4]==1 && sensor[5]==1 && sensor[6]==1){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(PWM_A, vel_A*0.8);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(PWM_B, vel_B*0);
  }

  //CURVA 90º À DIREITA
  else if(sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==1 && sensor[5]==1 && sensor[6]==0){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(PWM_A, vel_A*0);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(PWM_B, vel_B*1);
  }

  //CURVA 90º À ESQUERDA
  else if(sensor[0]==0 && sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==1 && sensor[5]==1 && sensor[6]==1){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(PWM_A, vel_A*1);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(PWM_B, vel_B*0);
  }


  // CARRO PARA
  else if((sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && sensor[3]==0 && sensor[4]==0 && sensor[5]==0 && sensor[6]==0) ||
        (sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==1 && sensor[5]==1 && sensor[6]==1)){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);

  }
*/
}
