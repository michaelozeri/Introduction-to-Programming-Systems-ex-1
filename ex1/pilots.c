#include "pilots.h"

int GetPilots(char* path) {
	if (path == NULL) {
		return -1;
	}
	FILE* fp;
	char* line = NULL;
	size_t len = 0;
	char* read;
	int retval = fopen_s(&fp, path, "r");
	if (retval) {
		char buf[200];
		strerror_s(buf, 100, errno);
		return -1;
	}
	while ((read = fgets(&line, &len, fp)) != NULL) {
		printf("Retrieved line: %s\n", read);
		char** arr;
		splitPilotLine(read, ',', &arr);
		char* rank = arr[3];
		rank[strlen(rank) - 2] = '\0';
		Pilot* pilot = createPilot(arr[0], arr[1] + 1, arr[2] + 1, rank);
		printf(pilot->name);
		printf(pilot->type);
		printf(pilot->flightHours);
		printf(pilot->rank);
	}
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

void freePilotSpace(Pilot * pilot)
{
	free(pilot->name);
	free(pilot->rank);
	free(pilot->type);
	free(pilot);
}


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