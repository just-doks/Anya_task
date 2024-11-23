#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "../../../dataManagment/base_data.h"
#include "../drive.h"

void printDriveInfo(DriveInfo drive) {
	printf("FAT type is: %s\n", drive.fileSysName);
	printf("Size of drive: %.2lfGb\n", (double) drive.sizeOfDrive/Gb);
	printBootSecInfo(drive.bootSec);
}

void fprintDriveInfo(FILE *file, DriveInfo drive) {
	fprintf(file, "FAT type is: %s\n", drive.fileSysName);
	fprintf(file, "Size of drive: %.2lfGb\n", (double) drive.sizeOfDrive/Gb);
	fprintBootSecInfo(file, drive.bootSec);
}