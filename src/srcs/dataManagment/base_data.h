#ifndef BASE_DATA_H
#define BASE_DATA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define BYTE 8
#define Kb 1024
#define Mb 1048576
#define Gb 1073741824

typedef unsigned long int UInt_8;

/// Структуры
	// Структура с данными из загрузочного сектора ФС ФАТ16
	typedef struct {
			// Число байт в секторе
			// Допустимые значения - 512, 1024, 2048 и 4096
			UInt_8 bytesPerSec;

			// Количество секторов на кластер
			// допустимо 2, 4, 8, 16 и 32
			UInt_8 secPerClustr;

			// Количество зарезервированных секторов под загрузочный раздел
			UInt_8 reservedSec;

			// Количество секторов в одной таблице ФАТ
			// равно нулю, если это FAT32
			UInt_8 secPerFAT;

			// количество таблиц ФАТ
			UInt_8 amountOfFAT;

			// Размер корневой директории
	    	UInt_8 sizeofRootDir;

	} BootSecInfo;
///--- } структуры


//// base_printers.c
	// Печатает все данные структуры
	void printBootSecInfo(BootSecInfo drive);

	// печатает данные загрузочного сектора в файл
	void fprintBootSecInfo(FILE *file, BootSecInfo drive);
//-----


//// base_getters.c
	// Получение целочисленного значения из байт файла, слева направо
	UInt_8 getIntFromBytes(FILE * file, int size, UInt_8 offset);

	// Принимает указатель на файл и смещение, с которого читать, 
	// возвращает структуру
	BootSecInfo getBootSecInfo(FILE * file, UInt_8 offset);
//----

//// showBytesOf.c
	void showBytesOf(FILE *file, UInt_8 sectors, UInt_8 offset);
//----
	

#endif /*BASE_DATA_H*/
