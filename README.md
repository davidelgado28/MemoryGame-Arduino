# Arduino Memory Game

A classic **Simon Says (Genius)** style memory game built with Arduino, featuring 4 colored LEDs, 4 buttons, and a buzzer for audiovisual feedback.

## Table of Contents
- [Overview](#-overview)
- [Components](#-components)
- [Wiring](#-wiring)
- [Installation](#-installation)
- [How to Play](#-how-to-play)
- [Code Structure](#-code-structure)
- [Customization](#-customization)

## Overview

The game generates a random sequence of lights and sounds. Each round, the sequence grows by one step. The player must repeat the sequence by pressing the corresponding buttons. One mistake and the game is over!

**Features:**
- Progressive difficulty (up to 100 levels)
- Audio feedback with different tones per LED
- Visual feedback on button presses
- Victory and defeat animations
- Serial monitor output for debugging

## Components

| Component | Quantity |
|-----------|----------|
| Arduino Uno/Nano | 1 |
| LEDs (red, green, blue, yellow) | 4 |
| Push buttons | 4 |
| 220Ω resistors (LEDs) | 4 |
| Passive buzzer | 1 |
| Breadboard + jumper wires | — |


## Wiring

| Component | Arduino Pin |
|-----------|-------------|
| LED 1 (red) | 2 |
| LED 2 (green) | 3 |
| LED 3 (blue) | 4 |
| LED 4 (yellow) | 5 |
| Button 1 | 8 |
| Button 2 | 9 |
| Button 3 | 10 |
| Button 4 | 11 |
| Buzzer (+) | 12 |
| Buzzer (−) | GND |

Connect each LED's cathode through a 220Ω resistor to GND. Each button connects its pin to GND (internal pull-ups handle the rest).

## Installation

1. Open the Arduino IDE
2. Create a new sketch and paste the code (or open `memory_game.ino`)
3. Select your board: **Tools → Board → Arduino Uno**
4. Select the port: **Tools → Port**
5. Upload the sketch (**Ctrl+U**)
6. Open the Serial Monitor (**Ctrl+Shift+M**) at **9600 baud** to follow the game

## How to Play

1. **Start**: Press any button to begin
2. **Watch**: The LEDs light up in a sequence — pay attention!
3. **Repeat**: Press the buttons in the same order
4. **Level up**: Each round adds one more step to the sequence
5. **Game over**: A wrong press triggers the defeat animation and the game restarts
6. **Win**: Complete all 100 levels to trigger the victory melody! 🏆

## Code Structure

| Function | Description |
|----------|-------------|
| `loop()` | Main game loop — controls game flow |
| `aguardarInicio()` | Waits for a button press to start |
| `mostrarSequencia()` | Plays back the current sequence |
| `lerJogador()` | Reads and validates player input |
| `aguardarBotao()` | Waits for a button press with debounce |
| `piscarLed()` | Lights an LED and plays its tone |
| `derrota()` / `vitoria()` | End-game animations and sounds |

## Customization

**Change difficulty:**
```c
piscarLed(sequencia[i], 400);  // Lower = faster sequence
delay(200);                     // Lower = less gap between steps
```

**Lower the max level for a shorter game:**
```c
const int MAX_NIVEL = 100;  // Change to e.g. 10
```

**Change the tones:**
```c
const int tom[NUM_LEDS] = {262, 330, 392, 523};  // Frequencies in Hz
```

**Using external pull-down resistors?** Replace `INPUT_PULLUP` with `INPUT` and swap the logic from `LOW` to `HIGH` for button presses.

---
