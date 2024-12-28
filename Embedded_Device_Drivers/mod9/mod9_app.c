#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include "my_ioctls.h"  // This should define DEL_LIST and SHOW_LIST

#define DEV    "/dev/cdac_dev"
#define BUF_SZ (1024)  // Buffer size for reading file

// Function to trim leading and trailing whitespaces
void trim_spaces(char *str) {
    int start = 0;
    int end = strlen(str) - 1;

    // Trim leading spaces
    while (start < end && isspace(str[start])) start++;

    // Trim trailing spaces
    while (end >= start && isspace(str[end])) end--;

    // Create a new string with trimmed spaces
    for (int i = start; i <= end; i++) {
        str[i - start] = str[i];
    }
    str[end - start + 1] = '\0';
}

int main()
{
    int ans;
    char c;
    unsigned int choice;
    char *str = (char *)malloc(sizeof(char) * BUF_SZ);  // Allocate buffer for data

    if (str == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    int fd = open(DEV, O_RDWR);  // Open the device file for IOCTL
    if (fd < 0) {
        perror("Cannot open device file");
        free(str);
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen("ajay.csv", "r");  // Open the file ajay.csv for reading
    if (file == NULL) {
        perror("Cannot open ajay.csv");
        close(fd);
        free(str);
        exit(EXIT_FAILURE);
    }

    int i = 0;
    printf("Enter 1) Delete list 2) Show list: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // Call IOCTL to delete the list
            ans = ioctl(fd, DEL_LIST, NULL);  // Passing NULL for deletion, as no argument needed
            if (ans < 0) {
                perror("IOCTL delete list failure");
                fclose(file);
                close(fd);
                free(str);
                exit(EXIT_FAILURE);
            }
            break;

        case 2:
            // Read the file line-by-line and send each line to kernel
            while (fgets(str, BUF_SZ, file)) {  // Read each line from the file
                char *token;
                char *line = strdup(str);  // Duplicate the string for tokenization
                if (!line) {
                    perror("Memory allocation failed for line");
                    fclose(file);
                    close(fd);
                    free(str);
                    exit(EXIT_FAILURE);
                }

                // Tokenize the line by commas
                token = strtok(line, ",");
                while (token != NULL) {
                    trim_spaces(token);  // Remove spaces from each token
                    if (write(fd, token, strlen(token)) < 0) {  // Write the token to the kernel
                        perror("Write to device failed");
                        free(line);
                        fclose(file);
                        close(fd);
                        free(str);
                        exit(EXIT_FAILURE);
                    }
                    memset(str, 0, BUF_SZ);  // Clear the string buffer for the next token
                    token = strtok(NULL, ",");  // Get next token
                }
                free(line);  // Free the duplicated line
            }
            break;

        default:
            fprintf(stderr, "Invalid choice\n");
            break;
    }

    fclose(file);  // Close the file after reading
    close(fd);     // Close the device file
    free(str);     // Free the allocated memory
    return EXIT_SUCCESS;
}









/*
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>

#include "my_ioctls.h"  // This should define DEL_LIST and SHOW_LIST

#define DEV    "/dev/cdac_dev"
#define BUF_SZ (1024)  // Buffer size for reading file

int main()
{
    int ans;
    char c;
    unsigned int choice;
    char *str = (char *)malloc(sizeof(char) * BUF_SZ);  // Allocate buffer for data

    if (str == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    int fd = open(DEV, O_RDWR);  // Open the device file for IOCTL
    if (fd < 0) {
        perror("Cannot open device file");
        free(str);
        exit(EXIT_FAILURE);
    }

    FILE *file= fopen("ajay.csv", "r");  // Open the file ajay.csv for reading
    if (file == NULL) {
        perror("Cannot open ajay.csv");
        close(fd);
        free(str);
        exit(EXIT_FAILURE);
    }
	int i=0;
    printf("Enter 1) Delete list 2) Show list: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            ans = ioctl(fd, DEL_LIST, (unsigned int *)&choice);  // Pass the choice to delete list
            if (ans < 0) {
                perror("IOCTL delete list failure");
                fclose(file);
                close(fd);
                free(str);
                exit(EXIT_FAILURE);
            }
            break;

        case 2:
            // Read the file line-by-line and send each line to kernel
            while (read(file, &c, 1) > 0) {
		
			if (c == ',') {
			    str[i--] = '\0';  // Null-terminate the string
			     write(fd,str,strlen(str));
			    //fprintf(stderr, " %s\n", str);  
			    memset(str, 0, strlen(str));  // Clear the string buffer
			    i = 0;  // Reset index for the next token
			}
			else{
				str[i++] = c;
			}
		    
                ans = ioctl(fd, SHOW_LIST, str);
                if (ans < 0) {
                    perror("IOCTL show list failure");
                    fclose(file);
                    close(fd);
                    free(str);
                    exit(EXIT_FAILURE);
                }
           }
            break;

        default:
            fprintf(stderr, "Invalid choice\n");
            break;
    }

    fclose(file);  // Close the file after reading
    close(fd);     // Close the device file
    free(str);     // Free the allocated memory
    return EXIT_SUCCESS;
}


*/
