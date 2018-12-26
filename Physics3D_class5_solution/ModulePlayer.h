#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f


struct defCar {

	PhysVehicle3D* vehicle = nullptr;

	float turn;
	float acceleration;
	float brake;

	vec3 Ipos = vec3(0.0f, 0.0f, 0.0f);
	btVector3 IOrientation_vector;

	float boost_quantity = 100.0f;
	uint Coins = 6;
	uint boost_recover = 0;
	bool maxCreached = false;
	bool boosting = false;
};


class ModulePlayer : public Module
{
public:

	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

private:

	void HandleInput_P1();
	void HandleInput_P2();

	VehicleInfo SetDefaultCar();
	void SetConstCarProperties(VehicleInfo* car, float connection_height, float wheel_radius, float wheel_width, float suspensionRestLength);

	void RestartCar(btVector3 Iorientation, PhysVehicle3D* vehicle, vec3 Ipos, bool inverted = false);
	void OnCollision(PhysBody3D* bA, PhysBody3D* bB);
	void Restart();
	bool LimitsReached(defCar vehicle);

public:

	
	uint coin_fx;
	uint loseCoin_fx;
	uint shout_fx;

	defCar veh1;
	defCar veh2;

};
