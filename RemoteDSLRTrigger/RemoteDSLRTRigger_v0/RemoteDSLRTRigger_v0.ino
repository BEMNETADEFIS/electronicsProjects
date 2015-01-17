// Remote DSLR Trigger

// Libraries
#include <multiCameraIrControl.h> // Camera IR control

// Circuit-specifics
const int BUTTON_PIN = 2;
const int SENDING_LED_PIN = 13;
int buttonState = 0;

// IR Control
Pentax K20D(9); // IR Led on PIN 9

void setup(){
  Serial.begin(9600);
    
  pinMode(SENDING_LED_PIN, OUTPUT); // LED = output
  pinMode(BUTTON_PIN, INPUT); // button = input
}

void loop(){
  buttonState = digitalRead(BUTTON_PIN); // if current is applied, then the button is being pushed)
  
  if(buttonState == HIGH){
      Serial.println("Button pressed!");
      digitalWrite(SENDING_LED_PIN, HIGH);
      delay(250);
      digitalWrite(SENDING_LED_PIN, LOW);
      Serial.println("Sending signal to toggle focusl!");
      K20D.toggleFocus();
      Serial.println("Waiting");
      delay(5000);
      Serial.println("Sending signal to shutter now!");
      K20D.shutterNow();
      
      digitalWrite(SENDING_LED_PIN, HIGH);
      delay(1000); // let it up for a second
      digitalWrite(SENDING_LED_PIN, LOW);
      Serial.println("Signal Sent!");
 }      
  
  delay(60000); // 1 min delay between shots
}
