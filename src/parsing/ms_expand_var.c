#include "minishell.h"

//return a string with dollars replaced by their var content

void    ms_expand_var(char *str, char **env)
{
    char    **var_array;

    var_array = NULL;
    var_array = ms_var_array(str, var_array, env);
    if (!var_array)
        exit(EXIT_FAILURE);
    printarr(var_array);
}

