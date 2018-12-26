#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"
#include "ModuleAudio.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), veh1(), veh2()
{
	veh1.turn = veh1.acceleration = veh1.brake = veh2.turn = veh2.acceleration = veh2.brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car = SetDefaultCar(); //Default car

	veh1.Ipos = vec3(0.0f, 0.0f, -92.0f);
	veh2.Ipos = vec3(0.0f, 0.0f, 92.0f);

	veh1.vehicle = App->physics->AddVehicle(car);
	veh2.vehicle = App->physics->AddVehicle(car);

	veh1.vehicle->type = veh2.vehicle->type = PhysBodyType::OBJECT;

	veh1.vehicle->collision_listeners.add(this);
	veh2.vehicle->collision_listeners.add(this);

	veh1.IOrientation_vector = veh1.vehicle->vehicle->getForwardVector();
	veh2.IOrientation_vector = veh2.vehicle->vehicle->getForwardVector();

	RestartCar(veh1.IOrientation_vector, veh1.vehicle, veh1.Ipos);
	RestartCar(veh2.IOrientation_vector, veh2.vehicle, veh2.Ipos, true);

	veh1.vehicle->info.color = Color(1.0f, 0.65f, 0.13f);
	veh2.vehicle->info.color = Blue;

	coin_fx = App->audio->LoadFx("audio/fx/PickCoinSound.wav");
	loseCoin_fx = App->audio->LoadFx("audio/fx/loseCoin_fx.wav");
	shout_fx = App->audio->LoadFx("audio/fx/WilScream.wav");

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

	if (App->scene_intro->gameOver == true) {

		veh1.vehicle->SetPos(0.0f, 0.0f, -20.0f);
		veh2.vehicle->SetPos(0.0f, 0.0f, 20.0f);

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			Restart();

		char title[250];
		//FOR SOME REASON, /t doesn't work here :(
		if (veh1.Coins <= 0)
			sprintf_s(title, "--------------------------PLAYER 2 WINS--------------------------             press space");
		else if (veh2.Coins <= 0)
			sprintf_s(title, "--------------------------PLAYER 1 WINS--------------------------             press space");
		else
			sprintf_s(title, "PRESS SPACE");

		App->window->SetTitle(title);
	}
	else {

		if (Mix_PlayingMusic() == 0)
			App->audio->PlayMusic("audio/track_loop.ogg", -1, 0.0f);

		//Debug
		if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
			veh1.boost_quantity = veh2.boost_quantity = 100.0f;
		if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
			veh1.Coins = veh2.Coins += 1;

		if (veh1.Coins <= 0 || veh2.Coins <= 0)
			App->scene_intro->RunGameOver();

		veh1.turn = veh1.acceleration = veh1.brake = veh2.turn = veh2.acceleration = veh2.brake = 0.0f;

		HandleInput_P1();
		HandleInput_P2();

		//Vehicle 1 move
		veh1.vehicle->ApplyEngineForce(veh1.acceleration);
		veh1.vehicle->Turn(veh1.turn);
		veh1.vehicle->Brake(veh1.brake);

		veh1.vehicle->Render();

		//Vehicle 2 move
		veh2.vehicle->ApplyEngineForce(veh2.acceleration);
		veh2.vehicle->Turn(veh2.turn);
		veh2.vehicle->Brake(veh2.brake);

		veh2.vehicle->Render();

		veh1.vehicle->info.color = Color(1.0f, 0.65f, 0.13f);
		veh2.vehicle->info.color = Blue;

		char title[350];
		sprintf_s(title, "PLAYER 1:     Speed %.1f Km/h     Boost %.2f     BoostRecover: %i/2     Coins %i                                                    PLAYER 2:     Speed %.1f Km/h     Boost %.2f     BoostRecover: %i/2     Coins %i",
			veh1.vehicle->GetKmh(), veh1.boost_quantity, veh1.boost_recover, veh1.Coins, veh2.vehicle->GetKmh(), veh2.boost_quantity, veh2.boost_recover, veh2.Coins);

		App->window->SetTitle(title);
	}

	return UPDATE_CONTINUE;
}


