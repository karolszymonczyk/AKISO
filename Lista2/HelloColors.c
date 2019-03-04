#include <stdio.h>

int main (int argc, char const *argv[]) {

	for(int i = 0; i <256; i++) {
		
		for(int j = 0; j < i+1; j++) {

			for(int k = 0; k < i+1; k++) {
	
				printf("\033[38;2;%d;%d;%dmHello World!\n",i ,j, k);
			}
		}
	}
	return 0;
}