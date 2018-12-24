#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
<<<<<<< HEAD
#include "Coins.h"
#include "ModulePhysics3D.h"
class Coin;
=======
#include "ModulePlayer.h"
#include "PhysVehicle3D.h"
>>>>>>> SECCOPYBranch

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
<<<<<<< HEAD
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
=======
	LOG("Loading Intro assets");
	bool ret = true;

	float height = 20.0f;
	float width = 2.0f;
	float longitude = 200.0f;
	float limit_mass = 0.0f; //0 for Static bodies
>>>>>>> SECCOPYBranch

	limit1 = limit2 = Cube(width, height, longitude);
	limit3 = limit4 = Cube(longitude + 2.0f, height, width);

	limit1.axis = limit2.axis = limit3.axis = limit4.axis = false;

<<<<<<< HEAD

	float dFromAxis = 100.0f;
	limit1.SetPos(-dFromAxis, 0.0f, 0.0f);
	limit2.SetPos(dFromAxis, 0.0f, 0.0f);
	limit3.SetPos(0.0f, 0.0f, -dFromAxis - 1.0f);
	limit4.SetPos(0.0f, 0.0f, dFromAxis + 1.0f);

	float limit_mass = 50000.0f;
=======
	float dFromAxis = 100.0f;
	limit1.SetPos(-dFromAxis, height/2.0f, 0.0f);
	limit2.SetPos(dFromAxis, height/2.0f, 0.0f);
	limit3.SetPos(0.0f, height/2.0f, -dFromAxis - 1.0f);
	limit4.SetPos(0.0f, height/2.0f, dFromAxis + 1.0f);

>>>>>>> SECCOPYBranch
	pb_limit1 = App->physics->AddBody(limit1, limit_mass);
	pb_limit2 = App->physics->AddBody(limit2, limit_mass);
	pb_limit3 = App->physics->AddBody(limit3, limit_mass);
	pb_limit4 = App->physics->AddBody(limit4, limit_mass);

<<<<<<< HEAD
	
	
	App->audio->PlayMusic("audio/track_intro.ogg", 0, 0.0f);
	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
