#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	float ShowTime();
	void Restart();
	void GameWin();
	void UI(bool reset);
	void SetScore();
	void Stop();


public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	float bestTime = 0.0f;
	Timer playerTime;

	bool controls = true;
	bool reset = false;

};