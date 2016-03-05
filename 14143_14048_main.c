#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "14143_14048_header.h"

int main(void)
{
	char fs_name[50];
	int nbytes;
	int blocks_left;

	while(1)
	{
		int choice;
		printf("* To Create A New File System - Type 1 and Press Enter\n");
		printf("* To Write A New File onto the Disk - Type 2 and Press Enter\n");
		printf("* To Read A File From the Disk - Type 3 and Press Enter\n");
		printf("* To Exit - Type 9 and Press Enter\n");
		printf("\nEnter your Choice: ");
		scanf("%d", &choice);
		if(choice == 1)
		{
			if(access("superBlock", F_OK) == -1)
			{	
				printf("Enter File System Name: ");
				scanf("%s",fs_name);
				printf("Enter Size of File System (in bytes and multiple of 4096): ");
				scanf("%d", &nbytes);

				blocks_left = nbytes / 4096;

				int fileSystemID = createSFS(fs_name, nbytes);

				printf("File System Created.\n");
				printf("File System Name: %s\n", fs_name);
				printf("File System ID: %d\n",fileSystemID);
				printf("File System Size: %d Blocks\n",blocks_left);
			}
			else
			{
				printf("\nFile System Already Created\n");
			}
		}
		else if(choice == 2 && access("superBlock", F_OK) != -1)
		{
			char filename[50];
			char * buffer;
			int blocks = 1, size, i = 0;

			printf("Enter Absolute Path of File: ");
			scanf("%s",filename);

			int fd = open(filename,O_RDONLY);
			if(fd != -1)
			{
				FILE * fp = fdopen(fd, "r");
			
				fseek(fp, 0, SEEK_END);
				size = ftell(fp);
				buffer = (char *)malloc((size + 1) * sizeof(char));
				blocks += size / 4096;
				blocks_left -= blocks;

				if(blocks_left >= 0)
				{
					fseek(fp, 0, SEEK_SET);
					//printf("%d\n",size);

					while(!feof(fp))
					{
						buffer[i] = fgetc(fp);
						i++;
					}

					buffer[size] = '\0';
					//printf("%s\n", buffer);
					//printf("\n Unallocated Blocks on Disk: %d\n", blocks_left);
					//printf("\n Blocks Required by File: %d\n", blocks);
					writeFile(fd, filename, buffer);

					fclose(fp);
					close(fd);
				}
				else
				{
					printf("\nDisk Does Not Have Enough Space to Store the File");
					blocks_left += blocks;
					printf("\nUnallocated Blocks on Disk: %d\n", blocks_left);
					printf("\nBlocks Required by File: %d\n", blocks);
				}

				free(buffer);
			}
			else
			{
				printf("\nInvalid Absolute File Path\n");
			}
		}
		else if(choice == 3)
		{	
			char filename[50];
			char * block = NULL;

			printf("Enter Absolute Path of File: ");
			scanf("%s",filename);

			readFile(0, filename, block);
		}
		else if(choice == 9)
		{
			free(inodeBitMap);
			free(dataBitMap);
			free(inode);
			remove(fs_name);
			remove("superBlock");
			break;
		}
		else
		{
			printf("\nInvalid Operation - Maybe File System is Not Created\n");
		}
		printf("\n");
	}
	return(0);
}