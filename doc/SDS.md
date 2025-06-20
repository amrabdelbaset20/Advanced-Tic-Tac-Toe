# Software Design Specification (SDS)
## Advanced Tic Tac Toe Game

**Project By:** Dr. Omar Nasr, and ChatGPT
**Date:** April, 2025
**Version:** 1.0

---

### 1. Introduction
This document outlines the software architecture and high-level design for the "Advanced Tic Tac Toe Game". It is intended for the development team to understand the system's structure and components.

---

### 2. System Architecture
The system follows a Model-View-Controller (MVC) architectural pattern, separating the internal data model and logic from the user interface.

- **Model:** Consists of the core game logic (`Game`, `Board`), AI logic (`AI`), and data management (`DatabaseManager`, `User`). This part is independent of the UI.
- **View:** Consists of the Qt GUI classes (`MainWindow`, `GameWindow`, `LoginDialog`). It is responsible for all rendering and user input.
- **Controller:** The Qt signals and slots mechanism acts as the controller, connecting user actions in the View to updates in the Model, and then refreshing the View with the new state.

---

### 3. High-Level Design

#### 3.1 Class Diagram
This UML Class Diagram shows the main classes and their relationships.

```mermaid
classDiagram
    class MainWindow {
        -currentUser : User
        +showLoginDialog()
        +onLoginSuccess()
        +showGameHistory()
    }
    class LoginDialog {
        +signals:
        +loginRequested(string, string)
        +registrationRequested(string, string)
    }
    class GameWindow {
        -game : Game
        -ai : AI
        +updateBoard()
        +handleCellClick(int)
        +displayResult(string)
    }
    class Game {
        -board : Board
        -currentPlayer : Player
        +makeMove(int, int) bool
        +checkWin() Player
        +isDraw() bool
        +switchPlayer()
    }
    class Board {
        -grid[3][3] : char
        +isCellEmpty(int, int) bool
        +placeMark(int, int, char)
    }
    class AI {
        +findBestMove(Board) : int
        -minimax(Board, int, bool, int, int)
    }
    class DatabaseManager {
        -db : QSqlDatabase
        +getInstance() : DatabaseManager*
        +validateUser(string, string) : bool
        +addUser(string, string) : bool
        +saveGame(Game, User)
        +getGameHistory(User) : list
    }
    class User {
        -id : int
        -username : string
    }
    class Player {
        -symbol : char
    }

    MainWindow --|> QMainWindow
    LoginDialog --|> QDialog
    GameWindow --|> QWidget

    MainWindow *-- LoginDialog
    MainWindow *-- GameWindow
    GameWindow *-- Game
    GameWindow *-- AI
    Game *-- Board
    Game *-- Player

    DatabaseManager ..> User
    MainWindow ..> User
    MainWindow ..> DatabaseManager
    LoginDialog ..> DatabaseManager