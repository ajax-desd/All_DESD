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
	int ans
	unsigned int choice ;
	printf("Enter 1)show 2)del  ");
	scanf("%d",&choice);
	if(choice == 2){
	ans = ioctl(fd, DEL_LIST, (unsigned int *)&choice);
	if (ans<0)
	{
		perror("IOCTL read failure");
		exit(EXIT_FAILURE);
		close(fd);
	}
	
	}
	else if(choice == 1){
		ans = ioctl(fd, SHOW_LIST, (unsigned int *)&choice);
		if (ans<0)
		{
			perror("IOCTL read failure");
			exit(EXIT_FAILURE);
			close(fd);
		}
	}
	close(fd);

	

	return (EXIT_SUCCESS);
}

