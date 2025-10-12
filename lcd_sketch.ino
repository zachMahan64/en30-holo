#include <LiquidCrystal.h>

// PINS FOR ESP32

constexpr int RS = 32,
              EN = 33,
              D4 = 14,
              D5 = 27,
              D6 = 26,
              D7 = 25;
constexpr uint8_t FLOATING_PIN = 34;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// blank canvas for copying
byte BLANK_SPRITE[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

byte SHIP_SPRITE[8] = {
  0b01000,
  0b11100,
  0b01110,
  0b11111,
  0b01110,
  0b11100,
  0b01000,
  0b00000
};

byte ASTEROID_1_SPRITE[8] = {
  0b00000,
  0b00110,
  0b01110,
  0b11111,
  0b01110,
  0b00000,
  0b00110,
  0b00110
};

byte ASTEROID_2_SPRITE[8] = {
  0b00100,
  0b10101,
  0b01110,
  0b11111,
  0b01110,
  0b10101,
  0b00100,
  0b00000
};


byte ASTEROID_3_SPRITE[8] = {
  0b00011,
  0b00011,
  0b11000,
  0b11000,
  0b00110,
  0b00110,
  0b00000,
  0b00000
};


byte ASTEROID_4_SPRITE[8] = {
  0b00000,
  0b00011,
  0b00011,
  0b00000,
  0b00000,
  0b11000,
  0b11000
};


byte ASTEROID_5_SPRITE[8] = {
  0b01100,
  0b01100,
  0b00010,
  0b00111,
  0b01010,
  0b11100,
  0b01000,
  0b00000
};

byte EXPLOSION_6_SPRITE[8] = {
  0b10001,
  0b00010,
  0b10100,
  0b11011,
  0b01010,
  0b10100,
  0b01100,
  0b10001
};

byte TITLE_0_SPRITE[8] = {
  0b00000,
  0b00001,
  0b00011,
  0b00111,
  0b01110,
  0b01100,
  0b11100,
  0b11000
};

byte TITLE_1_SPRITE[8] = {
  0b11111,
  0b10000,
  0b01110,
  0b10000,
  0b10000,
  0b10111,
  0b10001,
  0b01111
};

byte TITLE_2_SPRITE[8] = {
  0b00000,
  0b10000,
  0b11000,
  0b01100,
  0b00110,
  0b00110,
  0b00011,
  0b00011
};


byte TITLE_3_SPRITE[8] = {
  0b11000,
  0b11000,
  0b01100,
  0b01110,
  0b00111,
  0b00011,
  0b00000
};


byte TITLE_4_SPRITE[8] = {
  0b11110,
  0b10001,
  0b11110,
  0b10100,
  0b10010,
  0b10001,
  0b11111
};


byte TITLE_5_SPRITE[8] = {
  0b00111,
  0b00111,
  0b01110,
  0b01110,
  0b11100,
  0b11000,
  0b00000
};

byte TITLE_6_SPRITE[8] = {
  0b00010,
  0b00111,
  0b00010,
  0b01000,
  0b11100,
  0b01010,
  0b00111,
  0b00010
};

byte TITLE_7_SPRITE[8] = {
  0b01000,
  0b11100,
  0b01010,
  0b00111,
  0b00010,
  0b01000,
  0b11100,
  0b01000
};


constexpr int PIN_A = 5;
constexpr int PIN_B = 4;

// for moveBackAndForth ~~~~~~
bool moveLeft = false;
int col = 0;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^

// constants for game ~~~~~~~~~~~~~~~~
constexpr uint8_t FIELD_WIDTH = 16;
constexpr uint8_t FIELD_HEIGHT = 2;
char field[FIELD_HEIGHT][FIELD_WIDTH] = { 0 };
constexpr uint8_t SHIP_ID = 1;
constexpr uint8_t EXPLOSION_ID = 7;
constexpr uint8_t BLANK = 0xFF;  // maigc # for getting a blank sprite

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void setup() {
  pinMode(PIN_A, INPUT_PULLUP);
  pinMode(PIN_B, INPUT_PULLUP);
  // init lcd
  lcd.begin(16, 2);
  // init randomn
  randomSeed(analogRead(FLOATING_PIN) ^ micros());
}

void loop() {
  enterTitleScreen();
}

// legacy code, but works nicely
void backAndForth() {
  lcd.clear();
  if (col >= 13) {
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
  drawFirstSixRegisteredSprites(col);
  delay(100);
}

// legacy code but works nicely
void drawFirstSixRegisteredSprites(int col) {
  lcd.setCursor(col, 0);
  lcd.write(static_cast<char>(0));
  lcd.write(static_cast<char>(1));
  lcd.write(static_cast<char>(2));
  lcd.setCursor(col, 1);
  lcd.write(static_cast<char>(3));
  lcd.write(static_cast<char>(4));
  lcd.write(static_cast<char>(5));
}

void initSpritesForPlayingGame() {
  // register space
  lcd.createChar(0, SHIP_SPRITE);
  lcd.createChar(1, ASTEROID_1_SPRITE);
  lcd.createChar(2, ASTEROID_2_SPRITE);
  lcd.createChar(3, ASTEROID_3_SPRITE);
  lcd.createChar(4, ASTEROID_4_SPRITE);
  lcd.createChar(5, ASTEROID_5_SPRITE);
  lcd.createChar(6, EXPLOSION_6_SPRITE);
}

void initSpritesForTitleScreen() {
  // register space
  lcd.createChar(0, TITLE_0_SPRITE);
  lcd.createChar(1, TITLE_1_SPRITE);
  lcd.createChar(2, TITLE_2_SPRITE);
  lcd.createChar(3, TITLE_3_SPRITE);
  lcd.createChar(4, TITLE_4_SPRITE);
  lcd.createChar(5, TITLE_5_SPRITE);
  lcd.createChar(6, TITLE_6_SPRITE);
  lcd.createChar(7, TITLE_7_SPRITE);
}

void drawSprite(int row, int col, byte id) {
  lcd.setCursor(col, row);
  if (id == BLANK) {
    lcd.write(' ');
    return;
  }
  lcd.write(id);
}
void displayTitleScreen() {
  lcd.setCursor(4, 0);
  lcd.print(" Galaxy Run");
  lcd.setCursor(4, 1);
  lcd.print("(A) to start");
  initSpritesForTitleScreen();
  drawFirstSixRegisteredSprites(0);
  delay(100);
  drawSprite(0, 4, 6);   // sparkle
  drawSprite(0, 15, 6);  // sparkle
  drawSprite(0, 3, 7);   // sprinkle
  drawSprite(1, 3, 7);   // sprinkle
}
void enterTitleScreen() {
  displayTitleScreen();
  // conditionally start up game
  bool answered = false;
  while (!answered) {
    if (digitalRead(PIN_A) == LOW) {  // pressed means LOW for this button
      answered = true;
      initSpritesForPlayingGame();
      playGame();
      displayTitleScreen();  // effectively go back to title screen
    } else if (digitalRead(PIN_B) == LOW) {
      // ignore B press
      //answered = true;
      //initSpritesForPlayingGame();
    }
    delay(50);
  }

  lcd.clear();
  delay(100);
}
void renderGameScreen() {
  for (int i = 0; i < FIELD_WIDTH; i++) {
    for (int k = 0; k < FIELD_HEIGHT; k++) {
      char curr = field[k][i];
      if (curr == 0) {
        drawSprite(k, i, BLANK);
      } else {
        drawSprite(k, i, curr - 1);  // -1 to get sprite value in LCD for rendering
      }
    }
  }
}

void doGameCountDown() {
  constexpr long TICK = 750;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Get Ready!");
  lcd.setCursor(0, 1);
  lcd.print("3...");
  delay(TICK);
  lcd.print("2...");
  delay(TICK);
  lcd.print("1...");
  delay(TICK);
  lcd.print("GO!");
  delay(TICK);
  lcd.clear();
}

void playGame() {
  doGameCountDown();
  bool hasDied = false;
  bool lastColClear = true;
  bool shipLow = false;  //start ship high
  long score = 0;
  long GAME_TICK = 700;
  while (!hasDied) {
    // poll input and delay sim by tick speed
    long start = millis();
    while (true) {
      if (digitalRead(PIN_A) == LOW) {  // pressed means LOW for this button
        shipLow = true;
      } else if (digitalRead(PIN_B) == LOW) {
        shipLow = false;
      }
      if (millis() - start >= GAME_TICK) {
        break;  // esc
      }
    }
    if (score > 100) {
      GAME_TICK = 500;
    } else if (score > 400) {
      GAME_TICK = 400;
    } else {
      GAME_TICK = 350;
    }
    for (int i = 1; i < FIELD_WIDTH; i++) {
      for (int k = 0; k < 2; k++) {  // fixed header
        char curr = field[k][i];
        char last = field[k][i - 1];
        if (i == 1 && curr && last == SHIP_ID) {
          hasDied = true;
        }
        field[k][i - 1] = curr;
      }
    }
    char shipSprite = (hasDied) ? EXPLOSION_ID : SHIP_ID;
    if (shipLow) {
      field[1][0] = shipSprite;
    } else {
      field[0][0] = shipSprite;
    }
    // clear far-right column
    field[0][FIELD_WIDTH - 1] = 0;
    field[1][FIELD_WIDTH - 1] = 0;
    // randomize far-right column
    char rowRoll;
    char roll;
    if (lastColClear) {
      rowRoll = static_cast<char>(random(2));
      roll = static_cast<char>(random(1, 12));
      field[rowRoll][FIELD_WIDTH - 1] = (roll <= 5) ? roll + 1 : 0;
      lastColClear = false;
    } else {
      lastColClear = true;
    }

    renderGameScreen();
    ++score;
  }
  // hasDied
    delay(1000); // show explosion
  enterDiedScreen(score);
  clearField();
}

void displayDiedScreen(int score) {
  initSpritesForTitleScreen();
  drawFirstSixRegisteredSprites(0);
  delay(100);
  drawSprite(0, 13, 6);  // sparkle
  drawSprite(0, 14, 7);  // sprinkle
  drawSprite(0, 15, 6);  // sparkle
  drawSprite(0, 3, 7);   // sprinkle
  drawSprite(1, 3, 7);   // sprinkle
  lcd.setCursor(4, 0);
  lcd.print("Nice run!");
  lcd.setCursor(4, 1);
  lcd.print("Score: ");
  lcd.print(score);
  lcd.print("  ");
}

void enterDiedScreen(int score) {
  displayDiedScreen(score);
  // conditionally start up game
  bool answered = false;
  while (!answered) {
    if (digitalRead(PIN_A) == LOW) {  // pressed means LOW for this button
      answered = true;
    } else if (digitalRead(PIN_B) == LOW) {
      answered = true;
    }
    delay(50);
  }
  lcd.clear();
  delay(100);
}
void clearField() {
  for (int i = 0; i < FIELD_WIDTH; i++) {
    for (int k = 0; k < FIELD_HEIGHT; k++) {
      field[k][i] = 0;  // clear tile
    }
  }
}

void moveShipVisually(bool shipLow) {
  // clear
  drawSprite(0, 0, BLANK);
  drawSprite(1, 0, BLANK);
  // draw ship
  if (shipLow) {
    drawSprite(1, 0, SHIP_ID);
    return;
  }
  drawSprite(0, 0, SHIP_ID);
}