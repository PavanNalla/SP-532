#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 256
struct count
{ 
    char keyword[10];
    int word_count;
};
// If the input matches with any of the keywords, increment the corresponding keyword count by 1.
void keycount(char* input,struct count *i,int a)
{
    if(strcmp(input,i[a-1].keyword)==0)
    {
        i[a-1].word_count++;
    }
}
// To display the keyword table.
void print_table(struct count* i,int n)
{
    int a;
    for(a=0;a<n-1;a++){
       printf("%s: %d \n",i[a].keyword,i[a].word_count); 
    }
    
}

int main(int argc, char* keywords[])
{
    int word_count=0;
    int a;
    char *input_string = NULL;
    char *s= NULL;
    size_t input_len = 0;
    ssize_t char_num;
    struct count *i;
    // Allocate the memomy to the structure based on number of keywords in the command line arguments
    i=(struct count *)malloc(argc*sizeof(struct count)); 
    // Copy the keywords in to the structure
    for(a=1; a<argc; a++)
    {
        i[a-1].word_count=0;
        strcpy(i[a-1].keyword,keywords[a]);
    }

    
    // must take input using getline() method until NULL is found
    while ((char_num = getline (&input_string, &input_len, stdin)) > 0)
    {
        s=strtok(input_string," ");
        while(s!=NULL)
        {
            for(a=1;a<argc;a++)
            {
                keycount(s,i,a);
            }
            s=strtok(NULL, " ,.\n");
        }
    }
    print_table(i,argc);
    
    free(input_string);
    return 0;
}
