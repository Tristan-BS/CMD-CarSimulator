#include <iostream>
#include "Car.h"

#include <thread>
#include <chrono>

using std::cout;
using std::cerr;
using std::endl;

void Car::Drive(float Kilometres) {
    const float fuelConsumptionPerHalfKm = 0.04f;

    if (CanDrive && !DeadEngine && !DeadBody) {
        
        for (float i = 0; i <= Kilometres && CanDrive; i += 0.5f) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            float fuelConsumed = (i / 0.5f) * fuelConsumptionPerHalfKm;
            float remainingFuel = getFuelCapacity() - fuelConsumed;

            if (remainingFuel <= 0) {
                cout << "Out of Fuel! You can no longer drive without fuel o.O" << endl;
                CanDrive = false;
                break;
            } else if (!CanDrive) {
                cout << "The car can no longer drive, maybe check it?" << endl;
                break;
            }

            if (!i == 0) {
                cout << "Drove: " << i << " kilometres..." << endl;
            }

            setFuelCapacity(remainingFuel);
            setKilometres(i);
        }
        if (getFuelCapacity() != 0 && CanDrive) {
            cout << "Finished driving. Im going to rest now." << endl;
        }

    } else if (!CanDrive) {
        cout << "You can't drive. You have to figure out why!" << endl;
    }
}

void Car::RefillFuel(float Value) {
    setFuelCapacity(Value);
    std::this_thread::sleep_for(std::chrono::seconds(4));
    cout << "Finished, i refilled it!" << endl;
}

void Car::RefillOil(float Value) {
    // Implementierung folgt
    return;
}

void Car::RepairCar() {
    // Implementierung folgt
    return;
}

void Car::InspectCar() {
    if (!CanDrive) {
        cout << "I should take a closer look, just to be sure. This could take a while..." << endl;

        if (DeadEngine) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            cout << "It seems the Engine is damaged, its smoking a lot..." << endl;
        } else if (DeadBody) {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            cout << "Wow... I must've hit a few things to make the body look like that." << endl;
        } else if (getFuelCapacity() == 0) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            cout << "Really? I'm out of Fuel bro...." << endl;
        }
    }
}

// GETTER

float Car::getKilometres() {
    return Mileage;
}

float Car::getFuelCapacity() {
    return Fuel;
}

float Car::getOilCapacity() {
    return Oil;
}

float Car::getEngineCondition() {
    return EngineCondition;
}

float Car::getBodyCondition() {
    return BodyCondition;
}

// SETTER

void Car::setKilometres(float Value) {
    Mileage = Value;
}

void Car::setFuelCapacity(float Value) {
    Fuel = Value;
}

void Car::setOilCapacity(float Value) {
    Oil = Value;
}

void Car::setEngineCondition(float Value) {
    EngineCondition = Value;
}

void Car::setBodyCondition(float Value) {
    BodyCondition = Value;
}