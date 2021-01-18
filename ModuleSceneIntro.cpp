#include "Globals.h"
#include <time.h> 
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
	App->audio->PlayMusic("audio/democide.ogg");
	Mix_VolumeMusic(10);
	lvlFx = App->audio->LoadFx("audio/lvl.ogg");
	gameWinFx = App->audio->LoadFx("audio/win.ogg");
	deadFx = App->audio->LoadFx("audio/dead.ogg");

	//1 = path			 //2 = path limit
	//3 = flag			 //4 = slider 
	//5 = obstacle		 //6 = trap
	//7 = invisible road //8 = win condition
	//9 = change lvl	 //10 = ramp
	//11 = big wall		 //12 = end ramp 
	//13 = clued path
	
	int circuit0[70]
	{
		2,2,2,2,2,2,2,
		2,2,2,1,2,2,2,
		2,2,2,1,2,2,2,
		2,2,2,10,2,2,2,
		2,2,2,12,2,2,2,
		2,2,2,1,2,2,2,
		2,2,2,1,2,2,2,
		2,2,2,10,2,2,2,
		2,2,2,9,2,2,2,
		2,2,2,2,2,2,2,
	};

	int circuit1[70]
	{
		2,2,2,2,2,2,2,
		2,2,2,1,2,2,2,
		2,2,1,1,1,2,2,
		2,2,10,2,1,2,2,
		2,2,12,2,10,2,2,
		2,2,1,2,4,2,2,
		11,2,12,2,10,2,2,
		2,2,1,1,1,2,2,
		2,2,2,9,2,2,2,
		2,2,2,2,2,2,2,
	};

	int circuit2[70]
	{
		2,2,2,2,2,2,2,
		2,2,2,1,2,2,2,
		2,2,1,1,1,2,2,
		2,2,1,1,1,2,2,
		11,2,13,2,6,2,2,
		2,2,1,2,1,2,2,
		2,2,1,2,1,2,2,
		2,2,1,1,1,2,2,
		2,2,2,9,2,2,2,
		2,2,2,2,2,2,2,
	};

	int circuit3[70]
	{
		2,2,2,2,2,2,2,
		2,2,2,1,2,2,2,
		2,2,1,13,1,2,2,
		2,2,1,7,1,2,2,
		11,2,6,7,6,2,2,
		2,2,5,7,5,2,2,
		2,2,1,7,1,2,2,
		2,2,1,1,1,2,2,
		2,2,2,9,2,2,2,
		2,2,2,2,2,2,2,
	};

	int circuit4[70]
	{
		2,2,2,2,2,2,2,
		2,2,2,1,2,2,2,
		2,2,1,1,1,2,2,
		2,7,13,2,13,7,2,
		11,7,6,2,6,7,2,
		2,7,5,2,5,7,2,
		2,2,1,2,1,2,2,
		2,2,1,1,1,2,2,
		2,2,2,9,2,2,2,
		2,2,2,2,2,2,2,
	};

	int circuit5[70]
	{
		2,2,2,2,2,2,2,
		2,2,2,1,1,1,2,
		2,2,2,2,2,1,2,
		2,1,1,1,1,1,2,
		11,1,2,2,2,2,2,
		2,1,1,1,1,1,2,
		2,2,2,2,2,1,2,
		2,2,1,1,1,1,2,
		2,9,1,2,2,2,2,
		2,2,2,2,2,2,2,
	};

	int circuit6[70]
	{
		2,2,2,9,2,2,2,
		2,2,2,1,2,2,2,
		2,2,2,6,2,2,2,
		2,2,2,6,2,2,2,
		11,2,2,6,2,2,2,
		2,2,2,5,2,2,2,
		2,2,2,6,2,2,2,
		2,2,2,6,2,2,2,
		2,2,2,6,2,2,2,
		2,2,2,2,2,2,2,
	};

	int circuit7[70]
	{
		2,2,2,2,2,2,2,
		2,2,2,1,2,2,2,
		2,2,2,1,2,2,2,
		2,2,2,10,2,2,2,
		11,1,1,1,2,2,2,
		2,5,2,2,2,2,2,
		2,1,1,1,1,1,2,
		2,2,2,2,2,10,2,
		2,8,1,1,1,5,2,
		2,2,2,2,2,2,2,
	};

	//load circuit, only for 7-column circuits
	for (int i = 0; i < 8; ++i)
	{
		if (i == 0) LoadCircuit(circuit, circuit0, i);
		else if (i == 1) LoadCircuit(circuit, circuit1, i);
		else if (i == 2) LoadCircuit(circuit, circuit2, i);
		else if (i == 3) LoadCircuit(circuit, circuit3, i);
		else if (i == 4) LoadCircuit(circuit, circuit4, i);
		else if (i == 5) LoadCircuit(circuit, circuit5, i);
		else if (i == 6) LoadCircuit(circuit, circuit6, i);
		else if (i == 7) LoadCircuit(circuit, circuit7, i);

	}

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	lvltime.Start();

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
	// player will recieve a clue after 30s in lvl
	if (lvltime.Read() / 1000 >= 30)
	{
		App->player->clue = true;
	}

	//player restarts after some time
	if (App->player->Nmap == 7)
	{
		if (run == true)
		{
			timetrial.Start();
			run = false;
		}
		if (timetrial.Read() / 1000 == 15 && win == true)
		{

			App->player->Restart(7);
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if ((body1 == pb_victory) && (body2 == (PhysBody3D*)App->player->vehicle) || (body2 == pb_victory) && (body2 == (PhysBody3D*)App->player->vehicle))
	{
		if (win)
		{
			Mix_VolumeMusic(0);
			App->audio->PlayFx(gameWinFx);
			App->player->playerTime.Stop();
			reset.Start();
			win = false;
			App->player->controls = false;
			App->player->reset = 10;
			App->player->Stop();
		}
		if (reset.Read() >= 5000)
		{
			App->player->Nmap = 0;
			App->player->GameWin();
		}

	}
	for (int i = 0; i < s_limits.Count(); i++)
	{
		if ((body1 == pb_limits[i]) && (body2 == (PhysBody3D*)App->player->vehicle) || (body2 == pb_limits[i]) && (body1 == (PhysBody3D*)App->player->vehicle))
		{
			App->audio->PlayFx(deadFx);
			App->player->Restart(App->player->Nmap);
		}
	}

	for (int i = 0; i < s_endlvl.Count(); i++)
	{
		if ((body1 == pb_endlvl[i]) && (body2 == (PhysBody3D*)App->player->vehicle) || (body2 == pb_endlvl[i]) && (body1 == (PhysBody3D*)App->player->vehicle))
		{
			if (count == 0)
			{
				App->audio->PlayFx(lvlFx);
				lvltime.Start();
				App->player->clue = false;
				App->player->reset++;
				App->player->Nmap++;
				App->player->Restart(App->player->Nmap);
				count++;
			}
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
		//Floor
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
		//Flag
		LOG("%i, %i", posX, posZ);
		break;
	case 4:
		//Floor
		cubes.Size(scale.x, scale.y, 30);
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 0);
		pb_cube->SetPos(posX, 1, posZ);
		pb_cube->painting = true;
		pb_cubes.PushBack(pb_cube);

		//Slider
		cubes.Size(scale.x, 8, scale.y);
		//cubes.color = Green;
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 100);

		pb_cube->SetPos(posX, 14.5, posZ);
		App->physics->AddConstraintSlider(*pb_cube, false);
		pb_cube->sliders = true;
		pb_cube->painting = true;
		pb_cube->clued = true;
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
		pb_cube->painting = true;
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
		pb_cube->painting = true;
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
		cubes.color = Yellow;
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 0);
		pb_cube->SetPos(posX, 1, posZ);
		pb_cube->painting = true;
		pb_cubes.PushBack(pb_cube);
		App->player->Nmap = 0;

		//victory sensor
		sensor_victory.Size(30, 1, 15);
		pb_victory = App->physics->AddBody(sensor_victory, 0);
		pb_victory->SetPos(posX, 3, posZ);
		pb_victory->GetTransform(&sensor_victory.transform);
		pb_victory->SetAsSensor(true);
		pb_victory->collision_listeners.add(this);
		break;
	case 9:

		//floor
		cubes.Size(scale.x, scale.y, scale.z);
		cubes.color = Yellow;
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 0);
		pb_cube->SetPos(posX, 1, posZ);
		pb_cube->painting = true;
		pb_cubes.PushBack(pb_cube);

		//change lvl
		cubes2.Size(scale.x, scale.y, scale.z);
		cubes2.color = Yellow;
		s_endlvl.PushBack(cubes2);
		pb_cube2 = App->physics->AddBody(cubes2, 0);
		pb_cube2->SetPos(posX, 3, posZ);
		pb_endlvl.PushBack(pb_cube2);


		break;

	case 10:
		//ramp start
		cubes.Size(scale.x, scale.y, scale.z - 15);
		cubes.SetRotation(-15, vec3(1, 0, 0));
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 0);
		pb_cube->SetPos(posX, 3, posZ - 10);
		pb_cube->painting = true;
		pb_cubes.PushBack(pb_cube);
		break;

	case 11:
		// big wall
		cubes.Size(1, 100, 500); 
		cubes.color = Black;
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 0);
		pb_cube->SetPos(posX, 1, posZ);
		pb_cube->painting = true;
		pb_cubes.PushBack(pb_cube);

		break;

	case 12:
		//ramp end
		cubes.Size(scale.x, scale.y, scale.z - 15);
		cubes.SetRotation(10, vec3(1, 0, 0));
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 0);
		pb_cube->SetPos(posX, 3, posZ+10);
		pb_cube->painting = true;
		pb_cubes.PushBack(pb_cube);
		break;

	case 13:
		//Clued floor
		cubes.Size(scale.x, scale.y, scale.z);
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 0);
		pb_cube->SetPos(posX, 1, posZ);
		pb_cube->painting = true;
		pb_cube->clued = true;
		pb_cubes.PushBack(pb_cube);
		break;
	default:
		break;
	}
}

