#include <stdio.h> 
#include <stdlib.h>
#include <dirent.h> 
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


/*
Name: Pavan Kumar Nalla
BlazerId: pnalla
Project #: Homework 3
To compile: gcc HW3.c
To run: ./<name of executable> <commands and arguments> <directory>
ex: ./executable -f txt -S -s 100 -t f ./projects/
*/



char *filetype(unsigned char type)
{
  char *str;
  switch(type) 
  {
  case DT_BLK: str = "block device"; break;
  case DT_CHR: str = "character device"; break;
  case DT_DIR: str = "directory"; break;
  case DT_FIFO: str = "named pipe (FIFO)"; break;
  case DT_LNK: str = "symbolic link"; break;
  case DT_REG: str = "regular file"; break;  
  case DT_SOCK: str = "UNIX domain socket"; break;
  case DT_UNKNOWN: str = "unknown file type"; break;
  default: str = "UNKNOWN";
  }
  return str;
}
/******Just directory*********/
/*******************/

void just_directory(const char *base)
{
    char path[1000];
    char currentdir[1000];
    char file[1000];
    char basePath[1000];
    struct dirent *dp;
    DIR *dir;
    if (strcmp(base," ")==0){
        getcwd(currentdir,1000);
        strcpy(basePath,currentdir);
    }
    else
    {
        strcpy(basePath,base);
    }
    dir = opendir(basePath);
    if (!dir)
    {	
	printf("No such directory available\n");
        return;	
    }   
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {	
           printf("%s\t",dp->d_name);

        }
    } 
    dir = opendir(basePath);	
    if (!dir)
        return;
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
	    if(strcmp(filetype(dp->d_type),"directory")==0)
            {
	      printf("\n");
	      printf("\n"); 
	      strcpy(path, basePath);
              strcat(path, "/");
              strcat(path, dp->d_name);
              just_directory(path); 
            } 	

        }
    }
    	
    closedir(dir);
}

/** All files with size that contains the substring*****/
/*********************/
void directory_all(const char *base,int size, char *substr)
{
    char path[1000];
    char currentdir[1000];
    char file[1000];
    char basePath[1000];
    struct dirent *dp;
    struct stat statbuf;
    DIR *dir;
char* args[] = {"ls", "-l", NULL};
    int count = 0;
    if (strcmp(base," ")==0){
        getcwd(currentdir,1000);
        strcpy(basePath,currentdir);
    }
    else
    {
        strcpy(basePath,base);
    }
    dir = opendir(basePath);
    if (!dir)
    {	
	printf("No such directory available\n");
        return;	
    }   
   // printf("%s:\n", basePath);
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {	
              if (strstr(dp->d_name,substr))
            {
		count++;
	        strcpy(file,basePath);
	        strcat(file, "/");
      	        strcat(file, dp->d_name);
        	/* FILE* fp = fopen(file, "r");
  
                if (fp == NULL) {
                printf("File Not Found!\n");
                return;
                }
                fseek(fp, 0L, SEEK_END);
                long int res = ftell(fp);
                fclose(fp);
		if (res >= size)
                printf("%s(%d)\t",dp->d_name,res); */

		if (stat(file, &statbuf) == -1)
       			return;		
		printf("%s %9jd",dp->d_name,statbuf.st_size);	
strcpy(path, basePath);
              strcat(path, "/");
              strcat(path, dp->d_name);
	      execvp(path,args);	
	      printf("after this\n");
            }
        }
    }
    if(count>0)	
    printf("\n");	
    dir = opendir(basePath);	
    if (!dir)
        return;
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
	    if(strcmp(filetype(dp->d_type),"directory")==0)
            {
	      strcpy(path, basePath);
              strcat(path, "/");
              strcat(path, dp->d_name);
              directory_all(path,size,substr); 
            } 	

        }
    }
    closedir(dir);
}

