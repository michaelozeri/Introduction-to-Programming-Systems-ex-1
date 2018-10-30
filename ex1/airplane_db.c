#include "airplane_db.h"

Airplane* createAirplane(char* type, char** destinations, int dest_size) {

	Airplane* airplane_t = (Airplane*)malloc(sizeof(Airplane));
	//set destination size to array
	airplane_t->destinations = (char*)malloc(sizeof(char*)*dest_size);

	//copies model name to new airplane created.
	strcpy(airplane_t->type, type);
	//copy all destinations array to airplane
	int i = 0;
	for (i = 0; i < dest_size; i++) {
		airplane_t->destinations[i] = (char*)malloc(sizeof(char)*strlen(destinations[i]));
		strcpy(airplane_t->destinations[i], destinations[i]);
	}
	//set destination size
	airplane_t->dest_size = dest_size;
	return airplane_t;
}

void printAirplane(Airplane* airplane) {
	printf("****** Airplane ******\n");
	printf("airplane type: %s\n", airplane->type);
	printf("airplane desttination size: %d\n", airplane->dest_size);
	for (int i = 0; i < airplane->dest_size; i++) {
		printf("desination %d: %s\n", i, airplane->destinations[i]);
	}
	printf("****** end of Airplane ******\n");
}

Airplane* GetAirplaneType(char* destination) {
	
	for (int i = 0; i < 3; i++) {
		int dest_size = db[i].dest_size;
		for (int j = 0; j < dest_size; j++) {
			if (strcmp(destination, db[i].destinations[j])) {
				return (db+i);
			}
		}
	}
	return NULL;
}

