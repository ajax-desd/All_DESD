#include<stdio.h>
#include<stdlib.h>
#include<string.h>


// creating a struct student ,typedef to student
typedef struct student
{
 char name[20];
 int age;
 int rollnum;
 char address[20];
 union ID			// union for govt id
 {
     char adhaar[20];
     char pan[20];
     char passport[20];
 }id;


}student;

//function declaratons 
void add();
void search();
void showall();
int total_students();
void add_node();

int id_option;            // for govt id
int main()
{
int option;

while(1){
printf("choose an option \n 1)add \n 2)search\n 3)show all\n 4)total students\n 5)exit \n");
scanf("%d",&option);

if(option==5)			// for exit
{
   break;
}
else
{
switch(option)			// menu driven purpose 
{
    case 1:
           add();
           break;

    case 2:
           search();
           break;
    case 3:
           showall();
           break;
    case 4:
          printf("total no.of students = %d\n",total_students());
           break;
           
    default:
            printf("Invalid....Try again");
            break;
}
}
}
return 0;
}

// functions definitions

void add()
{
  student var;
  int option;				// for menu driven
  int flag=0;				// for loop exiting
 FILE *fp;				// creating file pointer
 fp=fopen("database.txt","a+");	// opening the file in a+ mode, if file is not present will create one

printf("Enter the details of the student(use _ instead of spaces) \n");
getchar();
printf("NAME:");
scanf("%[^\n]s",var.name);
printf("AGE:");
scanf("%d",&var.age);
printf("ROLLNUM:");
scanf("%d",&var.rollnum);
getchar();				// buffer to consume newline 
while(1)
{
printf("choose an option for govt id \n 1)adhaar \n 2)pan\n 3)passport\n");
scanf("%d",&option);
id_option=option;
getchar();
switch(option)			// menu driven purpose for ids
{
    case 1:
           	printf("ADHAAR:");
           	scanf("%[^\n]s",var.id.adhaar);
               break;
 
    case 2:
		printf("PAN:");
		scanf("%[^\n]s",var.id.pan);
               break;
    case 3:
		printf("PASSPORT:");
		scanf("%[^\n]s",var.id.passport);
               break;
           
    default:
               printf("Invalid....Try again\n");
               flag=1;
               break;
}
if(flag==0)			// out of while loop , if invalid asks again
{
    break;

}
}
getchar();
printf("ADDRESS: ");
scanf("%[^\n]s",var.address);


fprintf(fp,"%s %d %d %s %s\n",var.name,var.age,var.rollnum,var.id.adhaar,var.address);   // loading the data in file at once
fclose(fp);                          //closing file
}

void search()
{
  student var;
  int flag=0;
  char name[20];
 FILE *fp;				// creating file pointer
 fp=fopen("database.txt","r");	// opening the file in r mode

printf("Enter the student name you want to search\n");
getchar();
scanf("%[^\n]s",name);
while(fscanf(fp,"%s %d %d %s %s\n",var.name,&var.age,&var.rollnum,var.id.adhaar,var.address)!=EOF)	// reading from file till end
{
     if(!strcmp(name,var.name))					// returns 0 if matches not operater(becomes 1) , pritnts student data
     {    printf("----->STUDENT DETAILS<------\n");
       	 printf("NAME:       %s\n",var.name);
      	         printf("AGE:        %d\n",var.age);
                printf("ROLLNUM:     %d\n",var.rollnum);
     
     switch(id_option)
     {
     case 1:
     		printf("ADHAAR:    %s\n",var.id.adhaar);
     		break;
     case 2:
     		printf("PAN:       %s\n",var.id.adhaar);
    		 break;
     case 3:
        	printf("PASSPORT:  %s\n",var.id.adhaar);
     		break;
     default:
      		break;
     }
               printf("ADDRESS:   %s\n",var.address);
       flag=1;							// if found sets flag
     }
  
 
}

 if(flag==0)						//  prints if not found
   {
     printf("DATA OF THE STUDENT NOT FOUND\n");
   
   }
   fclose(fp);
}

void showall()				// for displaying all the students
{
student var;
 FILE *fp;				// creating file pointer
 fp=fopen("database.txt","r");	// opening the file in r mode

while(fscanf(fp,"%s %d %d %s %s\n",var.name,&var.age,&var.rollnum,var.id.adhaar,var.address)!=EOF)
{
                printf("NAME:      %s\n",var.name);
                printf("AGE:       %d\n",var.age);
                printf("ROLLNUM:   %d\n",var.rollnum);
     switch(id_option)
     {
     case 1:
     		printf("ADHAAR:    %s\n",var.id.adhaar);
     		break;
     case 2:
     		printf("PAN:       %s\n",var.id.adhaar);
    		 break;
     case 3:
        	printf("PASSPORT:  %s\n",var.id.adhaar);
     		break;
     default:
      		break;
     }
               printf("ADDRESS:  %s\n",var.address);
     }
  

fclose(fp);        //closing file

}
int total_students()
{
 student var;
 int count=0;
 FILE *fp;				// creating file pointer
 fp=fopen("database.txt","r");	// opening the file in r mode
while(fscanf(fp,"%s %d %d %s %s\n",var.name,&var.age,&var.rollnum,var.id.adhaar,var.address)!=EOF) // reading untill end of file
{
  
  count++;
}
fclose(fp);
return count;						// returns the no of students in file
}
void add_node()
{
   
  FILE *fp;				// creating file pointer
  fp=fopen("database.txt","a+");

   
fclose(fp);

}


