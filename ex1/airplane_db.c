#include "airplane_db.h"


int AirplanesFound[NUM_OF_OPTIONS] = { 0,0,0 };

AirplaneType* createAirplane(char* type, char** destinations, int dest_size) {

	//allocate size for Airplane
	AirplaneType* airplane = (AirplaneType*)malloc(sizeof(AirplaneType));

	//set destination size
	airplane->dest_size = dest_size;

	//copies model name to new airplane created. TODO: check if this is ok
	airplane->type = type;

	//copy all destinations array to airplane
	int i = 0;
	for (i = 0; i < dest_size; i++) {
		airplane->destinations[i] = (char*)malloc(sizeof(char)*strlen(destinations[i]));
		airplane->destinations[i] = destinations[i];
	}

	return airplane;
}

void printAirplane(AirplaneType* airplane) {
	printf("****** Airplane ******\n");
	printf("airplane type: %s\n", airplane->type);
	printf("airplane desttination size: %d\n", airplane->dest_size);
	for (int i = 0; i < airplane->dest_size; i++) {
		printf("desination %d: %s\n", i, airplane->destinations[i]);
	}
	printf("****** end of Airplane ******\n");
}

int GetAirplaneType(AirplaneType** airplane, char* destination) {
	for (int i = 0; i < 3; i++) {
		int dest_size = db[i]->dest_size;
		for (int j = 0; j < dest_size; j++) {
			if (!strcmp(destination, db[i]->destinations[j]) && !AirplanesFound[i]) {
				*airplane = db[i];
				return 0;
			}
		}
	}
	return -1;
}

Airplane2* createAirplane2(char* name, char* type, double age) {

	//allocate size for Airplane
	Airplane2* airplane2 = (Airplane2*)malloc(sizeof(Airplane2));
	//allocate size for fields
	int nameLength = strlen(name);
	airplane2->name = (char*)malloc(sizeof(char)*(nameLength));
	airplane2->type = (char*)malloc(sizeof(char) * 3);
	//set name
	strcpy_s(airplane2->name, nameLength + 1, name);
	//copies model name to new airplane created.
	strcpy_s(airplane2->type, 4, type);
	//set age
	airplane2->age = age;
	return airplane2;
}

//part 4
int CreateAirplaneList(Airplane2** airplane2) {

	Airplane2* head;
	Airplane2* currentAirplane2;
	head = createAirplane2("Beit-Shean", "737", 5);
	currentAirplane2 = head;
	for (int i = 1; i < AIRPLANE_LIST_SIZE; i++) {
		switch (i) {
		case 1:
			currentAirplane2->nextAirplane = createAirplane2("Ashkelon", "737", 10.25);
			currentAirplane2 = currentAirplane2->nextAirplane;
			break;
		case 2:
			currentAirplane2->nextAirplane = createAirplane2("Hadera", "737", 3);
			currentAirplane2 = currentAirplane2->nextAirplane;
			break;
		case 3:
			currentAirplane2->nextAirplane = createAirplane2("Kineret", "737", 7.5);
			currentAirplane2 = currentAirplane2->nextAirplane;
			break;
		case 4:
			currentAirplane2->nextAirplane = createAirplane2("Nahariya", "737", 1);
			currentAirplane2 = currentAirplane2->nextAirplane;
			break;
		case 5:
			currentAirplane2->nextAirplane = createAirplane2("Tel-Aviv", "747", 20);
			currentAirplane2 = currentAirplane2->nextAirplane;
			break;
		case 6:
			currentAirplane2->nextAirplane = createAirplane2("Haifa", "747", 15);
			currentAirplane2 = currentAirplane2->nextAirplane;
			break;
		case 7:
			currentAirplane2->nextAirplane = createAirplane2("Jerusalem", "747", 17);
			currentAirplane2 = currentAirplane2->nextAirplane;
			break;
		case 8:
			currentAirplane2->nextAirplane = createAirplane2("Ashdod", "787", 1);
			currentAirplane2 = currentAirplane2->nextAirplane;
			break;
		case 9:
			currentAirplane2->nextAirplane = createAirplane2("Bat Yam", "787", 1.5);
			currentAirplane2 = currentAirplane2->nextAirplane;
			break;
		case 10:
			currentAirplane2->nextAirplane = createAirplane2("Rehovot", "787", 0.5);
			currentAirplane2 = currentAirplane2->nextAirplane;
			break;
		}
	}
	currentAirplane2->nextAirplane = NULL;
	*airplane2 = head;
	return 0;
}

