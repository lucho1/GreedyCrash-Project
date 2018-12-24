#include "Coins.h"
#include <ctime>
#include <cmath>
#include <iostream>
#include <random>
#include "glmath.h"
#include "ModulePhysics3D.h"
#include "PhysBody3D.h"
Coin::Coin(){
	
}

Coin::~Coin(){}

bool Coin::Start(){

	
	/*p2List_item<Coin>* CoinItem;

	CoinItem = Coins.getFirst();*/
	PhysMonedita->type = PhysBodyType::COIN;
	
	angle = 0;
	return true;
}
void Coin::Update(float dt) {
	
	if (PhysMonedita->ToDelete == false) {

		monedita.color.r = 155;
		monedita.color.g = 155;
		monedita.color.b = 0;

		angle += 6;

		if (up) {
			pos.y += 0.025f;
			if (pos.y > 3) {
				down = true;
				up = false;
			}
		}
		if (down) {
			pos.y -= 0.025f;
			if (pos.y < 1) {
				up = true;
				down = false;
			}
		}


		monedita.SetRotation(angle, vec3(0.0f, pos.y, 0.0f));
		monedita.SetPos(pos.x, pos.y, pos.z);
		PhysMonedita->GetTransform(&monedita.transform);

		monedita.Render();
	}
	else
		CleanUp();

	
}
bool Coin::CleanUp() {



	return true;
}
