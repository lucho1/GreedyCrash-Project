#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "Coins.h"
#include "ModulePhysics3D.h"
class Coin;

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	for (int i = 0; i < 10; i++) {
		CreateCoin(3);
	}
	p2List_item<Coin*>* Item = Coins.getFirst();

	

	while (Item != nullptr) {

		Item->data->Start();
			if ((Item->data->PhysMonedita->IsSensor()) == false) {
			Item->data->PhysMonedita->SetAsSensor(true);
		}
		Item = Item->next;
	}
	


	LOG("Loading Intro assets");
	bool ret = true;

	float height = 8.0f;
	float width = 2.0f;
	float longitude = 200.0f;

	limit1 = limit2 = Cube(width, height, longitude);
	limit3 = limit4 = Cube(longitude + 2.0f, height, width);

	limit1.axis = limit2.axis = limit3.axis = limit4.axis = false;


	float dFromAxis = 100.0f;
	limit1.SetPos(-dFromAxis, 0.0f, 0.0f);
	limit2.SetPos(dFromAxis, 0.0f, 0.0f);
	limit3.SetPos(0.0f, 0.0f, -dFromAxis - 1.0f);
	limit4.SetPos(0.0f, 0.0f, dFromAxis + 1.0f);

	float limit_mass = 50000.0f;
	pb_limit1 = App->physics->AddBody(limit1, limit_mass);
	pb_limit2 = App->physics->AddBody(limit2, limit_mass);
	pb_limit3 = App->physics->AddBody(limit3, limit_mass);
	pb_limit4 = App->physics->AddBody(limit4, limit_mass);

	
	
	App->audio->PlayMusic("audio/track_intro.ogg", 0, 0.0f);
	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	//To hear music, comment or delete the next line
	Mix_VolumeMusic(0);
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{

	p2List_item<Coin*>* Item = Coins.getFirst();

	while (Item != nullptr) {

		if (Item->data->ToDelete) {
			Coins.del(Item);
		}
		else if (Item->data->ToDelete == false) {
			Item->data->Update(dt);
		}
		Item = Item->next;
	}

	if (Mix_PlayingMusic() == 0)
		App->audio->PlayMusic("audio/track_loop.ogg", -1, 0.0f);


	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	pb_limit1->GetTransform(&limit1.transform);
	limit1.Render();

	pb_limit2->GetTransform(&limit2.transform);
	limit2.Render();

	pb_limit3->GetTransform(&limit3.transform);
	limit3.Render();

	pb_limit4->GetTransform(&limit4.transform);
	limit4.Render();

	LOG("CAMERA POS: %.2f %.2f %.2f", App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::CreateCoin(float scale) {
	vec3 pos;
	pos.x = rand() % 200 + -100;
	pos.z = rand() % 200 + -100;
	pos.y = rand() % 1 + 1;

	Coin* NewCoin = new Coin();
	NewCoin->monedita.radius = 0.3 * scale;
	goto safezone;
	//DANGER ZONE BELLOW
	int a;
	a *= 3;
	//DANGER ZONE UPPER
	safezone:
	NewCoin->monedita.height = 0.1 * scale;
	NewCoin->monedita.SetPos(pos.x, pos.y, pos.z);
	NewCoin->pos.x = pos.x;
	NewCoin->pos.y = pos.y;
	NewCoin->pos.z = pos.z;
	NewCoin->active = false;
	NewCoin->monedita.wire = false;
	//physmonedita
	NewCoin->PhysMonedita = App->physics->AddBody(NewCoin->monedita, 0.0f);
	
	//NewCoin->monedita.color = Red;
	NewCoin->monedita.SetPos(pos.x, pos.y, pos.z);
	Coins.add(NewCoin);
	
}

