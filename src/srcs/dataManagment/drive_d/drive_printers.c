#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "../base_data.h"
#include "../drive.h"

/*
void printDriveInfo(DriveInfo drive) {
	printf("FAT type is: %s\n", drive.fileSysName);
	printf("Size of drive: %.2lfGb\n", (double) drive.sizeOfDrive/Gb);
	printBootSecInfo(drive.bootSec);
} */

void printDriveInfo(DriveInfo drive) {
	BootSecInfo bootSec = getBootSecInfo(drive.file, 0);
	printBootSecInfo(bootSec);
	printf("fat size: %d Bytes\n", drive.fat_size);
	printf("Amount of address units in fat table: %d\n", drive.fat_size / 2);
	printf("Size of cluster: %d Bytes\n", drive.sizeOfCluster);
	printf("Clusters amount (last cluster): %d\n", drive.clustersAmount);
	UInt_8 av_space = drive.sizeOfCluster * drive.clustersAmount;
	printf("Available space for data: %dMB or %.2lfGb\n", av_space / Mb, (double) av_space / Gb);
	printf("------------------------------\n");

}

void fprintDriveInfo(FILE *file, DriveInfo drive) {
	fprintf(file, "Drive info:\n");
	BootSecInfo bootSec = getBootSecInfo(drive.file, 0);
	fprintBootSecInfo(file, bootSec);
	fprintf(file, "fat size: %d Bytes\n", drive.fat_size);
	fprintf(file, "Amount of address units in fat table: %d\n", drive.fat_size / 2);
	fprintf(file, "Size of cluster: %d Bytes\n", drive.sizeOfCluster);
	fprintf(file, "Clusters amount (last cluster): %d\n", drive.clustersAmount);
	UInt_8 av_space = drive.sizeOfCluster * drive.clustersAmount;
	fprintf(file, "Available space for data: %.2lfMb or %.2lfGb\n", (double) av_space / Mb, (double) av_space / Gb);
	fprintf(file, "------------------------------\n");
}