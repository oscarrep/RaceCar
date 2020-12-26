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

	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 4; i++) {
			int cir = circuit[(4 * j) + i];
			CreateFloor(vec3(30, 1, 30), 30 * i, 30 * j, circuit[(4 * j) + i]);
		}
	}

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
	/*Plane p(0, 1, 0, 0);
	p.color = Yellow;
	p.axis = true;
	p.Render();*/

	if (pb_cubes.Count() != 0 && s_cubes.Count() != 0 && s_cubes.Count() == pb_cubes.Count()) {
		for (int i = 0; i < s_cubes.Count(); i++) {
			pb_cubes[i]->GetTransform(&s_cubes[i].transform);
			s_cubes[i].Render();
		}

	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	//if (body1 == )
}

void ModuleSceneIntro::CreateFloor(vec3 scale, int posX, int posZ, int cir) 
{
	Cube cubes;
	PhysBody3D* pb_cube;
	Cube cubes2;
	cubes2.color = Yellow;
	cubes2.SetRotation(-15, vec3(1, 0, 0));
	PhysBody3D* pb_cube2;

	switch (cir)
	{
	case 1:
		cubes.Scale(scale.x, scale.y, scale.z);
		s_cubes.PushBack(cubes);
		pb_cube = App->physics->AddBody(cubes, 0);
		pb_cube->SetPos(posX, 0, posZ);
		pb_cubes.PushBack(pb_cube);
		break;
	case 2:
		break;
	case 3:
		cubes2.Scale(scale.x, scale.y, scale.z);
		s_cubes.PushBack(cubes2);
		pb_cube2 = App->physics->AddBody(cubes2, 0);
		pb_cube2->SetPos(posX, 0, posZ);
		pb_cubes.PushBack(pb_cube2);
		break;
	default:
		break;
	}

}