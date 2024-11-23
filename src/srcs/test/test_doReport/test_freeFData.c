#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

#include "../../dataManagment/base_data.h"
#include "../test_dataManagment/test_drive.h"
#include "test_dr_header.h"

void freeFiles(FileData fdata) {
	int i = 0;
	if ((fdata.fileList != NULL) && (fdata.amountOfFiles != 0)) {
		for (i = 0; i < fdata.amountOfFiles; i++) {
			
			if ((fdata.fileList + i) != 0) {
				freeFiles(*(fdata.fileList + i));
				continue;
			}
			free((fdata.fileList + i)->name);
			free((fdata.fileList + i)->fileList);
		}
	}
	free(fdata.name);
	free(fdata.fileList);
}