int ModuleSceneIntro::Size(int* vec)
{
	int count = 0;
	for (int i = 0; vec[i] <= 13 && vec[i] >= 1; ++i)
	{
		count++;
	}
	return count;
}

void ModuleSceneIntro::Painting()
{
	Cube* floor_cube = new Cube(5000.0f, 0.0f, 800.0f);
	floor_cube->color = Green;
	floor_cube->Render();

	if (pb_cubes.Count() != 0 && s_cubes.Count() != 0 && s_cubes.Count() == pb_cubes.Count())
	{
		for (int i = 0; i < s_cubes.Count(); i++) 
		{
			pb_cubes[i]->GetTransform(&s_cubes[i].transform);

			//only paints necessary cubes
			if (pb_cubes[i]->painting == true)
			{
				s_cubes[i].Render();
			}

			//If the cube is a slider apply up and down an impulse
			if (pb_cubes[i]->sliders == true)
			{
				if (move)
				{
					count3 = 0;
					pb_cubes[i]->GetBody()->applyCentralImpulse(btVector3(0, 500, 0));
					count2++;
				}
				if (count2 >= 50)
				{
					move = false;
					pb_cubes[i]->GetBody()->applyCentralImpulse(btVector3(0, -500, 0));
					count3++;
				}
				if (count3 >= 50)
				{
					move = true;
					count2 = 0;
				}
			}
			
			if (pb_cubes[i]->clued == true)
			{
				if (App->player->clue == true)
				{
					clueCount++;
					if (clueCount <= 0)
					{
						s_cubes[i].color = Green;
					}

					else if (clueCount >= 21 && clueCount <= 40)
					{
						s_cubes[i].color = White;
					}
					else
					{
						clueCount = 0;
					}
				}
				else
				{
					s_cubes[i].color = White;
				}
			}
		}

	}

	delete floor_cube;
	floor_cube = nullptr;
}

