#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "ModuleSceneIntro.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	playerTime.Start();

	// Car properties ----------------------------------------
	car.chassis_size.Set(3, 1.5, 6);
	car.chassis_offset.Set(0, 1.5, 0);
	car.cabin_size.Set(3, 0.25, 3);
	car.cabin_offset.Set(0, 4, -1.5);
	car.headlight_size.Set(0.5, 0.5, 0.5);
	car.headlight_offset.Set(1, 1.5, 3);
	car.headlight2_size.Set(0.5, 0.5, 0.5);
	car.headlight2_offset.Set(-1, 1.5, 3);
	car.stickLeftDown_size.Set(0.25, 1.7, 0.25);
	car.stickLeftDown_offset.Set(1.38, 3.09, -2.88);
	car.stickLeftUp_size.Set(0.25, 1.7, 0.25);
	car.stickLeftUp_offset.Set(1.38, 3.09, -0.12);
	car.stickRightDown_size.Set(0.25, 1.7, 0.25);
	car.stickRightDown_offset.Set(-1.38, 3.09, -2.88);
	car.stickRightUp_size.Set(0.25, 1.7, 0.25);
	car.stickRightUp_offset.Set(-1.38, 3.09, -0.12);
	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(30, 2, 30);
	/*vehicle->collision_listeners.add(this);*/
	
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
	turn = acceleration = brake = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && controls)
	{
		acceleration = MAX_ACCELERATION;
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && controls)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && controls)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && controls)
	{
		acceleration = -MAX_ACCELERATION;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && controls)
	{
		brake = BRAKE_POWER;
	}

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		playerTime.Start();
		Restart();
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();
	
	UI(reset);

	return UPDATE_CONTINUE;
}

float ModulePlayer::ShowTime()
{
	return playerTime.Read() / 1000;
}

void ModulePlayer::Restart()
{
	mat4x4 matrix;
	vehicle->SetTransform(matrix.M);
	Stop();
	vehicle->SetPos(30, 2, 30);
}

void ModulePlayer::GameWin()
{
	SetScore();
	Restart();
	playerTime.Start();
	App->scene_intro->win = true;
	controls = true;
	reset = false;
}

void ModulePlayer::UI(bool reset)
{
	char title[80];

	if (!reset)
	{
		sprintf_s(title, "%.1f Km/h Time: %.0f Best Time: %.0f", vehicle->GetKmh(), ShowTime(), bestTime);
	}
	if (reset)
	{
		sprintf_s(title, "YOU WON! Your Time: %.0f Best Time: %.0f", ShowTime(), bestTime);
	}

	App->window->SetTitle(title);
}

void ModulePlayer::SetScore()
{
	if (bestTime == 0)
	{
		bestTime = ShowTime();
	}
	if (ShowTime() < bestTime)
	{
		bestTime = ShowTime();
	}
}

void ModulePlayer::Stop()
{
	vehicle->GetBody()->setAngularVelocity({ 0, 0, 0 });
	vehicle->GetBody()->setLinearVelocity({ 0, 0, 0 });
}