#pragma once
#include "body.h"

//typedef struct Body Body;

extern Body* bodies;
extern int bodyCount;
extern Vector2 gravity;

Body* CreateBody();
void DestroyBody(Body* body);
void DestroyAllBodies();