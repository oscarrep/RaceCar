#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	Cylinder wheel;

	wheel.color = Blue;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	Cube cabin(info.cabin_size.x, info.cabin_size.y, info.cabin_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&cabin.transform);
	Cube headlight(info.headlight_size.x, info.headlight_size.y, info.headlight_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&headlight.transform);

	Cube headlight2(info.headlight2_size.x, info.headlight2_size.y, info.headlight2_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&headlight2.transform);

	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	btVector3 cabin_offset(info.cabin_offset.x, info.cabin_offset.y, info.cabin_offset.z);
	cabin_offset = cabin_offset.rotate(q.getAxis(), q.getAngle());

	btVector3 headlight_offset(info.headlight_offset.x, info.headlight_offset.y, info.headlight_offset.z);
	headlight_offset = headlight_offset.rotate(q.getAxis(), q.getAngle());

	btVector3 headlight2_offset(info.headlight2_offset.x, info.headlight2_offset.y, info.headlight2_offset.z);
	headlight2_offset = headlight2_offset.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();

	cabin.transform.M[12] += cabin_offset.getX();
	cabin.transform.M[13] += cabin_offset.getY();
	cabin.transform.M[14] += cabin_offset.getZ();

	headlight.transform.M[12] += headlight_offset.getX();
	headlight.transform.M[13] += headlight_offset.getY();
	headlight.transform.M[14] += headlight_offset.getZ();

	headlight2.transform.M[12] += headlight2_offset.getX();
	headlight2.transform.M[13] += headlight2_offset.getY();
	headlight2.transform.M[14] += headlight2_offset.getZ();

	chassis.color = White;
	cabin.color = Red;
	headlight.color = Yellow;
	headlight2.color = Yellow;

	chassis.Render();
	cabin.Render();
	headlight.Render();
	headlight2.Render();
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}