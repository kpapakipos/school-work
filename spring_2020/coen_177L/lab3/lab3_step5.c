// Name: Keegan Papakipos 
// Date: Tuesday (the day you have lab) 
// Title: Lab3 – Pthreads and IPC- Pipes
// Description: This program solves the producer-consumer problem using pipes.

/**************************
*   Lab3 - pipe()
**************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h> 

// main
int main(int argc,char *argv[]){
   int  fds[2];
   char buff[60];
   int count;
   int i;
   pipe(fds);
   
   if (fork()==0){ //writer
       close(fds[0]);
       write(fds[1],"Hello, this is message one!",strlen("Hello, this is message one!"));
       write(fds[1],"I have something to tell you, and this is it.",strlen("I have something to tell you, and this is it."));
       write(fds[1],"Bye!",strlen("Bye!"));
       exit(0);
   }
   else if(fork()==0){ //reader
       close(fds[1]);
       while((count=read(fds[0],buff,60))>0){
           for(i=0;i<count;i++){
               write(1,buff+i,1);
               write(1," ",1);
           }
           printf("\n");
       }
       exit(0);
    }
   else{     
      close(fds[0]);
      close(fds[1]);
      wait(0);
      wait(0);
   }
return 0;
}
