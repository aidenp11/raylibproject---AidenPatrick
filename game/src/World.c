#include "World.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

Body* bodies = NULL;
int bodyCount = 0;
Vector2 gravity;

Body* CreateBody(Vector2 position, float mass, BodyType bodyType)
{
	Body* newBody = (Body*)malloc(sizeof(Body));
	assert(newBody);

	memset(newBody, 0, sizeof(newBody));
	newBody->position = position;
	newBody->mass = mass;
	newBody->inverseMass = (bodyType == BT_DYNAMIC) ? 1 / mass : 0;
	newBody->bodyType = bodyType;

	return newBody;
}

void AddBody(Body* body)
{
	assert(body);

	body->velocity.x = 0.0f;
	body->velocity.y = 0.0f;
	body->force.x = 0.0f;
	body->force.y = 0.0f;

	body->prev = NULL;
	body->next = bodies;

	if (bodies != NULL) {
		bodies->prev = body;
	}

	bodies = body;
	bodyCount++;
}

void DestroyBody(Body* body)
{
	assert(body != NULL);

	if (body->prev != NULL) {
		body->prev->next = body->next;
	}

	if (body->next != NULL) {
		body->next->prev = body->prev;
	}

	if (body == bodies) {
		bodies = body->next;
	}

	bodyCount--;
	free(body);
}
