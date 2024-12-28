#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_EMPLOYEES 50

struct node {
    char name[11];  // Name (max 10 characters, null terminator included)
    char sex[8];    // Sex (max 7 characters)
    char etype[15]; // Employment Type (max 14 characters)
    int emp_id;     // Unique Employee ID
};


int is_unique_id(int emp_id, int *used_ids, int size) {
    for (int i = 0; i < size; i++) {
        if (used_ids[i] == emp_id) {
            return 0;  // ID is not unique
        }
    }
    return 1;  // ID is unique
}

// Function to generate a random name of random length between 4 and 10 characters
void generate_random_name(char *name) {
    int name_length = rand() % 7 + 4;  // Name length between 4 and 10
    char alpa[53] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 
                     'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 
                     'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 
                     'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 
                     'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 
                     'Y', 'Z'};

    for (int i = 0; i < name_length; i++) {
        name[i] = alpa[rand() % 52];  // Pick a random character from the alphabet
    }
    name[name_length] = '\0';  // Null-terminate the string
}

int main() {
    srand(time(NULL)); // Seed random number generator

    char *arr[2] = {"Permanent", "Contractor"};
    char *sex[2] = {"Male", "Female"};

    struct node k[MAX_EMPLOYEES];
    int used_ids[MAX_EMPLOYEES];  // Array to track used employee IDs
    int id_count = 0;  
    
    
    FILE *fp = fopen("ajay.csv", "w");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Loop to create 1000 employee entries
    for (int j = 0; j < MAX_EMPLOYEES; j++) {
        // Generate random name with random length
        generate_random_name(k[j].name);
        fprintf(fp, "%s ,", k[j].name);

        // Assign random employment type and sex
        strcpy(k[j].etype, arr[rand() % 2]);   // Use strcpy to copy the string
        strcpy(k[j].sex, sex[rand() % 2]);      // Use strcpy to copy the string

        fprintf(fp, "%s ,", k[j].sex);
        fprintf(fp, "%s ,", k[j].etype);

        // Generate a unique employee ID in the range 1 to 1000
        int emp_id;
        do {
            emp_id = rand() % MAX_EMPLOYEES + 1;  // Generate a random ID between 1 and 1000
        } while (!is_unique_id(emp_id, used_ids, id_count)); // Check for uniqueness

        k[j].emp_id = emp_id;
        used_ids[id_count++] = emp_id;  // Store the ID in used_ids array

        fprintf(fp, "%d \n", k[j].emp_id);
    }

    fclose(fp);

    printf("Employee data generated successfully with unique IDs in range 1-50 and random name lengths.\n");
    return 0;
}

