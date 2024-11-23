#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

#include "../dataManagment/base_data.h"
#include "../dataManagment/drive.h"
#include "../dataManagment/fdata_header.h"
#include "dr_header.h"

void fprintFAT(FILE *destination, unsigned short *fat_table, size_t size) {

    //unsigned char a = 0; // буфер для байта
    int i = 0, k = 0; // счётчики

    // здесь реализован красивый вывод
    for (i = 0; i < size; i++) { // смещение по оси Y
    	if (i % 8 == 0) fprintf(destination, "%d.\t", ++k);
    	fprintf(destination, "%04X ", *(fat_table + i));

    	if ((i + 1) % 8 == 0) {
    		fprintf(destination, "\n");
    		continue;
    	} else if ((i + 1) % 4 == 0) {
            fprintf(destination, "%s", "    "); // пропуск после каждого восьмого байта
            continue;
            }
      }
	if ((i+1) % 512 == 0) fprintf(destination, "%s", "\n"); // делаем пропуск после конца каждого сектора  
}

void fprintReport(FILE *destination, Package pack, DriveInfo drive, char *direction) {
		UInt_8 i = 0;
	short flag = 0;
	short fragmentedFreeFATCells = 0;
	short busy = 0;
	for (i = 1; i < drive.clustersAmount; i++) {
		if (*(drive.fat_table + i) != 0) busy++;
		if (*(drive.fat_table + i) == 0) flag = 1;
		if ((*(drive.fat_table + i) != 0) && (flag != 0)) {
			fragmentedFreeFATCells++;
			flag = 0;
		}
	}

	fprintf(destination, "Direction: %s\n", direction);
	fprintDriveInfo(destination, drive);
	fprintf(destination, "Amount of Files: %d\n", pack.amountOfFiles);
	fprintf(destination, "________________________________________\n");
	if (pack.amountOfFiles != 0) {
		fprintf(destination, "Fragmented files: %d\n", pack.numOfFragFiles);
		fprintf(destination, "________________________________________\n");
		fprintf(destination, "Percent of fragmented files: %7.4lf%\n", (double) pack.numOfFragFiles / pack.amountOfFiles * 100);
		fprintf(destination, "________________________________________\n");
	}
	fprintf(destination, "Busy clusters: %d/%d\n", busy, drive.clustersAmount);
	fprintf(destination, "________________________________________\n");
	fprintf(destination, "Fragmented FAT free cells: %d/%d\n", fragmentedFreeFATCells, drive.clustersAmount);
	fprintf(destination, "________________________________________\n");
	fprintf(destination, "Percent of fragmented free space: %7.4lf%\n", (double) fragmentedFreeFATCells / drive.clustersAmount * 100);
	fprintf(destination, "________________________________________\n");
	if (destination != stdout) {
		//fprintFAT(destination, drive.fat_table, drive.fat_size);
	}
}