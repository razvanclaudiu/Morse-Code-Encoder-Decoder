#include <Wire.h> // for I2C communication
#include <LiquidCrystal_I2C.h> // for LCD display

#define DASH_BUTTON_PIN 4
#define DOT_BUTTON_PIN 2
#define SEPARATOR_BUTTON_PIN 6
#define TONE_PIN 8
#define LED_PIN 13
#define DISPLAY_NUM_OF_COLUMNS 16 // Working with a 16x2 display

int dotLength = 240; 
// dotLength = basic unit of speed in milliseconds
// 240 gives 5 words per minute (WPM) speed.
// WPM = 1200/dotLength.
// For other speeds, use dotLength = 1200/(WPM)
//
// Other lengths are computed from dot length
  int dotSpace = dotLength;
  int dashLength = dotLength*3;
  int letterSpace = dotLength*3;
  int wordSpace = dotLength*7; 
  float wpm = 1200./dotLength;

int toneFreq = 1000;

int dashButtonState = 0;
int dotButtonState = 0;
int separatorButtonState = 0;
int dashButtonLastState = 0;
int dotButtonLastState = 0;
int separatorButtonLastState = 0;
String tonesBuffer;
String text;

// Morse code alphabet
const char* symbolsAlphabet[][2] = {
    { ".-", "A" }, { "-...", "B" }, { "-.-.", "C" }, { "-..", "D" }, { ".", "E" },
    { "..-.", "F" }, { "--.", "G" }, { "....", "H" }, { "..", "I" }, { ".---", "J" },
    { "-.-", "K" }, { ".-..", "L" }, { "--", "M" }, { "-.", "N" }, { "---", "O" },
    { ".--.", "P" }, { "--.-", "Q" }, { ".-.", "R" }, { "...", "S" }, { "-", "T" },
    { "..-", "U" }, { "...-", "V" }, { ".--", "W" }, { "-..-", "X" }, { "-.--", "Y" },
    { "--..", "Z" }, { ".----", "1" }, { "..---", "2" }, { "...--", "3" }, { "....-", "4" },
    { ".....", "5" }, { "-....", "6" }, { "--...", "7" }, { "---..", "8" }, { "----.", "9" },
    { "-----", "0" }
};

LiquidCrystal_I2C lcd(0x27, DISPLAY_NUM_OF_COLUMNS, 2);

char getToneFromButtonStates() {
    // Returns in case of button release i.e., when the current state is 0 and the previous state is 1
    if (!dashButtonState && dashButtonLastState)
        return '-';
    if (!dotButtonState && dotButtonLastState)
        return '.';
    if (!separatorButtonState && separatorButtonLastState)
        return ' ';
    return (char)0;
}

char getSymbolFromBuffer() {
    if (tonesBuffer == "")
        return ' '; // inserts a space if there are no characters before
    for (int i = 0; i < sizeof(symbolsAlphabet) / sizeof(symbolsAlphabet[0]); i++) {
        // Iterates through all symbols and compares the buffer with the alphabet
        if (tonesBuffer == symbolsAlphabet[i][0])
            return symbolsAlphabet[i][1][0]; // if equal, returns the corresponding symbol
    }
    // Buffer does not match any symbol, returns nothing
    return (char)0;
}

void extractActionFromTonesBuffer() {
    if (tonesBuffer == "......") // 6x dot
        text.remove(text.length() - 1, 1); // removes one character
    if (tonesBuffer == "------") // 6x dash
        text = ""; // clears the whole text
}

void playTone(char tone) {
    int duration = 0; // Duration for dot or dash

    if (tone == '.') {
        digitalWrite(LED_PIN, HIGH); // Turn on LED for dot
        duration = dotLength; // Set duration for dot
    } else if (tone == '-') {
        digitalWrite(LED_PIN, HIGH); // Turn on LED for dash
        duration = dashLength; // Set duration for dash
    }

    // Toggle buzzer pin manually at the desired frequency
    for (int i = 0; i < duration; i++) {
        digitalWrite(TONE_PIN, HIGH); // Set buzzer pin high
        delay(1); // Delay for half the desired frequency
        digitalWrite(TONE_PIN, LOW); // Set buzzer pin low
        delay(1); // Delay for half the desired frequency
    }

    digitalWrite(LED_PIN, LOW); // Turn off LED
    delay(dotSpace); // Pause between tones
}


