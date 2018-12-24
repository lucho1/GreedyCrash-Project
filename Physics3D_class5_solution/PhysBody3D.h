#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"
<<<<<<< HEAD
=======
#include "glmath.h"
>>>>>>> SECCOPYBranch

class btRigidBody;
class Module;

<<<<<<< HEAD
=======
enum class PhysBodyType {

	BOUNCE_Y,
	BOUNCE_XZ,
	OBJECT,
	LIMIT,
	DEFAULT
	
};

>>>>>>> SECCOPYBranch
// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
<<<<<<< HEAD
public:
=======

public:

>>>>>>> SECCOPYBranch
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
<<<<<<< HEAD
	void SetPos(float x, float y, float z);
	void SetAsSensor(bool is_sensor);
	bool IsSensor()const;
=======

	void SetPos(float x, float y, float z);
	void SetRotation(vec3 axis, float angle, bool converse = true);
	void AddRotation(vec3 axis, float angle, float converse = true);
	void SetLinearVelocity(vec3 vel);
	const vec3 GetLinearVelocity() const;
	

>>>>>>> SECCOPYBranch
private:
	btRigidBody* body = nullptr;

public:
	p2List<Module*> collision_listeners;
<<<<<<< HEAD
public:
	///COLLISIONS
	bool is_sensor;
=======
	PhysBodyType type;

>>>>>>> SECCOPYBranch
};

#endif // __PhysBody3D_H__