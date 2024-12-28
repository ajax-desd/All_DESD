/* User space app to test IOCTL */

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <errno.h>

#include "my_ioctls.h"

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

	unsigned int to_send = 12345;
	int ans = ioctl(fd, MY_HW_WRITE, (unsigned int *)&to_send);
	if (ans<0)
	{
		perror("IOCTL read failure");
		exit(EXIT_FAILURE);
		close(fd);
	}
	printf("Send value: %d to kernel via IOCTL\n", to_send);

	unsigned int received = 0;
	ans = ioctl(fd, MY_HW_READ, (unsigned int *)&received);
	if (ans<0)
	{
		perror("IOCTL read failure");
		exit(EXIT_FAILURE);
		close(fd);
	}
	close(fd);

	printf("Received value %d from kernel via IOCTL\n", received);

	return (EXIT_SUCCESS);
}

