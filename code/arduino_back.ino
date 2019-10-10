
const int buzzer = 8;
const int threshold=85;
const int soundpin=A2;
const int ledpin=7;
const int btnpin = 13;

int lock = 1;



// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int buttonState = 0; 

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
    pinMode(btnpin, INPUT_PULLUP);
    pinMode(ledpin,OUTPUT);
pinMode(soundpin,INPUT);
    Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

lcdStart();
    

  // Print a message to the LCD.
}


void playing() {

    lock = 0;
        digitalWrite(ledpin, HIGH);


        // we only play the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, 1000, 500);

}

void stopping() {
  
    Serial.println("action : stopping");
}

void loop() {

    int soundsens=analogRead(soundpin);
    int sum = 0;
    for ( int i = 0 ; i <125; i ++)  
  {  
   int Sound_signal = analogRead(soundpin);  
    sum =sum + Sound_signal;  
  }  
      int level = sum / 125;

      lcd.setCursor(0, 1);
          delay(500);

    lcd.print(level);

        if(buttonState == 0 && soundsens>=threshold || lock == 0)
        {
            playing();
            buttonPressed();
        }


}

void lcdStart() {

    // modify the display



    lcd.clear();
    lcd.print("Sensor : On");

}

void lcdEnd() {
    Serial.println("hello");
    digitalWrite(ledpin, LOW);

    // modify the display
      lock = 1;
    Serial.print("capteur");
    lcd.clear();
    lcd.print("Stopping the alert sound");
    lcd.setCursor(0, 1);
    lcd.print("Quote incoming");
          delay(1000);

    lcdStart();
    

}

void buttonPressed() {
  
    if(!digitalRead(13)) {
        lcdEnd();
    }
}