=======
	pb_limit1->type = pb_limit2->type = pb_limit3->type = pb_limit4->type = PhysBodyType::LIMIT;

	//Slopes
	vec3 slope_sizes = vec3(10.0f, 6.0f, 13.0f);
	float Xangle = 18.0f;
	float Yangle = 45.0f;

	//Center slopes
	pb_slope1 = CreateSlope(slope1, slope_sizes, vec3(8.0f, -1.0f, 8.0f), Xangle, Yangle);
	pb_slope2 = CreateSlope(slope2, slope_sizes, vec3(-8.0f, -1.0f, -8.0f), -Xangle, Yangle);
	pb_slope3 = CreateSlope(slope3, slope_sizes, vec3(8.0f, -1.0f, -8.0f), -Xangle, -Yangle);
	pb_slope4 = CreateSlope(slope4, slope_sizes, vec3(-8.0f, -1.0f, 8.0f), Xangle, -Yangle);

	//Side Slopes
	pb_slope5 = CreateSlope(slope5, slope_sizes, vec3(95.0f, -1.0f, 8.0f), Xangle, -30.0f);
	pb_slope6 = CreateSlope(slope6, slope_sizes, vec3(95.0f, -1.0f, -8.0f), -Xangle, 30.0f);
	pb_slope7 = CreateSlope(slope7, slope_sizes, vec3(-95.0f, -1.0f, 8.0f), Xangle, 30.0f);
	pb_slope8 = CreateSlope(slope8, slope_sizes, vec3(-95.0f, -1.0f, -8.0f), -Xangle, -30.0f);

	pb_slCube = CreateSlope(slCube, vec3(10.0f, 6.0f, 10.0f), vec3(102.0f, 0.8f, 0.0f), 0.0f, -45.0f);
	pb_slCube2 = CreateSlope(slCube2, vec3(10.0f, 6.0f, 10.0f), vec3(-102.0f, 0.8f, 0.0f), 0.0f, 45.0f);

	//Traversal slopes
	pb_slTraversal = CreateSlope(slTraversal, vec3(74.0f, 6.0, 8.0f), vec3(52.0f, -1.8f, 2.9f), Xangle);
	pb_slTraversal2 = CreateSlope(slTraversal2, vec3(74.0f, 6.0, 8.0f), vec3(52.0f, -1.8f, -2.9f), -Xangle);
	pb_slTraversal3 = CreateSlope(slTraversal3, vec3(74.0f, 6.0, 8.0f), vec3(-52.0f, -1.8f, 2.9f), Xangle);
	pb_slTraversal4 = CreateSlope(slTraversal4, vec3(74.0f, 6.0, 8.0f), vec3(-52.0f, -1.8f, -2.9f), -Xangle);

	//Spheres
	sunkenSphere = Sphere(15.0f);
	sunkenSphere.SetPos(50.0f, -11.0f, 55.0f);
	pb_sunkenSphere = App->physics->AddBody(sunkenSphere, 0.0f);

	sunkenSphere2 = Sphere(15.0f);
	sunkenSphere2.SetPos(-50.0f, -11.0f, -55.0f);
	pb_sunkenSphere2 = App->physics->AddBody(sunkenSphere2, 0.0f);

	sunkenSphere.color = sunkenSphere2.color = Black;
	pb_sunkenSphere->type = pb_sunkenSphere2->type = PhysBodyType::OBJECT;

	//Balls
	bBall = Sphere(2.0f);
	bBall.SetPos(-50.0f, 20.0f, 55.0f);
	pb_bBall = App->physics->AddBody(bBall);

	bBall2 = Sphere(2.0f);
	bBall2.SetPos(-50.0f, 20.0f, -55.0f);
	pb_bBall2 = App->physics->AddBody(bBall2);

	bBall3 = Sphere(5.0f);
	bBall3.SetPos(-30.0f, 20.0f, 60.0f);
	pb_bBall3 = App->physics->AddBody(bBall3);

	bBall4 = Sphere(5.0f);
	bBall4.SetPos(-30.0f, 20.0f, -60.0f);
	pb_bBall4 = App->physics->AddBody(bBall4);

	bBall.color = bBall2.color = bBall3.color = bBall4.color = Color(0.6f, 0, 0.6f);

	pb_bBall->collision_listeners.add(this);
	pb_bBall2->collision_listeners.add(this);

	//Bouncing Cubes at center
	bCubeCenter = Cube(2.0f, 2.0f, 2.0f);
	bCubeCenter.SetPos(0.0f, 0.0f, 0.0f);
	pb_bCubeCenter = App->physics->AddBody(bCubeCenter, 0.0f);

	bCube = Cube(2.0f, 2.0f, 2.0f);
	bCube.SetPos(0.0f, 0.0f, 12.0f);
	pb_bCube = App->physics->AddBody(bCube, 0.0f);

	bCube2 = Cube(2.0f, 2.0f, 2.0f);
	bCube2.SetPos(0.0f, 0.0f, -12.0f);
	pb_bCube2 = App->physics->AddBody(bCube2, 0.0f);

	bCube3 = Cube(2.0f, 2.0f, 2.0f);
	bCube3.SetPos(12.0f, 0.0f, 0.0f);
	pb_bCube3 = App->physics->AddBody(bCube3, 0.0f);

	bCube4 = Cube(2.0f, 2.0f, 2.0f);
	bCube4.SetPos(-12.0f, 0.0f, 0.0f);
	pb_bCube4 = App->physics->AddBody(bCube4, 0.0f);

	bCube5 = Cube(2.0f, 2.0f, 2.0f);
	bCube5.SetPos(91.0f, 0.0f, 0.0f);
	pb_bCube5 = App->physics->AddBody(bCube5, 0.0f);

	bCube6 = Cube(2.0f, 2.0f, 2.0f);
	bCube6.SetPos(-91.0f, 0.0f, 0.0f);
	pb_bCube6 = App->physics->AddBody(bCube6, 0.0f);

	bCubeCenter.color = bCube.color = bCube2.color = bCube3.color = bCube4.color = bCube5.color = bCube6.color = Red;
	pb_bCubeCenter->type = pb_bCube3->type = pb_bCube4->type = pb_bCube5->type = pb_bCube6->type = PhysBodyType::BOUNCE_Y;
	pb_bCube->type = pb_bCube2->type = PhysBodyType::BOUNCE_XZ;
	
	//General Scenario Settings
	App->audio->PlayMusic("audio/track_intro.ogg", 0, 0.0f);

	App->camera->Move(vec3(0.0f, 103.28f, 167.10f));
	//App->camera->Move(vec3(0.0f, 30.0f, 30.0f));
>>>>>>> SECCOPYBranch
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

<<<<<<< HEAD
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

=======
	if (Mix_PlayingMusic() == 0)
		App->audio->PlayMusic("audio/track_loop.ogg", -1, 0.0f);
	
	Plane p(0, 1, 0, 0);
	p.axis = false;
	p.wire = false;
	p.Render();
	
>>>>>>> SECCOPYBranch
	pb_limit1->GetTransform(&limit1.transform);
	limit1.Render();

	pb_limit2->GetTransform(&limit2.transform);
	limit2.Render();

	pb_limit3->GetTransform(&limit3.transform);
	limit3.Render();

	pb_limit4->GetTransform(&limit4.transform);
	limit4.Render();

<<<<<<< HEAD
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

