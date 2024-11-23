#ifndef DR_HEADER_H
#define DR_HEADER_H

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "../../dataManagment/base_data.h"
#include "../dataManagment/drive.h"

typedef struct fileData {
	char *name;
	UInt_8 *fat_chain;
	UInt_8 *address_chain;
	UInt_8 *chain_size;
	struct fileData *fileList;
	UInt_8 *amountOfFiles;
} FileData;

//// report_getters.c {
	FileData getFileAddress(FileData fdata, DriveInfo drive, UInt_8 firstCluster);

	FileData getFileData(FileData * fdata);

	UInt_8 getNumOfFragments(FileData fdata);

	// получить количество всех связанных структур
	UInt_8 getAmountOfFiles(FileData fdata);
//---- }


//// report_printers.c {
	// напечатать все элементы структуры 
	void printFileInfo(FileData fdata, UInt_8 grade);

	// напечатать элементы в файл
	void fprintFileInfo(FILE* file, FileData fdata, UInt_8 grade);
//---- }


//// getFileData.c {
	char * getLFN(FILE *file, UInt_8 offset);

	char * getSFN(FILE *file, UInt_8 offset);

	FileData getFolder(FileData fdata, DriveInfo drive);
//---- }


//// freeFData.c {
	// очистить всю динамически выделенную память в структуре
	void freeFiles(FileData fdata);
//---- }


//// makeReport.c {
	// сканировать специальный файл раздела устройства с ФС ФАТ16 и создать отчёт
	void makeReport(char *direction, FILE *file, DriveInfo drive);
//---- }

#endif // DR_HEADER.H