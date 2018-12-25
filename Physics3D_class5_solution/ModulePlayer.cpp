#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"
#include "ModuleAudio.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL), vehicle2(NULL)
{
	turn = acceleration = brake = turn2 = acceleration2 = brake2 = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car = SetDefaultCar(); //Default car

	vehicle = App->physics->AddVehicle(car);
	vehicle2 = App->physics->AddVehicle(car);

	vehicle->type = vehicle2->type = PhysBodyType::OBJECT;

	vehicle->collision_listeners.add(this);
	vehicle2->collision_listeners.add(this);

	IOrientation_vector = vehicle->vehicle->getForwardVector();
	IOrientation_vector2 = vehicle2->vehicle->getForwardVector();

	starting = true;

	RestartCar(IOrientation_vector, vehicle,IposP1);
	RestartCar(IOrientation_vector2, vehicle2, IposP2, true);

	starting = false;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = turn2 = acceleration2 = brake2 = 0.0f;

	HandleInput_P1();
	HandleInput_P2();

	//Debug
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		boost_quantity = boost_quantity2 = 100.0f;

	//Vehicle 1 move
	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->info.color = Color(1.0f, 0.65f, 0.13f);

	vehicle->Render();

	//Vehicle 2 move
	vehicle2->ApplyEngineForce(acceleration2);
	vehicle2->Turn(turn2);
	vehicle2->Brake(brake2);

	vehicle2->info.color = Blue;
	vehicle2->Render();

	char title[200];
	sprintf_s(title, "PLAYER 1:     Speed %.1f Km/h     Boost %.2f     Coins %i                                                           PLAYER 2:     Speed %.1f Km/h     Boost %.2f     Coins %i",
		vehicle->GetKmh(), boost_quantity, 2, vehicle2->GetKmh(), boost_quantity2, 2);

	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}


void ModulePlayer::HandleInput_P1() {

	if (App->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN)
		RestartCar(IOrientation_vector, vehicle, IposP1);

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		acceleration = MAX_ACCELERATION;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {

		if (vehicle->GetKmh() >= 0)
			brake = BRAKE_POWER;
		else
			acceleration = -MAX_ACCELERATION;
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if (turn < TURN_DEGREES)
			turn += TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if (turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_RCTRL) == KEY_REPEAT && boost_quantity >= 0) {

		btVector3 vec = vehicle->vehicle->getForwardVector();
		vehicle->Push(vec.getX() * 150.0f, 0.0f, vec.getZ() * 150.0f);
		boost_quantity -= 2.0f;
	}
}


void ModulePlayer::HandleInput_P2() {

	if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
		RestartCar(IOrientation_vector2, vehicle2, IposP2, true);

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		acceleration2 = MAX_ACCELERATION;

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {

		if (vehicle2->GetKmh() >= 0)
			brake2 = BRAKE_POWER;
		else
			acceleration2 = -MAX_ACCELERATION;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if (turn2 < TURN_DEGREES)
			turn2 += TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if (turn2 > -TURN_DEGREES)
			turn2 -= TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT && boost_quantity2 >= 0) {

		btVector3 vec = vehicle2->vehicle->getForwardVector();
		vehicle2->Push(vec.getX() * 80.0f, 0.0f, vec.getZ() * 80.0f);
		boost_quantity2 -= 1.0f;
	}
}

VehicleInfo ModulePlayer::SetDefaultCar() {

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(4, 2, 8);
	car.chassis_offset.Set(0, 1.5, 0);
	car.mass = 100.0f;
	car.suspensionStiffness = 40.0f;
	car.suspensionCompression = 2.4f;
	car.suspensionDamping = 2.3f;
	car.maxSuspensionTravelCm = 20.0f;
	car.frictionSlip = 2.0f;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.0f;
	float wheel_radius = 0.6f;
	float wheel_width = 1.0f;
	float suspensionRestLength = 0.2f;

	SetConstCarProperties(&car, connection_height, wheel_radius, wheel_width, suspensionRestLength);
	return car;
}


