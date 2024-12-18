// Car.cpp
#include "Car.h"
#include "REngineGame.h"
#include "RandomEvent.h"
#include "GeneralFunctions.h"

#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <random>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

int Answer;

Car::Car() : randomEvent(this) {}
extern GeneralFunctions GF;

void Car::Drive(float Kilometres) {
    const float fuelConsumptionPerHalfKm = 0.075f;
    const float OilConsumptionPerHalfKm = 0.025f;
    const float EngineDamagePerKM = 0.25f;
    const float BodyDamagePerKM = 0.10f;

    float initialMileage = getKilometres();

    for (float i = 0; i <= Kilometres; i += 0.5f) {
        if (!CanDrive || DeadEngine || DeadBody) {
            cout << "You can't drive. You have to figure out why!" << endl;
            break;
        }

        if (!AdminMode) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        float remainingFuel = getFuelCapacity() - OilConsumptionPerHalfKm;
        float remainingOil = getOilCapacity() - OilConsumptionPerHalfKm;

        if (remainingFuel <= 0) {
            cout << "Out of Fuel! You can no longer drive without fuel o.O" << endl;
            CanDrive = false;
            break;
        }
        if (remainingOil <= 0) {
            cout << "Out of Oil! You can no longer drive without oil o.O" << endl;
            CanDrive = false;
            break;
        }

        if (i != 0) {
            system("cls");

            ShowProgressBar(i, Kilometres);

            cout << "Drove: " << i << " kilometres..." << endl;
        }

        setFuelCapacity(remainingFuel);
        setOilCapacity(remainingOil);
        setKilometres(initialMileage + i);

        float newEngineCondition = getEngineCondition() - EngineDamagePerKM;
        float newBodyCondition = getBodyCondition() - BodyDamagePerKM;

        setEngineCondition(newEngineCondition < 0 ? 0 : newEngineCondition);
        setBodyCondition(newBodyCondition < 0 ? 0 : newBodyCondition);

        // �berpr�fen Sie, ob ein zuf�lliges Ereignis auftritt
        if (randomEvent.CheckForEvent(i)) {
            randomEvent.ExecuteEvent();
        }
    }

    if (getFuelCapacity() != 0 && CanDrive) {
        cout << "Finished driving. Im going to rest now." << endl;
    }
}

void Car::ApplyDamage(float bodyDamage, float engineDamage) {
    setBodyCondition(getBodyCondition() - bodyDamage);
    setEngineCondition(getEngineCondition() - engineDamage);
}

void Car::RefillFuel(float Value) {
    float OverMax = getFuelCapacity() + Value;

    if (AdminMode) {
        setFuelCapacity(50000);
    }
    else if (OverMax > maxFuelCapacity) {
        cout << "I would overfill my fuel tank if I put it all in, so I only fill it to the limit." << endl;
        setFuelCapacity(maxFuelCapacity);
    }
    else {
        setFuelCapacity(getFuelCapacity() + Value);
    }

    if (!AdminMode) {
        std::this_thread::sleep_for(std::chrono::seconds(4));
        cout << "Finished, i refilled the Fuel!" << endl;
    }
}

void Car::RefillOil(float Value) {
    float OverMax = getOilCapacity() + Value;

    if (AdminMode) {
        setOilCapacity(50000);
    }
    else if (OverMax > maxOilCapacity) {
        cout << "I would overfill my oil tank if I put it all in, so I only fill it to the limit." << endl;
        setOilCapacity(maxOilCapacity);
    }
    else {
        setOilCapacity(getOilCapacity() + Value);
    }

    if (!AdminMode) {
        std::this_thread::sleep_for(std::chrono::seconds(4));
        cout << "Finished, i refilled the Oil!" << endl;
    }
}

