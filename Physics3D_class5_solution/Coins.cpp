#include "Coins.h"
#include <time.h>
#include "glmath.h"

Coin::Coin(){}

Coin::~Coin(){}

bool Coin::Start(){

	
	/*p2List_item<Coin>* CoinItem;

	CoinItem = Coins.getFirst();*/

	vec3 pos = (5,5,5);
	int scale = 3;
	for (int i = 0; i < 10; i++) {
		CreateCoin(scale);
	}


	return true;
}
void Coin::Update(float dt) {
	p2List_item<Coin*>* CoinItem = Coins.getFirst();

	for (CoinItem = Coins.getFirst(); CoinItem->next != nullptr; CoinItem = CoinItem->next) {

		Movement_variable++;
		YMovement*=(sin(Movement_variable));

			CoinItem->data->monedita.SetPos(RandPosMonedita.x, YMovement, RandPosMonedita.z);
		CoinItem->data->monedita.Render();
	}
}
bool Coin::CleanUp() {
	return true;
}
void Coin::CreateCoin( float scale) {
	vec3 pos;
	pos.x = rand() % 100 + -80;
	pos.z = rand() % 100 + -80;	
	pos.y = rand() % 10 + 1;

	Coin* NewCoin = new Coin();
	NewCoin->monedita.radius = 0.3 * scale;
	NewCoin->monedita.height = 0.1 * scale;
	NewCoin->monedita.SetPos(pos.x,pos.y,pos.z);
	NewCoin->active = false;
	NewCoin->monedita.wire = false;
	NewCoin->monedita.color = Red;
	Coins.add(NewCoin);
	RandPosMonedita.x = pos.x;
	RandPosMonedita.y = pos.y;
	RandPosMonedita.z = pos.z;



}