#include<stdio.h>

int main()
{

int r;
int c;
printf("Enter the number of rows\n");
scanf("%d",&r);				// for no.of rows
						
for(int i=1;i<=r;i++)					// for rows
{

for(int j=1;j<=(2*r)-1;j++)				// for columns
{

 if(i==j || j==(2*r)-i)
{
  printf("X");
}
else
{
    printf(" ");
}

}
printf("\n");

}


}
