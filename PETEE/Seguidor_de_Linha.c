int sensor0 = 33;
int sensor1 = 35;
int sensor2 = 37;
int sensor3 = 39;
int sensor4 = 41;
int sensor5 = 43;
int sensor6 = 45;
int sensor[7];

int IN1 = 22;
int IN2 = 24;
int IN3 = 26;
int IN4 = 28;

int PWM_A = 2;
int PWM_B = 3;

int Speed_A = 255;
int Speed_B = 255;


void setup(){
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
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(PWM_A, Speed_A*0.9);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(PWM_B, Speed_B*0.9);
    }

    //********** CURVA LEVE PARA A DIREITA *************
    else if(sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 1 && sensor[3] == 0 && sensor[4] == 0 && sensor[5] == 1 && sensor[6] == 1){
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(PWM_A, Speed_A*0.9);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(PWM_B, Speed_B*0.5);
    }

    //********** CURVA LEVE PARA A ESQUERDA *************
    else if(sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 0 && sensor[3] == 0 && sensor[4] == 1 && sensor[5] == 1 && sensor[6] == 1){
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(PWM_A, Speed_A*0.5);
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
    }

    //********** CURVA ACENTUADA PARA A ESQYERDA *************
    else if(sensor[0] == 1 && sensor[1] == 1 && sensor[2] == 0 && sensor[3] == 1 && sensor[4] == 1 && sensor[5] == 1 && sensor[6] == 1){
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(PWM_A, Speed_A*0.2);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(PWM_B, Speed_B*0.9);
    }
}