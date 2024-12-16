#include "Car.h"
#include "GeneralFunctions.h"

#include <iostream>
#include <thread>
#include <regex>
#include <tuple>
#include <cmath>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

int Option;
int Repeated = 0;
float Value;
std::string StringInput;

Car CDS;
GeneralFunctions GF;

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
        cout << "X. Show Inventory - Coming Soon" << endl;
        cout << "9. Access to the petrol station " << endl;
        cout << "10. Exit" << endl;
        cout << "11. Version" << endl << endl;
        cout << "----------          ADMIN          ----------" << endl;
        cout << "12. Admin Only" << endl;
        cout << "13. Admin Output" << endl << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Your Input: ";

        cin >> Option;

        switch (Option) {
        case 1: {
            system("cls");
            cout << "How many kilometres do you want to drive?" << endl;
            cout << "Your Input: ";
            cin >> StringInput;

            Value = GF.ConvertCommaToFloat(StringInput);

            CDS.Drive(Value);
            break;
        }
        case 2: {
            system("cls");
            cout << "Your Fuel Capacity: " << CDS.getFuelCapacity() << " litres." << endl;
            break;
        }
        case 3: {
            system("cls");
            cout << "Your Oil Capacity: " << CDS.getOilCapacity() << " litres." << endl;
            break;
        }
        case 4: {
            system("cls");
            cout << "Your Mileage with this car: " << CDS.getKilometres() << " kilometres" << endl;
            break;
        }
        case 5: {
            system("cls");
            CDS.InspectCar();
            break;
        }
        case 6: {
            do {
                system("cls");
                if (Repeated == 0) {
                    cout << "Luckily I've got an petrol can with me." << endl;
                }
                cout << "How much did I refilled the petrol can again?" << endl;
                cin >> StringInput;

                Value = GF.ConvertCommaToFloat(StringInput);

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
            system("cls");
            do {
                if (Repeated == 0) {
                    cout << "Luckily I've got an Oil can with me." << endl;
                }
                cout << "How much did I refilled the Oil can again?" << endl;
                cin >> StringInput;
                Value = GF.ConvertCommaToFloat(StringInput);
                

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
            system("cls");
            CDS.RepairCar();
            break;
        }
        case 9: {
            system("cls");

            cout << endl << endl;
            cout << "----------          PETROL STATION          ----------" << endl;

            auto petrolList = CDS.getPetrolList();
            for (size_t i = 0; i < petrolList.size(); ++i) {
                float km = std::get<0>(petrolList[i]);
                float fc = std::get<1>(petrolList[i]);
                float p = std::get<2>(petrolList[i]);

                cout << i + 1 << ". Distance: " << km << "km" << "\nFuel Capacity: " << fc << "l" << "\nPrice per L:" << p << "$" << endl << endl;
            }
            

            cout << "Which gas station would you like to drive to?" << endl;
            cout << "Your Input: ";
            cin >> StringInput;


            break;
        }
        case 10: {
            CDS.StopBackgroundThread();
            exit(0);
        }
        case 11: {
            cout << "Current Version: " << VERSION_STRING << endl;
            break;
        }
        case 12: {
            CDS.ApplyAdmin();
            break;
        }

        case 13: {
            if (CDS.getAdminMode()) {
                system("cls");
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
        default: {
            cout << "Please try again" << endl;
            break;
        }
        }
    }
}
