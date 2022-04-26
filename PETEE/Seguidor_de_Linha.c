/* **** -CONFIGURAÇÃO PARA PLACA DE SENSORES- **** */

int sensor0 = 33; //DECLARANDO O PINO PARA CADA SENSOR
int sensor1 = 35;
int sensor2 = 37;
int sensor3 = 39;
int sensor4 = 41;
int sensor5 = 43;
int sensor6 = 45;
int sensor[7]; //VETOR PARA ARMAZENAR INFORMAÇÃO DA PLACA

/* **** ---------------------------------------------------------- **** */

/* **** -CONFIGURAÇÃO PARA A PONTE H- **** */

int IN1 = 22; //PINOS PARA CONTROLAR O SENTIDO DOS DOIS MOTORES
int IN2 = 24;
int IN3 = 26;
int IN4 = 28;

int PWM_A = 2; //PINOS PARA CONTROLE DA VELOCIDADE
int PWM_B = 3;

int Speed_A = 255; //VELOCIDADES MÁXIMO DOS MOTORES 
int Speed_B = 255;

/* **** ---------------------------------------------------------- **** */

bool FaixaDePedestre = false;


void setup(){
    /* **** DECLARAÇÃO DE CADA PINO COMO ENTRADA E SAÍDA **** */
    pinMode(sensor0, INPUT); 
    pinMode(sensor1, INPUT);
    pinMode(sensor2, INPUT);
    pinMode(sensor3, INPUT);
    pinMode(sensor4, INPUT);
    pinMode(sensor5, INPUT);
    pinMode(sensor6, INPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(PWM_A, OUTPUT);
    pinMode(PWM_B, OUTPUT);
}

void loop(){
    sensor[0] = digitalRead(sensor0);
    sensor[1] = digitalRead(sensor1);
    sensor[2] = digitalRead(sensor2);
    sensor[3] = digitalRead(sensor3);
    sensor[4] = digitalRead(sensor4);
    sensor[5] = digitalRead(sensor5);
    sensor[6] = digitalRead(sensor6);
    
    //********** LINHA RETA *************
    if(sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 1 && sensor[3] == 0 && sensor[4] == 1 && sensor[5] == 1 && sensor[6] == 1){
        if(FaixaDePedestre){
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
            analogWrite(PWM_A, Speed_A*0.5);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
            analogWrite(PWM_B, Speed_B*0.5);
            delay(1000);
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, HIGH);
            delay(5500);
        }
        else{
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
            analogWrite(PWM_A, Speed_A*0.9);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
            analogWrite(PWM_B, Speed_B*0.9);
        }
    }

    //********** CURVA PARA A DIREITA *************
    else if(sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 1 && sensor[3] == 0 && sensor[4] == 0 && sensor[5] == 1 && sensor[6] == 1){
        delay(1000)
        if(sensor[3] == 0 && sensor[4] == 0 && sensor[5] == 0){
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
            analogWrite(PWM_A, Speed_A*0.5);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
            analogWrite(PWM_B, Speed_B*0);
        }
        else{
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
            analogWrite(PWM_A, Speed_A*0.9);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
            analogWrite(PWM_B, Speed_B*0.5);
        }
    }

    //********** CURVA PARA A ESQUERDA *************
    else if(sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 0 && sensor[3] == 0 && sensor[4] == 1 && sensor[5] == 1 && sensor[6] == 1){
        delay(1000);
        if(sensor[1] == 0 && sensor[2] == 0 && sensor[3] == 0){
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
            analogWrite(PWM_A, Speed_A*0);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
            analogWrite(PWM_B, Speed_B*0.9);
        }
        
        else{
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
            analogWrite(PWM_A, Speed_A*0.5);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
            analogWrite(PWM_B, Speed_B*0.9);
        }
    }

    //********** CURVA DE 90° PARA A DIREITA *************
    else if(sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 1 && sensor[3] == 0 && sensor[4] == 1 && sensor[5] == 1 && sensor[6] == 0){
        delay(1000)
        
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(PWM_A, Speed_A*0.5);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(PWM_B, Speed_B*0);
        
    }

    //********** CURVA DE 90° PARA A ESQUERDA *************
    else if(sensor[0] == 0 && sensor[1] == 1 && sensor[2] == 1 && sensor[3] == 0 && sensor[4] == 1 && sensor[5] == 1 && sensor[6] == 1){
        delay(1000);
        
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(PWM_A, Speed_A*0);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(PWM_B, Speed_B*0.9);
        
    }

    //********** CURVA ACENTUADA PARA A DIREITA *************
    else if(sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 1 && sensor[3] == 1 && sensor[4] == 0 && sensor[5] == 1 && sensor[6] == 1){
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(PWM_A, Speed_A*0.9);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(PWM_B, Speed_B*0.2);
        delay(1000);
    }

    //********** CURVA ACENTUADA PARA A ESQUERDA *************
    else if(sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 0 && sensor[3] == 1 && sensor[4] == 1 && sensor[5] == 1 && sensor[6] == 1){
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(PWM_A, Speed_A*0.2);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(PWM_B, Speed_B*0.9);
        delay(1000);
    }

    //********** FAIXA DE PEDESTRE **********
    else if(sensor[0] == 0 && sensor[1] == 0 && sensor[2] == 0 && sensor[3] == 1 && sensor[4] == 0 && sensor[5] == 0 && sensor[6] == 0){
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(PWM_A, Speed_A*0.9);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(PWM_B, Speed_B*0.9);
        FaixaDePedestre = true;
    }

    //********** DUAS CURVAS DE 90º POSSÍVEIS **********
    else if(sensor[0] == 0 && sensor[1] == 1 && sensor[2] == 1 && sensor[3] == 0 && sensor[4] == 1 && sensor[5] == 1 && sensor[6] == 0){
        
        //Decidir qual lado o carrinho vai, pois isso será indicado para os capitães em uma reunião
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW;
        analogWrite(PWM_A, Speed_A*0.2);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        analogWrite(PWM_B, Speed_B*0.9);
        delay(1000);
    }

    /*
    //********** DESAFIO DA ROTATÓRIA **********
    else if((sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 0 && sensor[3] == 0 && sensor[4] == 1 && sensor[5] == 1 && sensor[6] == 1) || 
            (sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 1 && sensor[3] == 0 && sensor[4] == 0 && sensor[5] == 1 && sensor[6] == 1)){

    }
    */

}