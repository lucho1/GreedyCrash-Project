#include "PhysBody3D.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// =================================================
PhysBody3D::PhysBody3D(btRigidBody* body) : body(body)
{}


// ---------------------------------------------------------
PhysBody3D::~PhysBody3D()
{
	delete body;
}

// ---------------------------------------------------------
void PhysBody3D::Push(float x, float y, float z)
{
	body->applyCentralImpulse(btVector3(x, y, z));
}


// ---------------------------------------------------------
void PhysBody3D::GetTransform(float* matrix) const
{
	if(body != NULL && matrix != NULL)
	{
		body->getWorldTransform().getOpenGLMatrix(matrix);
	}
}


// ---------------------------------------------------------
void PhysBody3D::SetTransform(const float* matrix) const
{
	if(body != NULL && matrix != NULL)
	{
		btTransform t;
		t.setFromOpenGLMatrix(matrix);
		body->setWorldTransform(t);
	}
}


// ---------------------------------------------------------
void PhysBody3D::SetPos(float x, float y, float z)
{
	btTransform t = body->getWorldTransform();
	t.setOrigin(btVector3(x, y, z));
	body->setWorldTransform(t);
}


void PhysBody3D::SetRotation(vec3 axis, float angle, bool converse) {

	btVector3 ax = btVector3(axis.x, axis.y, axis.z);

	if(converse)
		angle = angle * (M_PI / 180);

	btTransform t = body->getWorldTransform();
	t.setRotation(btQuaternion(ax, angle));
	body->setWorldTransform(t);

}


void PhysBody3D::AddRotation(vec3 axis, float angle, float converse) {

	btVector3 ax = btVector3(axis.x, axis.y, axis.z);

	if (converse)
		angle = angle * (M_PI / 180);

	btTransform t = body->getWorldTransform();

	btQuaternion rotationtoAdd = btQuaternion(ax, angle);
	btQuaternion rot_addition = t.getRotation() * rotationtoAdd;
	
	t.setRotation(rot_addition);
	body->setWorldTransform(t);
}


void PhysBody3D::SetLinearVelocity(vec3 vel) {

	const btVector3 velocity = btVector3(vel.x, vel.y, vel.z);
	body->setLinearVelocity(velocity);

}