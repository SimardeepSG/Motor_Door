//Keypad Control
// https://www.youtube.com/watch?v=vl1-R6NsejM
//Servo Control
//https://www.makerguides.com/how-to-control-a-360-degree-servo-motor-with-arduino/
//https://grabcad.com/library/servo-spt5435lv-35kg-180-25t-1
//When connecting your servo to an external 6V power supply, and it runs continuously, this issue is typically due to the lack of a common ground between the Arduino and the external power supply. Servos require the control signal (PWM) and the power supply to share the same ground reference; otherwise, the PWM signal is not correctly interpreted by the servo.

#include <Keypad.h>
#include <Servo.h>

const int arraySize = 4;  // Define the maximum size of the array
int myArray[arraySize];    // Create a blank array
int arrayIndex = 0;        // Counter to track the current index
int arrayLength = arraySize;
const char presetCode[] = "1234"; 

const byte ROWS = 4;
const byte COLS = 3;
Servo myServo;

char hexaKeys[ROWS][COLS] ={
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'}, 
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // open the serial port at 9600 bps:
  myServo.attach(9); // attach the servo to our servo object
  // myservo.write(90); // stop the motor

}

void loop() {
  // put your main code here, to run repeatedly:
  char customKey = customKeypad.getKey();
  Serial.print(customKey);



  if (customKey) {
    if (customKey == '#') {
      if(checkCode()) {
        Serial.println("");
        Serial.println("Acess Granted");
        myServo.write(0);   // Rotate the servo at full speed in one direction
        delay(2000);        // Rotate for 2 seconds
        myServo.write(90);  // Stop the servo (90 is the neutral position)
        delay(2000);        // Rotate for 2 seconds
        myServo.write(180); //Rotate the servo back to original position
        delay(2000);        // Rotate for 2 seconds
        myServo.write(90);  // Stop the servo (90 is the neutral position)

      } else {
        Serial.println("Acess Denied");
      }
      clearArray();  // Clear the input array after checking
    } else {
      //this is the outter else of the if customkey == which adds to the array
      
        myArray[arrayIndex] = customKey;
        arrayIndex++;
      
    }
  }
}

bool checkCode() {
  if (arrayIndex != arrayLength) {
    return false;
  }
  for (int i = 0; i < arrayLength; i++) {
    if (myArray[i] != presetCode[i]) {
      return false;
    } 
  }
  Serial.println(arrayIndex);
  return true;
}

void clearArray() {
  for (int i = 0; i < arraySize; i++) {
    myArray[i] = '\0'; // apparently this clears the array
  }
  arrayIndex = 0; // resetting the array index
}
