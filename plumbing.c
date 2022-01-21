#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
	int fds[2];
	pipe(fds);

	int fds2[2];
	pipe(fds2);

	int f = fork();


	if (f){
		close(fds[0]);
		close(fds2[1]);
		while (1){
			char * text = calloc(1000, 1);
			printf("input: \n");
			fgets(text, 1000, stdin);
			write(fds[1], text, strlen(text));
			read(fds2[0], text, 1000);
			printf("manipulated B): %s\n", text);
			free(text);
		}
	} else {
		close(fds[1]);
		close(fds2[0]);
		while (1){
			char * mess = calloc(1000, 1);
			read(fds[0], mess, 1000);
			char * temp = calloc(1000, 1);

			int i;
			for (i = strlen(mess) - 1; i >= 0; i--){
				if (*(mess + i) != 20){
					strncat(temp, mess + i, 1);
          strcat(temp, "!");
				}
			}

			write(fds2[1], temp, 1000);
			free(mess);
			free(temp);
		}
	}

	return 0;

}
