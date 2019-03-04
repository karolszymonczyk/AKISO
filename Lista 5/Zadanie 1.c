#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define BUFF_SIZE 1024
 
int power(int base, int powerRaised);
int strToInt(char *str, int base);
int myScanf (char * format, ...);
void myPrintf(char* format,...);
char *convert(unsigned int num, int base);

int main(int argc, char *argv[]) {

	int i;
	char *s;
	int x;
	int b;

	myScanf("%d", &i);
	myPrintf("This is your integer number : %d", i);
	printf("\nReal printf output : %d\n\n", i);
	myScanf("%s", &s);
	myPrintf("This is your string : %s", s);
	printf("\nReal printf output : %s\n\n", s);
	myScanf("%x", &x);
	myPrintf("This is your hexadecimal number : %x", x);
	printf("\nReal printf output : %x\n\n", x);
	myScanf("%b", &b);
	myPrintf("This is your binary number : %b", b);
	printf("\nThere is no binary output in printf\n\n");

	return 0;
}

int power(int base, int powerRaised) {
    if (powerRaised != 0)
        return (base*power(base, powerRaised-1));
    else
        return 1;
}

int strToInt(char *str, int base) {
  int result = 0;
  int int_length = 0;
  int isNegative = 0;
  if (str[0] == '-') {
    isNegative = 1;
  }
  int n = isNegative;
  while(str[n] != '\0' && str[n] != '\n') {
    int_length++;
    n++;
  }
  for (int i = (int_length - 1 + isNegative); i >= isNegative; i--) {
    if (str[i] >= 'A' && str[i] <= 'F') {
      result += (str[i] - 'A' + 10) * power(base, int_length - i + isNegative - 1);
    } else {
      result += (str[i] - '0') * power(base, int_length - i + isNegative - 1);
    }
  }
  return result * power(-1, isNegative);
}

int myScanf (char * format, ...) {
	char* p = (char* ) &format + sizeof format;
	while (*format) {
		 if (*format == '%') {
		   format++;
		   switch (*format) {

		     case 'd': {
		     	int *i = (int *)(*(int *)p);
		     	char *str = malloc(BUFF_SIZE);
		     	read(0, str, BUFF_SIZE);
		     	*i = strToInt(str, 10);
		     	p += sizeof(int *);
		     	break;
		     }
        	 case 's': {
		        char **strArg = (char**) (*(char**) p);
		        char *string = malloc(BUFF_SIZE);
		        read(0, string, BUFF_SIZE);   
		        if (string[strlen(string) - 1] == '\n') {
		          	string[strlen(string) - 1] = '\0';
		        }
		        *strArg = string;
		        p += sizeof(*strArg);
		        break;
			 }
	         case 'x': {
		        int *x = (int*)(*(int*)p);
		        char *str = malloc(BUFF_SIZE);
		        read(0, str, BUFF_SIZE);
		        *x = strToInt(str, 16);
		        p += sizeof(int*);
		        break;
			 }
			 case 'b': {
	            int *b = (int*)(*(int*)p);
	            char *str = malloc(BUFF_SIZE);
	            read(0, str, BUFF_SIZE);
	            *b = strToInt(str, 2);
	            p += sizeof(int*);
	          break;
			 }

	 		}
	 		format++;
		} else {
			format++;
		}
	}
	p = NULL;
	return 0;
}

void myPrintf(char* format,...) {
	char *traverse; 
	int i; 
	char *s; 
	char* p = (char* ) &format + sizeof format;	
	for(traverse = format; *traverse != '\0'; traverse++) { 
		while( *traverse != '%' ) { 
			write(1, traverse, 1);
			traverse++; 
		} 		
		traverse++; 		
		switch(*traverse) { 				
			case 'd' : i = *((int *)p);
						p += sizeof(int);
						if(i < 0) {
							i = -i;
							char* sign = "-";
							write(1,sign,1);
						}
						write(1, convert(i,10), strlen(convert(i,10)));
						break;  
						
			case 's': s = *((char* *)p);
						p += sizeof(char*);
						write(1, s, strlen(s)); 
						break; 
						
			case 'x': i = *((int *)p);
						p += sizeof(int);
						write(1, convert(i, 16), strlen(convert(i, 16)));
						break; 

			case 'b': i = *((int *)p);
						p += sizeof(int);
						write(1, convert(i, 2), strlen(convert(i, 2)));
						break;
		}	
	} 
	p = NULL;
} 
 
char *convert(unsigned int num, int base) { 
	static char representation[]= "0123456789ABCDEF";
	static char buffer[50]; 
	char *ptr; 
	ptr = &buffer[49]; 
	*ptr = '\0'; 
	do { 
		*--ptr = representation[num%base]; 
		num /= base; 
	}while(num != 0); 
	return(ptr); 
}