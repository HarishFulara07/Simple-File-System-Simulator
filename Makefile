all:
	gcc 14143_14048_main.c 14143_14048_header.h 14143_14048_CRW_Disk_API.c 14143_14048_File_RW_API.c -o main

clean:
	rm -rf ./main