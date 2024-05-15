#include "Collision.h"
#include "contact.h"
#include "body.h"
#include "mathf.h"

#include "raymath.h"

void CreateContacts(Body* bodies, Contact_t** contacts)
{
	for (Body* body = bodies; body; body = body->next)
	{

	}
}

Contact_t* GenerateContact(Body* body1, Body* body2)
{
	return NULL;
}

void SeparateContacts(Contact_t* contacts)
{
}

void ResolveContacts(Contact_t* contacts)
{
}
