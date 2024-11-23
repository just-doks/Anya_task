#ifndef DR_HEADER_H
#define DR_HEADER_H

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "../dataManagment/base_data.h"
#include "../dataManagment/drive.h"


typedef struct fileData {
	char *name;
	UInt_8 firstCluster;
	UInt_8 fileName_offset;
	unsigned char attribute;
	struct fileData *fileList;
	UInt_8 amountOfFiles;
	
} FileData;

//// report_getters.c {
	FileData getFileData(char *name, UInt_8 firstCluster, UInt_8 fileName_offset, unsigned char attribute);

	UInt_8 getUIntFromUChar(unsigned char * arr, size_t size, UInt_8 offset);

	//FileData getFileData();
	UInt_8 getNumOfFragments(DriveInfo drive, UInt_8 firstCluster);
	//UInt_8 getNumOfFragments(FileData fdata);

	// получить количество всех связанных структур
	UInt_8 getAmountOfFiles(FileData * fdata);
//---- }


//// report_printers.c {
	// напечатать все элементы структуры 
	//void printFileInfo(FileData fdata, UInt_8 grade);

	// напечатать элементы в файл
	void fprintFileInfo(FILE *file, DriveInfo drive, FileData * fdata, UInt_8 grade);
//---- }


//// getFileData.c {
	char * getLFN(unsigned char *buf, UInt_8 offset);

	char * getSFN(unsigned char *buf, UInt_8 offset);

	FileData getFolder(FileData fdata, DriveInfo drive);

	FileData getDirFiles(unsigned char * buf, UInt_8 buf_s, DriveInfo drive, FileData fdata);
//---- }


//// freeFData.c {
	// очистить всю динамически выделенную память в структуре
	void freeFiles(FileData fdata);
//---- }


//// makeReport.c {
	// сканировать специальный файл раздела устройства с ФС ФАТ16 и создать отчёт
	void makeReport(char *direction);
//---- }

#endif // DR_HEADER.H