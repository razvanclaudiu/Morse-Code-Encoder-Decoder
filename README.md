![Sample Image](https://github.com/at-cs-ubbcluj-ro/individual-project-razvanclaudiu/assets/91084651/678f8589-bf38-4997-9634-266da586ffe6)

Project Description

This Arduino Uno project facilitates the encoding and decoding of Morse code, presenting a formal exploration of this venerable communication system. Through the utilization of an LED indicator, a buzzer for signal interpretation, and buttons used for dot, dash, and separator for message translation, the project demonstrates the seamless integration of traditional Morse principles with the help of an LCD I2C screen. By engaging with this endeavor, participants are afforded a formal avenue for understanding Morse code's enduring relevance and practical implications within the context of modern technology.

Schematics

1 x Arduino Uno <br />
1 x Breadboard <br />
3 x Buttons <br />
1 x Buzzer <br />
1 x LED <br />
3 x 10k Rezistors <br />
1 x 220 Rezistor <br />
15 x Dupont Wire <br />

Pre-requisites

Arduino Uno R3 - https://docs.arduino.cc/hardware/uno-rev3/ <br />
Arduino IDE - https://docs.arduino.cc/ <br />
LiquidCrystal-I2C - https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library <br />


Setup and Build

1. First connect the LCD screen to the breaboard and the Arduino Uno, GND to negative rail, VCC to positive rail, SDA to A4, SCL to A5. Then connect from the Arduino, 5V to positive rail and GND to negative rail.

![step1](https://github.com/at-cs-ubbcluj-ro/individual-project-razvanclaudiu/assets/91084651/e2be6511-34e1-49fe-9ab2-4cf548b7f69f)

2. Connect 3 buttons on the breadboard, and one of their pins each to the positive rail.
![step2](https://github.com/at-cs-ubbcluj-ro/individual-project-razvanclaudiu/assets/91084651/dae3769c-3ec8-4c04-9ef2-99c8e16e2528)

3. Connect 3 10k resistors on the breadboard, from the negative rail to the other pin of each button.
![step3](https://github.com/at-cs-ubbcluj-ro/individual-project-razvanclaudiu/assets/91084651/381db798-2737-4332-9c6f-a14863906994)

4. Connect the buttons, on the same line which each resistor, to pin 2, 4, 6 respectively.
![step4](https://github.com/at-cs-ubbcluj-ro/individual-project-razvanclaudiu/assets/91084651/3ef30d19-e9fc-466c-b0b9-c8ba5794b311)

5. Connect a buzzer to the breadboard, its negative pin to negative rail and its positive pin to pin 8.
![step5](https://github.com/at-cs-ubbcluj-ro/individual-project-razvanclaudiu/assets/91084651/ca8c6d89-45da-4b3a-9964-0e2b88ac2ba1)

6. Connect a LED to the breadboard, its longer leg to pin 13 and the shorter leg to the negative rail with a 220 resistor.
![step6](https://github.com/at-cs-ubbcluj-ro/individual-project-razvanclaudiu/assets/91084651/8a0d13f2-b1c9-4832-8a54-ecd23400c285)

Running

The project has 2 main functionalities, to encode and decode Morse Code.
Enconding
The user writes a prompt by keyboard in the Serial Monitor, presses Enter, and then the LED and buzzer will flash, and buzz, the proper Morse Code for the word. On the LCD screen the user can see the word they inserted.
Deconding
The blue buttons are dot and dash, the user may press them at will, and after they have inserted the proper sequence, they may press the red button, which will check if the sequence matches a correct Morse code one, and then prints on the LCD screen the proper character. An additional functionality this buttons have is that by using 6 dots, you may erase a character, and by using 6 dashes, you may clear the LCD screen. <br />

Demo
Vide Demonstration - https://www.youtube.com/watch?v=EruZCIPv6bw
