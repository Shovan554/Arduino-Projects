#include "SR04.h"
#include <LiquidCrystal.h>
#include "pitches.h"

#define TRIG_PIN 2
#define ECHO_PIN 3
#define BUZZER_PIN 6
#define RED_LED_PIN 4
#define BLUE_LED_PIN 5

// Initialize the ultrasonic sensor
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
long currentDistance;
long lastDistance = 0;

// Initialize the LCD and set the pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Melody notes and duration
int melody[] = {
  NOTE_C5
};
int noteDuration = 500;  // 500 milliseconds

void setup() {
    // Start serial communication
    Serial.begin(9600);

    // Set up the LCD's number of columns and rows
    lcd.begin(16, 2);

    // Print a message to the LCD
    lcd.print("System working");

    // Initialize LED pins
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);

    // Short delay before starting the loop
    delay(1000);
}

void loop() {
    // Get the distance from the ultrasonic sensor
    currentDistance = sr04.Distance();
    Serial.print(currentDistance);
    Serial.println(" cm");

    // Check if the distance is less than 100 cm and less than the last distance (intruder moving closer)
    if (currentDistance < 200 && currentDistance < lastDistance) {
        // If distance is less than 100 cm, display "Intruder" on the LCD
        lcd.clear(); // Clear previous message
        lcd.setCursor(0, 0); // Set cursor to beginning of first line
        lcd.print("Intruder!");

        // Optionally, you can display the distance too
        lcd.setCursor(0, 1); // Set cursor to beginning of second line
        lcd.print(currentDistance);
        lcd.print(" cm");

        // Play a melody on the buzzer
        for (int thisNote = 0; thisNote < 6; thisNote++) {
            tone(BUZZER_PIN, melody[thisNote], noteDuration);
            delay(noteDuration * 1.3); // Duration + pause between notes
        }

        // Blink the LEDs randomly
        for (int i = 0; i < 10; i++) { // Blink 10 times
            digitalWrite(RED_LED_PIN, HIGH);
            delay(200);
            digitalWrite(RED_LED_PIN, LOW);
            digitalWrite(BLUE_LED_PIN, HIGH);
            delay(200);
            digitalWrite(BLUE_LED_PIN, LOW);
        }
    } else {
        // If distance is not less than 100 cm or the intruder is moving away, display "System working"
        lcd.clear(); // Clear previous message
        lcd.setCursor(0, 0); // Set cursor to beginning of first line
        lcd.print("System working");

        // Stop the buzzer when the system is working normally or intruder is moving away
        noTone(BUZZER_PIN);

        // Turn off LEDs
        digitalWrite(RED_LED_PIN, LOW);
        digitalWrite(BLUE_LED_PIN, LOW);
    }

    // Store the current distance as the last distance for the next loop iteration
    lastDistance = currentDistance;

    // Short delay before the next reading
    delay(1000);
}
