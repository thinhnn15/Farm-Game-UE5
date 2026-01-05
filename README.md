# 🌾 MyFarm – Unreal Engine Farm Simulation Game

## Overview

**MyFarm** is a farm simulation game developed using **Unreal Engine (C++ + Blueprints)**.  
The project focuses on clean architecture, performance-oriented gameplay systems, and extensibility for future features such as crafting, inventory management, and character progression.

This repository contains the **core gameplay logic**, **UI systems**, and **world interaction mechanics** implemented primarily in C++, with Blueprint used for iteration and visualization.

---

## Key Features

- 🌱 **Farm Gameplay**
  - Grid-based farm plots
  - Crop planting, growing, and harvesting
  - Data-driven crop system

- 🎒 **Inventory System**
  - Seed and item management
  - UI-driven inventory with selection logic
  - Subsystem-based architecture

- 🧑‍🌾 **Character & Input**
  - Custom Character & PlayerController
  - Enhanced Input System (UE5)
  - Keyboard & controller friendly

- 🖥️ **UI System**
  - UMG widgets written in C++ and Blueprint
  - Main Menu & In-Game UI separation
  - MVC-like structure for maintainability

- ⚙️ **C++-First Design**
  - Core logic in C++
  - Blueprint used only for configuration & visuals
  - Clean naming conventions and folder structure

---

## Project Structure

```text
MyFarm/
├── Source/
│   ├── Gameplay/
│   │   ├── Farm/
│   │   ├── Crop/
│   │   └── Character/
│   ├── UI/
│   │   ├── Widgets/
│   │   └── Menus/
│   ├── Core/
│   │   ├── Inventory/
│   │   └── Subsystems/
│   └── Data/
│       └── DataAssets/
├── Content/
│   ├── Blueprints/
│   ├── UI/
│   └── Maps/
└── Config/
```

---

## Tech Stack

- **Engine**: Unreal Engine 5.x  
- **Language**: C++ (Primary), Blueprint (Secondary)  
- **UI**: UMG  
- **Input**: Enhanced Input System  
- **Version Control**: Git (LFS enabled for assets)

---

## Getting Started

### Requirements

- Unreal Engine 5.x
- Visual Studio 2022 (Windows)  
  or Rider for Unreal Engine
- Git + Git LFS

### Setup

```bash
git clone <repository-url>
git lfs pull
```

1. Open `MyFarm.uproject`
2. Generate project files
3. Build the project
4. Launch the editor

---

## Coding Guidelines

- Core gameplay logic must be written in **C++**
- Blueprints should:
  - Inherit from C++ classes
  - Be used only for visuals & tuning
- Follow Unreal naming conventions:
  - `A` for Actors
  - `U` for UObject
  - `F` for structs
- Avoid logic inside Tick unless necessary

---

## Roadmap

- [ ] NPC interaction system  
- [ ] Crafting & building mechanics  
- [ ] Save / Load system  
- [ ] Seasonal events  
- [ ] Steam release support  

---

## Contributing

Contributions are welcome.

- Create feature branches
- Follow existing code style
- Provide clear commit messages
- Test before submitting PRs

---

## License

This project is currently **private / proprietary**.  
License details will be added later.

---

## Author

Developed by **Thinh Nguyen**  
Unreal Engine Developer | C++ Gameplay Programmer
