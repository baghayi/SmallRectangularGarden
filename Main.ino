struct SensorLEDPins {
    int flood; // green led
    int wet; // yellow led
    int dry; // red led
};

SensorLEDPins sensorA0Leds = {2, 3, 4};

SensorLEDPins sensorA1Leds = {5, 6, 7};

const int LEDsPowerSwitchPin = 8;
boolean LEDsPowerSwitchState = LOW;

const int waterPompPin = 9;

void setup(){
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);

    pinMode(sensorA0Leds.flood, OUTPUT);
    pinMode(sensorA0Leds.wet, OUTPUT);
    pinMode(sensorA0Leds.dry, OUTPUT);

    pinMode(sensorA1Leds.flood, OUTPUT);
    pinMode(sensorA1Leds.wet, OUTPUT);
    pinMode(sensorA1Leds.dry, OUTPUT);

    pinMode(LEDsPowerSwitchPin, INPUT);
    digitalWrite(LEDsPowerSwitchPin, LOW);

    pinMode(waterPompPin, OUTPUT);
    
    Serial.begin(9600);
}

#define DRY 0
#define WET 1
#define FLOOD 2
int getSoilStatus(int sensorPin) {
    int sensorValue = analogRead(sensorPin);
    Serial.print("Row Value: ");
    Serial.print(sensorValue);
    Serial.print(" = ");

    sensorValue = constrain(sensorValue, 0, 861);
    sensorValue = map(sensorValue, 0, 861, 2, 0);
    switch(sensorValue){
        case 0:
        return DRY;
        break;

        case 1: 
        return WET;
        break;

        case 2:
        return FLOOD;
        break;
    }
}

boolean getLEDsPowerSwitchState(){
    int state = digitalRead(LEDsPowerSwitchPin);

    if(state == HIGH){
        LEDsPowerSwitchState = !LEDsPowerSwitchState;
        delay(150);
    }

    return LEDsPowerSwitchState;
}

void turnOnAppropriateSensorLED(int sensorState, SensorLEDPins ledPins, int powerSwitchState){

    if(powerSwitchState == LOW){
        digitalWrite(ledPins.dry, LOW);
        digitalWrite(ledPins.wet, LOW);
        digitalWrite(ledPins.flood, LOW);

        return;
    }

    switch(sensorState){
        case DRY:
        digitalWrite(ledPins.dry, HIGH);
        digitalWrite(ledPins.wet, LOW);
        digitalWrite(ledPins.flood, LOW);
        break;

        case WET:
        digitalWrite(ledPins.dry, LOW);
        digitalWrite(ledPins.wet, HIGH);
        digitalWrite(ledPins.flood, LOW);
        break;

        case FLOOD:
        digitalWrite(ledPins.dry, LOW);
        digitalWrite(ledPins.wet, LOW);
        digitalWrite(ledPins.flood, HIGH);
        break;
    }
}

void managerWaterPomp(int sensorValues[]){
    boolean startWaterPomp = false;

    for(int i=0; i < sizeof(sensorValues); i++){
        if(sensorValues[i] <= WET)
            startWaterPomp = true;
    }

    if(startWaterPomp)
        digitalWrite(waterPompPin, HIGH);
    else
        digitalWrite(waterPompPin, LOW);
}

void loop(){
    int ledsPowerSwitchState = getLEDsPowerSwitchState();

    int a0SoilSensorValue = getSoilStatus(A0);
    turnOnAppropriateSensorLED(a0SoilSensorValue, sensorA0Leds, ledsPowerSwitchState);
    Serial.print("Sensor A0: ");
    Serial.print(a0SoilSensorValue);
    Serial.print(" | ");

    int a1SoilSensorValue = getSoilStatus(A1);
    turnOnAppropriateSensorLED(a1SoilSensorValue, sensorA1Leds, ledsPowerSwitchState);
    Serial.print("Sensor A1: ");
    Serial.println(a1SoilSensorValue);

    int soilSensorValues[2] = {a0SoilSensorValue, a1SoilSensorValue};
    managerWaterPomp(soilSensorValues);

    delay(20);
}
