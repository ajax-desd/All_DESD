#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
//include <>
#define MAX_NAME_LENGTH 20
#define MAX_EMPLOYEE_NO_LENGTH 2

typedef struct {
    char name[MAX_NAME_LENGTH];
    unsigned int employeeNo;
    bool sex;
    bool employeeType;
} Employee;

void generateRandomString(char* str, int length) {
    char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int l=rand()%21;
    for (int i = 0; i < l;i++) {
        str[i] = characters[rand() % strlen(characters)];
    }
    str[l+1] = '\0';
}
void generateRandomEmployee(Employee* employee)
{
    generateRandomString(employee->name, MAX_NAME_LENGTH - 1);
    //generateRandomNumber
    employee->employeeNo= rand() % 1000;
    employee->sex = (rand() % 2 == 0);
    employee->employeeType = (rand() % 2 == 0);
}

void saveEmployeeToCSV(Employee* employee, FILE* file) {
    fprintf(file, "%s %d %s %s\n", employee->name, employee->employeeNo, (employee->sex ? "Male" : "Female"), (employee->employeeType ? "Permanent" : "Contractor"));
}

int main() {
    srand(time(NULL));
    FILE* file = fopen("employees.txt", "w+");
    if (file == NULL) {
        printf("Could not open file\n");
        return 1;
    }
 Employee employee;

    int arr[1000]={0};
    for (int i = 0; i < 1000; i++)
    {
        arr[i]= i + 1;
    }
    int k=0;
    for (int i = 0; k < 1000; k++)
    {
        i=rand() % 1000;
        arr[i]=arr[i]+arr[k];
        arr[k]=arr[i]-arr[k];
        arr[i]=arr[i]-arr[k];
    }
    for (int i = 0; i < 1000; i++) {

        usleep(500);
        generateRandomEmployee(&employee);
        //employee.employeeNo = i + 1;
        employee.employeeNo=arr[i];
        saveEmployeeToCSV(&employee, file);
    }
    fclose(file);
    return 0;
}

