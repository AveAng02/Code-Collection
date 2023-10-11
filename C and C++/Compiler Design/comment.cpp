
#include <stdio.h>
#include <string.h>


int main() 
{
    char line[100];
    printf("Enter a line of text: ");
    scanf("%s", line);

    if(line[0] == '/' && line[1] == '/')
    {
        printf("This line is a comment.\n");
        return 0;
    }

    if(line[0] == '/' && line[1] == '*')
    {
        printf("This line is a comment.\n");
        return 0;
    }

    return 0;
}
