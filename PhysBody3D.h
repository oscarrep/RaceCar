#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"

class btRigidBody;
class Module;
class vec3;

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	void SetAsSensor(bool is_sensor);
	void SetAngularVelocity(float x, float y, float z);

	btRigidBody* GetBody();
	vec3 GetPos() const;
private:
	btRigidBody* body = nullptr;
	bool is_sensor = false;


public:
	p2List<Module*> collision_listeners;
	bool painting = true;
	bool sliders = false;

};

#endif // __PhysBody3D_H__