#include "spring.h"
#include "body.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <raymath.h>

Spring* springs = NULL;
int SpringCount = 0;
Vector2 gravity;

Spring* CreateSpring(Body* body1, Body* body2, float restLength, float k)
{
	Spring* newSpring = (Spring*)malloc(sizeof(Spring));
	assert(newSpring);

	memset(newSpring, 0, sizeof(Spring));
	newSpring->body1 = body1;
	newSpring->body2 = body2;
	newSpring->restLength = restLength;
	newSpring->k = k;

	return newSpring;
}

void AddSpring(Spring* Spring)
{
	assert(Spring);

	Spring->prev = NULL;
	Spring->next = springs;

	if (springs != NULL) {
		springs->prev = Spring;
	}

	springs = Spring;
	SpringCount++;
}

void DestroySpring(Spring* Spring)
{
	assert(Spring);

	if (Spring->prev != NULL) {
		Spring->prev->next = Spring->next;
	}

	if (Spring->next != NULL) {
		Spring->next->prev = Spring->prev;
	}

	if (Spring == springs) {
		springs = Spring->next;
	}

	SpringCount--;
	free(Spring);
}

void ApplySpringForce(Spring* spring)
{
	for (Spring* spring = springs; spring; spring = spring->next)
	{
		Vector2 direction = Vector2Subtract(spring->body1->position, spring->body2->position);
		if (direction.x == 0 && direction.y == 0) continue;

		float length = Vector2Length(direction);
		float x = length - spring->restLength;
		float force = -spring->k * x;

		Vector2 ndirection = Vector2Normalize(direction);

		ApplyForce(spring->body1, Vector2Scale(ndirection, force), FM_FORCE);
		ApplyForce(spring->body2, Vector2Scale(Vector2Negate(ndirection), force), FM_FORCE);
	}
}

//void ApplySpringForcePosition(Vector2 position, Body* body, float restLength, float k, float damping)
//{
//	// Check if the body pointer is null; if so, exit the function
//	if (!body) return;
//
//	// Calculate the direction vector from the body's position to the given position
//	Vector2 direction = Vector2Subtract(position, body->position);
//
//	// If the direction vector is zero (i.e., positions are the same), exit the function
//	if (direction.x == 0 && direction.y == 0) return;
//
//	// Calculate the length of the direction vector (distance between the two positions)
//	float length = Vector2Length(direction);
//
//	// Calculate the displacement from the rest length
//	float x = <get displacement>
//
//		// Apply Hooke's Law (f = -kx) to determine the spring force
//		float force = <Hooke’s Law>
//
//		// Normalize the direction vector
//		Vector2 ndirection = <normalize vector>
//
//		// Calculate the damping force (opposing force due to velocity)
//		float dampingForce = <damping * DotProduct(body velocity, ndirection)>
//
//		// Calculate the total force by combining spring force and damping force
//		float totalForce = <force + damping force>
//
//		// Apply the total force to the body in the direction of the normalized vector
//		ApplyForce(body, <scale the normalized direction vector by - totalForce >, FM_FORCE);
//}