void Car::RepairCar() {
    do {
        cout << endl << endl;
        cout << " ----------          Repair Menu          ----------" << endl;
        cout << "What do you think is the Problem with the Car?" << endl;
        cout << "1. Engine" << endl;
        cout << "2. Body" << endl;
        cout << "3. Fuel" << endl;
        cout << "4. Go Back" << endl;
        cout << "Your Input: ";

        cin >> Answer;

        system("cls");
        switch (Answer) {
        case 1: {
            if (DeadEngine) {
                cout << "Yup. Thats not looking good.... Engine is at " << getEngineCondition() << "% engine performance." << endl;
                RepairMenu();
                DeadEngine = false;
                CanDrive = true;
            }
            else {
                cout << "The engine seems to be fine." << endl;
            }
            break;
        }
        case 2: {
            if (DeadBody) {
                cout << "The car... the car is completely dented, scratched and broken - what have I done to it? :=O" << endl;
                RepairBodyMenu();
                DeadBody = false;
                CanDrive = true;
            }
            else {
                cout << "The body seems to be fine." << endl;
            }
            break;
        }
        case 3: {
            cout << "Uhm. What? I'm a mechanic, not a petrol station. I should refill my car at a petrol station." << endl;
            break;
        }
        case 4: {
            cout << "Exiting repair mode." << endl;
            return;
        }
        default: {
            cout << "Uhhhhmmm. No? Something else please?" << endl;
            break;
        }
        }
    } while (true);
}

