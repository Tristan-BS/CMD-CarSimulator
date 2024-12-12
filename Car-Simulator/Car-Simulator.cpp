#include <iostream>
#include "Car.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

int Option;
float Value;

Car CDS;

int main() {
    while(true) {
        cout << endl << endl;
        cout << " ----------          MENU          ----------" << endl;
        cout << "1. Drive" << endl;
        cout << "2. Check Fuel Capacity" << endl;
        cout << "3. Check Oil Capacity" << endl;
        cout << "4. Check Mileage" << endl;
        cout << "5. Inspect Car" << endl;
        cout << "6. Refill Fuel" << endl;
        cout << "7. Refill Oil" << endl;
        cout << "8. Exit" << endl;

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
        }
        case 6: {
            int repeated = 0;
            do {
                if (repeated == 0) {
                    cout << "Luckily I've got an petrol can with me." << endl;
                }
                cout << "How much did I refilled the petrol can again?" << endl;
                cin >> Value;

                if (Value > CDS.maxPetrolCanCapacity) {
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
        }
    }
}