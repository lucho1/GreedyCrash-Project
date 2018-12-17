#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:

	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	PhysBody3D * CreateSlope(Cube &slope, vec3 sizes, vec3 pos, float angle);

public:

	PhysBody3D *pb_limit1 = nullptr;
	Cube limit1;

	PhysBody3D *pb_limit2 = nullptr;
	Cube limit2;

	PhysBody3D *pb_limit3 = nullptr;
	Cube limit3;

	PhysBody3D *pb_limit4 = nullptr;
	Cube limit4;

	//Slopes
	PhysBody3D *pb_slope1 = nullptr;
	Cube slope1;

	PhysBody3D *pb_slope2 = nullptr;
	Cube slope2;

	PhysBody3D *pb_slope3 = nullptr;
	Cube slope3;

	PhysBody3D *pb_slope4 = nullptr;
	Cube slope4;

};
