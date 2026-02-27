# Balloon Buster 2.0 🎯

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20macOS%20%7C%20Linux-green.svg)](#)

A modernized retro arcade balloon shooting game built with C++17.  
Originally inspired by the Turbo C++ version with 'graphics.h', now rebuilt with a structured game engine, terminal rendering, sound effects, and cross-platform support.

> Check out the old one👉 **Old Repository:**    [Balloon-Buster](https://github.com/patelritiq/Balloon-Buster)

---

## Project Statistics 📊

- **3 Progressive Levels + Survival Mode**
- **Level 1:** 12 balloons | 6 arrows
- **Level 2:** 10 balloons | 6 arrows
- **Level 3:** 8 balloons | 6 arrows
- **Survival Mode:** 15 arrows | 3 miss limit
- **20 points** per balloon
- **Score-based progression** (100 / 200 / 300 targets)
- **High score persistence**
- **Cross-platform terminal gameplay**

---

## Project Overview 🎮

Balloon Buster 2.0 is a complete redesign of the original Turbo C++ version.  
The game engine has been rewritten using modern C++17 standards with proper state management, structured game flow, and a clean update-render loop.

### Evolution
- **Original:** Turbo C++ 3.0 with `graphics.h` (DOS-based)
- **Version 2.0:** Terminal-based arcade engine
- **New Additions:** Survival mode, difficulty selection, sound effects, high score system, structured level transitions

---

## Game Features ✨

- **Structured Game States**
  - Menu
  - Difficulty Selection
  - Rule Screens
  - Level Gameplay
  - Level Result Screen
  - Survival Mode
  - Game Over

- **Score-Based Level Progression**
  - Level 1 → 100 Points
  - Level 2 → 200 Points
  - Level 3 → 300 Points
  - Survival Mode unlocks after Level 3

- **Survival Mode**
  - 15 arrows
  - Unlimited balloons
  - Game ends after 3 missed arrows
  - Speed increases every 40 points

- **Sound Effects**
  - Shoot sound
  - Hit sound
  - Game over sound

- **High Score System**
  - Persistent high score stored in `highscore.dat`
  - Automatically updates when surpassed

---

## Game Controls 🎮

| Action | Key |
|--------|-----|
| Move Bow Up | `W` |
| Move Bow Down | `S` |
| Shoot Arrow | `SPACE` |
| Quit Game | `Q` |

---

## Scoring System 🏆

- **Per Balloon:** 20 points
- **Level 1 Target:** 100 points
- **Level 2 Target:** 200 points
- **Level 3 Target:** 300 points
- **Survival Mode:** No cap

Score increases only when an arrow successfully hits a balloon.

---

## Installation & Setup 🚀

### Prerequisites
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.10+ (optional but recommended)

---

### Build Instructions

#### Option 1: Using CMake

```bash
git clone https://github.com/patelritiq/Balloon-Buster-2.0.git
cd Balloon-Buster-2.0
mkdir build && cd build
cmake ..
cmake --build .
./balloon_buster
```

### Option 2: Direct Compilation

**Windows:**
```bash
cl /std:c++17 src/balloon_buster.cpp /Fe:balloon_buster.exe
balloon_buster.exe
```

**macOS/Linux:**
```bash
g++ -std=c++17 src/balloon_buster.cpp -o balloon_buster
./balloon_buster
```
---

## How to Play 🎯

1. Start the game and select difficulty.
2. Review level rules before each stage.
3. Use W/S to position the bow.
4. Shoot carefully — only 6 arrows per level.
5. Reach required score to unlock the next level.
6. Enter Survival Mode after clearing Level 3.

### Strategy Tips
- Position bow in the middle for better coverage
- Anticipate balloon movement
- Conserve arrows for high-value shots
- Try to reach Level 3 for the ultimate challenge

---

## Technical Details 🛠️

### Architecture
- Object-oriented game structure
- State-driven game flow
- Fixed timestep update loop
- Separated physics and rendering timing

### Code Quality
- Modern C++17 standards
- Clean modular design
- Cross-platform console support
- No external dependencies

### Performance
- Lightweight (~1MB)
- Minimal memory usage
- ~10 FPS (intentional arcade pacing)
- Responsive controls
- ~4 FPS rendering (reduced flicker)

---

## Project Evolution 📈

### Original Version (Turbo C++)
- Developed in Turbo C++ 3.0
- BGI Rendering
- DOS-based graphics
- Limited to DOS environment
- Manual memory management

### Modern Version (C++17)
- Complete rewrite in modern C++
- Terminal-based gameplay
- Cross-platform support
- Structured game engine
- High Score persistence
- Survival Mode
- Diffculty scaling

---

## Future Enhancements 🔮

- [ ] Animated ASCII effects
- [ ] Expanded leaderboard system
- [ ] Combo scoring system
- [ ] Power-ups
- [ ] Multiplayer challenge mode
- [ ] Mobile adaptation

---

## Troubleshooting 🔧

### High score not saving
- Ensure write permissions in project directory.

### Controls not responding
- Ensure terminal has focus
- Try different key combinations

### Flickering in terminal
- This is expected in terminal rendering arcade pacing environments.

---

## License 📄

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## Author 👨‍💻

**Ritik Pratap Singh Patel**

- Creator of Balloon Buster
- Nostalgic Retro arcade game enthusiast
- C++ developer

---

## Play Now! 🎮

```bash
git clone https://github.com/patelritiq/Balloon-Buster-2.0.git
cd Balloon-Buster-2.0
mkdir build && cd build
cmake .. && cmake --build .
./balloon_buster
```

Enjoy the nostalgic arcade experience! 🎯


> ## Build System (CMake) 🏗️
>
> This project uses **CMake** as its build configuration system.
>
> ### Why CMake?
>
> - Ensures cross-platform compatibility
> - Simplifies compilation across Windows, macOS, and Linux
> - Automatically configures compiler settings
> - Enforces C++17 standard requirements
> - Applies appropriate warning levels for MSVC and GCC/Clang
>
> ### What CMakeLists.txt Does
>
> - Sets the project version and name
> - Specifies C++17 as the required standard
> - Defines the executable target (`balloon_buster`)
> - Applies strict compiler warnings
> - Enables consistent builds across different systems
>
> Using CMake allows the project to remain portable and scalable, especially if additional source files or modules are added in the future.
