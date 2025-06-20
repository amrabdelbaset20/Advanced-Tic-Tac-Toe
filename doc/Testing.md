# Testing Documentation
## Advanced Tic Tac Toe Game

**Version:** 1.0
**Date:** April, 2025

### 1. Testing Strategy
Our testing strategy combines unit tests for backend components and manual user acceptance testing (UAT) for the GUI.

- **Unit Testing:** The Google Test framework is used to test individual classes and functions in the `core` and `ai` modules. These tests verify the correctness of game logic (win/draw detection) and AI behavior (making optimal moves).
- **Integration Testing:** The interplay between the GUI, database, and game logic is tested implicitly by running the application. For instance, the login process tests the `LoginDialog`, `DatabaseManager`, and `User` class integration.
- **Manual UAT:** The final application is tested manually to ensure all GUI elements are responsive, workflows are intuitive, and all functional requirements from the SRS are met.

### 2. Test Cases

#### 2.1 Unit Test Cases (Automated)
- `BoardTest::Initialization`: Verifies that a new board is empty.
- `BoardTest::PlaceMark`: Verifies that marks are placed correctly.
- `GameTest::WinConditionRow`: Tests horizontal win detection.
- `GameTest::DrawCondition`: Tests a full board resulting in a draw.
- `AITest::BlocksWinningMove`: Verifies the AI defensively blocks an opponent's imminent win.
- `AITest::MakesWinningMove`: Verifies the AI plays a winning move when available.

### 3. Test Coverage
Automated test coverage focuses on the critical backend logic. The `Game`, `Board`, and `AI` classes have high test coverage for their public APIs. The `DatabaseManager` and GUI classes are primarily tested through manual UAT due to their dependency on external factors (database file, user interaction). The CI/CD pipeline ensures that all unit tests pass before any code is merged into the main branch.