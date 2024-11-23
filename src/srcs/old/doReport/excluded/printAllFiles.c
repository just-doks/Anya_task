#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../headers/main_header.h"
#include "../headers/dr_header.h"


UInt_8 printLFN(FILE *file, UInt_8 offset) {
	UInt_8 c = getIntFromBytes(file, 1, offset);

	if (c & 0x40 != 0x40) {
		return 0;
	}
	c -= 0x40;
	int i = 0, j = 0, k = 0;
	UInt_8 d;
	char string[260];

	for (i = c - 1; i >= 0; i--) {
		for (j = 0x1; j < 0x20; j+=0x2) {
			d = getIntFromBytes(file, 2, offset + i*0x20 + j);
			
			if (d == 0) {
				string[k] = '\0';
				break;
			}
			string[k++] = ((d >= 0x20) && (d <= 0x7E)) ? (char) d : '_'; 

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

	printf("%s\n", string);
	return c;	
} // is ok

UInt_8 printSFN(FILE *file, UInt_8 offset) {
	char eight[9];
	char three[4];
	unsigned char c;
	unsigned int i = 0;
	fseek(file, offset, SEEK_SET);
	for (i = 0; i < 8; i++) {
		fread(&c, sizeof(char), 1, file);
		if (c == 0x20) break;
		eight[i] = c;
	}
	eight[i] = '\0';
	fseek(file, offset + 0xB, SEEK_SET);	
	fread(&c, 1, 1, file);
	if ((c & 0x10) == 0x10) {
		printf("%s\n", eight);
	}   else {
		fseek(file, -4, SEEK_CUR);
		fread(three, sizeof(char), 3, file);
		three[3] = '\0';
		printf("%s.%s\n", eight, three);
	}
	return 0;
} // is ok, but need to fix

/*
UInt_8 getNumOfClusters(FILE *file, UInt_8 fat_offset, UInt_8 shift) {
	UInt_8 i = 0;
	UInt_8 bytes = shift;
	do {
		bytes = getIntFromBytes(file, 2, fat_offset + bytes*2);
		i++;
	} while (bytes != 0xFFFF);
	return i;
} // не актуально
*/

void checkFN(DriveInfo drive, FileData fAdres, UInt_8 grade) {
	UInt_8 offset = 0;
	UInt_8 i = 0, j = 0, k = 0;
	UInt_8 c = 0; // up to 8 bytes (from 0 to 2^64 - 1)

	for (j = 0; j < *fAdres.chain_size; j++) {
		offset = *(fAdres.address_chain + j);

		for (i = 0; i < drive.sizeOfCluster; i+=0x20) {
			c = getIntFromBytes(drive.file, 3, offset + i);

			if (c == 0) break;
			if (c == 0x20202E) {
				continue;
			}
			if (c == 0x202E2E) {
				continue;
			}
			if (((c & 0xE5) == 0xE5) || ((c & 0x05) == 0x05)) continue;

			c = getIntFromBytes(drive.file, 1, offset + i + 0xB);

			// красивый отступ для подкаталогов
			for (k = 0; k < grade; k++) { 
				if (k == grade - 1) {
					printf("|"); 
				}
				printf("\t"); 
				} 

			// отрисовка имени файла 	
			if (c == 0xF) { // проверка атрибута файла
				// если атрибут равен 0xF, значит имя длинное или содержит нестандартные символы
				int b = printLFN(drive.file, offset + i);

				if (b == 0) {
					printf("Damaged LFN record;\n");
					continue;
				}
				i += 0x20 * b;
			} else {
				printSFN(drive.file, offset + i); // ?
			}

			c = getIntFromBytes(drive.file, 1, offset + i + 0xB);

			// Если атрибут записи соотв каталогу (папке), то вызываем рекурсию
			if ((c & 0x10) == 0x10) {
				// Получаем смещение папки в области памяти
				UInt_8 folder_offset = getIntFromBytes(drive.file, 2, offset + i + 0x1A) - 1;
				folder_offset *= drive.sizeOfCluster;
				folder_offset += drive.dataSec_offset; 
				// создаём структуру с цепочкой адресов и размером ккаталога 
				// (на случай, если папка фрагментирована и имеет более 1024 записей)
				FileAddress fAdres = getFileAddress(drive, getIntFromBytes(drive.file, 2, offset + i + 0x1A));
				// Вызываем рекурсию
				checkFN(drive, fAdres, grade + 1);
				// Очищаем динамический массив цепочки адресов за ненадобностью
				free(fAdres.chain);
			}
		
			// main block of code
			
			//

		} // end of for(i)
	} // end of for(j)
} // end of checkFN()