

//Values
int soilMoisture = 0;
bool waterTankEmpty = false; 

int soilSensorDataPin = A0; 
int waterTankSensorDataPin = A1;

int soilSensorPowerPin = 6;
int waterPumpPowerPin = 7;
int waterTankLedPowerPin = 8;
int waterTankSensorPowerPin = 9;

//we'll use a digital pin to power the sensor. This will 
//prevent corrosion of the sensor as it sits in the soil. 

void setup() {
    Serial.begin(9600);   // open serial over USB

    pinMode(soilSensorDataPin, INPUT);
    pinMode(waterTankSensorDataPin, INPUT);

    pinMode(soilSensorPowerPin, OUTPUT);
    pinMode(waterPumpPowerPin, OUTPUT);
    pinMode(waterTankSensorPowerPin, OUTPUT);
    pinMode(waterTankLedPowerPin, OUTPUT);
  
    digitalWrite(soilSensorPowerPin, LOW);
    digitalWrite(waterPumpPowerPin, LOW);
    digitalWrite(waterTankSensorPowerPin, LOW);
    digitalWrite(waterTankLedPowerPin, LOW);
}

void loop() {
    readSoilMoisture();
    readTankWaterLevel();

    Serial.print("water: ");
    Serial.println(!waterTankEmpty);
    Serial.print("soil moisture: "); 
    Serial.println(soilMoisture); 

    if(waterTankEmpty) {
        digitalWrite(waterTankLedPowerPin, HIGH);
    } else {
        digitalWrite(waterTankLedPowerPin, LOW);
    }

    if(soilMoisture < 550 && !waterTankEmpty){
      analogWrite(waterPumpPowerPin, 1024);
      Serial.println("Pump: on");
    } else {
        digitalWrite(waterPumpPowerPin, LOW);
        Serial.println("Pump: off");
    }
   
    //This 1 second timefrme is used so you can test the sensor and see it change in real-time.
    //For in-plant applications, you will want to take readings much less frequently.
    long dl = 3600000;
    delay(dl);//take a reading every second
}

//This is a function used to get the soil moisture content
int readSoilMoisture() {
    digitalWrite(soilSensorPowerPin, HIGH);
    delay(10); //wait 10 milliseconds 
    soilMoisture = analogRead(soilSensorDataPin); //Read the SIG value form sensor 
    digitalWrite(soilSensorPowerPin, LOW);
    return soilMoisture;
}

//This is a function used to get the soil moisture content
bool readTankWaterLevel() {
    digitalWrite(waterTankSensorPowerPin, HIGH);
    delay(10); //wait 10 milliseconds 
    int val = analogRead(waterTankSensorDataPin); //Read the SIG value form sensor 
    if(val < 1000){
        waterTankEmpty = false;
    } else {
        waterTankEmpty = true;
    }
    digitalWrite(waterTankSensorPowerPin, LOW);
    return waterTankEmpty;
}
