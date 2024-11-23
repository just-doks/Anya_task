#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "../../dataManagment/base_data.h"
#include "../dataManagment/drive.h"
#include "dr_header.h"


// Функция получает инфо о первом кластере и анализирует цепочку адресов, после чего,
// заносит данные в структуру fdata и возвращает её 
FileData getFileAddress(FileData fdata, DriveInfo drive, UInt_8 firstCluster) {

	if (firstCluster == 0) {
		fdata.chain_size = calloc(1, sizeof(*fdata.chain_size));
		*fdata.chain_size = 0;
	}
	UInt_8 i = 0;
	UInt_8 bytes = firstCluster;
	do {
		bytes = getIntFromBytes(drive.file, 2, drive.fat_offset + bytes*2);
		i++;
	} while (bytes != 0xFFFF);

	fdata.chain_size = calloc(1, sizeof(*fdata.chain_size));
	*fdata.chain_size = i;

	fdata.address_chain = (UInt_8*) calloc(i, sizeof(UInt_8));
	fdata.fat_chain = (UInt_8*) calloc(i, sizeof(UInt_8));

	bytes = firstCluster;
	i = 0;

	do {
		*(fdata.address_chain + i) = (bytes - 1) * drive.sizeOfCluster + drive.dataSec_offset;
		*(fdata.fat_chain + i) = bytes;
		bytes = getIntFromBytes(drive.file, 2, drive.fat_offset + bytes*2);
		i++;
	} while (bytes != 0xFFFF);

	return fdata;
}

FileData getFileData(FileData * fdata) {
	fdata->name = NULL;
	fdata->fat_chain = NULL;
	fdata->address_chain = NULL;
	fdata->chain_size = NULL;
	fdata->fileList = NULL;
	fdata->amountOfFiles = NULL;
	return *fdata;
}
/*
UInt_8 getNumOfFragments(DriveInfo drive, UInt_8 firstCluster) {

	UInt_8 i = 0;
	UInt_8 first = firstCluster;
	UInt_8 second = 0;


	while (first != 0xFFFF) {
		second = getIntFromBytes(drive.file, 2, drive.fat_offset + first * 2);
		if (second - first != 1) i += 1;
		first = getIntFromBytes(drive.file, 2, drive.fat_offset + second * 2);		
	};

	return i;

} */

UInt_8 getNumOfFragments(FileData fdata) {
	if (*fdata.chain_size == 0) return 0;
	if (*fdata.chain_size == 1) return 1;
	UInt_8 i = 0;
	UInt_8 first = *fdata.fat_chain;

	UInt_8 amount = 0;

	for (i = 1; i < *fdata.chain_size; i++) {
		if (*(fdata.fat_chain + i) - *(fdata.fat_chain + i - 1) != 1) amount++; 
	}

	return amount;

} 

UInt_8 getAmountOfFiles(FileData fdata) {
	UInt_8 i = 0, num = 0;

	if (fdata.amountOfFiles != NULL) {
		num = *fdata.amountOfFiles;
		for (i = 0; i < *fdata.amountOfFiles; i++) {
			if ((fdata.fileList + i)->amountOfFiles != NULL) num += getAmountOfFiles(*(fdata.fileList + i)); 
		}
	}
	return num;
}