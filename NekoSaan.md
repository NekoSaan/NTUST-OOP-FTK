# 專案學習心得 / Project Learning Reflection

## 中文版 / Chinese Version

### 專案概述

這是一個基於 C++ 的地城探險遊戲專案，作為台灣科技大學物件導向程式設計課程的第二次專案作業。透過實作這個專案，我深入學習了物件導向程式設計的核心概念、設計模式的實際應用，以及遊戲開發的基礎架構。

---

### 一、設計模式的實踐

#### 1. Singleton（單例模式）

在 `GameManager` 類別中實作了 Singleton 模式，確保整個遊戲執行期間只存在一個遊戲管理器實例。這讓我理解了：

- **使用時機**：當系統中只需要一個全域實例時，Singleton 模式可以有效避免資源重複分配
- **實作細節**：私有建構子、靜態實例指標、`getInstance()` 靜態方法
- **優缺點**：雖然提供了全域存取點，但也可能造成緊耦合，需要謹慎使用

```cpp
// GameManager 使用私有建構子和靜態實例
static GameManager* instance;
static GameManager* getInstance();
```

#### 2. Observer（觀察者模式）

在 `Tent` 系統中實作了 Observer 模式，讓帳篷物件可以觀察遊戲回合的變化：

- **Subject**：`GameManager` 作為被觀察者，維護觀察者列表
- **Observer**：`Tent` 類別實作觀察者介面
- **通知機制**：當回合改變時，`GameManager::notifyObservers()` 會通知所有註冊的觀察者

這個設計讓我體會到如何解耦系統中的依賴關係，讓物件之間可以動態地建立通知機制。

#### 3. Template Method（模板方法模式）

`Event` 基類使用虛函數定義了一套事件處理的模板流程，子類別（如 `ChestEvent`、`SpringEvent`）實作具體的行為。這展示了如何透過繼承和多型來實作可擴展的架構。

---

### 二、物件導向程式設計核心概念

#### 1. 繼承與多型

專案中建立了清晰的繼承階層：

- **Entity 階層**：`Entity` → `Role` / `Enemy`
- **Object 階層**：`Object` → `Shop` / `Event` / `Tent` / `Role`
- **Item 階層**：`Item` → `Weapon` / `Armor` / `Accessory` / `TeleportScroll` / `Tent`

透過虛函數（virtual function）和多型（polymorphism），實現了「同一介面，不同行為」的設計：

```cpp
// Object 基類定義虛函數介面
virtual void active(Role* role) = 0;
virtual vector<string> getAllChoose() = 0;
```

#### 2. 多重繼承

`Role` 類別同時繼承自 `Entity` 和 `Object`，這讓我理解了多重繼承的使用場景和潛在問題：

- **使用原因**：`Role` 既是實體（有生命值、攻擊力等屬性），也是遊戲世界中的物件（可互動、有位置）
- **注意事項**：需要處理可能的命名衝突和鑽石繼承問題

#### 3. 抽象類別與純虛函數

`Entity` 和 `Object` 都使用了純虛函數來定義抽象介面，這強制子類別必須實作特定方法，確保了設計的一致性。

---

### 三、C++ 語言特性應用

#### 1. 前向聲明（Forward Declaration）

大量使用了前向聲明來減少編譯相依性：

```cpp
class Role;
class Object;
```

這不僅提升了編譯效率，也降低了類別之間的耦合度。

#### 2. 靜態成員變數與方法

`GameManager` 中大量使用靜態成員來管理全域狀態：
- 靜態成員變數：`mapHeight`、`mapWidth`、`gameStatus`、`gameBoard`
- 靜態方法：`getInstance()`、`isPositionValid()`

讓我理解了靜態成員適用於不依賴物件實例的共享資源。

#### 3. 枚舉類（enum class）

使用 `enum class` 來定義遊戲狀態，提供了型別安全和命名空間隔離：

```cpp
enum class GAME_STATUS {
    MAP, 
    COMBAT,
    BACKPACK,
    INTERACTIVE
};
```

#### 4. STL 容器使用

大量使用 `std::vector`、`std::pair`、`std::unordered_map` 等 STL 容器，熟悉了現代 C++ 的容器使用方式。

---

### 四、遊戲開發架構

#### 1. 遊戲循環（Game Loop）

實作了固定時間步長的遊戲循環：

```cpp
const double_t GTIMELOG = 0.03;  // 每 0.03 秒更新一次
double timeFrame = (endT - startT) / CLOCKS_PER_SEC;
if (timeFrame >= GTIMELOG) {
    update(gKeyState);
}
```

這確保了遊戲邏輯更新與畫面渲染的獨立性。

#### 2. 狀態管理

使用 `GAME_STATUS` 枚舉來管理遊戲的不同狀態（地圖、戰鬥、背包、互動），並根據狀態切換不同的更新邏輯。這是狀態模式的簡化實作。

#### 3. 相機系統

實作了動態相機，會跟隨當前角色移動。理解了如何在 2D 遊戲中實現視角追蹤。

#### 4. 地圖系統

