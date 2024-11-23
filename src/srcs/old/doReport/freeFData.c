#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

#include "../../dataManagment/base_data.h"
#include "../dataManagment/drive.h"
#include "dr_header.h"

void freeFiles(FileData fdata) {
	int i = 0;
	if ((fdata.fileList != NULL) && (fdata.amountOfFiles != NULL)) {
		for (i = 0; i < *fdata.amountOfFiles; i++) {
			
			if ((fdata.fileList + i) != NULL) {
				freeFiles(*(fdata.fileList + i));
				continue;
			}
			free((fdata.fileList + i)->name);
			free((fdata.fileList + i)->fat_chain);
			free((fdata.fileList + i)->address_chain);
			free((fdata.fileList + i)->chain_size);
			free((fdata.fileList + i)->fileList);
			free((fdata.fileList + i)->amountOfFiles);
		}
	}
	free(fdata.name);
	free(fdata.fat_chain);
	free(fdata.address_chain);
	free(fdata.chain_size);
	free(fdata.fileList);
	free(fdata.amountOfFiles);
}