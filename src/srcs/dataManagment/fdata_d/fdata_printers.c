#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../base_data.h"
#include "../drive.h"
#include "../fdata_header.h"

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

void fprintFileInfo(FILE *destination, DriveInfo drive, FileData * fdata, UInt_8 grade) {
	int i = 0, j = 0;
	int fragments = 0;
	if ((fdata->fileList != NULL) && (fdata->amountOfFiles != 0)) {

		for (i = 0; i < fdata->amountOfFiles; i++) {
			
			for (j = 0; j < grade; j++) {
				if (j == grade - 1) fprintf(destination, "|");
				fprintf(destination, "\t");
			}
			

			fprintf(destination, "%s", ((fdata->fileList + i)->name != NULL) ? (fdata->fileList + i)->name : "_"); 

			fragments = getNumOfFragments(drive, (fdata->fileList + i)->firstCluster);
			if (fragments != 1) {
				fprintf(destination, "\t\t(Fragments: %d)\n", fragments); 
			} else {
				fprintf(destination, "\n");
			}
			
			

			if ( (fdata->fileList + i)->fileList != NULL) fprintFileInfo(destination, drive, (fdata->fileList + i), grade + 1);
		}
	}
}