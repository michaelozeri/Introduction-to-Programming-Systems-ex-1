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

int GetPilots(Pilot** head, char* path);

Pilot* createPilot(char* name, char* type, int flightHours, char* rank);

void freePilotSpace(Pilot* pilot);

int splitPilotLine(const char *str, char c, char ***arr);

int DeletePilots(Pilot** head, Pilot* toDelete);

int findPilotListSize(Pilot* head);

bool areSamePilot(Pilot* p1, Pilot* p2);

/*
clears the pilots list and free's memory allocated for each pilot
*/
void ClearPilotList(Pilot* pilot);