#pragma once
#include "body.h"

//typedef struct Body Body;

extern Body* bodies;
extern int bodyCount;
extern Vector2 gravity;

Body* CreateBody(Vector2 position, float mass, BodyType bodyType);
void AddBody(Body* body);
void DestroyBody(Body* body);
void DestroyAllBodies();