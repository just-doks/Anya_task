#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../dataManagment/base_data.h"
#include "../dataManagment/drive.h"
#include "dr_header.h"

/*
void printFileInfo(FileData fdata, UInt_8 grade) {
	int i = 0, j = 0;
	if ((fdata.fileList != NULL) && (fdata.amountOfFiles != NULL)) {
		for (i = 0; i < *fdata.amountOfFiles; i++) {
			for (j = 0; j < grade; j++) {
				if (j == grade - 1) printf("|");
				printf("\t");
			}
			printf("%s", (fdata.fileList + i)->name); 
			printf("\t(Fragments: %d)\n", getNumOfFragments(fdata));

			//if ((fdata.fileList + i) != NULL) printFileInfo(*(fdata.fileList + i), grade + 1);
		}
	}
}
*/

void fprintFileInfo(FILE *file, DriveInfo drive, FileData * fdata, UInt_8 grade) {
	int i = 0, j = 0;
	if ((fdata->fileList != NULL) && (fdata->amountOfFiles != 0)) {

		for (i = 0; i < fdata->amountOfFiles; i++) {
			
			for (j = 0; j < grade; j++) {
				if (j == grade - 1) fprintf(file, "|");
				fprintf(file, "\t");
			}
			

			fprintf(file, "%s", ((fdata->fileList + i)->name != NULL) ? (fdata->fileList + i)->name : "_"); 
			fprintf(file, "\n");
			//fprintf(file, "\t(Fragments: %d)\n", getNumOfFragments(drive, fdata->firstCluster)); 

			if ( (fdata->fileList + i)->fileList != NULL) fprintFileInfo(file, drive, (fdata->fileList + i), grade + 1);
		}
	}
}