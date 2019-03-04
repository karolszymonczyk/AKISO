#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	for(int i = 0; i < 65; i++){

		if(kill(i,SIGKILL) == SIG_ERR){
			printf("NIE MOĹ»LIWE\n");
		}
	}
}