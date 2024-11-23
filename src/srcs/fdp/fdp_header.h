#ifndef FDP_HEADER_H
#define FDP_HEADER_H

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "../dataManagment/base_data.h"

//// fdp_printers.c
	// Отобразить объём раздела
	//void printCapacity (char * string);
	
	// Напечатать сведения о разделе
	void printPartitionData(char * string);
//----


//// fdp_getters.c
	// получить полный путь к файлу
	char* getWholeWay(char * arrarrs);

	// получить массив символов (строку) из байт файла
	char * getCharFromBytes(FILE *file, int size, UInt_8 offset);
//----


//// checkFileBytes.c
	// Супер важная функция по проверке байт 
	int checkFileBytes(char * str, UInt_8 offset);
//----


//// check_FileName_linux.c or check_FileName_macos.c
	// Функция принимает на вход строку, проверяет по заданному правилу и возвращает:
	// 1, если слово прошло по правилу
	// 0, если не прошло 
	int checkFileName(char* name);
//----


//// findDiskPartition.c
	char * find_Disk_Partition();
//----

#endif /*FDP_HEADER_H*/