void readSerialInput() {
    if (Serial.available() > 0) {
        text = Serial.readStringUntil('\n'); // Read the input string until newline character
        Serial.print("Entered text: ");
        Serial.println(text);
        lcd.clear(); // Clear the LCD display
        lcd.print("Entered text:");
        lcd.setCursor(0, 1);
        lcd.print(text); // Display the entered text on LCD
        // Convert the entered text to Morse code and play tones
        for (int i = 0; i < text.length(); i++) {
            char c = toupper(text[i]); // Convert character to uppercase
            for (int j = 0; j < sizeof(symbolsAlphabet) / sizeof(symbolsAlphabet[0]); j++) {
                if (c == symbolsAlphabet[j][1][0]) { // Match found in Morse code alphabet
                    String morse = symbolsAlphabet[j][0]; // Get Morse code for the character
                    for (int k = 0; k < morse.length(); k++) {
                        char tone = morse[k];
                        playTone(tone); // Play tone
                    }
                    delay(letterSpace); // Pause between letters
                    break;
                }
            }
            delay(wordSpace); // Pause between words
        }
        text = "";
    }
} 

void setup() {
    lcd.begin();
    lcd.backlight();
    lcd.print("Morse En/Decoder");
    lcd.setCursor(0, 1);
    lcd.print("By Tomuta Razvan");
    pinMode(DASH_BUTTON_PIN, INPUT);
    pinMode(DOT_BUTTON_PIN, INPUT);
    pinMode(SEPARATOR_BUTTON_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(TONE_PIN, OUTPUT);

    Serial.begin(9600);
    Serial.println();
    Serial.println("-------------------------------");
    Serial.println("Morse Code decoder/encoder");
    Serial.print("Speed=");
    Serial.print(wpm);
    Serial.print("wpm, ");
    Serial.print("dot=");
    Serial.print(dotLength);
    Serial.println("ms");   

    // Test the LED and tone
    tone(TONE_PIN, toneFreq);
    digitalWrite(LED_PIN, HIGH);
    delay(2000);
    digitalWrite(LED_PIN, LOW);
    noTone(TONE_PIN);
    delay(600);
}

void loop() {
    // Reads button states
    dashButtonState = digitalRead(DASH_BUTTON_PIN);
    dotButtonState = digitalRead(DOT_BUTTON_PIN);
    separatorButtonState = digitalRead(SEPARATOR_BUTTON_PIN);
    char tone = getToneFromButtonStates(); // checks which button is pressed
    if (tone != (char)0) {
        if (tone == ' ') { // ends the tone sequence, looks for a symbol
            char symbol = getSymbolFromBuffer();
            if (symbol != (char)0) { // If a symbol is found, adds it to the text
                text += symbol;
                if (text.length() > DISPLAY_NUM_OF_COLUMNS) { // If exceeds display size, adds a new character and clears the rest
                    text = (String)symbol;
                }
            } else { // If no symbol found, maybe some action is required (e.g., deleting a character)
                extractActionFromTonesBuffer();
            }
            tonesBuffer = ""; // clears the buffer (dots and dashes)
        } else { // dot or dash
            tonesBuffer += tone;
            if (tonesBuffer.length() > DISPLAY_NUM_OF_COLUMNS) { // If more tones than display size, clears the buffer
                tonesBuffer = (String)tone;
            }
        }
        // LCD writing only if a button was pressed
        lcd.clear(); // clears the display
        lcd.print(text); // writes the text
        lcd.setCursor(0, 1);
        lcd.print(tonesBuffer); // writes the tone sequence
    }

    readSerialInput();
    // updates previous state
    dashButtonLastState = dashButtonState;
    dotButtonLastState = dotButtonState;
    separatorButtonLastState = separatorButtonState;
}
