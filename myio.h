#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

typedef struct file_info MYFILE;

MYFILE *myopen(const char *pathname, const char *mode);
int myclose(MYFILE *stream);
int myseek(MYFILE *stream, long offset, int whence);
size_t myread(void *ptr, size_t size, size_t nmemb, MYFILE *stream);
