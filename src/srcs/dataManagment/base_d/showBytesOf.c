#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

#include "../base_data.h"

// функция отображения данных секторами, по смещению - (file, amount of sectors, offset)
void showBytesOf(FILE *file, UInt_8 sectors, UInt_8 offset) {

    unsigned char a = 0; // буфер для байта
    int i = 0, j = 0, k = 0; // счётчики
    fseek(file, offset, SEEK_SET); // возвращаем указатель в файле на начало

    // здесь реализован красивый вывод
    for (i = 0; i < sectors * 0x20; i++) { // смещение по оси Y

        if ((i % 512) == 0) {
            for (j = 0; j < 16; j++) {
                if (j == 0) printf("\t\t");
                printf("x%01X ", j);
                if (j == 7) printf("    ");
                if (j == 0xF) printf("\n\n"); 
            }
        }
        

    	//printf("%d.\t", ++k);
        printf("%08X\t", offset + 0x10 * i);
    
        for (j = 0; j < 0x10; j++) { // смещение по оси X
    		fread(&a, 1, 1, file); // Читаем байты из файла
            if (a <= 0xF) { // Рисуем нолик для красоты, если байт меньше 16
                printf ("0%X ", a);
            } else {
                printf("%X ", a);
            }
            if (j == 7) printf("%s", "    "); // пропуск после каждого восьмого байта
        }

    	printf("%s", "\n"); // переход на новую строку каждые 16 байт
    	//if (k % 2 == 0) printf("\n");

        if ((i+1) % 0x20 == 0) printf("%s", "\n"); // делаем пропуск после конца каждого сектора
    }
    fseek(file, 0, SEEK_SET); // возвращаем указатель в файле на начало
}