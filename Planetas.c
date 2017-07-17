#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void){
	FILE *file:
	file=fopen("coordinates(2).cvs","r");
	int len=250;
	char line_buffer[len];
	const char delimiter;
	delimiter:",";
	while(fgets(line_buffer, len, file)){
		printf("LINE IS: %s" line_buffer);
		split_buffer=strlok(line_buffer, delimiter);
		while(split_buffer !=null){
			//matriz[i][j]
			printf("ITEM IN LINE %s\n" split_buffer);
			split_buffer=strlok(null,delimiter);
						
		}

	}
return 0;

}
