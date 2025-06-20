# Software Requirements Specification (SRS)
## Advanced Tic Tac Toe Game

**Project By:** Dr. Omar Nasr, and ChatGPT
**Date:** April, 2025
**Version:** 1.0

---

### 1. Introduction

#### 1.1 Purpose
This document provides a detailed description of the requirements for the "Advanced Tic Tac Toe Game". It outlines the functional and non-functional requirements, system features, and constraints to guide the design and development of the project.

#### 1.2 Scope
The project is an advanced version of Tic Tac Toe featuring:
- A graphical user interface (GUI).
- Player-vs-Player (PvP) and Player-vs-AI (PvE) modes.
- User authentication (login/registration).
- Personalized game history tracking and replay.
- A challenging AI opponent using the Minimax algorithm.
- Continuous Integration and Deployment (CI/CD) pipeline.

#### 1.3 Definitions, Acronyms, and Abbreviations
- **AI:** Artificial Intelligence
- **CI/CD:** Continuous Integration/Continuous Deployment
- **GUI:** Graphical User Interface
- **SRS:** Software Requirements Specification
- **SDS:** Software Design Specification
- **UML:** Unified Modeling Language
- **PvP:** Player versus Player
- **PvE:** Player versus Environment (AI)

---

### 2. Overall Description

#### 2.1 Product Perspective
The product is a standalone desktop application developed in C++ using the Qt framework. It will be a complete, self-contained game that manages its own user data via an integrated SQLite database.

#### 2.2 Product Features
- **User Management:** Secure registration and login for players.
- **Game Modes:** Support for both two-player local games and single-player games against an AI.
- **Interactive Gameplay:** A user-friendly GUI for all interactions.
- **Game History:** Storage and retrieval of past games for review and analysis.
- **Intelligent AI:** A formidable AI opponent to challenge players.

---

### 3. Specific Requirements

#### 3.1 Functional Requirements

##### 3.1.1 User Authentication
- **FR1:** The system shall allow new users to create a player account with a unique username and a password.
- **FR2:** The system shall securely store user passwords using a strong hashing algorithm (e.g., SHA-256).
- **FR3:** The system shall allow registered users to log in using their credentials.
- **FR4:** The system shall prevent access to game history and gameplay until a user is logged in.

##### 3.1.2 Game Modes
- **FR5:** The system shall provide a main menu where logged-in users can select a game mode: Player vs. Player or Player vs. AI.
- **FR6:** In PvP mode, the system shall allow two players to take turns on the same computer.
- **FR7:** In PvE mode, the system shall allow a human player to play against an AI opponent.

##### 3.1.3 Gameplay
- **FR8:** The system shall display a 3x3 Tic Tac Toe grid.
- **FR9:** Players shall be able to make a move by clicking on an empty cell.
- **FR10:** The system shall alternate turns between 'X' and 'O'.
- **FR11:** The system shall detect and announce a win, loss, or draw condition.
- **FR12:** The system shall allow players to start a new game after the current one ends.

##### 3.1.4 AI Opponent
- **FR13:** The AI shall make strategic moves to attempt to win or draw the game.
- **FR14:** The AI's decision-making will be powered by the Minimax algorithm, optimized with alpha-beta pruning.

##### 3.1.5 Game History
- **FR15:** The system shall automatically save the result of every completed game (players, winner, date).
- **FR16:** The system shall provide a screen where users can view a list of their past games.
- **FR17:** Users shall be able to select a game from the history to view its final board state or a step-by-step replay.

#### 3.2 Non-Functional Requirements

- **NFR1 (Performance):** The AI's move calculation should take less than 500ms on a standard modern CPU. GUI actions should have a response time of less than 100ms.
- **NFR2 (Security):** User passwords must never be stored in plaintext. Hashing must be used.
- **NFR3 (Usability):** The GUI must be intuitive and easy to navigate for non-technical users.
- **NFR4 (Portability):** The application should be compilable and runnable on major desktop platforms (Windows, macOS, Linux) with minimal changes.
- **NFR5 (Maintainability):** The code must adhere to the Google C++ Style Guidelines.

#### 3.3 System Constraints
- **C1:** The application must be developed using C++.
- **C2:** The GUI framework must be Qt.
- **C3:** The testing framework must be Google Test.
- **C4:** Version control must be Git, hosted on GitHub.
- **C5:** The database must be SQLite.