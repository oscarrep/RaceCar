#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModulePlayer.h"
//#include "ModuleAudio.h"

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

	int circuit[40] // 1 = create a path ; 2 = create a limit path;
	{
		2,2,2,2,
		2,1,1,2,
		2,1,1,2,
		2,1,1,2,
		2,1,1,2,
		2,5,5,2,
		2,1,1,2,
		2,4,1,2,
		2,1,1,2,
		2,1,1,1
	};

	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 4; i++) {
			int cir = circuit[(4 * j) + i];
			//CreateFloor(vec3(30, 1, 30), 30 * i, 30 * j, circuit[(4 * j) + i]);
		}
	}

	sensor_victory.color = Yellow;
	sensor_victory.Size(15, 1, 30);
	pb_victory = App->physics->AddBody(sensor_victory, 0);
	pb_victory->SetPos(90, 1, 270);
	pb_victory->GetTransform(&sensor_victory.transform);
	pb_victory->SetAsSensor(true);
	pb_victory->collision_listeners.add(this);

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	float size = 2.0f;
	for (int i = 0; i < 5; i++)
	{
		chain[i].radius = size;
		chain[i].SetPos(40 + (size * (i + 1)) + (size * i), 10.f, 40);
		pb_chain[i] = App->physics->AddBody(chain[i]);
		if (i > 0)
		{
			App->physics->AddConstraintHinge(*pb_chain[i], *pb_chain[i - 1], vec3(-2 * size, 0, 0), vec3(0, 0, 0), vec3(0, 1, 0), vec3(0, 1, 0));
		}

	}

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

	Painting();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if ((body1 == pb_victory) && (body2 == (PhysBody3D*)App->player->vehicle) || (body2 == pb_victory) && (body2 == (PhysBody3D*)App->player->vehicle))
	{
		if (win)
		{
			App->player->playerTime.Stop();
			reset.Start();
			win = false;
			App->player->controls = false;
			App->player->reset = true;
			App->player->Stop();
		}
	}

	if (reset.Read() >= 5000)
	{
		App->player->GameWin();
	}

	for (int i = 0; i < s_limits.Count(); i++)
	{
		if ((body1 == pb_limits[i]) && (body2 == (PhysBody3D*)App->player->vehicle) || (body2 == pb_limits[i]) && (body2 == (PhysBody3D*)App->player->vehicle))
		{
			App->player->Restart();
		}
	}

}

void ModuleSceneIntro::CreateFloor(vec3 scale, int posX, int posZ, int cir) 
{
	Cube cubes;
	PhysBody3D* pb_cube;

	Cube cubes2;
	PhysBody3D* pb_cube2;

	switch (cir)
	{
	case 1:
		//floor
		cubes.Size(scale.x, scale.y, scale.z);
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 0);
		pb_cube->SetPos(posX, 0, posZ);
		pb_cubes.PushBack(pb_cube);
		break;
	case 2:
		//Limit
		cubes2.Size(scale.x, scale.y, scale.z);
		s_limits.PushBack(cubes2);
		pb_cube2 = App->physics->AddBody(cubes2, 0);
		pb_cube2->SetPos(posX, 0, posZ);
		pb_limits.PushBack(pb_cube2);
		break;
	case 3:
		//flag
		cubes2.Size(scale.x, scale.y, scale.z);
		s_cubes.PushBack(cubes2);
		pb_cube2 = App->physics->AddBody(cubes2, 0);
		pb_cube2->SetPos(posX, 0, posZ);
		pb_cubes.PushBack(pb_cube2);
		LOG("%i, %i", posX, posZ);
		break;
	case 4:
		//Floor
		cubes.Size(scale.x, scale.y, scale.z);
		cubes.color = Green;
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 0);
		pb_cube->SetPos(posX, 0, posZ);
		pb_cubes.PushBack(pb_cube);

		//SLIDER
		cubes.Size(scale.x, 7, scale.y);
		cubes.color = Red;
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 100);

		pb_cube->SetPos(posX, 13.5, posZ);
		App->physics->AddConstraintSlider(*pb_cube, true);
		pb_cubes.PushBack(pb_cube);
		break;
	case 5:
		//Floor
		cubes.Size(scale.x, scale.y, scale.z);
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 0);
		pb_cube->SetPos(posX, 0, posZ);
		pb_cubes.PushBack(pb_cube);

		//Obstacle
		cubes.Size(15, 7, 2);
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 0);
		pb_cube->SetPos(posX, 3, posZ);
		pb_cubes.PushBack(pb_cube);
		break;
	default:
		break;
	}

}

void ModuleSceneIntro::Painting()
{
	if (pb_cubes.Count() != 0 && s_cubes.Count() != 0 && s_cubes.Count() == pb_cubes.Count()) 
	{
		for (int i = 0; i < s_cubes.Count(); i++) {
			pb_cubes[i]->GetTransform(&s_cubes[i].transform);
			s_cubes[i].Render();
		}

	}

	if (pb_limits.Count() != 0 && s_limits.Count() != 0 && s_limits.Count() == pb_limits.Count()) 
	{
		for (int i = 0; i < s_limits.Count(); i++) {
			pb_limits[i]->GetTransform(&s_limits[i].transform);
			pb_limits[i]->SetAsSensor(true);
			pb_limits[i]->collision_listeners.add(this);
		}
		/*sensor_victory.Render();*/
	}

	for (int i = 0; i < 5; i++)
	{
		pb_chain[i]->GetTransform(&(chain[i].transform));
		chain[i].Render();
	}
}