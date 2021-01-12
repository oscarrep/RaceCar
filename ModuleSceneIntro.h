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
	void Painting();

public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	p2DynArray<PhysBody3D*> pb_cubes;
	p2DynArray<Cube>s_cubes;
	
	p2DynArray<PhysBody3D*> pb_limits;
	p2DynArray<Cube>s_limits;

	//PhysBody3D* pb_cube[5];
	//Cube s_cube[5];

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysBody3D* pb_chain[5];
	Sphere chain[5];

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	PhysBody3D* pb_victory;
	Cube sensor_victory;

	Timer reset;
	bool win = true;

	int circuit[70]{
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
		2,2,2,1,2,2,2,
	};

	
};
