/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/
int sensorValue = 0;
int infraredPin = 7;
int laserPin = 12;
bool loadedArrow = false;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(laserPin, OUTPUT);
  pinMode(infraredPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  delay(100);        // delay in between reads for stability
  if(sensorValue == 0) {
    if(loadedArrow == true){
      fireInf(2);
      loadedArrow == false;
    }else{
      fireInf(0);
    }
  }else if(sensorValue > 30) {
    fireInf(1);
    loadedArrow = true;
  }
}

void fireInf(int myState) {
  if(myState == 0) {
    digitalWrite(infraredPin, LOW);
    digitalWrite(laserPin, LOW);
  }else if (myState == 1){
    Serial.println("arrow loaded");
    digitalWrite(laserPin, HIGH);
    delay(200);
    digitalWrite(laserPin, LOW);
    Serial.println("laser locked");
  }else if (myState == 2){
    digitalWrite(laserPin, LOW);
    loadedArrow = false;
    Serial.println("arrow fired");
    digitalWrite(infraredPin, HIGH);
    
    delay(1000);
    digitalWrite(infraredPin, LOW);
    
  }
  
  
}