/***All files with size*******/
/*****************/
void directory_file_size(const char *base,int size)
{
    char path[1000];
    char currentdir[1000];
    char file[1000];
    char basePath[1000];
    struct dirent *dp;
    DIR *dir;
    int count = 0;
    if (strcmp(base," ")==0){
        getcwd(currentdir,1000);
        strcpy(basePath,currentdir);
    }
    else
    {
        strcpy(basePath,base);
    }
    dir = opendir(basePath);
    if (!dir)
    {	
	printf("No such directory available\n");
        return;	
    }   
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {	
              if (strcmp(filetype(dp->d_type),"regular file")==0)
            {
	        strcpy(file,basePath);
	        strcat(file, "/");
      	        strcat(file, dp->d_name);
        	FILE* fp = fopen(file, "r");
  
                if (fp == NULL) {
                printf("File Not Found!\n");
                return;
                }
                fseek(fp, 0L, SEEK_END);
                long int res = ftell(fp);
                fclose(fp);
		if (res >= size)
			printf("%s(%d)\t",dp->d_name,res);
            }
        }
    }
    if(count>1)
	printf("\n");
    dir = opendir(basePath);	
    if (!dir)
        return;
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
	    if(strcmp(filetype(dp->d_type),"directory")==0)
            { 
	      strcpy(path, basePath);
              strcat(path, "/");
              strcat(path, dp->d_name);
              directory_file_size(path,size); 
            } 	

        }
    }
    closedir(dir);
}
/*Files with size and substring*********/
/*********************/
void directory_size_str(const char *base,int size,char *substr)
{
    char path[1000];
    char currentdir[1000];
    char file[1000];
    char basePath[1000];
    struct dirent *dp;
    DIR *dir;
    int count = 0;
    if (strcmp(base," ")==0){
        getcwd(currentdir,1000);
        strcpy(basePath,currentdir);
    }
    else
    {
        strcpy(basePath,base);
    }
    dir = opendir(basePath);
    if (!dir)
    {	
	printf("No such directory available\n");
        return;	
    }   
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {	
              if (strcmp(filetype(dp->d_type),"regular file")==0 && (strstr(dp->d_name,substr)))
            {
	       /* strcpy(file,basePath);
	        strcat(file, "/");
      	        strcat(file, dp->d_name);
        	FILE* fp = fopen(file, "r");
  
                if (fp == NULL) {
                printf("File Not Found!\n");
                return;
                }
                fseek(fp, 0L, SEEK_END);
                long int res = ftell(fp);
                fclose(fp);
		if (res >= size)
			printf("%s(%d)\t",dp->d_name,res); */
	        printf("%s\t",dp->d_name);
		count++;
            }
	    else if (strcmp(filetype(dp->d_type),"directory")==0)
	    {
                printf("%s\t",dp->d_name);
		count++;
            }
        }
    }
    if (count > 0)
	printf("\n");	
    dir = opendir(basePath);	
    if (!dir)
        return;
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
	    if(strcmp(filetype(dp->d_type),"directory")==0)
            { 
	      strcpy(path, basePath);
              strcat(path, "/");
              strcat(path, dp->d_name);
              directory_size_str(path,size,substr); 
            } 	

        }
    }
    closedir(dir);
}
/*All files that contains substring******/
/******************/
void directory_file_str(const char *base,char *substr)
{
    char path[1000];
    char currentdir[1000];
    char file[1000];
    char basePath[1000];
    struct dirent *dp;
    DIR *dir;
    int count = 0;
    if (strcmp(base," ")==0){
        getcwd(currentdir,1000);
        strcpy(basePath,currentdir);
    }
    else
    {
        strcpy(basePath,base);
    }
    dir = opendir(basePath);
    if (!dir)
    {	
	printf("No such directory available\n");
        return;	
    }   
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {	
              if (strcmp(filetype(dp->d_type),"regular file")==0 && (strstr(dp->d_name,substr)))
            {
	        strcpy(file,basePath);
	        strcat(file, "/");
      	        strcat(file, dp->d_name);
        	FILE* fp = fopen(file, "r");
  
                if (fp == NULL) {
                printf("File Not Found!\n");
                return;
                }
                fseek(fp, 0L, SEEK_END);
                long int res = ftell(fp);
                fclose(fp);
		printf("%s(%d)\t",dp->d_name,res);
 		count++;
            }
	    else if (strcmp(filetype(dp->d_type),"directory")==0)
	    {
                printf("%s\t",dp->d_name);
		count++;
            }
        }
    }
    if (count > 0)
	printf("\n");	
    dir = opendir(basePath);	
    if (!dir)
        return;
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
	    if(strcmp(filetype(dp->d_type),"directory")==0)
            {
	      strcpy(path, basePath);
              strcat(path, "/");
              strcat(path, dp->d_name);
              directory_file_str(path,substr); 
            } 	

        }
    }
    closedir(dir);
}
/*ALl files********/
/************/
void directory_file(const char *base)
{
    char path[1000];
    char currentdir[1000];
    char file[1000];
    char basePath[1000];
    struct dirent *dp;
    DIR *dir;
    int count = 0;
    if (strcmp(base," ")==0){
        getcwd(currentdir,1000);
        strcpy(basePath,currentdir);
    }
    else
    {
        strcpy(basePath,base);
    }
    dir = opendir(basePath);
    if (!dir)
    {	
	printf("No such directory available\n");
        return;	
    }   
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {	
              if (strcmp(filetype(dp->d_type),"regular file")==0)
            {
	        strcpy(file,basePath);
	        strcat(file, "/");
      	        strcat(file, dp->d_name);
        	FILE* fp = fopen(file, "r");
  
                if (fp == NULL) {
                printf("File Not Found!\n");
                return;
                }
                fseek(fp, 0L, SEEK_END);
                long int res = ftell(fp);
                fclose(fp);
		printf("%s(%d)\t",dp->d_name,res);
		count++;
            }
	    else if (strcmp(filetype(dp->d_type),"directory")==0)
	    {
                printf("%s\t",dp->d_name);
		count++;
            }
        }
    }
    if (count > 0)
	printf("\n");	
    dir = opendir(basePath);	
    if (!dir)
        return;
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
	    if(strcmp(filetype(dp->d_type),"directory")==0)
            {
	      strcpy(path, basePath);
              strcat(path, "/");
              strcat(path, dp->d_name);
              directory_file(path); 
            } 	

        }
    }
    closedir(dir);
}

