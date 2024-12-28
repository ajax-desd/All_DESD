/* User space file to test userspace / kernelspace data exchange module */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <errno.h>

#define DEV	"/dev/cdac_dev"

int main()
{
	int fd = open(DEV, O_RDWR);
	if (fd<0)
	{
		perror("Cannot open device file");
		exit(EXIT_FAILURE);
	}

	char buf[] = "Hello from user space!\n";
	ssize_t nwrite = write(fd, buf, strlen(buf));

	//char *buf1 = (char *)calloc((strlen(buf)+1), sizeof(char));
	char *buf1 = (char *)calloc(5, sizeof(char));
	int nread = read(fd, (void *)buf1, 5);
	write(STDOUT_FILENO, buf1, strlen(buf1));
	printf("\n");
	nread = read(fd, (void *)buf1, 5);
	write(STDOUT_FILENO, buf1, strlen(buf1));
	close(fd);


	return (EXIT_SUCCESS);
}

