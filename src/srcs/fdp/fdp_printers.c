#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "../dataManagment/base_data.h"
#include "fdp_header.h"

/*
// Отобразить объём раздела
void printCapacity (char * string) {
	FILE *file;
	if (!(file=fopen(string, "rb"))) {
		printf("Error.\n");
		return;
	}
	fseek(file, 0, SEEK_END);
	UInt_8 length = ftell(file);
	fseek(file, 0, SEEK_SET);
	printf("Size of Drive: %.2lfGb\n", (float) length/Gb);
	printf("Size of Drive: %d\n", length);

	//////////////////////////////////////////////////////
	unsigned int var;
	fseek(file, 0x20, SEEK_SET);
	fread(&var, 4, 1, file);
	printf("Size of Drive: %u\n", var * 512);
	//////////////////////////////////////////////////////
	fclose(file);
	return;
}
*/


void printPartitionData(char * string) {
	FILE *file;
	if (!(file=fopen(string, "rb"))) {
		perror("Error.\n");
		exit(1);
	}
	UInt_8 size = getIntFromBytes(file, 2, 0xB) * getIntFromBytes(file, 4, 0x20);
	printf("\tSize of Drive: %.2lfGb or %.2lfMb\n\t\tor %u Bytes\n", (double) size/Gb, (double) size/Mb, size);

	UInt_8 SN = getIntFromBytes(file, 4, 0x27);
	printf("\tDrive's serial number: %d\n", SN);

	char *drive_name = getCharFromBytes(file, 11, 0x2B);
	printf("\tDrive name: %s\n", drive_name);
	free(drive_name);


	char * FAT_Type = getCharFromBytes(file, 8, 0x36);
	printf("\tFAT type: %s\n", FAT_Type);
	free(FAT_Type);


}