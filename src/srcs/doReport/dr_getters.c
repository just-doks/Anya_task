#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "../dataManagment/base_data.h"
#include "../dataManagment/drive.h"
#include "dr_header.h"

// Получение целочисленного значения из unsigned char * array, слева направо
// работает
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

/*
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

} */