void Car::InspectCar() {
    if (!CanDrive) {
        cout << endl << endl;
        cout << " ----------          Inspection          ----------" << endl;
        cout << "I should take a closer look, just to be sure. This could take a while..." << endl;

        if (DeadEngine) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            cout << "It seems the Engine is damaged, its smoking a lot..." << endl;
        }
        else if (DeadBody) {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            cout << "Wow... I must've hit a few things to make the body look like that." << endl;
        }
        else if (getFuelCapacity() == 0) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            cout << "Really? I'm out of Fuel bro...." << endl;
        }
    }
    else {
        cout << "Everything seems to be ok :)" << endl;
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

float Car::getAdminMode() {
    return AdminMode;
}

std::vector<std::tuple<float,float,float>> Car::getPetrolList() {  
   std::vector<std::tuple<float, float, float>> List = {};

   for (int i = 0; i < 5; ++i) {  
       float temp_Kilometres = GF.roundToTwoDecimalPlaces(getRandomKilometres(i+1));
       float temp_FuelCapacity = GF.roundToTwoDecimalPlaces(getPSFuelCapacity(i+1));
       float temp_PricePerL = GF.roundToTwoDecimalPlaces(getPSPricePerLitre(i+1));
       if (temp_Kilometres >= 0 && temp_FuelCapacity >= 0 && temp_PricePerL >= 0) {
           List.emplace_back(temp_Kilometres, temp_FuelCapacity, temp_PricePerL);
       }
   }
   return List;
}

void Car::ApplyAdmin() {
    std::string pw;

    cout << "Enter the Admin password" << endl;
    cin >> pw;

    if (pw == "12345") {
        if (AdminMode) {
            setAdminMode(false);
            cout << "Deactivated Adminmode" << endl;
        }
        else {
            setAdminMode(true);
            cout << "Activated Adminmode" << endl;
        }
    }
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

void Car::setAdminMode(bool Value) {
    AdminMode = Value;
}

// Games

void Car::RepairMenu() {
    cout << endl << endl;
    cout << " ----------          Repair - Menu          ----------" << endl;
    cout << "1. Repair Engine" << endl;
    cout << "2. Repair Body" << endl;
    cout << "3. Repair Both" << endl;
    cout << "4. Go Back" << endl;
    cout << "Your Input: ";
    cin >> Answer;

    switch (Answer) {
    case 1: {
        RepairEngineMenu();
        break;
    }
    case 2: {
        RepairBodyMenu();
        break;
    }
    case 3: {
        RepairBothMenu();
        break;
    }
    case 4: {
        system("cls");
        cout << "Return to Menu" << endl;
        return;
    }
    default: {
        system("cls");
        cout << "What are you talking about? Choose something..." << endl;
        break;
    }
    }
}

void Car::RepairEngineMenu() {
    cout << endl << endl;
    cout << " ----------          Repair Engine - Menu          ----------" << endl;
    cout << "1. Full Repair" << endl;
    cout << "2. Partial Repair" << endl;
    cout << "3. Quick Fix" << endl;
    cout << "4. Go Back" << endl;
    cout << "Your Input: ";
    cin >> Answer;

    switch (Answer) {
    case 1: {
        RepairEngineGame(1);
        break;
    }
    case 2: {
        RepairEngineGame(2);
        break;
    }
    case 3: {
        RepairEngineGame(3);
        break;
    }
    case 4: {
        system("cls");
        cout << "Return to Menu" << endl;
        return;
    }
    default: {
        system("cls");
        cout << "What are you talking about? Choose something..." << endl;
        break;
    }
    }
}

void Car::RepairBodyMenu() {
}

void Car::RepairBothMenu() {
}

void Car::RepairEngineGame(int difficulty) {
    REngineGame EG;
    bool success = EG.StartGame(difficulty);
    if (success) {
        int errorCount = EG.getErrorCount(); // Fehleranzahl abrufen
        float repairAmount = 20.0f - (errorCount * 1.0f); // 1% weniger pro Fehler
        if (repairAmount < 0) {
            repairAmount = 0; // Sicherstellen, dass der Reparaturwert nicht negativ ist
        }
        setEngineCondition(getEngineCondition() + repairAmount);
        if (getEngineCondition() > MaxPercentage) {
            setEngineCondition(MaxPercentage);
        }
        cout << "Engine condition improved by " << repairAmount << "%!" << endl;
    }
}

void Car::RepairBodyGame(int Difficulty) {
    setBodyCondition(MaxPercentage);
}

// Threads

void Car::CheckForDriveAbility() {
    bool previousCanDrive = true;

    while (keepRunning) {
        if (getEngineCondition() <= 5 || getBodyCondition() <= 0.5f || getFuelCapacity() <= 0 || getOilCapacity() <= 0.000f) {
            CanDrive = false;

            if (previousCanDrive) {
                if (getEngineCondition() <= 5) {
                    DeadEngine = true;
                }
                if (getBodyCondition() <= 0.5f) {
                    DeadBody = true;
                }
            }
        }
        else {
            CanDrive = true;
            DeadEngine = false;
            DeadBody = false;
        }

        previousCanDrive = CanDrive;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Car::StartBackgroundThread() {
    keepRunning = true;
    backgroundThread = std::thread(&Car::CheckForDriveAbility, this);
}

void Car::StopBackgroundThread() {
    keepRunning = false;
    if (backgroundThread.joinable()) {
        backgroundThread.join();
    }
}

void Car::ShowProgressBar(float i, float Kilometres) {
    float progress = (i / Kilometres) * PBHashtagCounter;
    int progressBars = static_cast<int>(progress);

    cout << "Progress: [";
    for (int j = 0; j < PBHashtagCounter; ++j) {
        if (j < progressBars) {
            cout << "#";
        }
        else {
            cout << " ";
        }
    }
    cout << "] " << static_cast<int>((progress / PBHashtagCounter) * 100) << "%\n";

}

float Car::getRandomKilometres(int Distance) {
    float min = 5;
    float max = 100;

    std::random_device rd;
    std::mt19937 gen(rd());

    switch (Distance) {
    case 1: {
        min = 15;
        max = 50;
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }
    case 2: {
        min = 25;
        max = 75;
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }
    case 3: {
        min = 25;
        max = 100;
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }
    case 4: {
        min = 40;
        max = 150;
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }
    case 5: {
        min = 50;
        max = 200;
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }
    default: {
        cout << "Error!" << endl;
        return -1.0;
    }
    }
}

float Car::getPSFuelCapacity(int Distance) {
    float min = 0.0;
    float max = 250;

    std::random_device rd;
    std::mt19937 gen(rd());

    switch (Distance) {
    case 1: {
        min = 5;
        max = 50;
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }
    case 2: {
        min = 15;
        max = 100;
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }
    case 3: {
        min = 25;
        max = 150;
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }
    case 4: {
        min = 45;
        max = 200;
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }
    case 5: {
        min = 50;
        max = 215;
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }
    default: {
        cout << "Error!" << endl;
        return -1.0;
    }
    }
}

float Car::getPSPricePerLitre(int Distance) {
    float min = 0.0;
    float max = 100;

    std::random_device rd;
    std::mt19937 gen(rd());

    switch (Distance) {
    case 1: {
        min = 1;
        max = 2;
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }
    case 2: {
        min = 1;
        max = 3;
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }
    case 3: {
        min = 1;
        max = 4;
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }
    case 4: {
        min = 1;
        max = 5;
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }
    case 5: {
        min = 1;
        max = 6.5;
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }
    default: {
        cout << "Error!" << endl;
        return -1.0;
    }
    }
}
