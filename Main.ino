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
        delay(200);
    }

    return LEDsPowerSwitchState;
}

void loop(){
    LEDsPowerSwitchState = getLEDsPowerSwitchState();
    if(LEDsPowerSwitchState == LOW){
        digitalWrite(sensorA0Leds.dry, LOW);
        digitalWrite(sensorA0Leds.wet, LOW);
        digitalWrite(sensorA0Leds.flood, LOW);

        digitalWrite(sensorA1Leds.dry, LOW);
        digitalWrite(sensorA1Leds.wet, LOW);
        digitalWrite(sensorA1Leds.flood, LOW);

        delay(20);
        return;
    }

    int a0SoilSensorValue = getSoilStatus(A0);
    switch(a0SoilSensorValue){
        case DRY:
        digitalWrite(sensorA0Leds.dry, HIGH);
        digitalWrite(sensorA0Leds.wet, LOW);
        digitalWrite(sensorA0Leds.flood, LOW);
        break;

        case WET:
        digitalWrite(sensorA0Leds.dry, LOW);
        digitalWrite(sensorA0Leds.wet, HIGH);
        digitalWrite(sensorA0Leds.flood, LOW);
        break;

        case FLOOD:
        digitalWrite(sensorA0Leds.dry, LOW);
        digitalWrite(sensorA0Leds.wet, LOW);
        digitalWrite(sensorA0Leds.flood, HIGH);
        break;
    }
    Serial.print("Sensor A0: ");
    Serial.print(a0SoilSensorValue);
    Serial.print(" | ");

    int a1SoilSensorValue = getSoilStatus(A1);
    switch(a1SoilSensorValue){
        case DRY:
        digitalWrite(sensorA1Leds.dry, HIGH);
        digitalWrite(sensorA1Leds.wet, LOW);
        digitalWrite(sensorA1Leds.flood, LOW);
        break;

        case WET:
        digitalWrite(sensorA1Leds.dry, LOW);
        digitalWrite(sensorA1Leds.wet, HIGH);
        digitalWrite(sensorA1Leds.flood, LOW);
        break;

        case FLOOD:
        digitalWrite(sensorA1Leds.dry, LOW);
        digitalWrite(sensorA1Leds.wet, LOW);
        digitalWrite(sensorA1Leds.flood, HIGH);
        break;
    }
    Serial.print("Sensor A1: ");
    Serial.println(a1SoilSensorValue);

    // if wet, then water it.
    if(a0SoilSensorValue == WET || a1SoilSensorValue == WET){
        digitalWrite(waterPompPin, HIGH);
    }else{
        digitalWrite(waterPompPin, LOW);
    }

    delay(300);
}
