#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct airplane_t {
	char  type[3];
	char**  destinations;
	int dest_size;
} Airplane;

Airplane db[3];

char* GetAirplaneType(char* destination);

Airplane* createAirplane(char* type, char** destinations, int dest_size);

void printAirplane(Airplane* airplane);
