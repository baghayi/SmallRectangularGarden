const int floatLedA0 = 2; // green led
const int wetLedA0 = 3; // yellow led
const int dryLedA0 = 4; // red led

const int floatLedA1 = 5; // green led
const int wetLedA1 = 6; // yellow led
const int dryLedA1 = 7; // red led

void setup(){
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);

    pinMode(floatLedA0, OUTPUT);
    pinMode(wetLedA0, OUTPUT);
    pinMode(dryLedA0, OUTPUT);

    pinMode(floatLedA1, OUTPUT);
    pinMode(wetLedA1, OUTPUT);
    pinMode(dryLedA1, OUTPUT);
    
    Serial.begin(9600);
}

#define DRY 0
#define WET 1
#define FLOAT 2
int getSoilStatus(int sensorPin) {
    int sensorValue = analogRead(sensorPin);
    sensorValue = map(sensorValue, 0, 1023, 2, 0);
    switch(sensorValue){
        case 0:
        return DRY;
        break;

        case 1: 
        return WET;
        break;

        case 2:
        return FLOAT;
        break;
    }
}

void loop(){
    int a0SoilSensorValue = getSoilStatus(A0);
    switch(a0SoilSensorValue){
        case DRY:
        digitalWrite(dryLedA0, HIGH);
        digitalWrite(wetLedA0, LOW);
        digitalWrite(floatLedA0, LOW);
        break;

        case WET:
        digitalWrite(dryLedA0, LOW);
        digitalWrite(wetLedA0, HIGH);
        digitalWrite(floatLedA0, LOW);
        break;

        case FLOAT:
        digitalWrite(dryLedA0, LOW);
        digitalWrite(wetLedA0, LOW);
        digitalWrite(floatLedA0, HIGH);
        break;
    }
    Serial.print("Sensor A0: ");
    Serial.print(a0SoilSensorValue);

    int a1SoilSensorValue = getSoilStatus(A1);
    switch(a1SoilSensorValue){
        case DRY:
        digitalWrite(dryLedA1, HIGH);
        digitalWrite(wetLedA1, LOW);
        digitalWrite(floatLedA1, LOW);
        break;

        case WET:
        digitalWrite(dryLedA1, LOW);
        digitalWrite(wetLedA1, HIGH);
        digitalWrite(floatLedA1, LOW);
        break;

        case FLOAT:
        digitalWrite(dryLedA1, LOW);
        digitalWrite(wetLedA1, LOW);
        digitalWrite(floatLedA1, HIGH);
        break;
    }
    Serial.print(", Sensor A1: ");
    Serial.println(a1SoilSensorValue);

    delay(300);
}
