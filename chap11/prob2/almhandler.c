#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void alarmHandler();

int main( )
{
   signal(SIGALRM, alarmHandler);
   alarm(5); 
   printf("Loop \n");
   while (1) {
      for (int i=1; i<5; i++){
         sleep(1);
         printf("%d second \n", i);
     }
   }
   printf("No \n");
}

void alarmHandler(int signo)
{
   printf("Wake up \n");
   exit(0);
}