/*Files with size************/
/******************/
void directory_size(const char *base,int size)
{
    char path[1000];
    char currentdir[1000];
    char file[1000];
    char basePath[1000];
    struct dirent *dp;
    DIR *dir;
    int count = 0;	
    if (strcmp(base," ")==0){
        getcwd(currentdir,1000);
        strcpy(basePath,currentdir);
    }
    else
    {
        strcpy(basePath,base);
    }
    dir = opendir(basePath);
    if (!dir)
    {	
	printf("No such directory available\n");
        return;	
    }   
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {	
		if (strcmp(filetype(dp->d_type),"regular file")==0)
		{
                strcpy(file,basePath);
	        strcat(file, "/");
      	        strcat(file, dp->d_name);
        	FILE* fp = fopen(file, "r");
  
                if (fp == NULL) {
                printf("File Not Found!\n");
                return;
                }
                fseek(fp, 0L, SEEK_END);
                long int res = ftell(fp);
                fclose(fp);
		if (res >= size)
                printf("%s(%d)\t",dp->d_name,res);
		count++;
            	}
		else if (strcmp(filetype(dp->d_type),"directory")==0)
	     {
                printf("%s\t",dp->d_name);
		count++;
            }

        }
    }
	if (count > 0)
	printf("\n");
    dir = opendir(basePath);	
    if (!dir)
        return;
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
	    if(strcmp(filetype(dp->d_type),"directory")==0)
            {
	      strcpy(path, basePath);
              strcat(path, "/");
              strcat(path, dp->d_name);
              directory_size(path,size); 
            } 	

        }
    }
    closedir(dir);
}

