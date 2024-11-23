#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "../dataManagment/base_data.h"
#include "fdp_header.h"

// Супер важная функция по проверке байт 
int checkFileBytes (char * str, UInt_8 offset) {
	FILE *file;
	char *word;
	word = getWholeWay(str);
	int i = 0;
	if (!(file=fopen(word, "rb"))) {
		printf("Opening Error.\n");
		free(word);
		return 2;
	}
	BootSecInfo bootSector = getBootSecInfo(file, offset);
	
	if (bootSector.secPerFAT == 0
		|| bootSector.sizeofRootDir == 0
		|| !(bootSector.bytesPerSec == 512 
			|| bootSector.bytesPerSec == 1024
			|| bootSector.bytesPerSec == 2048
			|| bootSector.bytesPerSec == 4096)
		|| !(bootSector.secPerClustr == 2
			|| bootSector.secPerClustr == 4
			|| bootSector.secPerClustr == 8
			|| bootSector.secPerClustr == 16
			|| bootSector.secPerClustr == 32
			|| bootSector.secPerClustr == 64)) 
	{
		fclose(file);
		free(word);
		return 1;
	}
	
	free(word);
	fclose(file);

	return 0;
}