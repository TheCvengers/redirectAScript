#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// \

void switchStdout(const char *newStream);
void revertStdout();
static int fd;
static fpos_t pos;

int main(void) {
	//int sout = fileno(stdout);
	//freopen("/home/utnso/Escritorio/file1", "a", stdout);
	int bak, new;
	fflush(stdout);
	bak = dup(1);
	new = open("/home/utnso/Escritorio/file1", O_WRONLY | O_APPEND | O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	dup2(new, 1);
	close(new);
	printf("asdasdasdasd\n");
	fflush(stdout);
	dup2(bak, 1);
	close(bak);
	printf("asd");
	//dup2(sout, fileno(stdout));
	//close(sout);
	return 0;
}

void switchStdout(const char *newStream)
{
  fflush(stdout);
  fgetpos(stdout, &pos);
  fd = dup(fileno(stdout));
  freopen(newStream, "w", stdout);
}

void revertStdout()
{
  fflush(stdout);
  dup2(fd, fileno(stdout));
  close(fd);
  clearerr(stdout);
  fsetpos(stdout, &pos);
}
