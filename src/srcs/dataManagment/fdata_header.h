#ifndef FDATA_HEADER_H
#define FDATA_HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct fileData {
	char *name;
	UInt_8 firstCluster;
	UInt_8 fileName_offset;
	unsigned char attribute;
	struct fileData *fileList;
	UInt_8 amountOfFiles;
	
} FileData;

//// fdata_getters.c {
	FileData getFileData(char *name, UInt_8 firstCluster, UInt_8 fileName_offset, unsigned char attribute);

	// получить количество всех связанных структур
	UInt_8 getAmountOfFiles(FileData * fdata);
//---- }

//// report_printers.c {
	// напечатать все элементы структуры 
	//void printFileInfo(FileData fdata, UInt_8 grade);

	// напечатать элементы в файл
	void fprintFileInfo(FILE *destination, DriveInfo drive, FileData * fdata, UInt_8 grade);
//---- }

//// freeFData.c {
	// очистить всю динамически выделенную память в структуре
	void freeFiles(FileData fdata);
//---- }

#endif /* FDATA_HEADER_H */