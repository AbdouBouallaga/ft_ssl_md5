#include "../inc/ft_ssl.h"

int md5(char *str)
{
    unsigned int len;
    unsigned int i;

    len = ft_strlen(str);
    
}

int main(int ac, char **av)
{
    if (ac == 2){
        md5(av[1]);
    }
    return(0);
}