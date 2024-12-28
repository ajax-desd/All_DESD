#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdint.h>

#define DEV "/dev/cdac_dev"  // Your device file path
#define COUNT 46  // Number of Fibonacci numbers you want to store

// Global array to store Fibonacci sequence
int arr[COUNT];  


static void fibo(void){
    int a = 0, b = 1;
    int i = 0;
    
    arr[i++] = a;
    arr[i++] = b;

    uint32_t temp;
    for (int j = 2; j < COUNT; j++) {
        temp = a + b;
        a = b;
        b = temp;
        arr[i++] = temp;
    }
}

int main() {
    int fd = open(DEV, O_RDWR);  // Open the device file for writing
    if (fd < 0) {
        perror("Cannot open device file");
        exit(EXIT_FAILURE);
    }

	int choice;
   printf("Press 1 : write 2) read\n");
   scanf("%d", &choice);
    srand(time(NULL));  
    if(choice==1){
    while (1) {
       
        int arr_size[6] = {100, 10, 1000, 10000, 100000, 1000000};
        int a = rand() % 6;  
        uint32_t num = rand() % arr_size[a];  
        fibo();

        
        for (int j = 0; j < COUNT; j++) {
            if (num == arr[j]) {
                int nwrite = write(fd, (void *)&num, sizeof(int));
                if (nwrite < 0) {
                    perror("Cannot write device file");
                    exit(EXIT_FAILURE);
                }
                printf("%d \n", num);
                break;  
            }
        }
    }
    
	}

   else{
      
    // Now, loop for the number of times specified by `change`
   
	uint32_t change,n;
	int nread = read(fd, (void *)&change, sizeof(uint32_t));
	 if (nread < sizeof(uint32_t)) {
		perror("Error reading 'change' value from device file");
		close(fd);
		exit(EXIT_FAILURE);
       }
      uint32_t *a = malloc(change * sizeof(uint32_t)); 
      if (a == NULL) {
    perror("Memory allocation failed");
    close(fd);
    exit(EXIT_FAILURE);
}
	for (int i = 0; i < change; i++) {
    nread = read(fd, (void *)&a[i], sizeof(uint32_t));  // Use uint32_t size
    if (nread < sizeof(uint32_t)) {
        if (nread == 0) {
            printf("End of file reached\n");
        } else {
            perror("Error reading from device file");
        }
        break; // Exit the loop on error
    }
    printf("Read from input : %d \n", a[i]);
}

free(a);
             
             }
    close(fd); 
    return 0;
}

