#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>

#define READ_END 0
#define WRITE_END 1
#define BUFFER 50

int main() {
	
	int pid;
	int pSeconds = 10;
	int cSeconds = 3;
	int status;
	char buff[50];
	pid_t wholeft;
	
	//Pipe stuff
	int parent_pipe[2]; 
	int child_pipe[2];
	
	if(pipe(parent_pipe) || pipe(child_pipe)) {
		perror("pipe(...)");
		exit(1);
	}
	
	//Forking and child creation	
	
	pid = fork();
	
	if(pid == -1) {
		perror("fork()");
		exit(1);
	}
	
	
	if(pid != 0) {
	//Parent process
		printf("Starting...\n\n");
		
		const char ptoc[] = "Are you upset?";	
		int in, out;
		int z = 0;
		in = parent_pipe[READ_END];
		out = child_pipe[WRITE_END];
		
		int rstatus;
		int inc = 0;
		int rcheck;
		
		while(z == 0) {
			sleep(1);
			inc++;
			rstatus = 0;
			
			if((inc % 10) == 0) {
				write(out, ptoc, strlen(ptoc) + 1);
			}
			
			while ((inc % 3) == 0 && rstatus == 0) {
				rcheck = read(in, buff, BUFFER);
				if(rcheck >= 0) {
					printf("Parent Recieved: %s\n\n", buff);
					rstatus++;
				}
				//End of while loop
			}
			
			if(inc == 55){
				z++;
			}
			//End of while loop		
		}	
		
		printf("Parent Done.\n\n");
		//End of Parent
	}
	
	
	
	
	
	else {
	//Child Process
		printf("Commencing child subroutine...\n\n");
		
		const char ctop[] = "I am not upset."; 
		int in, out;
		in = child_pipe[READ_END];
		out = parent_pipe[WRITE_END];
		
		int z = 0;
		int rstatus;
		int inc = 0;
		int rcheck;
		
		while(z == 0){
			
			sleep(1);
			inc++;
			rstatus = 0;
			
			if((inc % 3) == 0) {
				write(out, ctop, strlen(ctop) + 1);
			}
			
			while((inc % 10) == 0 && rstatus == 0){
				rcheck = read(in, buff, BUFFER);
				if(rcheck >= 0) {
					printf("\tChild Recieved: %s\n\n", buff);
					rstatus++;
				}
				//End of inner while loop
			}
			
			if(inc == 55) {
				z++;
			}
			
		}	
		
		printf("Child done.\n\n");
		//End of Child
	}
	
	
	
}


