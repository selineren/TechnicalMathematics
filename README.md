# Technical Mathematics Projects

This repository contains two graphical and interactive projects developed using C++ and OpenGL. These projects demonstrate fundamental concepts in computer graphics and user interaction, showcasing creativity and programming skills.

## Projects Overview

### 1. Turtle Animation

This project features an animated scene with a turtle moving along a path, a house, and a curtain controlled by user input.

#### Features:

- **Interactive Turtle Animation**: The turtle moves along a predefined path and can be started or stopped using the keyboard.
- **House Drawing**: A house is drawn with detailed elements like a roof, windows, and a door.
- **Curtain Control**: The curtain covering the house can be opened or closed by clicking inside the house.

#### How to Use:

1. **Compile and Run**:
   Ensure OpenGL is installed, then use the following command:
   ```bash
   g++ Technical-Mathematics-Project1.cpp -lGL -lGLU -lglut -o turtle_project
   ./turtle_project
   ```
2. **Controls**:
   - **Spacebar**: Start or stop the turtle's movement.
   - **Mouse**: Click inside the house to open or close the curtain.

#### Dependencies:

- OpenGL
- GLUT

---

### 2. Target Shooting Game

This project is a shooting game where the player controls a cannon to shoot moving targets within a time limit.

#### Features:

- **Dynamic Target Generation**: Randomly generated targets with varying speeds and directions.
- **Scoring System**: Points are awarded for hitting targets.
- **Timer**: The game ends after 20 seconds.
- **Interactive Cannon**: The cannon can be moved left or right, and bullets can be fired using keyboard controls.

#### How to Play:

1. **Compile and Run**:
   Ensure OpenGL is installed, then use the following command:
   ```bash
   g++ Technical-Mathematics-Project2.cpp -lGL -lGLU -lglut -o shooting_game
   ./shooting_game
   ```
2. **Controls**:
   - **A/D or Left/Right Arrows**: Move the cannon left or right.
   - **Spacebar**: Fire a bullet.
   - **F1**: Start or restart the game.
   - **ESC**: Exit the game.

#### Dependencies:

- OpenGL
- GLUT

---

## How to Clone the Repository

To clone this repository to your local machine, run:

```bash
git clone https://github.com/your-username/technical-mathematics-projects.git
```
