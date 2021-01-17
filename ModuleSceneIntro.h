#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2
#define MAX_CIRCUITSIZE 300

struct PhysBody3D;
struct PhysMotor3D;

enum FLOOR_TYPE 
{
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
	int Size(int* vec);
	void LoadCircuit(int* lvlcircuit, int* circuitx, int poscircuit);

public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	PhysBody3D* pb_slider;
	Cube* slid = new Cube(30, 8, 1);

	p2DynArray<PhysBody3D*> pb_cubes;
	p2DynArray<Cube>s_cubes;
	
	p2DynArray<PhysBody3D*> pb_limits;
	p2DynArray<Cube>s_limits;

	PhysBody3D* pb_cube[5];
	Cube s_cube[5];

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	Sphere chain;
	Cube  rightstick;
	PhysBody3D* pb_chain, * pb_leftstick, * pb_rightstick, * pb_pole;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	PhysBody3D* pb_victory;
	Cube sensor_victory;

	p2DynArray<PhysBody3D*> pb_endlvl;
	p2DynArray<Cube>s_endlvl;

	Timer reset;
	Timer lvltime;
	bool win = true;
	bool first = true;
	bool move = true;

	int count2 = 0;
	int count3 = 0;
	int count = 0;
	int lvlFx = 0;
	int gameWinFx = 0;

	int circuit[MAX_CIRCUITSIZE];

};
