#include "minishell.h"

int main(int argc, char **argv)
{
    char *line;

    while(1)
    {
        line = readline("\033[1;36mminishell> \033[0m");
        add_history(line);
        printf("line = %s\n", line);
        free(line);
    }
    free(line);
    return (0);
}
