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
		2,1,1,2,
		2,1,1,2,
		2,1,1,2,
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
	if ((body1 == pb_victory) || (body2 == pb_victory))
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
		if ((body1 == pb_limits[i]) || (body2 == pb_limits[i]))
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
	cubes2.color = Yellow;
	cubes2.SetRotation(-15, vec3(1, 0, 0));

	switch (cir)
	{
	case 1:
		cubes.Size(scale.x, scale.y, scale.z);
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 0);
		pb_cube->SetPos(posX, 0, posZ);
		pb_cubes.PushBack(pb_cube);
		break;
	case 2:
		break;
	case 3:
		cubes2.Size(scale.x, scale.y, scale.z);
		s_cubes.PushBack(cubes2);
		pb_cube2 = App->physics->AddBody(cubes2, 0);
		pb_cube2->SetPos(posX, 0, posZ);
		pb_cubes.PushBack(pb_cube2);
		LOG("%i, %i", posX, posZ);
		break;
	default:
		break;
	}

}

void ModuleSceneIntro::Painting()
{
	if (pb_cubes.Count() != 0 && s_cubes.Count() != 0 && s_cubes.Count() == pb_cubes.Count()) {
		for (int i = 0; i < s_cubes.Count(); i++) {
			pb_cubes[i]->GetTransform(&s_cubes[i].transform);
			s_cubes[i].Render();
		}

	}

	if (pb_limits.Count() != 0 && s_limits.Count() != 0 && s_limits.Count() == pb_limits.Count()) {
		for (int i = 0; i < s_limits.Count(); i++) {
			pb_limits[i]->GetTransform(&s_limits[i].transform);
			pb_limits[i]->SetAsSensor(true);
			pb_limits[i]->collision_listeners.add(this);
		}
		/*sensor_victory.Render();*/
	}
}