# Dungeon Game

A console-based dungeon crawler game project for NTUST Object-Oriented Programming course (2024 Spring, Project 2).

## Overview

This is a turn-based dungeon exploration game where players control multiple characters to explore a dungeon, engage in combat, interact with events, and manage inventory. The game features a tile-based map system, combat mechanics, item management, and various interactive objects.

## Features

- **Multiple Characters**: Control up to 3 different roles, switch between them during gameplay
- **Map Exploration**: Navigate through a procedurally generated dungeon map (140×50 tiles)
- **Combat System**: Turn-based combat encounters with enemies
- **Inventory Management**: Collect and manage various items including weapons, armor, accessories, and consumables
- **Shop System**: Purchase items from merchants
- **Interactive Events**:
  - **Chest Events**: Open chests to obtain rewards
  - **Spring Events**: Restore health and resources
  - **Tent**: Set up camps for rest and recovery
- **Item System**: 
  - Weapons (attack enhancement)
  - Armor (defense enhancement)
  - Accessories (stat bonuses)
  - Teleport Scrolls (instant movement)
  - Tents (camping equipment)

## Requirements

- Windows OS (uses Windows API for console operations)
- CMake (version 3.0 or higher)
- C++ compiler with C++11 support (MSVC, MinGW, or compatible)

## Build Instructions

1. Clone or download this repository

2. Create a build directory:
```bash
mkdir build
cd build
```

3. Generate build files using CMake:
```bash
cmake ..
```

4. Build the project:
```bash
cmake --build .
```

5. The executable will be generated in the build directory (or `exe/` folder if pre-compiled)

## Controls

### Map Navigation
- **W** / **w** : Move up
- **S** / **s** : Move down  
- **A** / **a** : Move left
- **D** / **d** : Move right
- **P** / **p** : Switch to next character
- **I** / **i** : Open inventory/backpack
- **ESC** : Exit game

### Inventory Management
- **W** / **w** : Navigate selection up
- **S** / **s** : Navigate selection down
- **Enter** : Use selected item
- **Backspace** : Close inventory (returns to map)

### Interactive Objects (Shop, Events, etc.)
- **W** / **w** : Navigate selection up
- **S** / **s** : Navigate selection down
- **Enter** : Confirm selection
- **Backspace** : Exit interaction (returns to map)

### Combat Mode
- Controls are context-specific to combat actions
- **ESC** and **Backspace** are disabled during combat

## Gameplay

1. **Starting the Game**: Launch the executable. The game window will automatically maximize.

2. **Character Movement**: Use WASD keys to move your current character on the map. Each character has movement points that limit how far they can move per turn.

3. **Switching Characters**: Press **P** to cycle through your available characters, then press **Enter** to confirm your selection.

4. **Interacting with Objects**: Move onto objects (enemies, shops, events) to interact with them automatically.

5. **Combat**: When encountering enemies, the game enters combat mode. Follow on-screen prompts to select actions.

6. **Inventory**: Press **I** to open your inventory, manage items, and use consumables.

## Project Structure

```
.
├── CMakeLists.txt          # CMake build configuration
├── README.md               # This file
├── src/                    # Source code directory
│   ├── Main.cpp           # Entry point and game loop
│   ├── GameManager.*      # Core game state management
│   ├── Role.*             # Player character class
│   ├── Entity.*           # Base entity class
│   ├── Enemy.*            # Enemy entity
│   ├── Combat.*           # Combat system
│   ├── Backpack.*         # Inventory system
│   ├── Items.*            # Base item class
│   ├── Weapon.*           # Weapon items
│   ├── Armor.*            # Armor items
│   ├── Accessory.*        # Accessory items
│   ├── Shop.*             # Shop interaction
│   ├── Event.*            # Base event class
│   ├── ChestEvent.*       # Chest event
│   ├── SpringEvent.*      # Spring healing event
│   ├── Tent.*             # Tent/camping item
│   ├── TeleportScroll.*   # Teleportation item
│   ├── Object.*           # Interactive object base class
│   ├── Rect.*             # Map tile representation
│   ├── Point.*            # Coordinate system
│   └── Dice.*             # Random number generation
└── exe/                   # Pre-compiled executables
    └── *.exe              # Windows executable files
```

## Technical Details

- **Design Patterns**: Singleton pattern (GameManager), Observer pattern (Tent system)
- **Inheritance Hierarchy**: Entity → Role/Enemy, Object → Shop/Event/Tent/Role
- **Game Loop**: Fixed-time step update loop (0.03 seconds per frame)
- **Console Rendering**: Windows Console API for colored text and cursor positioning
- **Camera System**: Dynamic camera that follows the current active character

## Notes

- The game requires a Windows console environment
- Window decorations are automatically removed for full-screen experience
- Map dimensions are fixed at 140×50 tiles
- Camera viewport scales based on console window size

## License

This project is created for educational purposes as part of NTUST OOP course requirements.
