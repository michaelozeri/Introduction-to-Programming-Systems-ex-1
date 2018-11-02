#include <stdio.h>
#include <stdlib.h>
#include "airplane_db.h"
#include "main.h"

int main() {

	createDB();

	Airplane* a1 = (Airplane*)malloc(sizeof(Airplane));
	Airplane2* a2 = (Airplane2*)malloc(sizeof(Airplane2));
	int retVal = GetAirplaneType(&a1, "Larnaca");
	printAirplane(a1);
	printf("retval: %d\n", retVal);

	if (!CreateAirplaneList(&a2)) {
		for (int i = 0; i < LIST_SIZE; i++) {
			printAirplane2(a2);
			printf("         |          \n");
			printf("         V          \n");
			a2 = a2->nextAirplane;
		}
	}
}

void createDB()
{
	printf("Creating DB!\n");
	char* destinations737[] = { "Larnaca","Athens","Budapest","Zurich","London","Paris","Rome" };
	char* destinations747[] = { "London","New York","Bangkok" };
	char* destinations787[] = { "London","New York","Los Angeles","Hong Kong","Miami" };

	db[0] = *createAirplane("737", destinations737, 7);
	//printAirplane(db);
	db[1] = *createAirplane("747", destinations747, 3);
	//printAirplane(db + 1);
	db[2] = *createAirplane("787", destinations787, 5);
	//printAirplane(db + 2);
}