void ModulePlayer::SetConstCarProperties(VehicleInfo* car, float connection_height, float wheel_radius, float wheel_width, float suspensionRestLength) {

	// Don't change anything below this line ------------------
	float half_width = car->chassis_size.x*0.5f;
	float half_length = car->chassis_size.z*0.5f;

	vec3 direction(0, -1, 0);
	vec3 axis(-1, 0, 0);

	car->num_wheels = 4;
	car->wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car->wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car->wheels[0].direction = direction;
	car->wheels[0].axis = axis;
	car->wheels[0].suspensionRestLength = suspensionRestLength;
	car->wheels[0].radius = wheel_radius;
	car->wheels[0].width = wheel_width;
	car->wheels[0].front = true;
	car->wheels[0].drive = true;
	car->wheels[0].brake = false;
	car->wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car->wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car->wheels[1].direction = direction;
	car->wheels[1].axis = axis;
	car->wheels[1].suspensionRestLength = suspensionRestLength;
	car->wheels[1].radius = wheel_radius;
	car->wheels[1].width = wheel_width;
	car->wheels[1].front = true;
	car->wheels[1].drive = true;
	car->wheels[1].brake = false;
	car->wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car->wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car->wheels[2].direction = direction;
	car->wheels[2].axis = axis;
	car->wheels[2].suspensionRestLength = suspensionRestLength;
	car->wheels[2].radius = wheel_radius;
	car->wheels[2].width = wheel_width;
	car->wheels[2].front = false;
	car->wheels[2].drive = false;
	car->wheels[2].brake = true;
	car->wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car->wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car->wheels[3].direction = direction;
	car->wheels[3].axis = axis;
	car->wheels[3].suspensionRestLength = suspensionRestLength;
	car->wheels[3].radius = wheel_radius;
	car->wheels[3].width = wheel_width;
	car->wheels[3].front = false;
	car->wheels[3].drive = false;
	car->wheels[3].brake = true;
	car->wheels[3].steering = false;

}


void ModulePlayer::RestartCar(btVector3 Iorientation, PhysVehicle3D* vehicle, vec3 Ipos, bool inverted) {

	float fAngle = Iorientation.angle(vehicle->vehicle->getForwardVector());
	vec3 Yaxis = vec3(0.0f, 1.0f, 0.0f);
	vec3 XYZaxis = vec3(1.0f, 1.0f, 1.0f);

	if (fAngle != 0)
		vehicle->SetRotation(XYZaxis, -fAngle);

	if (inverted == true)
		vehicle->SetRotation(Yaxis, 180.0f);

	if (vehicle->GetKmh() > 0)
		vehicle->SetLinearVelocity(vec3(0.0f, 0.0f, 0.0f));

	if (starting == true)
		vehicle->SetPos(Ipos.x, 15.0f, Ipos.z);
		
	
	else
		vehicle->SetPos(Ipos.x, Ipos.y, Ipos.z);


	vehicle->Brake(BRAKE_POWER);

}


void ModulePlayer::OnCollision(PhysBody3D* bA, PhysBody3D* bB) {

	float bounceY = 1500.0f;
	float bounceZ = 0.0f;

	if (bA == vehicle) {

		bounceZ = vehicle->vehicle->getForwardVector().getZ() * 1000.0f;

		if (bB->type == PhysBodyType::BOUNCE_Y)
			vehicle->Push(0.0f, bounceY, 0.0f);

		if (bB->type == PhysBodyType::BOUNCE_XZ)
			vehicle->Push(0.0f, 0.0f, -bounceZ);

		if (bB->type == PhysBodyType::COIN)
			bB->to_delete = true;
	}
	if (bA == vehicle2) {

		bounceZ = vehicle2->vehicle->getForwardVector().getZ() * 1000.0f;

		if (bB->type == PhysBodyType::BOUNCE_Y)
			vehicle2->Push(0.0f, bounceY, 0.0f);

		if (bB->type == PhysBodyType::BOUNCE_XZ)
			vehicle2->Push(0.0f, 0.0f, -bounceZ);

		if (bB->type == PhysBodyType::COIN)
			bB->to_delete = true;
	}
}
