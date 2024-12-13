#pragma once
#include <random>

class Car;

class RandomEvent {
public:
    RandomEvent(Car* car);
    bool CheckForEvent(float distanceDriven);
    void ExecuteEvent();

private:
    float eventProbability;
    float probabilityIncreasePerKm;
    std::mt19937 rng;
    std::uniform_real_distribution<float> dist;
    Car* car;

    void DeerCrossing();
    void RandomPerson();
};