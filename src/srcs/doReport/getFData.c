#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../dataManagment/base_data.h"
#include "../dataManagment/drive.h"
#include "../dataManagment/fdata_header.h"
#include "dr_header.h"

//int global_val = 0;

char * getLFN(unsigned char *buf, UInt_8 offset) {
	UInt_8 c = getUIntFromUChar(buf, 1, offset); 

	if (c & 0x40 != 0x40) {
		return NULL;
	}
	c -= 0x40;
	int i = 0, j = 0, k = 0;
	UInt_8 d;
	char *string = (char*) calloc(260, sizeof(char));

	for (i = c - 1; i >= 0; i--) {
		for (j = 0x1; j < 0x20; j+=0x2) {
			d = getUIntFromUChar(buf, 2, offset + i*0x20 + j);
			
			if (d == 0) {
				*(string + k)= '\0';
				break;
			}

			if ((d >= 0x20) && (d <= 0x7E)) {
				*(string + k++) = (char) d;
			} else {
				*(string + k++) = 0x5F;
			}

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

	return string;	
} 

char * getSFN(unsigned char *buf, UInt_8 offset) {
	char * eightThree = (char *) calloc(13, sizeof(char));
	unsigned char c;
	unsigned int i = 0, j = 0;

	for (i = 0; i < 8; i++) {
		c = *(buf + offset + i);
		if (c == 0x20) break;
		*(eightThree + i) = (((c >= 0x20) && (c <= 0x7E)) ? (char) c : 0x5F);
	}

	c = *(buf + offset + 0xB);

	if ((c & 0x10) != 0x10) {
		*(eightThree + i++) = '.';
		for (j = 8; j < 11; j++, i++) {
			c = *(buf + offset + j);
			*(eightThree + i) = (((c >= 0x20) && (c <= 0x7E)) ? (char) c : 0x5F);
		}
	}

	*(eightThree + i) = '\0';
	return eightThree;
} // end of getSFN



FileData getFolder(FileData fdata, DriveInfo drive) {
	//printf("Step0;\n");
	UInt_8 i = 0, j = 0, buf_s = 0;
	unsigned short fat_cell = fdata.firstCluster;
	unsigned char * buf;
	UInt_8 offset = 0;
	UInt_8 c = 0;

	do {
		if (fat_cell == 0) break;
		offset = drive.dataSec_offset + (fat_cell - 1) * drive.sizeOfCluster;
		fseek(drive.file, offset, SEEK_SET);

		
		for (i = 0; i < drive.sizeOfCluster; i+=0x20) {
			fread(&c, 1, 1, drive.file);
			if (c == 0) break;
			buf_s += 0x20;
			fseek(drive.file, 0x1F, SEEK_CUR);
		}
		//printf("buf_s = %d\n", buf_s);

		buf = (unsigned char *)calloc(buf_s, sizeof(unsigned char));
		fseek(drive.file, offset, SEEK_SET);
		fread(buf, sizeof(unsigned char), buf_s, drive.file);
		//printf("Step1;\n");
		// main block ////////////////////////////////////////
		fdata = getDirFiles(buf, buf_s, drive, fdata);		
		//////////////////////////////////////////////////////
		free(buf);

		fat_cell = *(drive.fat_table + fat_cell);
		//printf("fat cell = %d\n", fat_cell);

		if (fdata.firstCluster == 1) break;
	} while (fat_cell != 0xFFFF);
	//printf("Step2;\n");
	//////////////////////////////////////////////////////////
	/////////////// TEMPORAL /////////////////////////////////
	/*
	printf("Directory: %s\n", (fdata.name != NULL) ? fdata.name : "_");
	for (i = 0; i < fdata.amountOfFiles; i++) {
		printf("%d.\t", ++global_val);
		printf("\t%s\n", ((fdata.fileList + i)->name != NULL) ? (fdata.fileList + i)->name : "_");
		//printf("\tfirst cluster: %04X\n", (fdata.fileList + i)->firstCluster);
	}
	*/
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////



	for (i = 0; i < fdata.amountOfFiles; i++) {
		if (((fdata.fileList + i)->attribute & 0x10) == 0x10) {
			*(fdata.fileList + i) = getFolder(*(fdata.fileList + i), drive);
		}
	}
	

	return fdata;
}	


FileData getDirFiles(unsigned char * buf, UInt_8 buf_s, DriveInfo drive, FileData fdata) {
	UInt_8 i = 0, filename_offset = 0, fl_s = 0;
	UInt_8 c = 0; // up to 8 bytes (from 0 to 2^64 - 1)
	//char *string = NULL;

	// get amount of files for memory allocating
	for (i = 0; i < buf_s; i+=0x20) {

		// читаем первые 3 байта 32 байтовой записи
		c = getUIntFromUChar(buf, 3, i);

		if (c == 0) break; // Если первый байт нулевой - дальше записей нет
		if ((c == 0x20202E) || (c == 0x202E2E)) { 
			//if (global_val == 3) printf("1-----\n");
			continue;
		} // это точки, служат для навигации:
		// одна точка - это текущий каталог, две точки - предыдущий каталог

		c = getUIntFromUChar(buf, 1, i);
		if ((c  == 0xE5) || (c  == 0x05)) { 
			//if (global_val == 3) printf("2-----\n");
			continue;
		} // коды удалённого файла

		// читаем байт 32 байтовой записи по смещению 0xB - смещение атрибута файла
		c = getUIntFromUChar(buf, 1, i + 0xB);
		if (c == 0xF) continue;

		if (getUIntFromUChar(buf, 2, i + 0x1A) != 0) fl_s++;
	}

	fdata.amountOfFiles += fl_s;
	fdata.fileList = realloc(fdata.fileList, sizeof(FileData) * (fdata.amountOfFiles));
	
	fl_s = 0;

	for (i = 0; i < buf_s; i+=0x20) {
			// читаем первые 3 байта 32 байтовой записи
			c = getUIntFromUChar(buf, 3, i);

			if (c == 0) break; // Если первый байт нулевой - дальше записей нет
			if ((c == 0x20202E) || (c == 0x202E2E)) continue; // это точки, служат для навигации:
			// одна точка - это текущий каталог, две точки - предыдущий каталог
			c = getUIntFromUChar(buf, 1, i);
			if ((c  == 0xE5) || (c  == 0x05)) { 
				continue;
			} // коды удалённого файла

			// читаем байт 32 байтовой записи по смещению 0xB - смещение атрибута файла
			c = getUIntFromUChar(buf, 1, i + 0xB);

			filename_offset = i;

			char *string = NULL;

			// Получаем им. файла 	
			if (c == 0xF) { // проверка атрибута файла
				// если атрибут равен 0xF, значит имя длинное или содержит нестандартные символы

				// получаем длинное имя
				string = getLFN(buf, i);

				// если вместо имени пришел нулевой указатель - запись битая, пропустить итерацию
				if (string == NULL) continue;

				// читаем первый байт записи, в длинном имени, первая запись сверху вниз имеет размерность
				// вычитая 0x40 получаем количество 32 байтовых записей, хранящих длинное имя
				c = getUIntFromUChar(buf, 1, i) - 0x40;

				// перемещаемся вниз, пропустив все LFN записи
				i += 0x20 * c;
			} 
			else {
				// если атрибут не относится к длинному имени, отобразить короткое имя файла 
				string = getSFN(buf, i); 
			}

			// Если в записи файла указан номер первого кластера, то
			if (getUIntFromUChar(buf, 2, i + 0x1A) != 0) {
				// Снова читаем атрибут
				c = getUIntFromUChar(buf, 1, i + 0xB);
				filename_offset += fdata.fileName_offset;
				// создаём экземпляр структуры 
				FileData nfile = getFileData(string, getUIntFromUChar(buf, 2, i + 0x1A), filename_offset, c);
				// добавляем к списку
				*(fdata.fileList + fl_s++) = nfile;
			} else {
				free(string);
			}

		} // end of for

	return fdata;	
	} // end of getDirFiles()