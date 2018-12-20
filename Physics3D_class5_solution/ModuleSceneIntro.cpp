#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"
#include "PhysVehicle3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	float height = 20.0f;
	float width = 2.0f;
	float longitude = 200.0f;
	float limit_mass = 0.0f; //0 for Static bodies

	limit1 = limit2 = Cube(width, height, longitude);
	limit3 = limit4 = Cube(longitude + 2.0f, height, width);

	limit1.axis = limit2.axis = limit3.axis = limit4.axis = false;

	float dFromAxis = 100.0f;
	limit1.SetPos(-dFromAxis, height/2.0f, 0.0f);
	limit2.SetPos(dFromAxis, height/2.0f, 0.0f);
	limit3.SetPos(0.0f, height/2.0f, -dFromAxis - 1.0f);
	limit4.SetPos(0.0f, height/2.0f, dFromAxis + 1.0f);

	pb_limit1 = App->physics->AddBody(limit1, limit_mass);
	pb_limit2 = App->physics->AddBody(limit2, limit_mass);
	pb_limit3 = App->physics->AddBody(limit3, limit_mass);
	pb_limit4 = App->physics->AddBody(limit4, limit_mass);


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

	bBall.color = bBall2.color = bBall3.color = bBall4.color = Color(155, 0, 155, 255);
	
	//General Scenario Settings
	App->audio->PlayMusic("audio/track_intro.ogg", 0, 0.0f);

	App->camera->Move(vec3(0.0f, 103.28f, 167.10f));
	//App->camera->Move(vec3(0.0f, 30.0f, 30.0f));
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

	if (Mix_PlayingMusic() == 0)
		App->audio->PlayMusic("audio/track_loop.ogg", -1, 0.0f);
	
	Plane p(0, 1, 0, 0);
	p.axis = false;
	p.wire = false;
	p.Render();
	
	pb_limit1->GetTransform(&limit1.transform);
	limit1.Render();

	pb_limit2->GetTransform(&limit2.transform);
	limit2.Render();

	pb_limit3->GetTransform(&limit3.transform);
	limit3.Render();

	pb_limit4->GetTransform(&limit4.transform);
	limit4.Render();

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
	if (MustBounce(bBall) || BounceWithSphere(bBall, sunkenSphere) || BounceWithSphere(bBall, sunkenSphere2))
		pb_bBall->Push(0.0f, 40.0f, 0.0f);

	if (MustBounce(bBall2) || BounceWithSphere(bBall2, sunkenSphere) || BounceWithSphere(bBall2, sunkenSphere2) /*|| BounceWithCar(bBall2, App->player->vehicle->chassis) || BounceWithCar(bBall2, App->player->vehicle2->chassis)*/)
		pb_bBall2->Push(0.0f, 40.0f, 0.0f);


	/*float *N = nullptr;
	pb_bBall->GetTransform(N);
	float Xpb = N[3];
	float Ypb = N[7];
	float Zpb = N[11];*/

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
	

	slope.axis = false;
	return pb_slope;
}


bool ModuleSceneIntro::MustBounce(Sphere sphere) {

	float sphY = sphere.transform[13];
	return(sphY - sphere.radius <= 0.0f);
}


bool ModuleSceneIntro::BounceWithSphere(Sphere sphere1, Sphere sphere2) {

	float sph1Y = sphere1.transform[13];
	float sph2Y = sphere2.transform[13];

	float sph1X = sphere1.transform[12];
	float sph2X = sphere2.transform[12];

	float sph1Z = sphere1.transform[14];
	float sph2Z = sphere2.transform[14];

	float r1 = sphere1.radius;
	float r2 = sphere2.radius;

	if (sph1X <= sph2X + r2 && sph1X >= sph2X - r2 && sph1Z <= sph2Z + r2 && sph1Z >= sph2Z - r2)
		return(sph1Y - r1 <= sph2Y + r2);

	return false;
}


bool ModuleSceneIntro::BounceWithCube(Sphere sphere, Cube cube) {

	//float sphY = sphere1.transform[13];
	//float carY = car_chassis.transform[13];

	//if (sphY - sphere1.radius <= carY + car_chassis.size.y)
	//	return true;

	return false;
}