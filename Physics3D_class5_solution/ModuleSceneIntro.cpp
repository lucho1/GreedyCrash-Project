#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "ModulePlayer.h"
#include "PhysVehicle3D.h"
#include "ModulePhysics3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled) {}

ModuleSceneIntro::~ModuleSceneIntro() {}

// Load assets
bool ModuleSceneIntro::Start()
{
	for (int i = 0; i < 10; i++) 
		CreateCoin();

	LOG("Loading Intro assets");
	bool ret = true;

	//Scene Limits
	float height = 27.0f;
	float width = 2.0f;
	float longitude = 200.0f;
	float limit_mass = 0.0f; //0 for Static bodies

	float dFromAxis = 100.0f;
	vec3 limit_size = vec3(width, height, longitude);

	///Wall where camera is placed
	cam_wall.p_Sobject = Cube(limit_size.x, limit_size.y, limit_size.z);
	cam_wall.p_Sobject.SetPos(-dFromAxis, height / 2.0f, 0.0f);
	cam_wall.p_Sobject.axis = false;

	cam_wall.pb_Sobject = App->physics->AddBody(cam_wall.p_Sobject, 0.0f);
	cam_wall.pb_Sobject->type = PhysBodyType::LIMIT;

	///Other walls
	CreateSceneCube(limit_size, vec3(dFromAxis, height / 2.0f, 0.0f), 0.0f, 0.0f, 0.0f, PhysBodyType::LIMIT);

	limit_size = vec3(longitude + 2.0f, height, width);
	CreateSceneCube(limit_size, vec3(0.0f, height / 2.0f, -dFromAxis - 1.0f), 0.0f, 0.0f, 0.0f, PhysBodyType::LIMIT);
	CreateSceneCube(limit_size, vec3(0.0f, height / 2.0f, dFromAxis + 1.0f), 0.0f, 0.0f, 0.0f, PhysBodyType::LIMIT);

	//Slopes
	vec3 slope_sizes = vec3(10.0f, 6.0f, 13.0f);
	float Xangle = 18.0f;
	float Yangle = 45.0f;

	///Center slopes
	CreateSceneCube(slope_sizes, vec3(8.0f, -1.0f, 8.0f), Xangle, Yangle);
	CreateSceneCube(slope_sizes, vec3(-8.0f, -1.0f, -8.0f),-Xangle, Yangle);
	CreateSceneCube(slope_sizes, vec3(8.0f, -1.0f, -8.0f), -Xangle, -Yangle);
	CreateSceneCube(slope_sizes, vec3(-8.0f, -1.0f, 8.0f), Xangle, -Yangle);

	///Side Slopes
	CreateSceneCube(slope_sizes, vec3(95.0f, -1.0f, 8.0f), Xangle, -30.0f);
	CreateSceneCube(slope_sizes, vec3(95.0f, -1.0f, -8.0f), -Xangle, 30.0f);
	CreateSceneCube(slope_sizes, vec3(-95.0f, -1.0f, 8.0f), Xangle, 30.0f);
	CreateSceneCube(slope_sizes, vec3(-95.0f, -1.0f, -8.0f), -Xangle, -30.0f);

	CreateSceneCube(vec3(10.0f, 6.0f, 10.0f), vec3(102.0f, 0.8f, 0.0f), 0.0f, -45.0f);
	CreateSceneCube(vec3(10.0f, 6.0f, 10.0f), vec3(-102.0f, 0.8f, 0.0f), 0.0f, 45.0f);

	///Traversal slopes
	vec3 traversal_size = vec3(74.0f, 6.0f, 8.0f);
	CreateSceneCube(traversal_size, vec3(52.0f, -1.8f, 2.9f), Xangle);
	CreateSceneCube(traversal_size, vec3(52.0f, -1.8f, -2.9f), -Xangle);
	CreateSceneCube(traversal_size, vec3(-52.0f, -1.8f, 2.9f), Xangle);
	CreateSceneCube(traversal_size, vec3(-52.0f, -1.8f, -2.9f), -Xangle);

	//Bouncing Cubes at center
	float pos_correction = 12.0f;
	vec3 bCubes_size = vec3(2.0f, 2.0f, 2.0f);
	CreateSceneCube(bCubes_size, vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, PhysBodyType::BOUNCE_Y, Sob_state::ROTATE, Red); //Center
	CreateSceneCube(bCubes_size, vec3(0.0f, 0.0f, pos_correction), 0.0f, 0.0f, 0.0f, PhysBodyType::BOUNCE_XZ, Sob_state::ROTATE, Red); //Center Right
	CreateSceneCube(bCubes_size, vec3(0.0f, 0.0f, -pos_correction), 0.0f, 0.0f, 0.0f, PhysBodyType::BOUNCE_XZ, Sob_state::ROTATE, Red); //Center Left
	CreateSceneCube(bCubes_size, vec3(pos_correction, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, PhysBodyType::BOUNCE_Y, Sob_state::ROTATE, Red); //Center Up
	CreateSceneCube(bCubes_size, vec3(-pos_correction, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, PhysBodyType::BOUNCE_Y, Sob_state::ROTATE, Red); //Center Down
	CreateSceneCube(bCubes_size, vec3(91.0f, 0.2f, 0.0f), 0.0f, 0.0f, 0.0f, PhysBodyType::BOUNCE_Y, Sob_state::ROTATE, Red);
	CreateSceneCube(bCubes_size, vec3(-91.0f, 0.2f, 0.0f), 0.0f, 0.0f, 0.0f, PhysBodyType::BOUNCE_Y, Sob_state::ROTATE, Red);

	//Sunken Spheres
	CreateSceneSphere(15.0f, vec3(50.0f, -11.0f, 55.0f), 0.0f, PhysBodyType::OBJECT, Sob_state::NON, Black);
	CreateSceneSphere(15.0f, vec3(-50.0f, -11.0f, -55.0f), 0.0f, PhysBodyType::OBJECT, Sob_state::NON, Black);

	//Balls
	CreateSceneSphere(2.0f, vec3(-50.0f, 20.0f, 55.0f), 1.0f, PhysBodyType::DEFAULT, Sob_state::BOUNCE, Color(0.6f, 0, 0.6f), true);
	CreateSceneSphere(2.0f, vec3(50.0f, 20.0f, -55.0f), 1.0f, PhysBodyType::DEFAULT, Sob_state::BOUNCE, Color(0.6f, 0, 0.6f), true);
	CreateSceneSphere(5.0f, vec3(-30.0f, 20.0f, 60.0f), 1.0f, PhysBodyType::DEFAULT, Sob_state::NON, Color(0.6f, 0, 0.6f));
	CreateSceneSphere(5.0f, vec3(30.0f, 20.0f, -60.0f), 1.0f, PhysBodyType::DEFAULT, Sob_state::NON, Color(0.6f, 0, 0.6f));


	//General Scenario Settings
	gameOver_fx1 = App->audio->LoadFx("audio/fx/GameOver.wav");
	gameOver_fx2 = App->audio->LoadFx("audio/fx/LoseSound.wav");
	gameOver_fx3 = App->audio->LoadFx("audio/fx/IwinSound.wav");

	App->audio->PlayMusic("audio/gameOver_mus_intro.ogg", 0, 0.0f);

	//App->camera->Move(vec3(0.0f, 103.28f, 167.10f));
	App->camera->Move(vec3(-176.27f, 87.99f, -0.58f));
	App->camera->LookAt(vec3(0, 0, 0));

	//To hear music, comment or delete the next line
	//Mix_VolumeMusic(0);
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

	Plane p(0, 1, 0, 0);
	p.axis = false;
	p.Render();

	if (gameOver == true) {

		if (Mix_PlayingMusic() == 0 && !playMus)
				App->audio->PlayMusic("audio/gameOver_mus_loop.ogg", -1, 0.0f);


		if (fx_timer.Read() >= 1500 && play2) {

			App->audio->PlayFx(gameOver_fx2);
			play2 = false;
			play3 = true;
		}


		if (fx_timer.Read() >= 4500 && play3) {

			App->audio->PlayFx(gameOver_fx3);
			play3 = false;
		}

		if (fx_timer.Read() >= 6500 && playMus) {

			App->audio->PlayMusic("audio/gameOver_mus_intro.ogg", 0, 0.0f);
			playMus = false;

		}


		App->physics->debug = true;
	}
	else {

		p2List_item<Coin>*item = c_list.getFirst();
		while (item != nullptr) {

			item->data.pb_Coin->AddRotation(vec3(0.0f, 1.0f, 0.0f), 10.0f);
			item->data.pb_Coin->GetTransform(&item->data.Coin_c.transform);
			item->data.Coin_c.Render();
			item->data.Coin_c.SetPos(item->data.iPos.x, item->data.iPos.y, item->data.iPos.z);


			item = item->next;
		}

		cam_wall.pb_Sobject->GetTransform(&cam_wall.p_Sobject.transform);
		cam_wall.p_Sobject.CameraWall_Render();

		//Cubes
		p2List_item<Scene_Cube> *so_itemCube = SoCube_list.getFirst();
		for (; so_itemCube; so_itemCube = so_itemCube->next) {

			if (so_itemCube->data.state == Sob_state::ROTATE)
				so_itemCube->data.pb_Sobject->AddRotation(vec3(0.0f, 1.0f, 0.0f), 10.0f);

			so_itemCube->data.pb_Sobject->GetTransform(&so_itemCube->data.p_Sobject.transform);
			so_itemCube->data.p_Sobject.Render();
		}

		//Spheres
		p2List_item<Scene_Sphere> *so_itemSphere = SoSphere_list.getFirst();
		for (; so_itemSphere; so_itemSphere = so_itemSphere->next) {

			if (so_itemSphere->data.state == Sob_state::BOUNCE && MustBounce(so_itemSphere->data.p_Sobject)) {
			
					vec3 v = so_itemSphere->data.pb_Sobject->GetLinearVelocity();
					so_itemSphere->data.pb_Sobject->SetLinearVelocity(vec3(0.0f, 0.0f, 0.0f));
					so_itemSphere->data.pb_Sobject->Push(v.x, 20.0f, v.z);
			}

			so_itemSphere->data.pb_Sobject->GetTransform(&so_itemSphere->data.p_Sobject.transform);
			so_itemSphere->data.p_Sobject.Render();
		}
	}

	//LOG("CAMERA POS: %.2f %.2f %.2f", App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);
	return UPDATE_CONTINUE;
}


void ModuleSceneIntro::RunGameOver() {

	Mix_HaltMusic();
	fx_timer.Start();

	App->audio->PlayFx(gameOver_fx1);
	play2 = true;
	gameOver = true;
	playMus = true;
}


bool ModuleSceneIntro::MustBounce(Sphere sphere) {

	float sphY = sphere.transform[13];
	return(sphY - sphere.radius <= 0.0f);
}


void ModuleSceneIntro::OnCollision(PhysBody3D *bodyA, PhysBody3D *bodyB) {

	if (bodyB->type == PhysBodyType::BOUNCE_Y || bodyB->type == PhysBodyType::OBJECT)
			bodyA->Push(0.0f, 10.5f, 0.0f);

}


void ModuleSceneIntro::CreateCoin() {

	Coin coin;
	coin.iPos.x = rand() % 200 + -100;
	coin.iPos.z = rand() % 200 + -100;
	coin.iPos.y = rand() % 1 + 1;

	Cylinder Coin_Cyl = Cylinder(1.0f, 0.3f);
	Coin_Cyl.SetPos(coin.iPos.x, coin.iPos.y, coin.iPos.z);
	Coin_Cyl.color = Color(1.0f, 1.0f, 0.0f);

	PhysBody3D* pb_Coin = App->physics->AddBody(Coin_Cyl, 0.2f);
	pb_Coin->type = PhysBodyType::COIN;

	coin.Coin_c = Coin_Cyl;
	coin.pb_Coin = pb_Coin;
	
	c_list.add(coin);
}


void ModuleSceneIntro::CreateSceneCube(vec3 sizes, vec3 pos, float Xangle, float Yangle, float Zangle, PhysBodyType ptype, Sob_state state, Color col) {

	Scene_Cube OBJcube;

	vec3 Yaxis = vec3(0.0f, 1.0f, 0.0f);
	vec3 Xaxis = vec3(1.0f, 0.0f, 0.0f);
	vec3 Zaxis = vec3(0.0f, 0.0f, 1.0f);

	OBJcube.p_Sobject = Cube(sizes.x, sizes.y, sizes.z);
	OBJcube.p_Sobject.SetPos(pos.x, pos.y, pos.z);
	OBJcube.p_Sobject.color = col;
	OBJcube.p_Sobject.axis = false;

	OBJcube.pb_Sobject = App->physics->AddBody(OBJcube.p_Sobject, 0.0f);
	OBJcube.pb_Sobject->AddRotation(Yaxis, Yangle);
	OBJcube.pb_Sobject->AddRotation(Xaxis, Xangle);
	OBJcube.pb_Sobject->AddRotation(Zaxis, Zangle);

	OBJcube.pb_Sobject->type = ptype;
	
	OBJcube.state = state;
	SoCube_list.add(OBJcube);
}


void ModuleSceneIntro::CreateSceneSphere(float radius, vec3 pos, float mass, PhysBodyType ptype, Sob_state state, Color col, bool listen) {

	Scene_Sphere OBJsphere;

	OBJsphere.p_Sobject = Sphere(radius);
	OBJsphere.p_Sobject.SetPos(pos.x, pos.y, pos.z);
	OBJsphere.p_Sobject.color = col;
	OBJsphere.p_Sobject.axis = false;

	OBJsphere.pb_Sobject = nullptr;
	OBJsphere.pb_Sobject = App->physics->AddBody(OBJsphere.p_Sobject, mass);
	OBJsphere.pb_Sobject->type = ptype;

	if (listen)
		OBJsphere.pb_Sobject->collision_listeners.add(this);

	OBJsphere.state = state;
	SoSphere_list.add(OBJsphere);
}