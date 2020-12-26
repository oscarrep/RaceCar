#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

enum FLOOR_TYPE {
	TOP_FLOOR,
	BOTTOM_FLOOR,
	WALL,
	EMPTY_FLOOR,
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	void CreateFloor(vec3 scale, int posX, int posZ, int cir);
	//void CreateLimit(vec3 scale, int posX, int posZ, int lim);


public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	int circuit[39] // 1 = create a path ; 2 = doesnt create a path;
	{
		1,2,2,2,
		1,1,2,2,
		2,1,1,2,
		2,2,1,2,
		2,2,1,1,
		2,2,2,1,
		2,1,1,1,
		2,1,2,2,
		2,1,1,1,
		2,2,2
	};

	p2DynArray<PhysBody3D*> pb_cubes;
	p2DynArray<Cube>s_cubes;
	
	p2DynArray<PhysBody3D*> pb_cylinders;
	p2DynArray<Cylinder>s_cylinders;

	//PhysBody3D* pb_cube[5];
	//Cube s_cube[5];

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	Cube cubes2;
	PhysBody3D* pb_cube2;
};
