#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

#include "../dataManagment/base_data.h"
#include "../dataManagment/drive.h"
#include "../dataManagment/fdata_header.h"
#include "dr_header.h"


void makeReport(char *direction) {
	FILE *file = fopen(direction, "rb");

	DriveInfo drive = getDrive(file, 0);

	FILE *report = fopen("report.txt", "w"); // создаём текстовый файл, который будет отчётом
	
	FILE *filelist = fopen("filelist.txt", "w");

	FileData fdata = getFileData(NULL, 1, drive.dataSec_offset, 0);

	fdata = getFolder(fdata, drive);
	fprintFileInfo(filelist, drive, &fdata, 0);

	freeFiles(fdata);

	//showBytesOf(file, 1, 0);

	Package pack;
	pack.amountOfFiles = 0;
	pack.numOfFragFiles = 0;

	pack = scanDirs(1, drive, pack);

	fprintReport(report, pack, drive, direction);
	fprintReport(stdout, pack, drive, direction);

	fclose(report);
	fclose(filelist);

	free(drive.fat_table);
	fclose(file); // закрываем файл
}