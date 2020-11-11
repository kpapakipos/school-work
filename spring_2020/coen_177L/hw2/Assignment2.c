
/**********************************************
*   Keegan Papakipos- 4/15/20- COEN 177       *
*	Assignment 2: Run and comment in details  *
*   Spring 2019								  *
***********************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <signal.h>
int id;
//data structure for holding user message and data about the message, as well as tokens
struct Mesg{
   char Message[40];
	int count;
	char token[10][20];
	char sorttoken[10][20];
};

#define KEY       ((key_t)(713))
#define SEGSIZE   sizeof(struct Mesg)
//signal handler that cleans up memory segment and exits
void cleanup(int sigtype){
   shmdt(0);
   printf("\n Terminating\n");
   execlp("ipcrm","ipcrm","-M","713",(char*)(0));
   printf("ERROR!");
   exit(0);
}

int main(){
   int i,j;
	int count;
	char *token;
	char tmp[20];
	struct Mesg *msg;
	struct shmid_ds shmbuf;
    //after user presses ctrl-c, send OS an interrupt signal, then a quit signal. cleanup() is used to handle the signals.
	signal(SIGINT,cleanup);
	signal(SIGQUIT,cleanup);
    //get identifier of System V shared memory segment mapped to by KEY constant
	id=shmget(KEY,SEGSIZE,IPC_CREAT|0666);
	if(id<0){
	   perror("shmget failed 1\n");
		exit(1);
	}
    //attach shared memory segment pointed to by id to the process' address space
	msg=(struct Mesg*) shmat(id,0,0);
	if(msg<=(struct Mesg *)(0)){
	   perror("shma failed 2\n");
		exit(1);
	}
	msg->count=0;
	printf("Parent : Enter a Message : \n");
    //read in user-entered message to msg.Message
	count=read(0,msg->Message,40);
	if(count<=0){
	   printf("read failed or no text entered!\n");
	   exit(0);
	}
    //put a null char after the last character of the user's message
   msg->Message[count-1]='\0';
	printf("Parent pid = %d, Message readed:'%s'\n",getpid(),msg->Message);
	printf("Just before forking, pid = %d\n",getpid());
	if(fork()==0){
        //count the spaces in the message in a child process
	   printf("fork 1\n");
              msg->count=1;
	      for(i=0;i<count;i++)
	         if(msg->Message[i]==' ')
	            msg->count++;
	   printf("token count = %d\n",msg->count);
	   exit(0);
	}else //in another child process, get the separated-out tokens from the message and print them
    //note that child 1's work was picked up in child 2. This is because the children share memory.
	if(fork()==0){
	   sleep(1);
	   printf("fork 2\n");
		i=0;
		token=strtok(msg->Message," ");
		while(token!=NULL){
		   strcpy(msg->token[i],token);
			i++;
			token=strtok(NULL," ");
		}
		printf("Tokens : \n");
		for(i=0;i<msg->count;i++){
		   printf("%s\n",msg->token[i]);
		}
		printf("Tokens end\n");
		exit(0);
	}else //in a final child, sort the tokens to be in alphabetical order and print them
	if(fork()==0){
	   sleep(3);
	   printf("fork 3\n");
		for(i=0;i<msg->count;i++){
		   strcpy(tmp,msg->token[i]);
		   strcpy(msg->sorttoken[i],tmp);
		}
		for(i=msg->count-1;i>=0;i--){
		   for(j=0;j<i;j++){
			   if(strcmp(msg->sorttoken[j],msg->sorttoken[j+1])>0){
				   strcpy(tmp,msg->sorttoken[j]);
				   strcpy(msg->sorttoken[j],msg->sorttoken[j+1]);
				   strcpy(msg->sorttoken[j+1],tmp);
				}
			}
		}
		printf("Sorted tokens : \n");
		for(i=0;i<msg->count;i++){
		   printf("%s\n",msg->sorttoken[i]);
		}
		printf("Sorted tokens end\n");
		exit(0);
	}
	//process waits for all three children to terminate, then prompts the user to clean up and exit.
	for(i=0;i<3;i++)
	   wait(0);
	printf("Press Ctrl-C (or) Ctrl-\\ to clean up the memory and exit.\n");
    //infinite loop to wait for user input! I'm surprised this doesn't eat up a bunch of performance on my machine. In my experience in Swift it would be a problem.
	for(;;);
 return 0; 
}

