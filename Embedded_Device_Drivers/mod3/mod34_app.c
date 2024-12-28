/* User space file to test file operations module */

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <errno.h>

#define DEV	"/dev/cdac_dev"
#define BUF_SZ	(10)

int main()
{
	int fd = open(DEV, O_RDWR);
	if (fd<0)
	{
		perror("Cannot open device file");
		exit(EXIT_FAILURE);
	}

	char buf[BUF_SZ] = "Hello";
	ssize_t nwrite = write(fd, buf, BUF_SZ);

	int nread = read(fd, (void *)buf, BUF_SZ);

	close(fd);

	return (EXIT_SUCCESS);
}

