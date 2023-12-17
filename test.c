#include <stdio.h>
#include "inc/pipex.h"



//int main(int argc, char *argv[], char *envp[])
int main ()
{
    char *test;

  //  char *command[] ={"cat", "texto1.txt", NULL};
   // for (int i = 0; envp[i] != NULL; i++) {
   //     printf("%s %d %s\n", envp[i], argc, argv[1]);
    //    execve("/usr/bin/cat", command, NULL);
   // }
    test =  get_command_path("grep",NULL);
    printf("%s \n",test);
    return 0;
}