//section 5
int GetAirplane(Airplane2** youngestAirplane2, Airplane2* head, char* type) {
	bool found = false;
	Airplane2* currentAirplane2 = head;
	double minAge = DBL_MAX;
	if (sameType(currentAirplane2, type)) {
		*youngestAirplane2 = head;
		minAge = head->age;
		found = true;
	}
	for (int i = 1; i < findListSize(head); i++) {
		if (sameType(currentAirplane2->nextAirplane, type)) {
			double nextAirplaneAge = currentAirplane2->nextAirplane->age;
			if (minAge > nextAirplaneAge) {
				minAge = nextAirplaneAge;
				*youngestAirplane2 = currentAirplane2->nextAirplane;
				found = true;
			}
		}
		currentAirplane2 = currentAirplane2->nextAirplane;
	}
	if (found) {
		return 0;
	}
	return -1;
}

bool sameType(Airplane2 * currentAirplane2, char * type)
{
	return !strcmp(currentAirplane2->type, type);
}


void printAirplane2(Airplane2* airplane2) {
	printf("****** Airplane2 ******\n");
	printf("airplane name: %s\n", airplane2->name);
	printf("airplane type: %s\n", airplane2->type);
	printf("airplane age: %f\n", airplane2->age);
	printf("****** end of Airplane ******\n");
}

int DeleteAirplane(Airplane2** head, Airplane2* toDelete) {
	int tempListSize = findListSize(*head);
	Airplane2* currentAirplane = *head;
	//if delete the head
	if (areSameAirplane(currentAirplane, toDelete)) {
		(*head) = (*head)->nextAirplane;
		freeAirplaneMem(currentAirplane);
		return 0;
	}
	for (int i = 1; i < tempListSize; i++) {
		if (areSameAirplane(currentAirplane->nextAirplane, toDelete)) {
			Airplane2* ptrToFree = currentAirplane->nextAirplane;
			currentAirplane->nextAirplane = currentAirplane->nextAirplane->nextAirplane;
			freeAirplaneMem(ptrToFree);
			return 0;
		}
		currentAirplane = currentAirplane->nextAirplane;
	}
	return -1;
}


bool areSameAirplane(Airplane2* a1, Airplane2* a2) {
	return a1->age == a2->age && !strcmp(a1->name, a2->name) && !strcmp(a1->type, a2->type);
}

void ClearAirplaneList(Airplane2* head) {
	Airplane2* currentAirplane = head;
	Airplane2* ptrToFree;
	int listSize = findListSize(head);
	for (int i = 0; i < listSize; i++) {
		ptrToFree = currentAirplane;
		currentAirplane = currentAirplane->nextAirplane;
		freeAirplaneMem(ptrToFree);
	}
}

void freeAirplaneMem(Airplane2* airplane) {
	free(airplane);
}

int findListSize(Airplane2* head) {
	Airplane2* current = head;
	int size = 0;
	while (current != NULL) {
		current = current->nextAirplane;
		size++;
	}
	return size;
}

void updateAirPlanesFound(char* type)
{
	if (!strcmp(type, "737")) {
		AirplanesFound[0] = 1;
	}
	else if (!strcmp(type, "747")) {
		AirplanesFound[1] = 1;
	}
	else {
		AirplanesFound[2] = 1;
	}

}

void clearAirPlanesFound()
{
	AirplanesFound[0] = 0;
	AirplanesFound[1] = 0;
	AirplanesFound[2] = 0;

}


