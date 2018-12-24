#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"
#include "glmath.h"

class btRigidBody;
class Module;

enum class PhysBodyType {

	BOUNCE_Y,
	BOUNCE_XZ,
	OBJECT,
	LIMIT,
	COIN,
	DEFAULT

};

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
	void SetRotation(vec3 axis, float angle, bool converse = true);
	void AddRotation(vec3 axis, float angle, float converse = true);
	void SetLinearVelocity(vec3 vel);
	const vec3 GetLinearVelocity() const;
	void SetAsSensor(bool is_sensor);
	bool IsSensor()const;

private:
	btRigidBody* body = nullptr;

public:
	p2List<Module*> collision_listeners;

public:
	///COLLISIONS
	bool is_sensor;
	bool ToDelete = false;
	PhysBodyType type;

};

#endif // __PhysBody3D_H__
