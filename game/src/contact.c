#include "contact.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

Contact_t* Contacts = NULL;

void AddContact(Contact_t* contact, Contact_t** contacts)
{
	assert(contact);

	// add element to linked list
	contact->next = *contacts;

	// set head of elements to new element
	*contacts = contact;
}

void DestroyAllContacts(Contact_t** contacts)
{
	if (!*contacts) return;

	Contact_t* contact = *contacts;
	while (contact)
	{
		Contact_t* next = contact->next;
		free(contact);
		contact = next;
	}

	*contacts = NULL;
}