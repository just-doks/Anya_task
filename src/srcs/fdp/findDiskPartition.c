#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include <dirent.h>

#include "../dataManagment/base_data.h"
#include "fdp_header.h"

// Главная функция
char * find_Disk_Partition() {

	DIR *dir; // указатель на поток к папке

	struct dirent *dirent;  // структура данных (файлов) папки,
	// элемент структуры d_name является именем файла, на который ссылается указатель DIR *

	int i = 0, flag = 0; // счётчики

	//Открываем поток в указанную директорию и получаем указатель на первый элемент
	dir = opendir("/dev");

	printf("Connecting: ");
	//Если всё хорошо - продолжаем, иначе возвращаем нулевой указатель
	if (dir != NULL) {
		printf("success!\n");
	} else {
		printf("No such directory\n");
		return NULL;
	}

	while (i < 1024) {
		dirent = readdir(dir);
		if (dirent == NULL) break;
		flag += checkFileName(dirent->d_name);
		i++;
	}

	//Переносим указатель в потоке на первый элемент (файл)
	rewinddir(dir);

	// Создаём массив имён для подходящих под критерии файлов
	char ** disks = (char **) calloc (flag, sizeof(dirent->d_name));

	// Обнуляем счётчик
	i = 0;

	// Переносим в массив все подходящие имена
	while (i < flag) {
		dirent = readdir(dir);
		if (checkFileName(dirent->d_name) == 1) {
			*(disks+ i) = getWholeWay(dirent->d_name);
			i++;
		}
	}
	//закрываем поток
	closedir(dir);

	// Выводим все полученные имена
	printf("--------------------\n");
	printf("Available disks:\n");
	if (flag == 0) printf("No available drives.\n");
	for (i = 0; i < flag; i++) {
		printf("--------------------\n");
		printf("%d. Path: %s\n", i+1, *(disks+i));

		//printCapacity(*(disks + i));
		printPartitionData(*(disks + i));
	}
	printf("--------------------\n");

	int num = 0;
	if (flag > 0) {
		printf("Choose one: ");
		scanf("%1d", &num);
		printf("--------------------\n");
	}
	
	//char * direction = (char*) calloc(1, sizeof(dirent->d_name)); 
	// no need to allocate memory for existing pointing value
	char * direction;
	
	if (num <= flag && num >= 1) {
		direction = *(disks+num-1);
	} else {
		direction = NULL;
	}

	// Очистка массива
	for (i = 0; i < flag; i++) {
		if (i == num - 1) {
			continue;
			}
		free(*(disks+i));
	}
	free(disks);
	return direction;
}