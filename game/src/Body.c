#include "body.h"
#include "Integrator.h"
#include <World.h>

void Step(Body* body, float timeStep)
{
	body->force = Vector2Add(body->force, Vector2Scale(Vector2Scale(gravity, body->gravityScale), body->mass));
	body->acceleration = Vector2Scale(body->force, body->inverseMass);

	SemiImplicitEuler(body, timeStep);

	float damping = 1 / (1 + (body->damping * timeStep));
	body->velocity = Vector2Scale(body->velocity, damping);

	ClearForce(body);
}