#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet/include/btBulletDynamicsCommon.h"
#include "ModuleInput.h"
#include "Application.h"
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
	wheel.color = Green;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	chassis = Cube(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();

	chassis.color = info.color;

	cabina = Cube(3, 1, 5);

	vehicle->getChassisWorldTransform().getOpenGLMatrix(&cabina.transform);
	btVector3 cabina_offset(0, 3, 0);
	
	/*btQuaternion q2 = q;
	q2.setRotation(btVector3(1, 0, 0), 45);*/
	cabina_offset = cabina_offset.rotate(q.getAxis(), q.getAngle());

	cabina.transform.M[12] += cabina_offset.getX();
	cabina.transform.M[13] += cabina_offset.getY();
	cabina.transform.M[14] += cabina_offset.getZ();
	
	//cabina.SetRotation(10, vec3(1, 0, 0));
	cabina.color.Set(0, 1, 1);


	light1 = Cube(0.8, 0.5, 0.5);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&light1.transform);
	btVector3 light1_offset(1.5, 2.4, 4.1);
	light1_offset = light1_offset.rotate(q.getAxis(), q.getAngle());

	light1.transform.M[12] += light1_offset.getX();
	light1.transform.M[13] += light1_offset.getY();
	light1.transform.M[14] += light1_offset.getZ();
	

	light2 = Cube(0.8, 0.5, 0.5);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&light2.transform);
	btVector3 light2_offset(-1.5, 2.4, 4.1);
	light2_offset = light2_offset.rotate(q.getAxis(), q.getAngle());

	light2.transform.M[12] += light2_offset.getX();
	light2.transform.M[13] += light2_offset.getY();
	light2.transform.M[14] += light2_offset.getZ();


	light3 = Cube(0.8, 0.5, 0.5);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&light3.transform);
	btVector3 light3_offset(-1.5, 2.4, -4.1);
	light3_offset = light3_offset.rotate(q.getAxis(), q.getAngle());

	light3.transform.M[12] += light3_offset.getX();
	light3.transform.M[13] += light3_offset.getY();
	light3.transform.M[14] += light3_offset.getZ();

	
		

	light4 = Cube(0.8, 0.5, 0.5);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&light4.transform);
	btVector3 light4_offset(1.5, 2.4, -4.1);
	light4_offset = light4_offset.rotate(q.getAxis(), q.getAngle());

	light4.transform.M[12] += light4_offset.getX();
	light4.transform.M[13] += light4_offset.getY();
	light4.transform.M[14] += light4_offset.getZ();
	
	

	if (!forward){
		light1.color.Set(0.5, 0.5, 0);
		light2.color.Set(0.5, 0.5, 0);
		light3.color.Set(1, 0, 0);
		light4.color.Set(1, 0, 0);
	}
	if (forward) {
		light1.color.Set(1, 1, 0);
		light2.color.Set(1, 1, 0);
		light3.color.Set(0.3, 0, 0);
		light4.color.Set(0.3, 0, 0);
	}
		



	light3.Render();
	light4.Render();
	light2.Render();
	light1.Render();
	cabina.Render();
	chassis.Render();
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