/**Files with substr*******/
/*****************/
void directory_substr(const char *base,char *substr)
{
    char path[1000];
    char currentdir[1000];
    char file[1000];
    char basePath[1000];
    struct dirent *dp;
    DIR *dir;
    int count = 0;
    if (strcmp(base," ")==0){
        getcwd(currentdir,1000);
        strcpy(basePath,currentdir);
    }
    else
    {
        strcpy(basePath,base);
    }
    dir = opendir(basePath);
    if (!dir)
    {	
	printf("No such directory available\n");
        return;	
    }   
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {	
              if (strcmp(filetype(dp->d_type),"regular file")==0 && strstr(dp->d_name,substr))
            {
	        strcpy(file,basePath);
	        strcat(file, "/");
      	        strcat(file, dp->d_name);
        	FILE* fp = fopen(file, "r");
  
                if (fp == NULL) {
                printf("File Not Found!\n");
                return;
                }
                fseek(fp, 0L, SEEK_END);
                long int res = ftell(fp);
                fclose(fp);
                printf("%s(%d)\t",dp->d_name,res);
		count++;
            }
	     else if (strcmp(filetype(dp->d_type),"directory")==0)
	    {
                printf("%s\t",dp->d_name);
		count++;
            }

        }
    }
    if (count > 0)
	printf("\n");	
    dir = opendir(basePath);	
    if (!dir)
        return;
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
	    if(strcmp(filetype(dp->d_type),"directory")==0)
            {
	      strcpy(path, basePath);
              strcat(path, "/");
              strcat(path, dp->d_name);
              directory_substr(path,substr); 
            } 	

        }
    }
    closedir(dir);
}
/** List files/directories*****/
/*********************/
void list_directory(const char *base,char *file_type)
{
    char path[1000];
    char currentdir[1000];
    char file[1000];
    char basePath[1000];
    struct dirent *dp;
    DIR *dir;
    int count = 0;
    if (strcmp(base," ")==0){
        getcwd(currentdir,1000);
        strcpy(basePath,currentdir);
    }
    else
    {
        strcpy(basePath,base);
    }
    dir = opendir(basePath);
    if (!dir)
    {	
	printf("No such directory available\n");
        return;	
    }   
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {	
              if (strcmp(filetype(dp->d_type),"regular file")==0 && strcmp(file_type,"f")==0)
              {
	       printf("%s\t",dp->d_name);
	       count++;
              }
	      if (strcmp(filetype(dp->d_type),"directory")==0 && strcmp(file_type,"d")==0)
              {
	       printf("%s\t",dp->d_name);
	       count++;
              }

        }
    }
    if (count > 0)
	printf("\n");
    dir = opendir(basePath);	
    if (!dir)
        return;
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
	    if(strcmp(filetype(dp->d_type),"directory")==0)
            {
	      strcpy(path, basePath);
              strcat(path, "/");
              strcat(path, dp->d_name);
              list_directory(path,file_type); 
            } 	

        }
    }
    closedir(dir);
}

/****/


int main (int argc, char **argv) { 
 	
  bool arg_set[4] = {false,false,false,false};
  char directory[4096] = " ";
  char substr[4096];
  char file_type[1];
  int size = 0,i=0;

  for(i = 1; i<= argc - 1;i++){
      if (strcmp(argv[i],"-S") == 0)
      {
         arg_set[0] = true;
      }
      else if (strcmp(argv[i],"-s") == 0)
      {
          arg_set[1] = true;
          size = atoi(argv[++i]);
      }
      else if (strcmp(argv[i],"-f") == 0)
      {
          arg_set[2] = true;
          strcpy(substr,argv[++i]); 	
      }
      else if (strcmp(argv[i],"-t") == 0)
      {
	  arg_set[3] = true;
	 strcpy(file_type,argv[++i]);
      }			
      else
      {
	strcpy(directory,argv[i]);
      }
  } 	
  if(arg_set[0] && arg_set[1] && arg_set[2])
  {
      directory_all(directory,size,substr); 
  }
  else if(arg_set[0] && arg_set[1])
  {
      directory_file_size(directory,size);
  }
  else if(arg_set[1] && arg_set[2])
  {	
      directory_size_str(directory,size,substr);
  }
  else if(arg_set[0] && arg_set[2])
  {
      directory_file_str(directory,substr);
  }
  else if(arg_set[0])
  {
      directory_file(directory);
  }
  else if(arg_set[1])
  {
      directory_size(directory,size);
  }
  else if(arg_set[2])
  {
      directory_substr(directory,substr);
  }
  else if(arg_set[3])
  {
      list_directory(directory,file_type);
  }

  else
  {
     just_directory(directory);
  }
  return 0; 
}