使用 2D 向量 `vector<vector<Rect>>` 來表示地圖，每個 `Rect` 包含：
- 可通行性（`canPass`）
- 可見性（`isVisible`）
- 關聯物件（`Object*`）

這展示了如何設計靈活的地圖資料結構。

#### 5. 碰撞檢測與互動

當角色移動到物件所在位置時，自動觸發互動。理解了簡單的碰撞檢測邏輯。

---

### 五、Windows API 應用

#### 1. Console API

使用 Windows Console API 來控制：
- 游標位置：`SetConsoleCursorPosition()`
- 文字顏色：`SetConsoleTextAttribute()`
- 視窗狀態：`GetConsoleWindow()`、`ShowWindow()`

這讓我理解了如何在控制台應用程式中實現更豐富的視覺效果。

#### 2. 輸入處理

使用 `_getch()` 來實現即時鍵盤輸入，不等待 Enter 鍵。這對遊戲開發很重要。

---

### 六、專案架構設計

#### 1. 類別職責劃分

專案中的類別職責劃分明確：
- `GameManager`：遊戲狀態管理、渲染控制
- `Entity`：角色屬性與戰鬥行為
- `Object`：互動物件的通用介面
- `Item`：物品系統基類
- `Rect`：地圖格子的資料結構

#### 2. 關注點分離

不同功能模組被分離到不同的類別中，提高了程式碼的可維護性和可擴展性。

#### 3. CMake 建置系統

使用 CMake 來管理專案建置，學會了如何組織大型 C++ 專案的編譯配置。

---

### 七、學習收穫與反思

#### 優點

1. **設計模式的理解**：透過實際應用，對 Singleton 和 Observer 模式有了更深的理解
2. **OOP 概念的掌握**：繼承、多型、封裝等核心概念得到實際運用
3. **遊戲開發基礎**：理解了遊戲循環、狀態管理、地圖系統等基礎概念
4. **程式碼組織能力**：學會了如何組織大型專案的結構

#### 可改進之處

1. **記憶體管理**：專案中大量使用原始指標，可以考慮使用智慧指標（`std::unique_ptr`、`std::shared_ptr`）來提升安全性
2. **錯誤處理**：缺少異常處理機制，可以加入更完善的錯誤處理
3. **程式碼重複**：部分功能有重複實作，可以進一步抽象
4. **測試**：缺少單元測試，可以加入測試框架

#### 未來方向

1. 學習現代 C++ 特性（C++11/14/17）
2. 深入研究更複雜的設計模式
3. 學習遊戲引擎的架構設計
4. 加強記憶體管理和效能優化

---

### 八、總結

這個專案讓我從理論走向實踐，將課堂上學到的物件導向程式設計知識應用到實際專案中。透過實作一個完整的遊戲系統，我不僅加深了對 C++ 語言的理解，也學到了軟體架構設計的基本原則。

正如《設計模式：可復用物件導向軟體基礎》一書所說：「模式不是發明，而是發現」。在這個專案中，我發現了設計模式如何自然地出現在實際問題的解決過程中。

---

## English Version

### Project Overview

This is a C++-based dungeon exploration game project, completed as the second assignment for the Object-Oriented Programming course at National Taiwan University of Science and Technology. Through implementing this project, I gained in-depth understanding of core OOP concepts, practical applications of design patterns, and fundamental game development architecture.

---

### I. Design Pattern Implementation

#### 1. Singleton Pattern

Implemented the Singleton pattern in the `GameManager` class to ensure only one game manager instance exists throughout execution. This taught me:

- **When to use**: Singleton pattern effectively prevents resource duplication when only one global instance is needed
- **Implementation details**: Private constructor, static instance pointer, `getInstance()` static method
- **Pros and cons**: While providing a global access point, it can create tight coupling and should be used cautiously

```cpp
// GameManager uses private constructor and static instance
static GameManager* instance;
static GameManager* getInstance();
```

#### 2. Observer Pattern

Implemented the Observer pattern in the `Tent` system, allowing tent objects to observe game round changes:

- **Subject**: `GameManager` acts as the subject, maintaining observer list
- **Observer**: `Tent` class implements observer interface
- **Notification mechanism**: When rounds change, `GameManager::notifyObservers()` notifies all registered observers

This design demonstrated how to decouple dependencies in a system, allowing objects to dynamically establish notification mechanisms.

#### 3. Template Method Pattern

The `Event` base class uses virtual functions to define a template process for event handling, with subclasses (like `ChestEvent`, `SpringEvent`) implementing specific behaviors. This demonstrates how inheritance and polymorphism can be used to create extensible architectures.

---

### II. Core Object-Oriented Programming Concepts

#### 1. Inheritance and Polymorphism

The project establishes clear inheritance hierarchies:

- **Entity hierarchy**: `Entity` → `Role` / `Enemy`
- **Object hierarchy**: `Object` → `Shop` / `Event` / `Tent` / `Role`
- **Item hierarchy**: `Item` → `Weapon` / `Armor` / `Accessory` / `TeleportScroll` / `Tent`

Through virtual functions and polymorphism, I achieved a "same interface, different behavior" design:

```cpp
// Object base class defines virtual function interface
virtual void active(Role* role) = 0;
virtual vector<string> getAllChoose() = 0;
```

