#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

void hello() {
	printf("Hello World!\n");
}

int fib(int n)
{
	if (n <= 1)
		return n;
	return fib(n-1) + fib(n-2);
}

int main(int argc, char **argv) {

	
	while(1) {
		char shell[100];
		printf("uab_sh > ");
		scanf("%s", shell);
		
		FILE *fp;
   		fp = fopen("uab_sh.log", "a+");
   		fprintf(fp, "%s\n", shell);
		fclose(fp);

		if(strcmp(shell, "quit") == 0)
			break;
		else if(strcmp(shell, "hello") == 0) {
			hello();
		}
		else if(strcmp(shell, "fibonacci") == 0) {
			int n;
			printf("How many elements you want to display: ");
			scanf("%d", &n);
			FILE *fp;
	   		fp = fopen("uab_sh.log", "a+");
	   		fprintf(fp, "%d\n", n);
			fclose(fp);
			printf("\n");
			printf("The first %d value: ", n);
			printf("%d", fib(0));
			for(int i = 1; i < n; i++)
				printf(", %d", fib(i));
			printf("\n");
		}
		else if(strcmp(shell, "list") == 0) {
			DIR *d;
			struct dirent *dir;
			d = opendir(".");
			if (d) {
				while ((dir = readdir(d)) != NULL) {
					printf("%s\n", dir->d_name);
				}
				closedir(d);
			}
		}
		else if(strcmp(shell, "help") == 0) {
			printf("hello : print 'Hello World!'\n");
			printf("fibonacci : get number and print fibonacci series from number\n");
			printf("fibonacci x : print fibonacci series from x\n");
			printf("list : get all files from current directory\n");
			printf("cd <directory> : change directory as input directory\n");
			printf("quit : quit program\n");
		}
		else if(strcmp(shell, "history") == 0) {
			FILE* ptr;
		    char ch;
		 
		    // Opening file in reading mode
		    ptr = fopen("uab_sh.log", "r");
		 
		    if (NULL == ptr) {
		        printf("file can't be opened \n");
		    }
		 
		    // Printing what is written in file
		    // character by character using loop.
		    do {
		        ch = fgetc(ptr);
		        printf("%c", ch);
		 
		        // Checking if character is not EOF.
		        // If it is EOF stop eading.
		    } while (ch != EOF);
		 
		    // Closing the file
		    fclose(ptr);
		}
		else if(strcmp(shell, "cd") == 0) {
			scanf("%s", shell);
			if (chdir(shell) != 0) 
    			printf("chdir() to %s failed", shell);
		}
		
	}


	return 0;
}