#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "14143_14048_header.h"

 int createSFS(char * filename, int nbytes)
 {
 	int fsID = 0, i, blocks;
 	FILE * fs;

 	for(i=0 ; filename[i] != '\0' ; i++)
 	{
 		fsID += (int)filename[i];
 	}
 	
 	fs = fopen(filename,"w");
 	fclose(fs);

 	fs = fopen("superBlock","w");
 	fprintf(fs, "%d\n", fsID);
 	fprintf(fs, "%s\n", filename);
 	fprintf(fs, "%d\n", nbytes);
 	fclose(fs);

 	/*
 	fs = fopen("inodeTable","w");
 	fclose(fs);

 	fs = fopen("inodeBitMap","w");
 	fclose(fs);

 	fs = fopen("dataBitMap","w");
 	fclose(fs);
	*/

 	blocks = nbytes / 4096;	// Total blocks in the file system
 	
 	strcpy(fs_name, filename);
 	i_header = 0;
 	d_header = 0;
 	total_blocks = blocks;
 	inodeBitMap = (int *)malloc(blocks * sizeof(int));
 	dataBitMap = (int *)malloc(blocks * sizeof(int));
 	inode = (Inode *)malloc(blocks * sizeof(Inode));

 	for(i=0; i<blocks; i++)
 	{
 		dataBitMap[i] = 0;
 		inodeBitMap[i] = 0;
 	}

 	return(fsID);
 }

 int writeData(int disk, int blockNum, void * block)
 {
 	if(disk != -1)
 	{
 		FILE * fs = fopen(fs_name,"a");
 		fprintf(fs, "[%d]\n", blockNum);
 		fprintf(fs, "%s\n", (char *)block);
 		fclose(fs);
 	}
 	else
 	{
 		printf("\nError: Corrupted Data\n");
 	}

 	return(0);
 }