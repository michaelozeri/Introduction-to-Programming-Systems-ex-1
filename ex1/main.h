#pragma once

/*
Description - this function creates the airPlaneType DB at start of program
*/
void createArieplaneDB();

/*
Description - this function prints error message to file and exits
return - (-1) always since if we arrive here we have an error
*/
int printErrorAndExit(FILE * destFile, char* path);