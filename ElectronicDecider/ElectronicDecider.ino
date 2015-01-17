// Electronic decider
const int buttonPin = 2;
const int yesPin = 3;
const int noPin = 4;

int buttonState = 0;
int randomNumber = 0;

void setup(){
  Serial.begin(9600);
  
  randomSeed(analogRead(0)); // try and get a "random" seed (read an unconnected pin)
  
  pinMode(yesPin, OUTPUT); // LED = output
  pinMode(noPin, OUTPUT);
  
  pinMode(buttonPin, INPUT); // button = input
}

void loop(){
  buttonState = digitalRead(buttonPin); // if current is applied, then the button is being pushed)
  
  Serial.println(buttonState);
  
  if(buttonState == HIGH){
    randomNumber = random(2); // either 0 or 1
    
    if(randomNumber == 0){
      digitalWrite(yesPin, HIGH); // power the green LED
      Serial.println("Yes!");
      delay(1000); // let it up for a second
    }else{
      digitalWrite(noPin, HIGH); // power the red LED
      Serial.println("No!");
     delay(1000); // let it up for a second
    }
  }
  // ensure that both LEDs are off
  digitalWrite(yesPin, LOW);
  digitalWrite(noPin, LOW);
  
  delay(50); // delay for stability
}
