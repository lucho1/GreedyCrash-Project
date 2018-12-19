#include "Coins.h"
#include <ctime>
#include <cmath>
#include <iostream>
#include <random>
#include "glmath.h"

Coin::Coin(){}

Coin::~Coin(){}

bool Coin::Start(){

	
	/*p2List_item<Coin>* CoinItem;

	CoinItem = Coins.getFirst();*/

	angle = 0;
	return true;
}
void Coin::Update(float dt) {
	
	monedita.color.r = 155;
	monedita.color.g = 155;
	monedita.color.b = 0;

	angle += 6;
	/*if (ypos < 2) {
		ypos += 0.2f;
	}
	else if (ypos >= 2) {
		ypos -= 0.2;
	}*/
	monedita.SetRotation(angle, vec3(0.0f, 1.0f, 0.0f));
	//monedita.SetPos(0.0f, ypos, 0.0f);


	monedita.Render();
	
}
bool Coin::CleanUp() {
	return true;
}
