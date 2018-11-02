#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <float.h>

#define LIST_SIZE 11

//part 1-2
typedef struct airplane_t {
	char*  type;
	char*  destinations[10];
	int dest_size;
} Airplane;

//part 3
typedef struct airplane_t_2 {
	char* name;
	char* type;
	double age;
	struct airplane_t_2* nextAirplane;
} Airplane2;

Airplane db[3];

int GetAirplaneType(Airplane** airplane, char* destination);

Airplane* createAirplane(char* type, char** destinations, int dest_size);

void printAirplane(Airplane* airplane);

int CreateAirplaneList(Airplane2** airplane2);

Airplane2* createAirplane2(char* name, char* type, double age);

int GetAirplane(Airplane2** youngestAirplane2, Airplane2* head, char* type);

int sameType(Airplane2 * currentAirplane2, char * type);

/*
get a pointer to the pointer of the head of the list and removes toDelete from the list
and also free's its memory allocated
return val: 0 if success else -1
*/
int DeleteAirplane(Airplane2** head, Airplane2* toDelete);

void printAirplane2(Airplane2* airplane2);

/*
this function compares 2 structs of airplanes by their fields
return val: true if are the same else false
*/
bool areSameAirplane(Airplane2* a1, Airplane2* a2);

/*
clears the airplane list and free's memory allocated for each Airplane
*/
void ClearAirplaneList(Airplane2* airplane);

/*
this function free's a single Ariplane2 struct memory
*/
void freeAirplaneMem(Airplane2* airplane);

/*
find the list size from the head Given 
*/
int findListSize(Airplane2* airplane);