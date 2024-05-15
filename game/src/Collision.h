#pragma once
#include "raylib.h"

typedef struct Contact Contact_t;
typedef struct Body Body;

void CreateContacts(Body* bodies, Contact_t** contacts);
Contact_t* GenerateContact(Body* body1, Body* body2);

void SeparateContacts(Contact_t* contacts);
void ResolveContacts(Contact_t* contacts);