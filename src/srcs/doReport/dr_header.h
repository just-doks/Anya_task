#ifndef DR_HEADER_H
#define DR_HEADER_H

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "../dataManagment/base_data.h"
#include "../dataManagment/drive.h"
#include "../dataManagment/fdata_header.h"

typedef struct package
{
	int numOfFragFiles;
	int amountOfFiles;

} Package;

//// dr_getters.c {
	UInt_8 getUIntFromUChar(unsigned char * arr, size_t size, UInt_8 offset);

	//UInt_8 getNumOfFragments(DriveInfo drive, UInt_8 firstCluster);
//---- }


//// dr_printers.c {
	//напечатать таблицу FAT из буфера в указанный файл
	void fprintFAT(FILE *destination, unsigned short *fat_table, size_t size);

	void fprintReport(FILE *destination, Package pack, DriveInfo drive, char *direction);

	// напечатать все элементы структуры 
	//void printFileInfo(FileData fdata, UInt_8 grade);

	// напечатать элементы в файл
	//void fprintFileInfo(FILE *file, DriveInfo drive, FileData * fdata, UInt_8 grade);
//---- }


//// getFData.c {
	char * getLFN(unsigned char *buf, UInt_8 offset);

	char * getSFN(unsigned char *buf, UInt_8 offset);

	Package scanDirs(UInt_8 firstCluster, DriveInfo drive, Package pack);

	FileData getFolder(FileData fdata, DriveInfo drive);

	FileData getDirFiles(unsigned char * buf, UInt_8 buf_s, DriveInfo drive, FileData fdata);
//---- }


//// makeReport.c {
	// сканировать специальный файл раздела устройства с ФС ФАТ16 и создать отчёт
	void makeReport(char *direction);
//---- }

#endif // DR_HEADER.H