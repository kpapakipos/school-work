// Name: Keegan Papakipos 
// Date: Tuesday (the day you have lab) 
// Title: Lab3 – Pthreads and IPC- Pipes
// Description: This program uses pipes to implement the command:
// cat /etc/passwd | grep root

/**************************
*	pipe()
**************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <sys/wait.h> 
//main
int main() {
 	int fds[2];
 	pipe(fds);
	if (fork() == 0) { //writer
		close(fds[0]);
		dup2(fds[1], 1);
		execlp("cat", "cat", "/etc/passwd", 0);
	}
	else if (fork() == 0) { //reader
		close(fds[1]);
		dup2(fds[0], 0);
		execlp("grep", "grep", "root", 0);
	}
	else {  /*parent closes both ends and wait for children*/
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0); 
	}
} 
