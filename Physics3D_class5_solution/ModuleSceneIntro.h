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

	PhysBody3D *CreateSlope(Cube &slope, vec3 sizes, vec3 pos, float Xangle = 0.0f, float Yangle = 0.0f, float Zangle = 0.0f);
	void OnCollision(PhysBody3D *bodyA, PhysBody3D *bodyB);

	bool MustBounce(Sphere sphere);
	//bool BounceWithSphere(Sphere sphere1, Sphere sphere2);
	//bool BounceWithCube(Sphere sphere, Cube cube);

private:

	//Scenario Limits
	PhysBody3D *pb_limit1 = nullptr;
	Cube limit1;

	PhysBody3D *pb_limit2 = nullptr;
	Cube limit2;

	PhysBody3D *pb_limit3 = nullptr;
	Cube limit3;

	PhysBody3D *pb_limit4 = nullptr;
	Cube limit4;

	//Center Slopes
	PhysBody3D *pb_slope1 = nullptr;
	Cube slope1;

	PhysBody3D *pb_slope2 = nullptr;
	Cube slope2;

	PhysBody3D *pb_slope3 = nullptr;
	Cube slope3;

	PhysBody3D *pb_slope4 = nullptr;
	Cube slope4;

	//Side slopes
	PhysBody3D *pb_slope5 = nullptr;
	Cube slope5;

	PhysBody3D *pb_slope6 = nullptr;
	Cube slope6;

	PhysBody3D *pb_slope7 = nullptr;
	Cube slope7;

	PhysBody3D *pb_slope8 = nullptr;
	Cube slope8;

	PhysBody3D *pb_slCube = nullptr;
	Cube slCube;

	PhysBody3D *pb_slCube2 = nullptr;
	Cube slCube2;

	//Traversal slopes
	PhysBody3D *pb_slTraversal = nullptr;
	Cube slTraversal;

	PhysBody3D *pb_slTraversal2 = nullptr;
	Cube slTraversal2;

	PhysBody3D *pb_slTraversal3 = nullptr;
	Cube slTraversal3;

	PhysBody3D *pb_slTraversal4 = nullptr;
	Cube slTraversal4;

	//Spheres
	PhysBody3D *pb_sunkenSphere = nullptr;
	Sphere sunkenSphere;

	PhysBody3D *pb_sunkenSphere2 = nullptr;
	Sphere sunkenSphere2;

	//Balls
	PhysBody3D* pb_bBall = nullptr;
	Sphere bBall;

	PhysBody3D* pb_bBall2 = nullptr;
	Sphere bBall2;

	PhysBody3D* pb_bBall3 = nullptr;
	Sphere bBall3;

	PhysBody3D* pb_bBall4 = nullptr;
	Sphere bBall4;

public:

	//Bouncing Cubes
	PhysBody3D* pb_bCube = nullptr;
	Cube bCube;
	PhysBody3D* pb_bCube2 = nullptr;
	Cube bCube2;
	PhysBody3D* pb_bCube3 = nullptr;
	Cube bCube3;
	PhysBody3D* pb_bCube4 = nullptr;
	Cube bCube4;
	PhysBody3D* pb_bCube5 = nullptr;
	Cube bCube5;
	PhysBody3D* pb_bCube6 = nullptr;
	Cube bCube6;
	PhysBody3D* pb_bCubeCenter = nullptr;
	Cube bCubeCenter;
	
};