void ModuleSceneIntro::LoadCircuit(int* lvlcircuit, int* circuitx, int poscircuit)
{	
	// distance between circuits
	int desp = poscircuit * 8 * 30;

	//choosing the right circuit
	for (int i = 0; i < Size(circuitx); ++i)
	{
		lvlcircuit[i] = circuitx[i];
	}
	//create map
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 7; i++) {
			CreateFloor(vec3(30, 1, 30), 30 * i + desp, 30 * j, circuit[(7 * j) + i]);
		}
	}
	//create sensors
	if (pb_limits.Count() != 0 && s_limits.Count() != 0 && s_limits.Count() == pb_limits.Count())
	{
		for (int i = 0; i < s_limits.Count(); i++)
		{
			pb_limits[i]->SetAsSensor(true);
			pb_limits[i]->collision_listeners.add(this);
		}

		for (int i = 0; i < s_endlvl.Count(); i++)
		{
			pb_endlvl[i]->SetAsSensor(true);
			pb_endlvl[i]->collision_listeners.add(this);
		}
	}
}

void ModuleSceneIntro::LevelSelector(int lvlnumber)
{
	lvltime.Start();
	App->player->clue = false;
	switch (lvlnumber)
	{
	case 0:
		App->player->reset = 0;
		App->player->Nmap = 0;
		break;
	case 1:
		App->player->reset = 1;
		App->player->Nmap = 1;
		break;
	case 2:
		App->player->reset = 2;
		App->player->Nmap = 2;
		break;
	case 3:
		App->player->reset = 3;
		App->player->Nmap = 3;
		break;
	case 4:
		App->player->reset = 4;
		App->player->Nmap = 4;
		break;
	case 5:
		App->player->reset = 5;
		App->player->Nmap = 5;
		break;
	case 6:
		App->player->reset = 6;
		App->player->Nmap = 6;
		break;
	case 7:
		App->player->reset = 7;
		App->player->Nmap = 7;
		break;
	case 8:
		App->player->reset = 8;
		App->player->Nmap = 8;
		break;
	case 9:
		App->player->reset = 9;
		App->player->Nmap = 9;
		break;
	default:
		break;
	}
	App->player->Restart(App->player->Nmap);
}