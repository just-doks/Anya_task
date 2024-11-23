#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <time.h>

#include "dataManagment/base_data.h"
#include "old/dataManagment/drive.h"
#include "fdp/fdp_header.h"
#include "old/doReport/dr_header.h"
//#include "../headers/dr_header.h"

int main(int argc, char* argv[]) {
	clock_t begin = clock();
	printf("///////////////////////////////////////\n");
	char * direction; // объявляем строку - путь к файлу
	direction = find_Disk_Partition(); // Получаем путь к файлу устройства
	printf("///////////////////////////////////////\n");

	if (direction == NULL) { // если сстрока пустая - завершить программу
		fprintf(stdout, "No FAT16 devices chosen or connected.\n");
		free(direction);
		printf("///////////////////////////////////////\n");
		return 0;
	}

	FILE *file = fopen(direction, "rb");

	DriveInfo drive = getDrive(file, 0);

	printDriveInfo(drive);

	makeReport(direction, file, drive);

	free(direction); // очищаем массив символов (строку пути к файлу устройства)
	//free(drive.fat_table);
	//free(drive.fileSysName); // очищаем массив символов (строку имени файловой системы) из структуры
	fclose(file); // закрываем файл
	printf("///////////////////////////////////////\n");
	clock_t end = clock();
	printf("Interval = %lfms\n", (double)(end - begin) / CLOCKS_PER_SEC * 1000.0);
	return 0;	
}