void ModulePlayer::Restart() {

	veh1.Coins = 6;
	veh2.Coins = 6;
	veh1.boost_quantity = 100.0f;
	veh2.boost_quantity = 100.0f;
	veh1.boost_recover = 0;
	veh2.boost_recover = 0;

	RestartCar(veh1.IOrientation_vector, veh1.vehicle, veh1.Ipos);
	RestartCar(veh2.IOrientation_vector, veh2.vehicle, veh2.Ipos, true);

	App->scene_intro->gameOver = false;
	App->physics->debug = false;
	App->audio->PlayMusic("audio/track_intro.ogg", 0, 0.0f);
}


bool ModulePlayer::LimitsReached(defCar vehicle) {

	btVector3 curr_pos = vehicle.vehicle->GetPos();

	if (curr_pos.getX() > 150 || curr_pos.getX() < -150 || curr_pos.getZ() > 150 || curr_pos.getZ() < -150 || curr_pos.getY() > 100)
		return true;

	return false;
}


void ModulePlayer::HandleInput_P1() {

	if (veh1.boost_recover >= 2) {

		veh1.boost_quantity = 100.0f;
		veh1.boost_recover = 0;
	}

	if (veh1.Coins == 12)
		veh1.maxCreached = true;
	if (veh1.Coins <= 9)
		veh1.maxCreached = false;

	if (LimitsReached(veh1)) {

		App->audio->PlayFx(shout_fx);
		RestartCar(veh1.IOrientation_vector, veh1.vehicle, veh1.Ipos);
		veh1.Coins -= 2;
		App->audio->PlayFx(loseCoin_fx);

	}


	if (App->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN && veh1.Coins > 0) {

		RestartCar(veh1.IOrientation_vector, veh1.vehicle, veh1.Ipos);
		veh1.Coins--;
		App->audio->PlayFx(loseCoin_fx);
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
		veh1.vehicle->forward = true;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
		veh1.vehicle->forward = false;

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		veh1.acceleration = MAX_ACCELERATION;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {

		if (veh1.vehicle->GetKmh() >= 0)
			veh1.brake = BRAKE_POWER;
		else
			veh1.acceleration = -MAX_ACCELERATION;
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if (veh1.turn < TURN_DEGREES)
			veh1.turn += TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if (veh1.turn > -TURN_DEGREES)
			veh1.turn -= TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_RCTRL) == KEY_REPEAT && veh1.boost_quantity >= 0) {

		btVector3 vec = veh1.vehicle->vehicle->getForwardVector();
		veh1.vehicle->Push(vec.getX() * 50.0f, 0.0f, vec.getZ() * 50.0f);
		veh1.boost_quantity -= 1.0f;
	}

	if (App->input->GetKey(SDL_SCANCODE_RCTRL) == KEY_DOWN)
		veh1.boosting = true;
}


void ModulePlayer::HandleInput_P2() {

	if (veh2.boost_recover >= 2) {

		veh2.boost_quantity = 100.0f;
		veh2.boost_recover = 0;
	}

	if(veh2.Coins == 12)
		veh2.maxCreached = true;
	if (veh2.Coins <= 9)
		veh2.maxCreached = false;

	if (LimitsReached(veh2)) {

		App->audio->PlayFx(shout_fx);
		RestartCar(veh2.IOrientation_vector, veh2.vehicle, veh2.Ipos, true);
		veh2.Coins -= 2;
		App->audio->PlayFx(loseCoin_fx);

	}

	if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN && veh2.Coins > 0) {

		RestartCar(veh2.IOrientation_vector, veh2.vehicle, veh2.Ipos, true);
		veh2.Coins--;
		App->audio->PlayFx(loseCoin_fx);
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
		veh2.vehicle->forward = true;

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		veh2.vehicle->forward = false;

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		veh2.acceleration = MAX_ACCELERATION;

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {

		if (veh2.vehicle->GetKmh() >= 0)
			veh2.brake = BRAKE_POWER;
		else
			veh2.acceleration = -MAX_ACCELERATION;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if (veh2.turn < TURN_DEGREES)
			veh2.turn += TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if (veh2.turn > -TURN_DEGREES)
			veh2.turn -= TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT && veh2.boost_quantity >= 0) {

		btVector3 vec = veh2.vehicle->vehicle->getForwardVector();
		veh2.vehicle->Push(vec.getX() * 50.0f, 0.0f, vec.getZ() * 50.0f);
		veh2.boost_quantity -= 1.0f;
	}

	if(App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_DOWN)
		veh2.boosting = true;
}

