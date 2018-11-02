#include <stdio.h>
#include <stdlib.h>
#include "airplane_db.h"
#include "main.h"
#include "pilots.h"


void createDB()
{
	printf("Creating DB!\n");
	char* destinations737[] = { "Larnaca","Athens","Budapest","Zurich","London","Paris","Rome" };
	char* destinations747[] = { "London","New York","Bangkok" };
	char* destinations787[] = { "London","New York","Los Angeles","Hong Kong","Miami" };

	db[0] = *createAirplane("737", destinations737, 7);
	db[1] = *createAirplane("747", destinations747, 3);
	db[2] = *createAirplane("787", destinations787, 5);
}

int main(int argc, char** argv) {

	createDB();

	
}


