#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "../base_data.h"
#include "../drive.h"


/*
// Получение целочисленного значения из unsigned char * array, слева направо
UInt_8 getUIntFromUChar(unsigned char * arr, size_t size, UInt_8 offset) {
	UInt_8 a = 0; // буфер для байта
	unsigned char l;
    int i = 0;
    for (i = 0; i < size; i++) {
    	l = *(arr + offset + i);

    	a += (UInt_8) (l << (BYTE*i));
    }
    return a;
}
*/


// Функция для получения наименования файловой системы
// not used
/*
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
*/

// Получение массива байт из потока данных файла
unsigned char * getBytesInUChar(FILE * file, UInt_8 amount, UInt_8 offset) {
		unsigned char * tmp_string = (unsigned char *) calloc(amount, sizeof(unsigned char));
		fseek(file, offset, SEEK_SET);
		fread(tmp_string, sizeof(unsigned char), amount, file);
		fseek(file, 0, SEEK_SET);
		return tmp_string;
}


/*
UInt_8 getUIntFromFATTable(DriveInfo drive, UInt_8 offset) {
	UInt_8 i = 0;
	UInt_8 tmp = 0;
	tmp += *(drive.fat_table + (offset * 2)); 
	tmp += *(drive.fat_table + (offset * 2) + 1) << BYTE; 
	return tmp;
} */

// Получение массива байт из потока данных файла
unsigned short * getUShortFromBytes(FILE * file, UInt_8 amount, UInt_8 offset) {
		unsigned short * tmp_string = (unsigned short *) calloc(amount, sizeof(unsigned short));
		fseek(file, offset, SEEK_SET);
		fread(tmp_string, sizeof(unsigned short), amount, file);
		fseek(file, 0, SEEK_SET);
		return tmp_string;
}

// работает
UInt_8 getNumOfFragments(DriveInfo drive, UInt_8 firstCluster) {

	UInt_8 i = 1;
	UInt_8 first = firstCluster;
	UInt_8 second = *(drive.fat_table + firstCluster);

	while (second != 0xFFFF) {
		if (second - first != 1) i += 1;
		first = second;
		second = *(drive.fat_table + first);		
	};

	return i;

} 

DriveInfo getDrive(FILE *file, UInt_8 shift) {
		DriveInfo drive;

		BootSecInfo bootSec = getBootSecInfo(file, shift);

		/*
		fseek(file, 0L, SEEK_END);
		UInt_8 _DriveEnd = ftell(file);
		fseek(file, 0L, SEEK_SET);
		*/

		UInt_8 _sizeOfDrive = bootSec.bytesPerSec * getIntFromBytes(file, 4, 0x20);

		UInt_8 _SizeOfFAT = bootSec.secPerFAT * bootSec.bytesPerSec;

		//////////////////////////////////////////////////
		// defining drive variables

		drive.fat_offset = bootSec.bytesPerSec * bootSec.reservedSec;

		drive.fat_size = bootSec.secPerFAT * bootSec.bytesPerSec;

		drive.fat_table = getUShortFromBytes(file, _SizeOfFAT/2, drive.fat_offset);
		
		drive.dataSec_offset = bootSec.bytesPerSec * (bootSec.reservedSec 
			+ bootSec.secPerFAT * bootSec.amountOfFAT);
	
		drive.sizeOfCluster = bootSec.bytesPerSec * bootSec.secPerClustr;

		drive.clustersAmount = (_sizeOfDrive - drive.dataSec_offset) / drive.sizeOfCluster;

		drive.file = file;

		return drive;
}

