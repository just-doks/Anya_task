#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../dataManagment/base_data.h"
#include "../dataManagment/drive.h"
#include "dr_header.h"

char * getLFN(FILE *file, UInt_8 offset) {
	UInt_8 c = getIntFromBytes(file, 1, offset);

	if (c & 0x40 != 0x40) {
		return NULL;
	}
	c -= 0x40;
	int i = 0, j = 0, k = 0;
	UInt_8 d;
	char *string = (char*) calloc(260, sizeof(char));

	for (i = c - 1; i >= 0; i--) {
		for (j = 0x1; j < 0x20; j+=0x2) {
			d = getIntFromBytes(file, 2, offset + i*0x20 + j);
			
			if (d == 0) {
				*(string + k)= '\0';
				break;
			}
			*(string + k++) = ((d >= 0x20) && (d <= 0x7E)) ? (char) d : '_'; 

			if (j == 0x9) {
				j += 3;
				continue;
			}
			if (j == 0x18) {
				j += 2;
				continue;
			}
		}
	}

	//printf("%s\n", string);
	return string;	
} 

char * getSFN(FILE *file, UInt_8 offset) {
	char * eightThree = (char *) calloc(13, sizeof(char));
	unsigned char c;
	unsigned int i = 0, j = 0;

	fseek(file, offset, SEEK_SET);
	for (i = 0; i < 8; i++) {
		fread(&c, sizeof(char), 1, file);
		if (c == 0x20) break;
		*(eightThree + i) = c;
	}

	fseek(file, offset + 0xB, SEEK_SET);	
	fread(&c, 1, 1, file);

	if ((c & 0x10) != 0x10) {
		fseek(file, -4, SEEK_CUR);
		*(eightThree + i++) = '.';
		for (j = 0; j < 3; j++) {
			fread(&c, sizeof(char), 1, file);
			*(eightThree + i++) = c;
		}
	}

	*(eightThree + i) = '\0';
	return eightThree;
} // end of getSFN

FileData getFolder(FileData fdata, DriveInfo drive) {

	UInt_8 offset = 0;
	UInt_8 i = 0, j = 0, s = 0;
	UInt_8 c = 0; // up to 8 bytes (from 0 to 2^64 - 1)
	//char *string;
	
	for (j = 0; j < *fdata.chain_size; j++) {
		offset = *(fdata.address_chain + j);

		for (i = 0; i < drive.sizeOfCluster; i+=0x20) {


			// читаем первые 3 байта 32 байтовой записи
			c = getIntFromBytes(drive.file, 3, offset + i);

			if (c == 0) break; // Если первый байт нулевой - дальше записей нет
			if ((c == 0x20202E) || (c == 0x202E2E)) continue; // это точки, служат для навигации:
			// одна точка - это текущий каталог, две точки - предыдущий каталог

			c = getIntFromBytes(drive.file, 1, offset + i);
			if ((c == 0xE5) || (c == 0x05)) continue; // коды удалённого файла

			// читаем байт 32 байтовой записи по смещению 0xB - смещение атрибута файла
			c = getIntFromBytes(drive.file, 1, offset + i + 0xB);

			char *string;

			// Получаем им. файла 	
			if (c == 0xF) { // проверка атрибута файла
				// если атрибут равен 0xF, значит имя длинное или содержит нестандартные символы

				// получаем длинное имя
				string = getLFN(drive.file, offset + i);

				// если вместо имени пришел нулевой указатель - запись битая, пропустить итерацию
				if (string == NULL) continue;
				// читаем первый байт записи, в длинном имени, первая запись сверху вниз имеет размерность
				// вычитая 0x40 получаем количество 32 байтовых записей, хранящих длинное имя
				c = getIntFromBytes(drive.file, 1, offset + i) - 0x40;
				i += 0x20 * c;
			} 
			else {
				// если атрибут не относится к длинному имени, отобразить короткое имя файла 
				string = getSFN(drive.file, offset + i); 
			}

			c = getIntFromBytes(drive.file, 1, offset + i + 0x1A);
			if (c == 0) {
				free(string);
				continue;
			}

			// создаём экземпляр структуры 
			FileData nfile = getFileData(&nfile);

			// Занесли имя
			nfile.name = string;
			// заполняем адресную информацию
			nfile = getFileAddress(nfile, drive, getIntFromBytes(drive.file, 2, offset + i + 0x1A));

			// Снова читаем атрибут
			c = getIntFromBytes(drive.file, 1, offset + i + 0xB);
			// Если атрибут записи соотв каталогу (папке), то вызываем рекурсию
			if ((c & 0x10) == 0x10) {
				// Вызов рекурсии
				nfile = getFolder(nfile, drive);
			}

			fdata.fileList = (FileData*) realloc(fdata.fileList, sizeof(FileData)*(++s));
			*(fdata.fileList + s - 1) = nfile;

		} // end of for(i)
	} // end of for(j)
	fdata.amountOfFiles = (UInt_8*)calloc(1, sizeof(UInt_8));
	*fdata.amountOfFiles = s;

	return fdata;	
	} // end of getFileList()