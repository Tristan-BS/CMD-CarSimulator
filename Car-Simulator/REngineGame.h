#pragma once

#include <vector>
#include <thread>
#include <atomic>
#include <functional>

class REngineGame {
public: 
	REngineGame();
	bool StartGame(int Value);

private:

	void setDifficulty(int Value);

	// Grid Variables
	std::vector<std::vector<char>> Grid;
	int GridSize;
	int EmptyCells;
	int ErrorCount;
	std::atomic<bool> GameRunning;

	// Time Variables
	double EASY_Time = 120;
	double MEDIUM_Time = 60;
	double HARD_Time = 30;

	// Methods
	void InitializeGrid();
	void DisplayGrid();
	void ProcessInput();
	bool RunGame();
	void Timer();

	// Other Vars
	int Difficulty;
	double TimeLimit;
};