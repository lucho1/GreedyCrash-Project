#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

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

public:

	bool gameOver = false;
	uint coin_fx;
	uint gameOver_fx1;
	uint gameOver_fx2;
	uint gameOver_fx3;
	Timer fx_timer;
	bool play2 = true;
	bool play3 = false;

	PhysVehicle3D* vehicle = nullptr;
	float turn;
	float acceleration;
	float brake;
	vec3 IposP1 = vec3(0.0f, 0.0f, -92.0f);
	btVector3 IOrientation_vector;
	float boost_quantity = 100.0f;
	uint P1Coins = 6;
	uint boost_recover1 = 0;
	bool maxCreached1 = false;

	PhysVehicle3D* vehicle2 = nullptr;
	float turn2;
	float acceleration2;
	float brake2;
	vec3 IposP2 = vec3(0.0f, 0.0f, 92.0f);
	btVector3 IOrientation_vector2;
	float boost_quantity2 = 100.0f;
	uint P2Coins = 6;
	uint boost_recover2 = 0;
	bool maxCreached2 = false;

};
