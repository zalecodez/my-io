#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define FILE_BUFFER_SIZE 4096
#define CREATE_MODE 666

typedef struct file_info{
	int fd;
	long file_offset;
	int buffer_offset;
	char buffer[FILE_BUFFER_SIZE];
}MYFILE;

void getFlags(const char *mode, int* flags, int* end);


size_t myread(void *ptr, size_t size, size_t nmemb, MYFILE *stream){

	int bytes_read = 0;
	if((bytes_read=read(stream->fd, stream->buffer, FILE_BUFFER_SIZE)) == -1){
		return 0;
	}
	else{
		//set file offset to the number of bytes read
		stream->file_offset += bytes_read;

		//read from stream buffer into ptr
		
		strncpy(ptr, stream->buffer, nmemb*size);


		//update buffer offset
		
	}
}

int myseek(MYFILE *stream, long offset, int whence){
	if((stream->file_offset=lseek(stream->fd, (off_t)offset, whence)) == -1){
		return -1;
	}
	else{
		return 0;
	}
}

int myclose(MYFILE *stream){
	
	if(close(stream->fd) == 0){
		free(stream);
		return 0;
	}
	else{
		perror("myclose");
		free(stream);
		return EOF;
	}
}

MYFILE *myopen(const char *pathname, const char *mode){
	
	int fd;
	int flags = 0;
	int end = 0;
	char flagstring[100] = {0};
	struct stat sb;
	long offset = 0;

	//determine flags
	flags = getFlags(mode, &flags, &end);

	//get file stat to check if it's a valid file 
	//and to determine it's size later
	if(stat(pathname, &sb) == -1){
		perror(pathname);
		return NULL;
	}

	//use file's size to determine the offset if append is used.
	if(end){
		offset = (long)sb.st_size;
	}

	//open file and get the file descriptor
	if((fd = open(pathname,flags,CREATE_MODE)) == -1){
		perror(pathname);
		return NULL;
	}

	//initialize an instance of MYFILE struct with relevant info
	MYFILE *fp;
	fp = malloc(sizeof(MYFILE));

	fp->fd = fd;
	fp->file_offset = offset;
	fp->buffer_offset = 0;
	strncpy(fp->buffer, "", FILE_BUFFER_SIZE);

	//return MYFILE struct
	return fp;
}

void getFlags(const char *mode, int* flags, int* end){
	if(mode[1] == '+'){
		*flags = O_RDWR;
	}

	switch(mode[0]){
		case 'a':
			*flags = flags ? flags : O_WRONLY;
			*flags |= O_APPEND | O_CREAT;
			end = 1;
			break;
		case 'r':
			*flags = flags ? flags : O_RDONLY;
		case 'w':
			*flags = flags ? flags : O_WRONLY;
			*flags |= O_CREAT | O_TRUNC;
			break;
		default:
			break;
	}
}
