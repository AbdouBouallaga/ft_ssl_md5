#include "../inc/ft_ssl.h"

void usage(char *str)
{
    printf("usage: %s [algo] [-s string] [files ...]", str);
    exit(0);
}

void md5PREP(int ac ,char **av){
    int i = 2;
    char str[16];
    char *buffer;
    while(av[i] && av[i][0] == '-' && i < ac){
        if (av[i][1] == 's'){
            md5(av[i+1]);
        }
        i++;
    }
}

int main(int ac, char **av)
{
    if(ac < 2)
	{
		usage(av[0]);
	}
    if (strcmp(av[1], "md5") == 0)
        md5PREP(ac, av);
    else
        usage(av[0]);
    return(0);
} 