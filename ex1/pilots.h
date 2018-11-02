#pragma once


typedef struct pilot_t {
	char* name;
	char* type;
	int flightHours;
	char* rank;
	struct pilot_t* nextPilot;
} Pilot;

int GetPilots(char* path);