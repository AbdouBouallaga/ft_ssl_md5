#include "../inc/ft_ssl.h"

void usage(char *str)
{
    printf("usage: %s [algo] [-s string] [files ...]", str);
    exit(0);
}
// void md5FromStdin(){
//     char str[16];
//     ft_bzero(str, 16);
//     char *buffer;
//     while (read(0, str, 16) > 0)
//     {
//         buffer = ft_strjoin(buffer, str);
//     }
//     buffer[ft_strlen(buffer) - 1] = '\0';
//     md5(buffer);
// }

void    stdinread(){
    
}
#include <sys/select.h>
void md5PREP(int ac ,char **av){
    int i = 2;
    char str[16];
    char *buffer;
    struct timeval tv = {0, 100000};
    // fd_set fds;
    // FD_ZERO(&fds);
    // FD_SET(0, &fds);
    int r = select(1, (fd_set *)str, NULL, NULL, &tv); //wtf
    if (r > 0){
        while (read(0, str, 16) > 0)
        {
            buffer = ft_strjoin(buffer, str);
        }
        buffer[ft_strlen(buffer) - 1] = '\0';
        md5(buffer);
    }
    while(av[i] && av[i][0] == '-' && i < ac){
        if (av[i][1] == 's'){
            md5(av[i+1]);
        }
        if (av[i][1] == 'p'){
            stdinread();
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
    if (ft_strcmp(av[1], "md5") == 0)
        md5PREP(ac, av);
    else
        usage(av[0]);
    return(0);
} 