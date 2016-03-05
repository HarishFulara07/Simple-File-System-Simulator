#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "14143_14048_header.h"

 int writeFile(int disk, char * filename, void * block)
 {
 	char * buffer = (char *)block;
 	int size = strlen(buffer);
 	int blocks = (size/4096) + 1;
 	int i, j, startBlock, endBlock, k = 0;
 	char data[blocks][4097];

 	inodeBitMap[i_header] = 1;
 	inode[i_header].index = i_header;
 	strcpy(inode[i_header].fileName, filename);

 	if(i_header == 0)
 	{
 		startBlock = inode[i_header].startBlock = 0;
 		endBlock = inode[i_header].endBlock = blocks - 1;
 	}
 	else
 	{
 		startBlock = inode[i_header].startBlock = inode[i_header - 1].endBlock + 1;
 		endBlock = inode[i_header].endBlock = inode[i_header].startBlock + blocks - 1;	
 	}

 	i_header++;

 	//printf("%d %d %d %d %d\n",blocks,startBlock,endBlock,i_header,size);
 	//Dividing the data into blocks
 	for(i=0; i<blocks; i++)
 	{
 		for(j=0; j<4096; j++)
 		{
 			if(buffer[k] == '\0')
 			{
 				while(j < 4096)
 				{
 					data[i][j] = '|';
 					j++;
 				}
 			}
 			else
 			{
 				data[i][j] = buffer[k];
 				k++;
 			}
 		}
 		data[i][4096] = '\0';
 	}

 	k = 0;

 	//Writing blocks onto the disk
 	for(i=startBlock; i<=endBlock; i++)
 	{
 		dataBitMap[d_header] = 0;
 		d_header++;

 		writeData(disk, i, data[k]);
 		k++; 
 	}

 	return(0);
}

int readFile(int disk, char * filename, void * block)
{
	int i = 0, flag = 0, startBlock, endBlock, offset;

	for(i=0; i<i_header; i++)
	{
		if(strstr(inode[i].fileName, filename) != NULL)
		{
			flag = 1;
			startBlock = inode[i].startBlock;
 			endBlock = inode[i].endBlock;
 			printf("%d %d\n", startBlock, endBlock);
 			break;
		}  
	}

	if(flag == 0)
	{
		printf("\nNo Such File Exists in The Disk\n");
		return(0);
	}

	for(i=startBlock; i<=endBlock; i++)
	{
		offset = (4096 * i) + ((i+1)*4) + i;
		printf("%d\n",offset);
	}

	return(0);
}