#include <iostream>
#include "Car.h"

#include <thread>
#include <regex>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

int Option;
int Repeated = 0;
float Value;
std::string RefillInput;

Car CDS;

int main() {
    // Starten Sie den Hintergrundthread
    CDS.StartBackgroundThread();

    while (true) {
        cout << endl << endl;
        cout << "----------          MENU          ----------" << endl;
        cout << "Balance: " << CDS.Balance << endl << endl;
        cout << "1. Drive" << endl;
        cout << "2. Check Fuel Capacity" << endl;
        cout << "3. Check Oil Capacity" << endl;
        cout << "4. Check Mileage" << endl;
        cout << "5. Inspect Car" << endl;
        cout << "6. Refill Fuel" << endl;
        cout << "7. Refill Oil" << endl;
        cout << "8. Repair Car" << endl;
        cout << "x. Show Inventory - Coming Soon" << endl;
        cout << "9. Exit" << endl;
        cout << "10. Admin Only" << endl;
        cout << "11. Admin Output" << endl;
        cout << "Your Input: ";

        cin >> Option;

        switch (Option) {
        case 1: {
            cout << "How many kilometres do you want to drive?" << endl;
            cout << "Your Input: ";
            cin >> Value;

            CDS.Drive(Value);
            break;
        }
        case 2: {
            cout << "Your Fuel Capacity: " << CDS.getFuelCapacity() << " litres." << endl;
            break;
        }
        case 3: {
            cout << "Your Oil Capacity: " << CDS.getOilCapacity() << " litres." << endl;
            break;
        }
        case 4: {
            cout << "Your Mileage with this car: " << CDS.getKilometres() << " kilometres" << endl;
            break;
        }
        case 5: {
            CDS.InspectCar();
            break;
        }
        case 6: {
            do {
                if (Repeated == 0) {
                    cout << "Luckily I've got an petrol can with me." << endl;
                }
                cout << "How much did I refilled the petrol can again?" << endl;
                cin >> RefillInput;

                if (RefillInput.find(',')) {
                    std::replace(RefillInput.begin(), RefillInput.end(), ',', '.');
                }
                Value = stof(RefillInput);

                if (Value > CDS.maxPetrolCanCapacity && !CDS.getAdminMode()) {
                    cout << "I dont think so... the maximum amount of litres are " << CDS.maxPetrolCanCapacity << " litres, in this petrol can." << endl << endl << endl;
                }
                else {
                    cout << "Perfect. Refilling now." << endl;
                    CDS.RefillFuel(Value);
                    break;
                }
            } while (true);
            break;
        }
        case 7: {
            do {
                if (Repeated == 0) {
                    cout << "Luckily I've got an Oil can with me." << endl;
                }
                cout << "How much did I refilled the Oil can again?" << endl;
                cin >> RefillInput;

                if (RefillInput.find(',')) {
                    std::replace(RefillInput.begin(), RefillInput.end(), ',', '.');
                }
                Value = stof(RefillInput);
                

                if (Value > CDS.maxOilCanCapacity && !CDS.getAdminMode()) {
                    cout << "I dont think so... the maximum amount of litres are " << CDS.maxOilCanCapacity << " litres, in this Oil can." << endl << endl << endl;
                }
                else {
                    cout << "Perfect. Refilling now." << endl;
                    CDS.RefillOil(Value);
                    break;
                }
            } while (true);
            break;
        }
        case 8: {
            CDS.RepairCar();
            break;
        }
        case 9: {
            CDS.StopBackgroundThread();
            exit(0);
        }
        case 10: {
            CDS.ApplyAdmin();
            break;
        }

        case 11: {
            if (CDS.getAdminMode()) {
                cout << endl << endl;
                cout << " ----------          ADMIN          ----------" << endl;
                cout << "Body Condition: " << CDS.getBodyCondition() << endl;
                cout << "Engine Condition: " << CDS.getEngineCondition() << endl;
                cout << "Fuel: " << CDS.getFuelCapacity() << endl;
                cout << "Oil: " << CDS.getOilCapacity() << endl;
                cout << "Mileage: " << CDS.getKilometres() << endl;
            }
            else {
                cout << "You're not registered as an Admin. sorry :(" << endl;
            }
            break;
        }
        }
    }
}