#### 2. Multiple Inheritance

The `Role` class inherits from both `Entity` and `Object`, teaching me about multiple inheritance use cases and potential issues:

- **Reason for use**: `Role` is both an entity (has health, attack attributes) and a game world object (interactive, has position)
- **Considerations**: Need to handle potential naming conflicts and diamond inheritance problems

#### 3. Abstract Classes and Pure Virtual Functions

Both `Entity` and `Object` use pure virtual functions to define abstract interfaces, forcing subclasses to implement specific methods and ensuring design consistency.

---

### III. C++ Language Features Application

#### 1. Forward Declaration

Extensive use of forward declarations to reduce compilation dependencies:

```cpp
class Role;
class Object;
```

This not only improves compilation efficiency but also reduces coupling between classes.

#### 2. Static Members

`GameManager` extensively uses static members to manage global state:
- Static member variables: `mapHeight`, `mapWidth`, `gameStatus`, `gameBoard`
- Static methods: `getInstance()`, `isPositionValid()`

This taught me that static members are suitable for shared resources that don't depend on object instances.

#### 3. Enum Classes

Used `enum class` to define game states, providing type safety and namespace isolation:

```cpp
enum class GAME_STATUS {
    MAP, 
    COMBAT,
    BACKPACK,
    INTERACTIVE
};
```

#### 4. STL Container Usage

Extensive use of STL containers like `std::vector`, `std::pair`, `std::unordered_map`, familiarizing me with modern C++ container usage.

---

### IV. Game Development Architecture

#### 1. Game Loop

Implemented a fixed timestep game loop:

```cpp
const double_t GTIMELOG = 0.03;  // Update every 0.03 seconds
double timeFrame = (endT - startT) / CLOCKS_PER_SEC;
if (timeFrame >= GTIMELOG) {
    update(gKeyState);
}
```

This ensures independence between game logic updates and rendering.

#### 2. State Management

Used `GAME_STATUS` enum to manage different game states (map, combat, backpack, interactive), switching update logic based on state. This is a simplified implementation of the State pattern.

#### 3. Camera System

Implemented dynamic camera that follows the current character. Understood how to implement view tracking in 2D games.

#### 4. Map System

Used 2D vector `vector<vector<Rect>>` to represent the map, where each `Rect` contains:
- Passability (`canPass`)
- Visibility (`isVisible`)
- Associated object (`Object*`)

This demonstrates how to design flexible map data structures.

#### 5. Collision Detection and Interaction

When a character moves to an object's position, interaction is automatically triggered. Understood simple collision detection logic.

---

### V. Windows API Application

#### 1. Console API

Used Windows Console API to control:
- Cursor position: `SetConsoleCursorPosition()`
- Text color: `SetConsoleTextAttribute()`
- Window state: `GetConsoleWindow()`, `ShowWindow()`

This taught me how to achieve richer visual effects in console applications.

#### 2. Input Handling

Used `_getch()` to implement real-time keyboard input without waiting for Enter key, which is crucial for game development.

---

### VI. Project Architecture Design

#### 1. Class Responsibility Separation

Clear responsibility separation in project classes:
- `GameManager`: Game state management, rendering control
- `Entity`: Character attributes and combat behavior
- `Object`: Common interface for interactive objects
- `Item`: Item system base class
- `Rect`: Map tile data structure

#### 2. Separation of Concerns

Different functional modules are separated into different classes, improving code maintainability and extensibility.

#### 3. CMake Build System

Used CMake to manage project builds, learning how to organize compilation configuration for large C++ projects.

---

### VII. Learning Gains and Reflections

#### Strengths

1. **Design Pattern Understanding**: Through practical application, gained deeper understanding of Singleton and Observer patterns
2. **OOP Concept Mastery**: Core concepts like inheritance, polymorphism, and encapsulation were practically applied
3. **Game Development Fundamentals**: Understood fundamental concepts like game loops, state management, and map systems
4. **Code Organization Skills**: Learned how to organize structure for large projects

#### Areas for Improvement

1. **Memory Management**: Extensive use of raw pointers; could consider smart pointers (`std::unique_ptr`, `std::shared_ptr`) for improved safety
2. **Error Handling**: Lacks exception handling mechanisms; could add more comprehensive error handling
3. **Code Duplication**: Some functionality has repeated implementations; could be further abstracted
4. **Testing**: Lacks unit tests; could add testing framework

#### Future Directions

1. Learn modern C++ features (C++11/14/17)
2. Deepen understanding of more complex design patterns
3. Learn game engine architecture design
4. Strengthen memory management and performance optimization

---

### VIII. Conclusion

This project took me from theory to practice, applying OOP knowledge learned in class to real-world projects. Through implementing a complete game system, I not only deepened my understanding of the C++ language but also learned fundamental principles of software architecture design.

As stated in "Design Patterns: Elements of Reusable Object-Oriented Software": "Patterns are not invented, they are discovered." In this project, I discovered how design patterns naturally emerge in the process of solving practical problems.

---

**Date**: 2024  
**Course**: Object-Oriented Programming (NTUST)  
**Project**: Dungeon Game

