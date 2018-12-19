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

	Cylinder monedita;
	float angle = 0;
	float ypos = 0;
	int YMovement;
	int Movement_variable;
public:

	p2List<Coin*> Coins;
	
};





#endif // !COINS_H

