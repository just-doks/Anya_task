#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../dataManagment/base_data.h"
#include "../dataManagment/drive.h"
#include "dr_header.h"


 Package scanDirs(UInt_8 out_firstCluster, DriveInfo drive, Package pack) {

	UInt_8 i = 0, buf_s = 0;
	UInt_8 attribute = 0;
	UInt_8 firstCluster = 0;
	UInt_8 fileSize = 0;
	unsigned short fat_cell = out_firstCluster;
	UInt_8 offset = 0;
	UInt_8 c = 0;

	do {
		if (fat_cell == 0) break;
		offset = drive.dataSec_offset + (fat_cell - 1) * drive.sizeOfCluster;
		fseek(drive.file, offset, SEEK_SET);

		// проверяем, сколько всего записей в одном кластере
		for (i = 0; i < drive.sizeOfCluster; i+=0x20) {
			fread(&c, 1, 1, drive.file);
			if (c == 0) break;
			buf_s += 0x20;
			fseek(drive.file, 0x1F, SEEK_CUR);
		}

		// записываем в буфер все найденные записи
		unsigned char * buf;
		buf = (unsigned char *)calloc(buf_s, sizeof(unsigned char));
		fseek(drive.file, offset, SEEK_SET);
		fread(buf, sizeof(unsigned char), buf_s, drive.file);

		// main block ////////////////////////////////////////
		//////////////////////////////////////////////////////
		short *folders;
		short fArrSize = 0;

		//в этом цикле считаем все файлы и определяем количество папок 
		for (i = 0; i < buf_s; i +=0x20) {
			
			// читаем первые 3 байта 32 байтовой записи
			c = getUIntFromUChar(buf, 3, i);

			if ((c == 0x20202E) || (c == 0x202E2E)) { 
				continue;
			} // это точки, служат для навигации:
			// одна точка - это текущий каталог, две точки - предыдущий каталог

			c = getUIntFromUChar(buf, 1, i);
			if ((c  == 0xE5) || (c  == 0x05)) { 
				continue;
			} // коды удалённого файла

			// читаем два байта 32 байтовой записи по смещению 0x1А - смещение первого кластера файла
			firstCluster = getUIntFromUChar(buf, 2, i + 0x1A);
			if (firstCluster != 0) {
				attribute = getUIntFromUChar(buf, 1, i + 0xB);
				fileSize = getUIntFromUChar(buf, 4, i + 0x1C);

				if (   ( ( (attribute & 0x20) == 0x20) && (fileSize != 0) )
					|| ( ( (attribute & 0x10) == 0x10) && (fileSize == 0) ) 
					) {
					pack.amountOfFiles++;
					//printf("first cluster: %04X\t", firstCluster);
					//printf("num of fragments: %d\n", getNumOfFragments(drive, firstCluster));
					pack.numOfFragFiles += (getNumOfFragments(drive, firstCluster) > 1) ? 1 : 0;
				}

				if ( ( (attribute & 0x10) == 0x10) && (fileSize == 0) ) {
					fArrSize++;
				}
			}
		}

		// если папок нет - прекратить итерацию
		if (fArrSize == 0) {
			free(buf);
			fat_cell = *(drive.fat_table + fat_cell);
			if (out_firstCluster == 1) break;
			continue;
		}

		folders = (short*) calloc(fArrSize, sizeof(short));
		short flag = 0;

		// добавляем в список номера первых кластеров всех папок
		for (i = 0; i < buf_s; i += 0x20) {
			c = getUIntFromUChar(buf, 3, i);
			if ((c == 0x20202E) || (c == 0x202E2E)) continue;

			c = getUIntFromUChar(buf, 1, i);
			if ((c  == 0xE5) || (c  == 0x05)) continue;

			firstCluster = getUIntFromUChar(buf, 2, i + 0x1A);
			if (firstCluster != 0) {
				attribute = getUIntFromUChar(buf, 1, i + 0xB);
				fileSize = getUIntFromUChar(buf, 4, i + 0x1C);

				if ( ( (attribute & 0x10) == 0x10) && (fileSize == 0) ) {
					*(folders + flag++) = (short) firstCluster;
				}
			}
		}

		free(buf);

		for (i = 0; i < fArrSize; i++) {
			pack = scanDirs(*(folders + i), drive, pack);
		}

		free(folders);
		//////////////////////////////////////////////////////
		//////////////////////////////////////////////////////

		fat_cell = *(drive.fat_table + fat_cell);

		if (out_firstCluster == 1) break;

	} while (fat_cell != 0xFFFF);

	return pack;
}	
