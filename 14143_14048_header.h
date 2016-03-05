/*
* Data structures declaration
*/

// Inode entry
typedef struct Inode{
	int index;
	char fileName[50];
	long int startBlock;
	long int endBlock;
}Inode;	

char fs_name[50];
int i_header;	//header for inodeBitMap
int d_header;	//header for dataBitMap
int total_blocks;
int * inodeBitMap;	//array for inodeBitMap
int * dataBitMap;	//array for dataBitMap
Inode * inode;

/*
* Functions Declaration
*/

int createSFS(char * filename, int nbytes);
int writeFile(int disk, char * filename, void * block);
int writeData(int disk, int blockNum, void * block);
int readFile(int disk, char * filename, void * block);