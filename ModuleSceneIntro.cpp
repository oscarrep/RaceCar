#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

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
	App->audio->PlayMusic("audio/bushweek.ogg");
	Mix_VolumeMusic(50);

	int circuit1[70]
	{
		//1 = create path //2 = create path limit
		//3 = create flag //4 = create slider //5 = create obstacle
		2,2,2,1,2,2,2,
		2,2,2,7,2,2,2,
		2,2,2,1,2,2,2,
		2,2,1,1,1,2,2,
		2,2,1,7,6,2,2,
		2,2,5,7,5,2,2,
		2,2,1,7,1,2,2,
		2,2,1,7,1,2,2,
		2,2,1,5,1,2,2,
		2,2,2,8,2,2,2,
	};
	//load circuit1, only for 7-column circuits
	LoadCircuit(circuit, circuit1);

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	/*float size = 2.0f;
	for (int i = 0; i < 5; i++)
	{
		chain[i].radius = size;
		chain[i].SetPos(40 + (size * (i + 1)) + (size * i), 10.f, 40);
		pb_chain[i] = App->physics->AddBody(chain[i]);
		if (i > 0)
		{
			App->physics->AddConstraintHinge(*pb_chain[i], *pb_chain[i - 1], vec3(-2 * size, 0, 0), vec3(0, 0, 0), vec3(0, 1, 0), vec3(0, 1, 0));
		}

	}*/

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
		pb_cube->SetPos(posX, 1, posZ);
		pb_cube->painting = true;
		pb_cubes.PushBack(pb_cube);
		break;
	case 2:
		//Limit
		cubes2.Size(scale.x, scale.y, scale.z);
		s_limits.PushBack(cubes2);
		pb_cube2 = App->physics->AddBody(cubes2, 0);
		pb_cube2->SetPos(posX, 1, posZ);
		pb_limits.PushBack(pb_cube2);
		break;
	case 3:
		//flag
		/*cubes2.Size(scale.x, scale.y, scale.z);
		s_cubes.PushBack(cubes2);
		pb_cube2 = App->physics->AddBody(cubes2, 0);
		pb_cube2->SetPos(posX, 0, posZ);
		pb_cubes.PushBack(pb_cube2);*/
		LOG("%i, %i", posX, posZ);
		break;
	case 4:
		//Floor
		cubes.Size(scale.x, scale.y, scale.z);
		cubes.color = Green;
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 0);
		pb_cube->SetPos(posX, 1, posZ);
		pb_cube->painting = true;
		pb_cubes.PushBack(pb_cube);

		//SLIDER
		cubes.Size(scale.x, 8, scale.y);
		cubes.color = Green;
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 100);

		pb_cube->SetPos(posX, 14.5, posZ);
		App->physics->AddConstraintSlider(*pb_cube, false);
		pb_cube->painting = true;
		pb_cubes.PushBack(pb_cube);
		break;
	case 5:
		//Floor
		cubes.Size(scale.x, scale.y, scale.z);
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 0);
		pb_cube->SetPos(posX, 1, posZ);
		pb_cube->painting = true;
		pb_cubes.PushBack(pb_cube);

		//Obstacle
		cubes.Size(15, 8, 2);
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 0);
		pb_cube->SetPos(posX, 3, posZ);
		pb_cubes.PushBack(pb_cube);
		break;
	case 6:
		//floor
		cubes.Size(scale.x, scale.y, scale.z);
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 0);
		pb_cube->SetPos(posX, 1, posZ);
		pb_cubes.PushBack(pb_cube);

		//limit
		cubes2.Size(scale.x, scale.y, scale.z);
		s_limits.PushBack(cubes2);
		pb_cube2 = App->physics->AddBody(cubes2, 0);
		pb_cube2->SetPos(posX, 1.1, posZ);
		pb_limits.PushBack(pb_cube2);
		break;
	case 7:
		//invisible floor
		cubes.Size(scale.x, scale.y, scale.z);
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 0);
		pb_cube->SetPos(posX, 1, posZ);
		pb_cube->painting = false;
		pb_cubes.PushBack(pb_cube);
		break;
	case 8:
		//floor
		cubes.Size(scale.x, scale.y, scale.z);
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 0);
		pb_cube->SetPos(posX, 1, posZ);
		pb_cube->painting = true;
		pb_cubes.PushBack(pb_cube);

		//victory sensor
		sensor_victory.Size(30, 1, 15);
		pb_victory = App->physics->AddBody(sensor_victory, 0);
		pb_victory->SetPos(posX, 3, posZ);
		pb_victory->GetTransform(&sensor_victory.transform);
		pb_victory->SetAsSensor(true);
		pb_victory->collision_listeners.add(this);
	}

}

void ModuleSceneIntro::Painting()
{
	Cube* floor_cube = new Cube(2500.0f, 0.0f, 2500.0f);
	floor_cube->color = Green;
	floor_cube->Render();

	if (pb_cubes.Count() != 0 && s_cubes.Count() != 0 && s_cubes.Count() == pb_cubes.Count()) 
	{
		for (int i = 0; i < s_cubes.Count(); i++) {
			pb_cubes[i]->GetTransform(&s_cubes[i].transform);
			if (pb_cubes[i]->painting == true)
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

	/*for (int i = 0; i < 5; i++)
	{
		pb_chain[i]->GetTransform(&(chain[i].transform));
		chain[i].Render();
	}*/
	delete floor_cube;
	floor_cube = nullptr;
}

int ModuleSceneIntro::Size(int* vec)
{
	int count = 0;
	for (int i = 0; vec[i] <= 8 && vec[i] >= 1; ++i)
	{
		count++;
	}
	return count;
}

void ModuleSceneIntro::LoadCircuit(int* lvlcircuit, int* circuitx)
{
	for (int i = 0; i < Size(circuitx); ++i)
	{
		lvlcircuit[i] = circuitx[i];
	}
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 7; i++) {
			CreateFloor(vec3(30, 1, 30), 30 * i, 30 * j, circuit[(7 * j) + i]);
		}
	}

	if (pb_limits.Count() != 0 && s_limits.Count() != 0 && s_limits.Count() == pb_limits.Count())
	{
		for (int i = 0; i < s_limits.Count(); i++)
		{
			pb_limits[i]->SetAsSensor(true);
			pb_limits[i]->collision_listeners.add(this);
		}
	}
}