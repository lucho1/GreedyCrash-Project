#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

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
	pb_slope1 = CreateSlope(slope1, vec3(slope_sizes), vec3(0.0f, -1.0f, 10.0f), 15.0f);
	pb_slope2 = CreateSlope(slope2, vec3(slope_sizes), vec3(0.0f, -1.0f, -10.0f), -15.0f);
	//pb_slope3 = CreateSlope(slope3, vec3(slope_sizes), vec3(10.0f, -1.0f, 0.0f));
	//pb_slope4 = CreateSlope(slope4, vec3(slope_sizes), vec3(-10.0f, -1.0f, 10.0f));


	App->audio->PlayMusic("audio/track_intro.ogg", 0, 0.0f);

	//App->camera->Move(vec3(0.0f, 103.28f, 167.10f));
	App->camera->Move(vec3(0.0f, 30.0f, 30.0f));
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
	p.Render();
	
	pb_limit1->GetTransform(&limit1.transform);
	limit1.Render();

	pb_limit2->GetTransform(&limit2.transform);
	limit2.Render();

	pb_limit3->GetTransform(&limit3.transform);
	limit3.Render();

	pb_limit4->GetTransform(&limit4.transform);
	limit4.Render();

	//Slopes
	pb_slope1->GetTransform(&slope1.transform);
	slope1.Render();

	pb_slope2->GetTransform(&slope2.transform);
	slope2.Render();

	//pb_slope3->GetTransform(&slope3.transform);
	//slope3.Render();

	//pb_slope4->GetTransform(&slope4.transform);
	//slope4.Render();

//	LOG("CAMERA POS: %.2f %.2f %.2f", App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);
	return UPDATE_CONTINUE;
}


PhysBody3D * ModuleSceneIntro::CreateSlope(Cube &slope, vec3 sizes, vec3 pos, float angle) {

	slope = Cube(sizes.x, sizes.y, sizes.z);
	slope.SetPos(pos.x, pos.y, pos.z);

	PhysBody3D*pb_slope = nullptr;
	pb_slope = App->physics->AddBody(slope, 0.0f);
	pb_slope->SetRotation(1.0f, 0.0f, 0.0f, angle);
//	pb_slope->SetRotation(0.0f, 1.0f, 0.0f, 40.0f);

	slope.axis = false;
	return pb_slope;
}