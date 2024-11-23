#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "../base_data.h"

// Печатает все данные структуры (не используется)
void printBootSecInfo(BootSecInfo drive) {
	//printf("Type of FS: %s\n", (drive.fileSysName == NULL) ? "-" : drive.fileSysName);
	printf("------------------------------\n");
	printf("Bytes per sector: %ld\n", drive.bytesPerSec);
	printf("sectors per cluster: %ld\n", drive.secPerClustr);
	printf("Reserved sectors for Boot Sector: %lX\n", drive.reservedSec);
	printf("sectors per FAT: %ld\n", drive.secPerFAT);
	printf("Amount of FAT tables: %ld\n", drive.amountOfFAT);
	printf("Size of Root Directory: %ld (bytes) or %ld (records)\n", drive.sizeofRootDir, drive.sizeofRootDir/32);
	printf("------------------------------\n");
}


void fprintBootSecInfo(FILE *file, BootSecInfo drive) {
	fprintf(file, "------------------------------\n");
	fprintf(file, "Bytes per sector: %ld\n", drive.bytesPerSec);
	fprintf(file, "sectors per cluster: %ld\n", drive.secPerClustr);
	fprintf(file, "Reserved sectors for Boot Sector: %lX\n", drive.reservedSec);
	fprintf(file, "sectors per FAT: %ld\n", drive.secPerFAT);
	fprintf(file, "Amount of FAT tables: %ld\n", drive.amountOfFAT);
	fprintf(file, "Size of Root Directory: %ld (bytes) or %ld (records)\n", drive.sizeofRootDir, drive.sizeofRootDir/32);
	fprintf(file, "------------------------------\n");
}