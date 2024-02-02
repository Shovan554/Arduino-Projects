#include <IRremote.h>
#include <Servo.h>

Servo myservo;
int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11

IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

void setup() {
  Serial.begin(9600);
  myservo.attach(9);         // Attaches the servo on pin 9 to the servo object
  irrecv.enableIRIn();       // Start the receiver
  Serial.println("IR Receiver and Servo Test");
}

void loop() {
  if (irrecv.decode(&results)) {
    switch(results.value) {
      case 0xFF906F: // Replace with the code for your remote's "UP" button
        myservo.write(90); // Turn servo to 90 degrees
        break;
      case 0xFFE01F: // Replace with the code for your remote's "DOWN" button
        myservo.write(0);   // Turn servo back to 0 degrees
        break;
    }
    irrecv.resume(); // Receive the next value
  }
}
