// E:\dev\advanced_tic_tac_toe\src\main.cpp

#include "MainWindow.h"
#include "DatabaseManager.h"

#include <QApplication>
#include <QDir>
#include <QMessageBox>
#include <QStandardPaths>
#include <QDebug>
#include <QFile> // For loading stylesheet (optional but good practice)

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // --- State of the Art GUI Style ---
    // We define our entire blue and yellow theme here using QSS.
    QString styleSheet = R"(
        /* Main window and dialog styles */
        QMainWindow, QDialog {
            background-color: #2c3e50; /* Dark Slate Blue */
        }

        /* General widget styling */
        QWidget {
            color: #ecf0f1; /* Light Gray/White text */
            font-family: Arial, sans-serif;
        }

        /* Label styling */
        QLabel {
            color: #ecf0f1;
        }
        
        QLabel#statusLabel { /* Target the status label specifically */
            font-size: 16px;
            font-weight: bold;
            color: #f1c40f; /* Sunflower Yellow */
        }

        /* Push Button styling (Login, Register, New Game, etc.) */
        QPushButton {
            background-color: #f39c12; /* Amber/Orange */
            color: #2c3e50; /* Dark text on buttons */
            border: none;
            padding: 10px 20px;
            font-size: 14px;
            font-weight: bold;
            border-radius: 5px;
        }

        QPushButton:hover {
            background-color: #f1c40f; /* Sunflower Yellow on hover */
        }
        
        QPushButton:pressed {
            background-color: #d35400; /* A darker orange for pressed state */
        }

        /* Game Board Button Styling - this is special */
        QPushButton[isGameBoard="true"] {
            background-color: #34495e; /* A slightly lighter blue for the board */
            color: #f1c40f; /* Yellow for 'X' and 'O' */
            font-size: 48px;
            font-weight: bold;
            border: 2px solid #2c3e50; /* Border matches main background */
            border-radius: 5px;
        }
        
        QPushButton[isGameBoard="true"]:hover {
            background-color: #4a627a; /* Lighter blue on hover */
        }

        /* Line Edit styling (Username/Password fields) */
        QLineEdit {
            background-color: #ecf0f1;
            color: #2c3e50;
            border: 1px solid #bdc3c7;
            border-radius: 5px;
            padding: 8px;
            font-size: 14px;
        }
        
        QLineEdit:focus {
            border: 1px solid #f39c12; /* Highlight with yellow on focus */
        }
        
        /* Table styling for Game History */
        QTableWidget {
            background-color: #34495e;
            border: 1px solid #2c3e50;
            gridline-color: #4a627a;
        }
        QHeaderView::section {
            background-color: #4a627a;
            color: #ecf0f1;
            padding: 5px;
            border: 1px solid #2c3e50;
            font-weight: bold;
        }
    )";

    // Apply the master stylesheet to the entire application
    a.setStyleSheet(styleSheet);


    // --- Database Setup (from before) ---
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dataDir(dataPath);
    if (!dataDir.exists()) {
        dataDir.mkpath("."); 
    }
    QString dbPath = dataDir.filePath("game_data.db");
    qDebug() << "Using database at:" << dbPath;

    DatabaseManager& dbManager = DatabaseManager::getInstance();
    if (!dbManager.openDatabase(dbPath)) {
        QMessageBox::critical(nullptr, "Database Error", 
            QString("Could not create or open the database.\nChecked path: %1\n\nThe application will now exit.").arg(dbPath));
        return -1;
    }

    MainWindow w;
    return a.exec();
}