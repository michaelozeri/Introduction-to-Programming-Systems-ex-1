#include "pilots.h"

int GetPilots(Pilot** head, char* path) {
	*head = NULL;
	Pilot* current = NULL;
	if (path == NULL) {
		return -1;
	}
	FILE* fp;
	size_t len = 200;
	char* line = (char*)malloc(sizeof(char)*len);
	char* read;
	int retval = fopen_s(&fp, path, "r");
	if (retval) {
		char buf[200];
		strerror_s(buf, 100, errno);
		return -1;
	}
	while ((read = fgets(line, len, fp)) != NULL) {
		char** arr;
		splitPilotLine(read, ',', &arr);
		char* rank = arr[3] + 1;
		char* ptr = strchr(arr[3], '\n');
		*ptr = '\0';
		Pilot* pilot = createPilot(arr[0], arr[1] + 1, atoi(arr[2] + 1), rank);
		if (*head != NULL) {
			current->nextPilot = pilot;
			current = current->nextPilot;
		}
		else {
			*head = pilot;
			current = pilot;
		}
	}
	current->nextPilot = NULL;
	fclose(fp);
	if (line) {
		free(line);
	}
	return 0;
}

Pilot* createPilot(char* name, char* type, int flightHours, char* rank)
{
	Pilot* pilot = (Pilot*)malloc(sizeof(Pilot));
	pilot->name = (char*)malloc(sizeof(char)*strlen(name));
	strcpy_s(pilot->name, strlen(name) + 1, name); //in strcpy_s need to give in the len always +1 from actual size of source because of '\0'
	pilot->type = (char*)malloc(sizeof(char) * 3);
	strcpy_s(pilot->type, 4, type);
	pilot->flightHours = flightHours;
	pilot->rank = (char*)malloc(sizeof(char)*strlen(rank));
	strcpy_s(pilot->rank, strlen(rank) + 1, rank);
	return pilot;
}

void freePilotSpace(Pilot * pilot) {
	free(pilot);
}

/*
taken from stackoverflow
*/
int splitPilotLine(const char *str, char c, char ***arr)
{
	int count = 1;
	int token_len = 1;
	int i = 0;
	char *p;
	char *t;
	p = str;
	while (*p != '\0')
	{
		if (*p == c)
			count++;
		p++;
	}
	*arr = (char**)malloc(sizeof(char*) * count);
	if (*arr == NULL)
		exit(1);
	p = str;
	while (*p != '\0')
	{
		if (*p == c)
		{
			(*arr)[i] = (char*)malloc(sizeof(char) * token_len);
			if ((*arr)[i] == NULL)
				exit(1);

			token_len = 0;
			i++;
		}
		p++;
		token_len++;
	}
	(*arr)[i] = (char*)malloc(sizeof(char) * token_len);
	if ((*arr)[i] == NULL)
		exit(1);
	i = 0;
	p = str;
	t = ((*arr)[i]);
	while (*p != '\0')
	{
		if (*p != c && *p != '\0')
		{
			*t = *p;
			t++;
		}
		else
		{
			*t = '\0';
			i++;
			t = ((*arr)[i]);
		}
		p++;
	}
	return count;
}

int DeletePilots(Pilot ** head, Pilot * toDelete) {
	int tempListSize = findPilotListSize(*head);
	Pilot* currentPilot = *head;
	//if delete the head
	if (areSamePilot(currentPilot, toDelete)) {
		(*head) = (*head)->nextPilot;
		freePilotSpace(currentPilot);
		return 0;
	}
	for (int i = 1; i < tempListSize; i++) {
		if (areSamePilot(currentPilot->nextPilot, toDelete)) {
			Pilot* ptrToFree = currentPilot->nextPilot;
			currentPilot->nextPilot = currentPilot->nextPilot->nextPilot;
			freePilotSpace(ptrToFree);
			return 0;
		}
		currentPilot = currentPilot->nextPilot;
	}
	return -1;
}

int findPilotListSize(Pilot* head)
{
	Pilot* current = head;
	int size = 1;
	while (current->nextPilot != NULL) {
		current = current->nextPilot;
		size++;
	}
	return size;
}

bool areSamePilot(Pilot * p1, Pilot * p2)
{
	return p1->flightHours == p2->flightHours && !strcmp(p1->name, p2->name) && !strcmp(p1->rank, p2->rank) && !strcmp(p1->type, p2->type);
}

void ClearPilotList(Pilot * pilot)
{
	Pilot* currentPilot = pilot;
	Pilot* ptrToFree;
	int listSize = findPilotListSize(pilot);
	for (int i = 0; i < listSize; i++) {
		ptrToFree = currentPilot;
		currentPilot = currentPilot->nextPilot;
		freePilotSpace(ptrToFree);
	}
}

int getYoungestPilotForType(Pilot ** pilot, Pilot * head, char * type, char* rank)
{
	Pilot* current = head;

	Pilot* minPilot = NULL;
	int minFlightHours = INT_MAX;

	if (areSameType(head->type, type) && areSameType(current->rank, rank)) {
		minPilot = head;
		minFlightHours = head->flightHours;
		current = current->nextPilot;
	}
	int listSize = findPilotListSize(head);
	for (int i = 1; i < listSize; i++) {
		if (areSameType(current->type, type) && areSameType(current->rank, rank)) {
			if (current->flightHours < minFlightHours) {
				minPilot = current;
				minFlightHours = current->flightHours;
			}

		}
		current = current->nextPilot;
	}
	if (minPilot != NULL) {
		*pilot = minPilot;
		return 0;
	}
	return -1;
}

bool areSameType(char* type1, char * type)
{
	return !strcmp(type1, type);
}
