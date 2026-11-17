# Whack-a-Mole Reaction Game (Arduino)

A two-player reaction game built on an Arduino Uno and simulated in Tinkercad Circuits. An LED (the "mole") lights up at random, and the player has to press the matching button before time runs out. Scores and game status show on a 16x2 I2C LCD.

**Simulation:** [Open in Tinkercad](https://www.tinkercad.com/things/9rMBLJRebSD-whackamole)

![Circuit diagram](circuit.png)

## Features
- Two players take turns, 5 rounds each
- 4 mole LEDs, each paired with its own push button
- Easy mode (3 s per round) for rounds 1-3, hard mode (1.5 s) for rounds 4-5
- Green LED and a high tone for a correct hit; red LED and a low tone for a wrong press or a miss
- LCD shows the round, difficulty, result, final scores, winner and the session high score
- A flashing LED animation plays at the end of each game

## Components
| Component | Qty |
|-----------|-----|
| Arduino Uno | 1 |
| 16x2 LCD with I2C backpack (address 0x27) | 1 |
| LEDs (white, blue, orange, yellow) | 4 |
| Status LEDs (green, red) | 2 |
| Push buttons | 4 |
| Piezo buzzer | 1 |
| Resistors (LED current-limiting and button pull-down) | as needed |
| Breadboard and jumper wires | 1 set |

## Pin Connections
| Component | Arduino Pin |
|-----------|-------------|
| White LED | D2 |
| Blue LED | D3 |
| Orange LED | D4 |
| Yellow LED | D5 |
| Yellow button | D6 |
| Orange button | D7 |
| Blue button | D8 |
| White button | D9 |
| Green LED (correct) | D10 |
| Red LED (wrong) | D11 |
| Buzzer | D12 |
| LCD SDA | A4 |
| LCD SCL | A5 |
| LCD VCC / GND | 5V / GND |

Each LED is paired with a button: white (D2/D9), blue (D3/D8), orange (D4/D7), yellow (D5/D6).

## Libraries
- `Wire` (built in)
- `LiquidCrystal_I2C`

## How to Run
**In Tinkercad:** open the link above, click **Start Simulation**, and click the buttons.

**On real hardware:**
1. Wire the circuit using the pin table.
2. Install the `LiquidCrystal_I2C` library from the Arduino IDE Library Manager.
3. Open `whackamole/whackamole.ino`, select **Arduino Uno**, and upload.

## How to Play
1. Player 1 gets a "Get Ready" screen, then 5 rounds.
2. In each round one LED lights up. Press its matching button before the timer ends.
3. Player 2 then plays the same 5 rounds.
4. The LCD shows both scores and the winner, then the high score.
5. The game restarts automatically.

## Concepts Used
- Structs (pairing each LED with its button)
- Pointers (`updateScore(int*)`)
- Non-blocking-style timing with `millis()`
- I2C communication with an LCD
- `randomSeed(analogRead(0))` for random moles

## Project Structure
- `whackamole/whackamole.ino` is the Arduino sketch
- `circuit.png` is the circuit screenshot
- `README.md` is this file
