/*
Authors – Michael Ozeri 302444229 Omer Machluf 200892917
Project – ex1 
Description – this is a flight-company program, as requested in ex1 HW.
we added a few helper functions so the code will be more readable.
áãé÷ä ðòéîä
*/
#include <stdio.h>
#include <stdlib.h>
#include "airplane_db.h"
#include "main.h"
#include "pilots.h"

#define ERR_MSG "An error occurred during execution, couldn’t complete the task!\n"

void createArieplaneDB() {
	char* destinations737[] = { "Larnaca","Athens","Budapest","Zurich","London","Paris","Rome" };
	char* destinations747[] = { "London","New York","Bangkok" };
	char* destinations787[] = { "London","New York","Los Angeles","Hong Kong","Miami" };
	db[0] = createAirplane("737", destinations737, 7);
	db[1] = createAirplane("747", destinations747, 3);
	db[2] = createAirplane("787", destinations787, 5);
}

int main(int argc, char* argv[]) {

	FILE* destFile;
	int retVal;
	//open destination file
	retVal = fopen_s(&destFile, argv[3], "w");
	if (retVal) {
		return printErrorAndExit(destFile,argv[3]);
	}

	if (argc < 4) {
		return printErrorAndExit(destFile, argv[3]);
	}
	createArieplaneDB();

	Pilot* pilotListHead;
	retVal = GetPilots(&pilotListHead, argv[1]);
	if (retVal) {
		return printErrorAndExit(destFile, argv[3]);
	}

	FILE* fp;
	size_t len = 200;
	char* line = (char*)malloc(sizeof(char)*len);
	char* destination;
	AirplaneType* airplaneType;
	Airplane2* youngestAirplane;
	Airplane2* Airplane2Listhead;
	Pilot* captain;
	Pilot* firstOfficer;
	char* type = NULL;

	//open file from argument
	retVal = fopen_s(&fp, argv[2], "r");
	if (retVal) {
		fprintf(destFile, ERR_MSG);
		return -1;
	}
	
	//create Airplane List
	retVal = CreateAirplaneList(&Airplane2Listhead);
	if (retVal) {
		return printErrorAndExit(destFile, argv[3]);
	}
	//for each destination
	while ((destination = fgets(line, len, fp)) != NULL) {
		printf("Retrieved destination: %s\n", destination);
		if (!strcmp(destination, "\n")) {
			continue;
		}
		char* ptr = strchr(destination, '\n');
		*ptr = '\0';

		/*****************************************************************/

		int minAge = INT_MAX;
		Airplane2* mostYoungAirplane = NULL;
		bool found = false;


		for (int i = 0; i < 3; i++) {
			//get Airplane type from DB
			retVal = GetAirplaneType(&airplaneType, destination);
			if (!retVal) {
				type = airplaneType->type;
				//get youngest airplane that flies to that location from the list
				retVal = GetAirplane(&youngestAirplane, Airplane2Listhead, type);
				if (!retVal) {
					if (found) {
						if (youngestAirplane->age < minAge) {
							minAge = youngestAirplane->age;
							mostYoungAirplane = youngestAirplane;
						}
					}
					else {
						found = true;
						minAge = youngestAirplane->age;
						mostYoungAirplane = youngestAirplane;
					}
				}
			}

			updateAirPlanesFound(type);

		}

		if (!found) {
			return printErrorAndExit(destFile, argv[3]);
		}
		else {
			type = mostYoungAirplane->type;
		}

		/*****************************************************************/

		//get captain and first officer for that flight that have min flight hours
		retVal = getYoungestPilotForType(&captain, pilotListHead, type, "Captain");
		if (retVal) {
			return printErrorAndExit(destFile, argv[3]);
		}
		retVal = getYoungestPilotForType(&firstOfficer, pilotListHead, type, "First Officer");
		if (retVal) {
			return printErrorAndExit(destFile, argv[3]);
		}
		//print the line into the file
		fprintf(destFile, "%s, %s, %s, %s\n", destination, mostYoungAirplane->name, captain->name, firstOfficer->name);

		//remove all selected pilots / planes
		retVal = DeleteAirplane(&Airplane2Listhead, mostYoungAirplane);
		if (retVal) {
			return printErrorAndExit(destFile, argv[3]);
		}
		retVal = DeletePilots(&pilotListHead, captain);
		if (retVal) {
			return printErrorAndExit(destFile, argv[3]);
		}
		retVal = DeletePilots(&pilotListHead, firstOfficer);
		if (retVal) {
			return printErrorAndExit(destFile, argv[3]);
		}
		clearAirPlanesFound();
	}
	ClearAirplaneList(Airplane2Listhead);
	ClearPilotList(pilotListHead);
	fclose(destFile);
	fclose(fp);
	if (line) {
		free(line);
	}
	return 0;
}

int printErrorAndExit(FILE * destFile,char* path)
{
	freopen_s(destFile, path, "w", destFile);
	fprintf(destFile, ERR_MSG);
	fclose(destFile);
	return -1;
}


