#include "REngineGame.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;

REngineGame::REngineGame() : GridSize(10), EmptyCells(0), ErrorCount(0), GameRunning(false) {
    srand(static_cast<unsigned int>(time(0)));
}

bool REngineGame::StartGame(int difficulty) {
    setDifficulty(Difficulty);
    return RunGame();
}

void REngineGame::setDifficulty(int Value) {
    Difficulty = Value;
}

void REngineGame::InitializeGrid() {
    GridSize = 10; // Beispielgröße
    Grid.resize(GridSize, std::vector<char>(GridSize, 'O'));

    switch (Difficulty) {
    case 1:
        EmptyCells = 10; // Leicht
        break;
    case 2:
        EmptyCells = 20; // Mittel
        break;
    case 3:
        EmptyCells = 30; // Schwer
        break;
    default:
        EmptyCells = 10;
        break;
    }

    for (int i = 0; i < EmptyCells; ++i) {
        int row = rand() % GridSize;
        int col = rand() % GridSize;
        Grid[row][col] = ' ';
    }
}

void REngineGame::DisplayGrid() {
    cout << "  ";
    for (int col = 0; col < GridSize; ++col) {
        cout << col << " ";
    }
    cout << endl;

    for (int row = 0; row < GridSize; ++row) {
        cout << row << " ";
        for (int col = 0; col < GridSize; ++col) {
            cout << Grid[row][col] << " ";
        }
        cout << endl;
    }
}

void REngineGame::ProcessInput() {
    int row, col;
    cout << "Enter row: ";
    cin >> row;
    cout << "Enter column: ";
    cin >> col;

    if (row >= 0 && row < GridSize && col >= 0 && col < GridSize) {
        if (Grid[row][col] == ' ') {
            Grid[row][col] = 'O';
        }
        else if (Grid[row][col] == 'O') {
            cout << "This cell is already filled. Try again." << endl;
        }
        else {
            Grid[row][col] = 'X';
            ++ErrorCount;
        }
    }
    else {
        cout << "Invalid input. Try again." << endl;
    }
}

bool REngineGame::RunGame() {
    InitializeGrid();
    TimeLimit = (Difficulty == 1) ? EASY_Time : (Difficulty == 2) ? MEDIUM_Time : HARD_Time;

    GameRunning = true;
    std::thread timerThread(&REngineGame::Timer, this);

    bool gameCompleted = false;

    while (GameRunning) {
        DisplayGrid();
        ProcessInput();

        bool allFilled = true;
        for (int row = 0; row < GridSize; ++row) {
            for (int col = 0; col < GridSize; ++col) {
                if (Grid[row][col] == ' ') {
                    allFilled = false;
                    break;
                }
            }
            if (!allFilled) {
                break;
            }
        }

        if (allFilled) {
            GameRunning = false;
            gameCompleted = true;
            cout << "Minigame completed, Well done!" << endl;
        }
    }

    timerThread.join();

    if (!gameCompleted) {
        cout << "Game over! Errors: " << ErrorCount << endl;
    }

    return gameCompleted;
}



void REngineGame::Timer() {
    std::this_thread::sleep_for(std::chrono::seconds(static_cast<int>(TimeLimit)));
    GameRunning = false;
}
