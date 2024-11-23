#ifndef DRIVE_H
#define DRIVE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "base_data.h"

//// STRUCTURES
	typedef struct driveInfo {

		unsigned short *fat_table;

		UInt_8 fat_offset;

		UInt_8 fat_size;

		UInt_8 dataSec_offset;
		//
		UInt_8 sizeOfCluster;

		UInt_8 clustersAmount;

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
	// не используется
	unsigned char * getBytesInUChar(FILE * file, UInt_8 amount, UInt_8 offset);

	UInt_8 getNumOfFragments(DriveInfo drive, UInt_8 firstCluster);

	unsigned short * getUShortFromBytes(FILE * file, UInt_8 amount, UInt_8 offset);

	// Принимает указатель на файл и смещение, с которого читать, 
	// возвращает структуру 
	DriveInfo getDrive(FILE *file, UInt_8 offset);

//----

#endif /*DRIVE_H*/