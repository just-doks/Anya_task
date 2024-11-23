#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "../dataManagment/base_data.h"

#define strsize(args...) snprintf(NULL, 0, args) + sizeof('\0')

// получить полный путь к файлу
char* getWholeWay(char * arrarrs) {
	int i = 0;
	char * word = (char*) calloc(strsize("/dev/%s", arrarrs), sizeof(char));
	sprintf(word, "/dev/%s", arrarrs);
	return word;
}

char * getCharFromBytes(FILE *file, int size, UInt_8 offset) {
	char *string = (char*) calloc(size + 1, sizeof(char));
	char l;
	int i = 0;
	fseek(file, offset, SEEK_SET);
	for (i = 0; i < size; i++) {
		fread(&l, 1, 1, file);
		*(string + i) = ((l >= 0x20) && (l <= 0x7E)) ? l : '_';
	}
	*(string + i) = '\0';

	return string;
}