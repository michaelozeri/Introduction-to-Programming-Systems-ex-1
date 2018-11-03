#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <float.h>
#include <errno.h>
#include <assert.h>


typedef struct pilot_t {
	char* name;
	char* type;
	int flightHours;
	char* rank;
	struct pilot_t* nextPilot;
} Pilot;


/*
Description - opens a pilots file from given path "path" argument and creates a dynamically allocated pilot linked-list
sets the head to point on the begginning of the list
return 0 on success else -1;
*/
int GetPilots(Pilot** head, char* path);

/*
Description - creates a pilot with the following arguments as fields and returns a pointer to the pilot
return: pointer to the dynamically allocated pilot struct
*/
Pilot* createPilot(char* name, char* type, int flightHours, char* rank);

/*
Description - function to free dynamically allocated struct of pilot including fields
*/
void freePilotSpace(Pilot* pilot);

/*
Description - helper function to split line read from pilot file
return 0 on success else -1;
*/
int splitPilotLine(const char *str, char c, char ***arr);

/*
Description - deletes pilot from list given head pointer
toDelete - the pilot to delete from the list
return : 0 success else -1;
*/
int DeletePilots(Pilot** head, Pilot* toDelete);

/*
Description - find list size by given pointer to head
return : list size
*/
int findPilotListSize(Pilot* head);

/*
Description - compare to pilots by thier fields
return true if same else false
*/
bool areSamePilot(Pilot* p1, Pilot* p2);

/*
Description - clears the pilots list and free's memory allocated for each pilot
*/
void ClearPilotList(Pilot* pilot);

/*
Description - this function gets from the list "head" the pilot with the smallest flight hours for the type given and the rank we are looking for
return : 0 on success else -1
*/
int getYoungestPilotForType(Pilot** pilot, Pilot* head, char* type, char* rank);

/*
Description - compares two strings that represent types of planes
return: true if same type else false
*/
bool areSameType(char* type1, char * type);
