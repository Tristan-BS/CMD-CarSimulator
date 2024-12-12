#pragma once

#include <iostream>


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

	float maxFuelCapacity = 65;
	float maxOilCapacity = 4.5;
	float maxPetrolCanCapacity = 7.5;
	bool CanDrive = true;
	bool DeadEngine = false;
	bool DeadBody = false;
	bool isDriving = false;

private:
	void setKilometres(float Value);
	void setFuelCapacity(float Value);
	void setOilCapacity(float Value);

	void setEngineCondition(float Value);
	void setBodyCondition(float Value);

	float EngineCondition = 100;
	float BodyCondition = 100;
	float Fuel = 65;
	float Oil = 4.5;
	float Mileage = 0;
};
