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

	Cube stickLeftDown(info.stickLeftDown_size.x, info.stickLeftDown_size.y, info.stickLeftDown_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&stickLeftDown.transform);

	Cube stickLeftUp(info.stickLeftUp_size.x, info.stickLeftUp_size.y, info.stickLeftUp_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&stickLeftUp.transform);

	Cube stickRightUp(info.stickRightUp_size.x, info.stickRightUp_size.y, info.stickRightUp_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&stickRightUp.transform);

	Cube stickRightDown(info.stickRightDown_size.x, info.stickRightDown_size.y, info.stickRightDown_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&stickRightDown.transform);

	Cube backheadlight(info.backheadlight_size.x, info.backheadlight_size.y, info.backheadlight_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&backheadlight.transform);

	Cube backheadlight2(info.backheadlight2_size.x, info.backheadlight2_size.y, info.backheadlight2_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&backheadlight2.transform);

	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	btVector3 cabin_offset(info.cabin_offset.x, info.cabin_offset.y, info.cabin_offset.z);
	cabin_offset = cabin_offset.rotate(q.getAxis(), q.getAngle());

	btVector3 headlight_offset(info.headlight_offset.x, info.headlight_offset.y, info.headlight_offset.z);
	headlight_offset = headlight_offset.rotate(q.getAxis(), q.getAngle());

	btVector3 headlight2_offset(info.headlight2_offset.x, info.headlight2_offset.y, info.headlight2_offset.z);
	headlight2_offset = headlight2_offset.rotate(q.getAxis(), q.getAngle());

	btVector3 stickLeftDown_offset(info.stickLeftDown_offset.x, info.stickLeftDown_offset.y, info.stickLeftDown_offset.z);
	stickLeftDown_offset = stickLeftDown_offset.rotate(q.getAxis(), q.getAngle());

	btVector3 stickRightDown_offset(info.stickRightDown_offset.x, info.stickRightDown_offset.y, info.stickRightDown_offset.z);
	stickRightDown_offset = stickRightDown_offset.rotate(q.getAxis(), q.getAngle());

	btVector3 stickLeftUp_offset(info.stickLeftUp_offset.x, info.stickLeftUp_offset.y, info.stickLeftUp_offset.z);
	stickLeftUp_offset = stickLeftUp_offset.rotate(q.getAxis(), q.getAngle());

	btVector3 stickRightUp_offset(info.stickRightUp_offset.x, info.stickRightUp_offset.y, info.stickRightUp_offset.z);
	stickRightUp_offset = stickRightUp_offset.rotate(q.getAxis(), q.getAngle());

	btVector3 backheadlight_offset(info.backheadlight_offset.x, info.backheadlight_offset.y, info.backheadlight_offset.z);
	backheadlight_offset = backheadlight_offset.rotate(q.getAxis(), q.getAngle());

	btVector3 backheadlight2_offset(info.backheadlight2_offset.x, info.backheadlight2_offset.y, info.backheadlight2_offset.z);
	backheadlight2_offset = backheadlight2_offset.rotate(q.getAxis(), q.getAngle());

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

	stickLeftDown.transform.M[12] += stickLeftDown_offset.getX();
	stickLeftDown.transform.M[13] += stickLeftDown_offset.getY();
	stickLeftDown.transform.M[14] += stickLeftDown_offset.getZ();

	stickLeftUp.transform.M[12] += stickLeftUp_offset.getX();
	stickLeftUp.transform.M[13] += stickLeftUp_offset.getY();
	stickLeftUp.transform.M[14] += stickLeftUp_offset.getZ();

	stickRightUp.transform.M[12] += stickRightUp_offset.getX();
	stickRightUp.transform.M[13] += stickRightUp_offset.getY();
	stickRightUp.transform.M[14] += stickRightUp_offset.getZ();

	stickRightDown.transform.M[12] += stickRightDown_offset.getX();
	stickRightDown.transform.M[13] += stickRightDown_offset.getY();
	stickRightDown.transform.M[14] += stickRightDown_offset.getZ();

	backheadlight.transform.M[12] += backheadlight_offset.getX();
	backheadlight.transform.M[13] += backheadlight_offset.getY();
	backheadlight.transform.M[14] += backheadlight_offset.getZ();

	backheadlight2.transform.M[12] += backheadlight2_offset.getX();
	backheadlight2.transform.M[13] += backheadlight2_offset.getY();
	backheadlight2.transform.M[14] += backheadlight2_offset.getZ();

	chassis.color = Red;
	cabin.color = Red;
	headlight.color = Yellow;
	headlight2.color = Yellow;
	backheadlight.color = Yellow;
	backheadlight2.color = Yellow;
	stickRightDown.color = Red;
	stickRightUp.color = Red;
	stickLeftDown.color = Red;
	stickLeftUp.color = Red;

	chassis.Render();
	cabin.Render();
	headlight.Render();
	headlight2.Render();
	backheadlight.Render();
	backheadlight2.Render();
	headlight2.Render();
	stickRightDown.Render();
	stickRightUp.Render();
	stickLeftDown.Render();
	stickLeftUp.Render();
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