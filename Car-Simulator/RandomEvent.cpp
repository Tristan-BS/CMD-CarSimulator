#include "RandomEvent.h"
#include "Car.h"
#include <iostream>
#include <thread>
#include <chrono>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

char choice;

RandomEvent::RandomEvent(Car* car)
    : eventProbability(0.005f), // Starting probability
    probabilityIncreasePerKm(0.000004f), // Increase per km
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
    //DeerCrossing();
    RandomPerson();
}

void RandomEvent::DeerCrossing() {
    cout << "A deer is crossing the road! Do you want to swerve left or right? (l/r): ";
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

void RandomEvent::RandomPerson() {
    bool Psycho = (dist(rng) < 0.35f);
    bool Beggar = (dist(rng) < 0.55f);
    bool AllGood = (dist(rng) < 0.45f);

    cout << "There is a Person on the road, should I stop and ask if he needs help? (y/n): ";
    cin >> choice;

    if (choice == 'y') {
        if (Psycho) {
            cout << "Oh shit!! He were a f*cking psycho and hit my car, luckily he didn't hit me, but my car was a bit damaged." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));

            float bodyDamage = 5.25f;
            car->ApplyDamage(bodyDamage, 0);
        } else if (Beggar) {
            cout << "It is just a beggar... Should I give him something?" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));

            cerr << "NOT YET IMPLEMENTED" << endl;

            // TODO: Implement Money System
        } else {
            cout << "I stopped and asked, everything's fine. Thanks to me i guess :)" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
    else {
        cout << "Nah I'm Good, I guess i'll not going to stop today" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        if (Psycho) {
            cout << "I looked at the Person as I drove past him, he had a bat and looked very like a psycho. puhhh...... " << endl;
            std::this_thread::sleep_for(std::chrono::seconds(4));
        } else if (Beggar) {
            cout << "Maybe I should have stopped.. It was just a Beggar :(" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(4));
        } else {
            cout << "I'm glad I did'nt waste much time, everything was fine with the person :)" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(4));
        }
    }
}