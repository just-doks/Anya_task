#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "../../dataManagment/base_data.h"
#include "../test_dataManagment/test_drive.h"
#include "test_dr_header.h"

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

// Получение целочисленного значения из unsigned char * array, слева направо
// работает
UInt_8 getUIntFromUChar(unsigned char * arr, size_t size, UInt_8 offset) {
	UInt_8 a = 0; // буфер для байта
	unsigned char l;
    int i = 0;
    for (i = 0; i < size; i++) {
    	l = *(arr + offset + i);

    	a += (UInt_8) (l << (BYTE*i));
    }
    return a;
}

// работает
UInt_8 getNumOfFragments(DriveInfo drive, UInt_8 firstCluster) {

	UInt_8 i = 1;
	UInt_8 first = firstCluster;
	UInt_8 second = *(drive.fat_table + firstCluster);

	while (second != 0xFFFF) {
		if (second - first != 1) i += 1;
		first = second;
		second = *(drive.fat_table + first);		
	};

	return i;

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