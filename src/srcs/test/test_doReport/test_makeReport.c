#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

#include <time.h>

#include "../../dataManagment/base_data.h"
#include "../test_dataManagment/test_drive.h"
#include "test_dr_header.h"

void makeReport(char *direction, FILE *file, DriveInfo drive) {

	FILE *report = fopen("report.txt", "w"); // создаём текстовый файл, который будет отчётом
	FileData fdata = getFileData(NULL, 1, drive.dataSec_offset, 0); // создям экземпляр класса FileData
	
	//clock_t begin = clock();

	fdata = getFolder(fdata, drive);

	//clock_t end = clock();
	//printf("\nFIRST interval = %lfms\n\n", (double)(end - begin) / CLOCKS_PER_SEC * 1000.0);


	// вычисляем количество файлов
	
	UInt_8 FilesAmount = getAmountOfFiles(&fdata);
	printf("Amount of Files: %d\n", FilesAmount);

	

	// создаём буфер, в который будут выводиться данные, прежде, чем запишутся в файл
	//unsigned char *out_buf = calloc((FilesAmount+1) * 300, sizeof(unsigned char));

	// с помощью данной функции мы сообщаем, что данные, выводимые в указанный файл,
	// требуется буферизовать полностью в указанный массив
	// _IOFBF - режим буферизации, означает "буферизовать всё"
	//setvbuf(report, out_buf, _IOFBF, (FilesAmount+1) * 300);


	
	//begin = clock();
	fprintf(report, "Direction: %s\n", direction);
	fprintDriveInfo(report, drive);
	fprintf(report, "Amount of Files: %d\n", FilesAmount);
	fprintf(report, "________________________________________\n");
	fprintFileInfo(report, drive, &fdata, 0);
	//fflush(report);
	fclose(report);

	//end = clock();
	//printf("\nSECOND interval = %lfms\n\n", (double)(end - begin) / CLOCKS_PER_SEC * 1000.0);
	
	
	freeFiles(fdata);
	//free(out_buf);
	
}