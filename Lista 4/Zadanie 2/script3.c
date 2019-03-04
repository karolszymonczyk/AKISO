#include <stdio.h>
#include<signal.h>

void signal_handler(int sign){

	if(sign==SIGUSR1){
		printf("RECIVED SIGNAL SIGNUSR1\n");
	}
}

int main(int argc, char const *argv[])
{


	signal(SIGUSR1,signal_handler);
	pid_t pid;

	for (int i = 0; i < 20; ++i)
	{
		kill(pid,SIGUSR1);
	}
	
	return 0;
}