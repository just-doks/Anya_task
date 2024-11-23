#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "../drive.h"


// Функция для получения наименования файловой системы
char * getStringFromBytes(FILE *file, unsigned short int size,  UInt_8 offset) {
		// Выделяем память под символьный массив (строку)
		char * string = (char *) calloc (size + 1, sizeof(char));
		char l;
		short i = 0;
		// перемещаем указатель в потоке файла от начала (SEEK_SET) по смещению offset
		fseek(file, offset, SEEK_SET);
		for (i = 0; i < size; i++) {
			// переносим байты по одному в буферную переменную и переносим в строку
			fread(&l, 1, 1, file);
			
			if (l == 20) break;
			if (!(l >= 48 && l <= 57) 
				&& !(l >= 65 && l <= 90)
				&& !(l >= 97 && l <= 122)) {
				free(string);
				return NULL;
			}
			*(string + i) = l;
		}
		*(string+i) = '\0';
		return string;
}


// Получение массива байт из потока данных файла
unsigned char * getBytesInUChar(FILE * file, UInt_8 amount, UInt_8 offset) {
		unsigned char * tmp_string = (unsigned char *) calloc(amount, sizeof(unsigned char));
		fseek(file, offset, SEEK_SET);
		fread(tmp_string, sizeof(unsigned char), amount, file);
		fseek(file, 0, SEEK_SET);
		return tmp_string;
}


DriveInfo getDrive(FILE *file, UInt_8 shift) {
		DriveInfo drive;
		//UInt_8 fileSysName_offset = 0x36 + shift; // 5 bytes

		drive.bootSec = getBootSecInfo(file, shift);

		fseek(file, 0L, SEEK_END);
		drive.sizeOfDrive = ftell(file);
		fseek(file, 0L, SEEK_SET);

		drive.fileSysName = getStringFromBytes(file, 5, 0x36 + shift);

		drive.fat_offset = drive.bootSec.bytesPerSec * drive.bootSec.reservedSec;
		
		drive.dataSec_offset = drive.bootSec.bytesPerSec 
		* (drive.bootSec.reservedSec 
			+ drive.bootSec.secPerFAT * drive.bootSec.amountOfFAT);
	
		drive.sizeOfCluster = drive.bootSec.bytesPerSec 
				* drive.bootSec.secPerClustr;

		drive.file = file;
		return drive;
}