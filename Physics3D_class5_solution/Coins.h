#ifndef COINS_H_
#define COINS_H_



#include <math.h>
#include "p2List.h"
#include "Globals.h"
#include "p2Point.h"
#include "Primitive.h"

struct PhysBody3D;
class Cube;
class btRigidBody;

struct position {
	float x;
	float y;
	float z;
};


class Coin {
public:
	Coin();
	~Coin();
public:
	bool Init() { return true; }
	bool Start();
	void Update(float dt);
	void PrepareUpdate(){}
	void FinishUpdate(){}
	bool CleanUp();
	

public:
	

public:

	bool active;
	bool ToDelete = false;

	Cylinder monedita;
	PhysBody3D* PhysMonedita = nullptr;
	float angle = 0;

	//int YMovement;
	//int Movement_variable;

	position pos;
	bool up = true;
	bool down = false;

public:

	p2List<Coin*> Coins;
	
};





#endif // !COINS_H

