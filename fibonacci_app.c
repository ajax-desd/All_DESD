#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE_PATH "/dev/fibonacci_device"

int main()
{
    	int fd;
    	uint32_t random_number;

    	fd = open(DEVICE_PATH, O_WRONLY);
    	if (fd < 0)
    	{
        	perror("Failed to open device");
        	return -1;
    	}

	for (int i = 0; i < 100; i++)
	{
        	//random_number = rand() % 1000000000;
        	random_number = rand() % 100;
        	  
        	write(fd, &random_number, sizeof(uint32_t));  
    	}
    	close(fd);
    	return 0;
}

