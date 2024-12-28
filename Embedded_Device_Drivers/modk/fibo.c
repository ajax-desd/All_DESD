#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>




int main()
{
	int a=0,b=1;
	int num;
	printf("enter range of fibonaki numebrs ");
	scanf("%d",&num);
	printf("1 %d 2 %d \n",a,b);
	uint32_t temp;	
	for(int i=0;i<num;i++){
		temp=a+b;
		a=b;
		b=temp;
		
			printf("%d %u \n", i+2, temp);
		    
	}
	

}
