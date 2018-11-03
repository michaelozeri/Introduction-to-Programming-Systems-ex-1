#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <float.h>

#define AIRPLANE_LIST_SIZE 11

#define NUM_OF_OPTIONS 3



/*
part 1-2
this is the struct for the first part of creating the DB of planes and matching destinations
*/
typedef struct airplane_t {
	char*  type;
	char*  destinations[10];
	int dest_size;
} AirplaneType;

/*
part 3
this is the struct for the later parts that creates a list of pleans etc.
*/
typedef struct airplane_t_2 {
	char* name;
	char* type;
	double age;
	struct airplane_t_2* nextAirplane;
} Airplane2;

AirplaneType* db[3];

/*
Description - gets a pointer to the pointer of the requested airplane for that destination and points it to that airplane
Parameters - airplane, the pointer that we shell point to the found type, destination- the destination to search the AirplaneTypeDB
return -  0 on sucess else -1
*/
int GetAirplaneType(AirplaneType** airplane, char* destination);

/*
Description - a "cto'r" for a new airplane object
Parameters - the type, destinations array and destinations array size to init
return: a pointer for the new Airplane struct
*/
AirplaneType* createAirplane(char* type, char** destinations, int dest_size);

/*
Description - helper function for debug - prints all fields of a given Airplane struct
Parameters - airplane - the struct to print its fields
*/
void printAirplane(AirplaneType* airplane);

/*
Description - section 4 - creates a dynamically allocated list of airplanes and points the arg given to
the head of the list
Parameters - airplane2 - the pointer to the pointer of the head of the list that will be created.
return: 0 on sucees else -1;
*/
int CreateAirplaneList(Airplane2** airplane2);

/*
Description - a "cto'r" for a new Airplane2 struct
return: a pointer for the new Airplane2 struct
*/
Airplane2* createAirplane2(char* name, char* type, double age);

/*
Description - section 5 - gets the youngest airplane from the given list which its head passes as argument
by type given
Parameters - youngestAirplane2 - the pointer to the Airplane 2 found from the list, head - the list head to search, type - the type to search
return: 0 on struct find else -1;
*/
int GetAirplane(Airplane2** youngestAirplane2, Airplane2* head, char* type);

/*
Description - checks in the Airplane2 object has the same type as the type given as arg
Parameters - the airplane to check wheather its type is like "type" arg
return: true if same type else false
*/
bool sameType(Airplane2 * currentAirplane2, char * type);

/*
Description - get a pointer to pointer of the head of the list and removes toDelete from the list
and also free's its memory allocated
Parameters - head - pointer to the head of list which to delete from the arg "toDelete"
return val: 0 if success else -1
*/
int DeleteAirplane(Airplane2** head, Airplane2* toDelete);

/*
Description - helper function for debug - prints all fields of a given Airplane2 struct
Parameters - airplane2 - the struct to print
*/
void printAirplane2(Airplane2* airplane2);

/*
Description - this function compares 2 structs of airplanes by their fields
Parameters - a1,a2 - the struct's to compare by fields
return val: true if are the same else false
*/
bool areSameAirplane(Airplane2* a1, Airplane2* a2);

/*
Description - clears the airplane list and free's memory allocated for each Airplane
Parameters - airplane - the head of the list to clear
*/
void ClearAirplaneList(Airplane2* airplane);

/*
Description - this function free's a single Ariplane2 struct memory
Parameters - airplane - the airplane struct to free
*/
void freeAirplaneMem(Airplane2* airplane);

/*
Description - find the list size from the head Given
Parameters - airplane - the head of the list to find its size
return - the list size
*/
int findListSize(Airplane2* airplane);

/*
Description - in main function after each iteration this function marks 1 if there are no planes of type "type" left;
Parameters - type - the type by which we mark global array AirPlanesFound
*/
void updateAirPlanesFound(char* type);

/*
Description - this zero's the AirPlanesFound global array
*/
void clearAirPlanesFound();