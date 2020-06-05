int relayPin = 7;   //relay pin is digital pin 7
int switchPin = A0;  // left button that controls the pulsing relay funtion , pin analog 0
int statusPin = 2;  // a red led that lights when the relay is disconnecting the circuit
int holdPin = A2;  // right button that controls the disconnect relay function
int potPin = A1;  // potentiometer pin that will read the values from the potentiometer itself
int potPinTwo = A3;  // potentiometer pin that will read the values from the potentiometer itself
int uniDelay = 100;  // a universal delay... probably will never get used
int potReading;  // global potentiometer reading variable that stores the potentiometer value output after it's been changed by math
int potReadingTwo;  // global potentiometer reading variable that stores the potentiometer value output after it's been changed by math
int switchPinReading; // switch pin reading value
int holdPinReading; // hold pin reading value

void setup() { //this loop only runs once on boot
Serial.begin(9600); //begin the serial port for diagnostics 
pinMode(relayPin, OUTPUT); //tell the relaypin to output a value
pinMode(switchPin, INPUT);  //tell the switchpin to expect an input value
pinMode(potPin, INPUT);  // tell the potpin to expect an input value
pinMode(potPinTwo, INPUT);  // tell the potpin to expect an input value
pinMode(holdPin, INPUT);  // tell the holdpin to expect an input value
pinMode(statusPin, OUTPUT); // tell the statuspin to output a value
};

void loop() { // constantly running loop after void setup
  digitalWrite(statusPin, LOW); // keep status pin off because some loops dont turn it off, so we'll leave it up to the main loop to ensure its not illuminated
  
  if (holdPinReading >= 300){ // if the holdpinreading is pressed.... 
    hold(); // ....call the code in this loop
    }else{
    digitalWrite(relayPin, HIGH);
  };
  
  switchPinReading = analogRead(switchPin);
  holdPinReading = analogRead(holdPin);

  potReading = analogRead(potPin);
  potReading = potReading / 3 + 50;

  potReadingTwo = analogRead(potPinTwo);
  potReadingTwo = potReadingTwo / 3 + 50;
  
  if (switchPinReading >= 200){
    active();
  }else{
    Serial.println(switchPinReading);
    Serial.println(holdPinReading);
  };
  
};

void active(){
// Serial.println(switchPinReading);
// Serial.println(holdPinReading);
  digitalWrite(statusPin, HIGH);  // red led will illuminate
  digitalWrite(relayPin, LOW); // open the ignition circuit!
  
//  Serial.println("");
//  Serial.println(switchPinReading);
//  Serial.println("");
  
  delay(potReadingTwo);
  
  digitalWrite(relayPin, HIGH); // close the ignition circuit, followed by a boom!
  digitalWrite(statusPin, LOW);
  
  delay(potReading); // delay for the engine to rev back up to a proper rpm. adjusted/variated by the potentiometer.
  
//  Serial.println("");
//  Serial.println(potReading);
//  Serial.println(potReadingTwo);
//  Serial.println("");
 };

 void hold(){
   digitalWrite(statusPin, HIGH); // illuminate the red led
   digitalWrite(relayPin, LOW); // open the ignition circuit, expect a boom upon button release!
   //Serial.print("reeee"); // print to serial
 };
