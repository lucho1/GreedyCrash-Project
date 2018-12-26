#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "PhysBody3D.h"

enum class Sob_state {

	ROTATE,
	BOUNCE,
	NON
};

struct Coin {

	Cylinder Coin_c;
	PhysBody3D *pb_Coin;
	vec3 iPos;
};

struct Scene_Cube {

	PhysBody3D *pb_Sobject;
	Cube p_Sobject;
	Sob_state state = Sob_state::NON;
};

struct Scene_Sphere {

	PhysBody3D *pb_Sobject;
	Sphere p_Sobject;
	Sob_state state = Sob_state::NON;
};

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

	void RunGameOver();

private:

	void CreateSceneCube(vec3 sizes, vec3 pos, float Xangle = 0.0f, float Yangle = 0.0f, float Zangle = 0.0f, PhysBodyType ptype = PhysBodyType::DEFAULT, Sob_state state = Sob_state::NON, Color col = White);
	void CreateSceneSphere(float radius, vec3 pos, float mass = 0.0f, PhysBodyType ptype = PhysBodyType::DEFAULT, Sob_state state = Sob_state::NON, Color col = White, bool listen = false);

	void OnCollision(PhysBody3D *bodyA, PhysBody3D *bodyB);
	bool MustBounce(Sphere sphere);

private:

	p2List<Scene_Cube> SoCube_list;
	p2List<Scene_Sphere> SoSphere_list;

public:

	void CreateCoin();
	p2List<Coin>c_list;

	bool gameOver = true;
	bool play2 = false;
	bool play3 = false;
	bool playMus = false;

	uint gameOver_fx1;
	uint gameOver_fx2;
	uint gameOver_fx3;

	Timer fx_timer;

};