=======
	//Center Slopes
	pb_slope1->GetTransform(&slope1.transform);
	slope1.Render();

	pb_slope2->GetTransform(&slope2.transform);
	slope2.Render();

	pb_slope3->GetTransform(&slope3.transform);
	slope3.Render();

	pb_slope4->GetTransform(&slope4.transform);
	slope4.Render();

	//Side Slopes
	pb_slope5->GetTransform(&slope5.transform);
	slope6.Render();

	pb_slope6->GetTransform(&slope6.transform);
	slope5.Render();

	pb_slope7->GetTransform(&slope7.transform);
	slope7.Render();

	pb_slope8->GetTransform(&slope8.transform);
	slope8.Render();

	pb_slCube->GetTransform(&slCube.transform);
	slCube.Render();

	pb_slCube2->GetTransform(&slCube2.transform);
	slCube2.Render();

	//Traversal Slopes
	pb_slTraversal->GetTransform(&slTraversal.transform);
	slTraversal.Render();

	pb_slTraversal2->GetTransform(&slTraversal2.transform);
	slTraversal2.Render();

	pb_slTraversal3->GetTransform(&slTraversal3.transform);
	slTraversal3.Render();

	pb_slTraversal4->GetTransform(&slTraversal4.transform);
	slTraversal4.Render();

	//Shperes
	pb_sunkenSphere->GetTransform(&sunkenSphere.transform);
	sunkenSphere.Render();

	pb_sunkenSphere2->GetTransform(&sunkenSphere2.transform);
	sunkenSphere2.Render();

	
	//Balls
	pb_bBall->GetTransform(&bBall.transform);
	bBall.Render();

	pb_bBall2->GetTransform(&bBall2.transform);
	bBall2.Render();

	pb_bBall3->GetTransform(&bBall3.transform);
	bBall3.Render();

	pb_bBall4->GetTransform(&bBall4.transform);
	bBall4.Render();

	//Balls 1 & 2 bounce
	if (MustBounce(bBall)) {

		vec3 v = pb_bBall->GetLinearVelocity();
		pb_bBall->SetLinearVelocity(vec3(0.0f, 0.0f, 0.0f));
		pb_bBall->Push(v.x, 20.0f, v.z);

	}

	if (MustBounce(bBall2)) {

		vec3 v = pb_bBall2->GetLinearVelocity();
		pb_bBall2->SetLinearVelocity(vec3(0.0f, 0.0f, 0.0f));
		pb_bBall2->Push(v.x, 20.0f, v.z);

	}
	//Bouncing Cubes
	pb_bCubeCenter->AddRotation(vec3(0.0f, 1.0f, 0.0f), 10.0f);
	pb_bCubeCenter->GetTransform(&bCubeCenter.transform);
	bCubeCenter.Render();

	pb_bCube->AddRotation(vec3(0.0f, 1.0f, 0.0f), 10.0f);
	pb_bCube->GetTransform(&bCube.transform);
	bCube.Render();

	pb_bCube2->AddRotation(vec3(0.0f, 1.0f, 0.0f), 10.0f);
	pb_bCube2->GetTransform(&bCube2.transform);
	bCube2.Render();

	pb_bCube3->AddRotation(vec3(0.0f, 1.0f, 0.0f), 10.0f);
	pb_bCube3->GetTransform(&bCube3.transform);
	bCube3.Render();

	pb_bCube4->AddRotation(vec3(0.0f, 1.0f, 0.0f), 10.0f);
	pb_bCube4->GetTransform(&bCube4.transform);
	bCube4.Render();

	pb_bCube5->AddRotation(vec3(0.0f, 1.0f, 0.0f), 10.0f);
	pb_bCube5->GetTransform(&bCube5.transform);
	bCube5.Render();

	pb_bCube6->AddRotation(vec3(0.0f, 1.0f, 0.0f), 10.0f);
	pb_bCube6->GetTransform(&bCube6.transform);
	bCube6.Render();

//	LOG("CAMERA POS: %.2f %.2f %.2f", App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);
	return UPDATE_CONTINUE;
}


PhysBody3D * ModuleSceneIntro::CreateSlope(Cube &slope, vec3 sizes, vec3 pos, float Xangle, float Yangle, float Zangle) {

	vec3 Yaxis = vec3(0.0f, 1.0f, 0.0f);
	vec3 Xaxis = vec3(1.0f, 0.0f, 0.0f);

	vec3 Zaxis = vec3(0.0f, 0.0f, 1.0f);

	slope = Cube(sizes.x, sizes.y, sizes.z);
	slope.SetPos(pos.x, pos.y, pos.z);

	PhysBody3D*pb_slope = nullptr;
	pb_slope = App->physics->AddBody(slope, 0.0f);
	pb_slope->AddRotation(Yaxis, Yangle);
	pb_slope->AddRotation(Xaxis, Xangle);
	pb_slope->AddRotation(Zaxis, Zangle);
	
	pb_slope->type = PhysBodyType::OBJECT;
	slope.axis = false;
	return pb_slope;
}


bool ModuleSceneIntro::MustBounce(Sphere sphere) {

	float sphY = sphere.transform[13];
	return(sphY - sphere.radius <= 0.0f);
}


void ModuleSceneIntro::OnCollision(PhysBody3D *bodyA, PhysBody3D *bodyB) {

	if (bodyB->type == PhysBodyType::BOUNCE_Y || bodyB->type == PhysBodyType::OBJECT) {

		if (bodyA == pb_bBall)
			pb_bBall->Push(0.0f, 10.5f, 0.0f);

		if (bodyA == pb_bBall2)
			pb_bBall2->Push(0.0f, 10.5f, 0.0f);
	}
}
>>>>>>> SECCOPYBranch
