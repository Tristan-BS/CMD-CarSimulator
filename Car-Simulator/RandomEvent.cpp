#include "RandomEvent.h"
#include "Car.h"
#include <iostream>
#include <thread>
#include <chrono>

using std::cout;
using std::cin;
using std::endl;

RandomEvent::RandomEvent(Car* car)
    : eventProbability(0.005f), // Starting probability
    probabilityIncreasePerKm(0.000003f), // Increase per km
    rng(std::random_device{}()),
    dist(0.0f, 1.0f),
    car(car) {
}

bool RandomEvent::CheckForEvent(float distanceDriven) {
    eventProbability += distanceDriven * probabilityIncreasePerKm;
    if (eventProbability > 0.5f) {
        eventProbability = 0.5f; // Maximum of 50% Chance
    }

    return dist(rng) < eventProbability;
}

void RandomEvent::ExecuteEvent() {
    DeerCrossing();
}

void RandomEvent::DeerCrossing() {
    cout << "A deer is crossing the road! Do you want to swerve left or right? (l/r): ";
    char choice;
    cin >> choice;

    bool accident = (dist(rng) < 0.5f); // 50% Chance

    if (accident) {
        cout << "You had an accident! Your car took damage." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        float bodyDamage = 20.75f;
        float engineDamage = 2.5f;

        car->ApplyDamage(bodyDamage, engineDamage);
    }
    else {
        cout << "You avoided the deer safely." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}