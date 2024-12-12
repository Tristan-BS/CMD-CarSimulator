#pragma once

#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>


class Car {


public:
	void Drive(float Value);
	void RefillFuel(float Value);
	void RefillOil(float Value);
	void RepairCar();
	void InspectCar();

	float getKilometres();
	float getFuelCapacity();
	float getOilCapacity();
	float getEngineCondition();
	float getBodyCondition();
	float getAdminMode();

	void ApplyAdmin();

	// Variables

		// Maximums
	float maxFuelCapacity = 65;
	float maxOilCapacity = 4.75;
	float maxPetrolCanCapacity = 7.5;
	float maxOilCanCapacity = 1;

		// Booleans
	bool CanDrive = true;
	bool DeadEngine = false;
	bool DeadBody = false;
	bool isDriving = false;

	// Items
	double Balance = 0.0;


	// Threads
	void StartBackgroundThread();
	void StopBackgroundThread();

	void CheckForDriveAbility();
	std::atomic<bool> keepRunning{ true };
	std::thread backgroundThread;
private:

	// Setter
	void setKilometres(float Value);
	void setFuelCapacity(float Value);
	void setOilCapacity(float Value);

	void setEngineCondition(float Value);
	void setBodyCondition(float Value);
	void setAdminMode(bool Value);

	// Minigames
	void RepairEngineGame();
	void RepairBodyGame();

	// Variables
		// Conditions
	float EngineCondition = 100;
	float BodyCondition = 100;
	float MaxPercentage = 100;

		// Capacities
	float Fuel = 65;
	float Oil = 4.75;
	float Mileage = 0;

		// AdminMode / DevMode
	bool AdminMode = false;
};
