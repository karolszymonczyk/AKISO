#include <unistd.h>
#include <signal.h>
#include <stdio.h>

//warunek w ifie probuje ustawic handler dla sygnalu o danej wartosci i
//jezeli sie nie da to drukuje "cant catch"
//nie da sie no dla SIGKILL o wartosci 9

void signal_handler(int sign) {
	printf("Signal: %d\n", sign);
}

int main(int argc, char **argv) {

	for (int i =1; i < 65; i++) {
		if (signal(i, signal_handler) == SIG_ERR) {
			printf("\ncant catch %d\n", i);
		}
	}
	while(1) {
		sleep(1);
	}

	return 0;
}
