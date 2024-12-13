#pragma once
#include "Version.h"
#include "RandomEvent.h"

#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

class Car {
public:
    Car();
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
    void ApplyDamage(float bodyDamage, float engineDamage); // Öffentlich machen

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
    RandomEvent randomEvent;

    // Setter
    void setKilometres(float Value);
    void setFuelCapacity(float Value);
    void setOilCapacity(float Value);

    void setEngineCondition(float Value);
    void setBodyCondition(float Value);
    void setAdminMode(bool Value);

    // Repair Menus
    void RepairMenu();
    void RepairEngineMenu();
    void RepairBodyMenu();
    void RepairBothMenu();

    void RepairEngineGame(int Value);
    void RepairBodyGame(int Value);

    // Variables
    // Conditions
    float EngineCondition = 100;
    float BodyCondition = 100;
    float MaxPercentage = 100;

    // Capacities
    float Fuel = 65;
    float Oil = 4.75;
    float Mileage = 0;

    // Repair Types
    int FullRepair = 100;
    int PartialRepair = 50;
    int QuickRepair = 20;

    // AdminMode / DevMode
    bool AdminMode = false;
};