#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "../base_data.h"

// Получение целочисленного значения из байт файла, слева направо
UInt_8 getIntFromBytes(FILE * file, int size, UInt_8 offset) {
	UInt_8 a = 0; // буфер для байта
	//unsigned char l;
    //int i = 0;

    fseek(file, offset, SEEK_SET); // возвращаем указатель в файле на начало

    fread(&a, size, 1, file); /*new way to get data*/
    /*
    for (i = 0; i < size; i++) {
    	fread(&l, 1, 1, file);
    	a += (unsigned long int) l << (BYTE*i);
    }
    */

    fseek(file, 0, SEEK_SET); // возвращаем указатель в файле на начало

    return a;
}

// Функция, заполняющая структуру BootSecInfo
// Принимает указатель на файл, возвращает структуру
BootSecInfo getBootSecInfo(FILE * file, UInt_8 offset) {
		BootSecInfo drive;
		UInt_8 bytesPerSec_offset = 0x0B + offset; // 2 bytes
		UInt_8 secPerClustr_offset = 0x0D + offset; // 1 byte
		UInt_8 reservedSec_offset = 0x0E + offset; // 2 bytes
		UInt_8 secPerFAT_offset = 0x16 + offset; // 2 bytes
		UInt_8 amountOfFAT_offset = 0x10 + offset; // 1 byte
		// 0, if it's FAT32
		UInt_8 sizeofRootDir_offset = 0x11 + offset; // 2 bytes
	
		drive.bytesPerSec = getIntFromBytes(file, 2, bytesPerSec_offset);
		drive.secPerClustr = getIntFromBytes(file, 1, secPerClustr_offset);
		drive.reservedSec = getIntFromBytes(file, 2, reservedSec_offset);
		drive.secPerFAT = getIntFromBytes(file, 2, secPerFAT_offset);
		drive.amountOfFAT = getIntFromBytes(file, 1, amountOfFAT_offset);
		drive.sizeofRootDir = getIntFromBytes(file, 2, sizeofRootDir_offset)*32;

		return drive;
}