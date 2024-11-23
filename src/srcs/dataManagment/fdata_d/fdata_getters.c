#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "../base_data.h"
#include "../drive.h"
#include "../fdata_header.h"

// работает
FileData getFileData(char *name, UInt_8 firstCluster, UInt_8 fileName_offset, unsigned char attribute) {
	FileData fdata;

	fdata.name = name;
	fdata.firstCluster = firstCluster;
	fdata.fileName_offset = fileName_offset;
	fdata.attribute = attribute;
	fdata.fileList = NULL;
	fdata.amountOfFiles = 0;
	return fdata;
}


UInt_8 getAmountOfFiles(FileData * fdata) {
	UInt_8 i = 0, num = 0;

	if (fdata->amountOfFiles != 0) {
		num = fdata->amountOfFiles;
		
		for (i = 0; i < fdata->amountOfFiles; i++) {
			if ((fdata->fileList + i)->amountOfFiles != 0) num += getAmountOfFiles((fdata->fileList + i)); 
		}

	}
	return num;
}