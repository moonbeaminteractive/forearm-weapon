/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

#include <IRLibSendBase.h>    // First include the send base
//Now include only the protocols you wish to actually use.
//The lowest numbered protocol should be first but remainder 
//can be any order.
#include <IRLib_P01_NEC.h>    
#include <IRLib_P02_Sony.h>   
#include <IRLibCombo.h>     // After all protocols, include this
// All of the above automatically creates a universal sending
// class called "IRsend" containing only the protocols you want.
// Now declare an instance of that sender.
IRsend mySender;

int sensorValue = 0;
int infraredPin = 7;
int laserPin = 12;
bool loadedArrow = false;
int arrowNum = 7;
int arrowTotal = 10;
int rechargeNum = 0;
int rechargeTotal = 10;
byte[] buf = null;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(laserPin, OUTPUT);
  pinMode(infraredPin, OUTPUT);
  //Initiate the array
  buf = new byte[20];
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
      //fireInf(2);
      mySender.send(SONY,0xa8bca, 20);//Send a IR light
      Serial.println(F("Sent signal."));
      loadedArrow == false;
      arrowNum--;    //The number of arrow decreases by one
    }else{
      fireInf(0);
    }
  }else if(sensorValue > 30) {
    fireInf(1);
    loadedArrow = true;
  }
  //Read array from Serial port
  
  //Increase the rechargeNum based on incoming array from Vest
  if(buf[2]==0){
      if(rechargeNum!=rechargeTotal){
          rechargeNum++;
        }
      else{
          rechargeNum=0;
        }
    }
   else{
      if(buf==){
          rechargeNum+=2;
        }
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
  }
//  else if (myState == 2){
//    digitalWrite(laserPin, LOW);
//    loadedArrow = false;
//    Serial.println("arrow fired");
//    digitalWrite(infraredPin, HIGH);
//    
//    delay(1000);
//    digitalWrite(infraredPin, LOW);
//    
//  }
  
  
}

