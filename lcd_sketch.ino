#include <LiquidCrystal.h>

// PINS FOR ESP32

const int rs = 32, 
          en = 33, 
          d4 = 14, 
          d5 = 27, 
          d6 = 26, 
          d7 = 25;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char screen[32] = {0};
  
byte smiley1[8] = {
  0b00000,
  0b00000,
  0b00011,
  0b00100,
  0b01000,
  0b01000,
  0b10000,
  0b10000
};  

byte smiley2[8] = {
  0b00000,
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b11011,
  0b11011,
  0b11011
};  

byte smiley3[8] = {
  0b00000,
  0b00000,
  0b11000,
  0b00100,
  0b00010,
  0b00010,
  0b00001,
  0b00001
}; 


byte smiley4[8] = {
  0b10000,
  0b10010,
  0b01001,
  0b01000,
  0b00100,
  0b00011,
  0b00000
};


byte smiley5[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b00000,
  0b00000,
  0b11111
};


byte smiley6[8] = {
0b00001,
0b01001,
0b10010,
0b00010,
0b00100,
0b11000,
0b00000
};

byte frowny4[8] = {
  0b10000,
  0b10000,
  0b01001,
  0b01010,
  0b00100,
  0b00011,
  0b00000
};


byte frowny5[8] = {
  0b00000,
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111
};


byte frowny6[8] = {
0b00001,
0b00001,
0b10010,
0b01010,
0b00100,
0b11000,
0b00000
};

const int yesPin = 5;
const int noPin = 4;

void setup() {
  pinMode(yesPin, INPUT_PULLUP);
  pinMode(noPin, INPUT_PULLUP);
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  // display image of smiley guy
  delay(1000);
  lcd.begin(16, 2);
  lcd.setCursor(4, 0);
  lcd.print("Is he tuff?");
  lcd.setCursor(4, 1);
  lcd.print("L=No R=Yes");
  makeSmiley();
  drawFace(0);

  // see if smiley guy will now frown or stay smiley
  bool answered = false;
  while (!answered) {
    if (digitalRead(yesPin) == LOW) {  // pressed means LOW for this button
      answered = true;
      makeSmiley();
    } else if (digitalRead(noPin) == LOW) {
      answered = true;
      makeFrowny();
    }
  delay(50);
  }

  lcd.clear();
  drawFace(0);


  lcd.clear();
  delay(100);
}


bool moveLeft = false;
int col = 0;

void loop() {
  lcd.clear();
  if(col >= 13) {
    moveLeft = true;
  }
  if (col <= 0) {
    moveLeft = false;
  }
  if (moveLeft) {
    --col;
  } else {
    ++col;
  }
  drawFace(col);
  delay(500);
}

void proclaimPuqisGoatedness(int col) {
  lcd.setCursor(col, 0);
  lcd.print("Puqi is");
  lcd.setCursor(col, 1);
  lcd.print("goated");
}

void makeSmiley() {
  // register face as smiley by setting char pixel art
  lcd.createChar(0,smiley1);
  lcd.createChar(1,smiley2);
  lcd.createChar(2,smiley3);
  lcd.createChar(3,smiley4);
  lcd.createChar(4,smiley5);
  lcd.createChar(5,smiley6);
}

void makeFrowny() {
  // register face as smiley by setting char pixel art
  lcd.createChar(0,smiley1);
  lcd.createChar(1,smiley2);
  lcd.createChar(2,smiley3);
  lcd.createChar(3,frowny4);
  lcd.createChar(4,frowny5);
  lcd.createChar(5,frowny6);
}

void drawFace(int col) {
  lcd.setCursor(col, 0);
  lcd.write(byte(0)); 
  lcd.write((byte)1); 
  lcd.write((byte)2); 
  lcd.setCursor(col, 1);
  lcd.write((byte)3); 
  lcd.write((byte)4); 
  lcd.write((byte)5);
}
