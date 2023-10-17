#include <stdio.h>
int main(int argc, char *argv[])
{
   FILE *fp;
   int c;
   if (argc < 2) 
      fp = stdin; 			 
   else{
	   for(int i=1; i<4; i++){
		   fp = fopen(argv[i],"r");
	   }
   }

   c = getc(fp); 			
   while (c != EOF) { 		
      putc(c, stdout); 		
      c = getc(fp);  
   }
   fclose(fp); 
   return 0;
}
