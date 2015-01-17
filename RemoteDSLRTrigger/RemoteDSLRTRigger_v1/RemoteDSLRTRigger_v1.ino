// Remote DSLR Trigger

// Libraries
#include <multiCameraIrControl.h> // Camera IR control

// Circuit-specifics
const int SENDING_LED_PIN = 13;

// IR Control
Pentax K20D(9); // IR Led on PIN 9

void setup(){   
  pinMode(SENDING_LED_PIN, OUTPUT); // LED = output
}

void loop(){
      digitalWrite(SENDING_LED_PIN, HIGH);
      delay(250);
      digitalWrite(SENDING_LED_PIN, LOW);
      
      K20D.shutterNow();
 }      
  
  delay(60000); // 1 min delay between shots
}
