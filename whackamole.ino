


#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address, 16 chars, 2 lines

#define GREEN_LED   10
#define RED_LED     11
#define BUZZER      12

// Struct for LED and button pairing
struct Mole {
  int led;
  int button;
};

Mole moles[4] = {
  {2, 9},  // WHITE
  {3, 8},  // BLUE
  {4, 7},  // ORANGE
  {5, 6}   // YELLOW
};

int p1Score = 0;
int p2Score = 0;
int highScore = 0;

void setupHardware() {
  for (int i = 0; i < 4; i++) {
    pinMode(moles[i].led, OUTPUT);
    pinMode(moles[i].button, INPUT);
  }
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void lcdInitDisplay() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Reaction Game!");
  delay(1500);
}

// Function to update score via pointer (pointer concept + & operator)
void updateScore(int* score) {
  (*score)++;
}

void showResultOnLCD(const char* line1, const char* line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

int playGame(int player) {
  int score = 0;
  char buf[16];

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Player ");
  lcd.print(player);
  lcd.setCursor(0, 1);
  lcd.print("Get Ready...");
  delay(2000);

  for (int round = 0; round < 5; round++) {
    bool hardMode = (round >= 3);
    unsigned long timeLimit = hardMode ? 1500 : 3000;

    int idx = random(0, 4);
    Mole mole = moles[idx];

    digitalWrite(mole.led, HIGH);

    lcd.clear();
    sprintf(buf, "P%d Round %d", player, round + 1);
    lcd.setCursor(0, 0);
    lcd.print(buf);
    lcd.setCursor(0, 1);
    lcd.print(hardMode ? "Hard" : "Easy");
    delay(800);

    bool answered = false;
    unsigned long startTime = millis();

    while (millis() - startTime < timeLimit) {
      for (int j = 0; j < 4; j++) {
        if (digitalRead(moles[j].button) == HIGH) {
          answered = true;
          lcd.clear();
          lcd.setCursor(0, 0);
          if (j == idx) {
            updateScore(&score);  // Using pointer to update score
            digitalWrite(GREEN_LED, HIGH);
            tone(BUZZER, 1000, 300);
            lcd.print("Correct!");
            digitalWrite(GREEN_LED, LOW);
          } else {
            digitalWrite(RED_LED, HIGH);
            tone(BUZZER, 200, 500);
            lcd.print("Wrong!");
            digitalWrite(RED_LED, LOW);
          }
          delay(500);
          break;
        }
      }
      if (answered) break;
    }

    if (!answered) {
      digitalWrite(RED_LED, HIGH);
      tone(BUZZER, 200, 500);
      showResultOnLCD("Too Slow!", "");
      digitalWrite(RED_LED, LOW);
      delay(500);
    }

    digitalWrite(mole.led, LOW);
    delay(300);
  }

  return score;
}

void loop() {
  p1Score = playGame(1);
  showResultOnLCD("Player 2", "Get Ready...");
  delay(3000);

  p2Score = playGame(2);

  char buf[16];
  lcd.clear();
  sprintf(buf, "P1:%2d  P2:%2d", p1Score, p2Score);
  lcd.setCursor(0, 0);
  lcd.print(buf);

  lcd.setCursor(0, 1);
  if (p1Score > p2Score) lcd.print("Player 1 Wins!");
  else if (p2Score > p1Score) lcd.print("Player 2 Wins!");
  else lcd.print("It's a Tie!");
  delay(4000);

  highScore = max(p1Score, max(p2Score, highScore));
  sprintf(buf, "High Score: %d", highScore);
  showResultOnLCD("High Score:", buf);
  delay(3000);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) digitalWrite(moles[j].led, HIGH);
    delay(200);
    for (int j = 0; j < 4; j++) digitalWrite(moles[j].led, LOW);
    delay(200);
  }
  delay(1000);
}

void setup() {
  setupHardware();
  lcdInitDisplay();
  randomSeed(analogRead(0));  // equivalent to srand(time(NULL));
}