VehicleInfo ModulePlayer::SetDefaultCar() {

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(4, 1.5, 8);
	car.chassis_offset.Set(0,2, 0);
	car.mass = 50.0f;
	car.suspensionStiffness = 60.0f;
	car.suspensionCompression = 4.0f;
	car.suspensionDamping = 0.15f;
	car.maxSuspensionTravelCm = 60.0f;
	car.frictionSlip = 2.0f;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.0f;
	float wheel_radius =0.6f;
	float wheel_width = 0.5f;
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
	car->wheels[2].connection.Set(half_width - 0.3f * (wheel_width), connection_height, -half_length + wheel_radius);
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
	car->wheels[3].connection.Set(-half_width + 0.3f * (wheel_width ), connection_height, -half_length + wheel_radius);
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
		

	if (App->scene_intro->gameOver == true) 
		vehicle->SetPos(Ipos.x, 15.0f, Ipos.z);
	else
		vehicle->SetPos(Ipos.x, Ipos.y, Ipos.z);
	

	vehicle->SetLinearVelocity(vec3(0.0f, 0.0f, 0.0f));
	vehicle->SetAngularVelocity(vec3(0.0f, 0.0f, 0.0f));
	vehicle->Brake(BRAKE_POWER);
}


void ModulePlayer::OnCollision(PhysBody3D* bA, PhysBody3D* bB) {

	float bounceY = 1500.0f;
	float bounceZ = 0.0f;

	if (bA == veh1.vehicle) {

		bounceZ = veh1.vehicle->vehicle->getForwardVector().getZ() * 1000.0f;

		if (bB->type == PhysBodyType::BOUNCE_Y)
			veh1.vehicle->Push(0.0f, bounceY, 0.0f);

		if (bB->type == PhysBodyType::BOUNCE_XZ)
			veh1.vehicle->Push(0.0f, 0.0f, -bounceZ);

		if (bB->type == PhysBodyType::COIN) {

			App->scene_intro->CreateCoin();
			App->audio->PlayFx(coin_fx);
			bB->to_delete = true;
			if (veh1.Coins < 12) {

				veh1.Coins++;
				if (!veh1.maxCreached)
					veh1.boost_recover++;
			}
		}

		if (bB == veh2.vehicle && veh1.boosting == true && veh1.vehicle->GetKmh() > 150) {

			veh2.vehicle->info.color = Color(1.0f, 0.0f, 0.0f, 1.0f);
			veh2.Coins -= 2;
			veh2.Coins++;
			App->audio->PlayFx(loseCoin_fx);
			veh1.boosting = false;
		}
	}
	if (bA == veh2.vehicle) {

		bounceZ = veh2.vehicle->vehicle->getForwardVector().getZ() * 1000.0f;

		if (bB->type == PhysBodyType::BOUNCE_Y)
			veh2.vehicle->Push(0.0f, bounceY, 0.0f);

		if (bB->type == PhysBodyType::BOUNCE_XZ)
			veh2.vehicle->Push(0.0f, 0.0f, -bounceZ);

		if (bB->type == PhysBodyType::COIN) {

			App->scene_intro->CreateCoin();
			App->audio->PlayFx(coin_fx);
			bB->to_delete = true;
			if (veh2.Coins < 12) {

				veh2.Coins++;
				if(!veh2.maxCreached)
					veh2.boost_recover++;
			}	
		}

		if (bB == veh1.vehicle && veh2.boosting == true && veh2.vehicle->GetKmh() > 150) {

			veh1.vehicle->info.color = Red;
			veh1.Coins -= 2;
			veh2.Coins++;
			App->audio->PlayFx(loseCoin_fx);
			veh2.boosting = false;
		}

	}
}
