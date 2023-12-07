#include <stdio.h>

int main( )
{
   alarm(5);
   printf("Loop start \n");
   while (1) {
	  for(int i=1; i<5;i++){
		  sleep(1);
		  printf("%d second \n", i);
	  }
   }
   printf("Alarm clock \n");
}
