#ifndef DRIVE_H
#define DRIVE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "../../dataManagment/base_data.h"

//// STRUCTURES
	typedef struct {
		// структура с данными загрузочного сектора
		BootSecInfo bootSec;
		// размер диска
		UInt_8 sizeOfDrive;
		// Наименование файловой системы
		char * fileSysName;
		//
		UInt_8 fat_offset;
		//
		UInt_8 dataSec_offset;
		//
		UInt_8 sizeOfCluster;

		FILE *file;
	} DriveInfo;
//----


//// drive_printers.c
	//void printDriveInfo(DriveImage drive);
	
	void printDriveInfo(DriveInfo drive);

	//Печатает данные диска в файл
	void fprintDriveInfo(FILE *file, DriveInfo drive);
//-----


//// drive_getters.c
	// Функция для получения наименования файловой системы
	char * getStringFromBytes(FILE *file, unsigned short int size, UInt_8 offset);

	// получить массив байт в строке
	char * getBytesInChar(FILE * file, UInt_8 amount, UInt_8 offset);

	// Принимает указатель на файл и смещение, с которого читать, 
	// возвращает структуру 
	//DriveImage getDrive(FILE *file, UInt_8 offset);
	DriveInfo getDrive(FILE *file, UInt_8 offset);
//----

#endif /*DRIVE_H*/