#include "../inc/ft_ssl.h"

struct flags g_flags;

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

// void    stdinread(){
    
// }
#include <sys/select.h>
void RUN(int ac ,char **av){
    int i = 2;
    int queueLen = 0;

    char **queue = (char **)malloc(sizeof(char *));
    char str[16];
    ft_bzero(str, 1);
    char *buffer;
    int bufflen = 0;
    struct timeval tv = {0, 100000};
    fd_set readfds;
    int nfds = 1;
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);
    int ret = select(nfds, &readfds, NULL, NULL, &tv);
    // printf("stdin %d\n", ret);
    while(av[i] && av[i][0] == '-' && i < ac){
        if (av[i][1] == 'q'){
            g_flags.q = 1;
        }
        else if (av[i][1] == 'r'){
            g_flags.r = 1;
        }
        else if (av[i][1] == 'p'){
            g_flags.p = 1;
        }
        else if (av[i][1] == 'r'){
            g_flags.r = 1;
        }
        i++;
    }
    if (ret != 0){
        int continueReaning = 1;
        while (continueReaning)
        {
            continueReaning = read(0, str, 1);
            buffer = (char *)realloc(buffer, sizeof(char)*(ft_strlen(str) + bufflen));
            if (buffer != NULL){
                ft_strcat(buffer, str);
                bufflen += continueReaning;
                // printf("buffer len: %d\n", bufflen);
            }
        }
        buffer[bufflen - 1] = '\0';
        // printf("buffer len: %d\n", ft_strlen(buffer));
        queue = realloc(queue, (queueLen+2) * sizeof(char *));
        queue[queueLen] = (char *)malloc(sizeof(char) * ft_strlen(buffer));
        ft_strcpy(queue[queueLen], buffer);
        if (g_flags.p == 1){
            queue[queueLen+1] = (char *)malloc(sizeof(char) * (ft_strlen(buffer)+3));
            ft_strcpy(queue[queueLen+1], "\"");
            ft_strcat(queue[queueLen+1], buffer);
            ft_strcat(queue[queueLen+1], "\"" );
        }
        else {
            queue[queueLen+1] = (char *)malloc(sizeof(char) * (ft_strlen("stdin")+1));
            ft_strcpy(queue[queueLen+1], "stdin");
            ft_strcat(queue[queueLen+1], "\0");
        }
        if (g_flags.p == 1 && g_flags.q == 1){
            write(1, buffer, ft_strlen(buffer));
            write(1, "\n", 1);
        }
        queueLen+=2;
    }
    i = 2;
    while(av[i] && av[i][0] == '-' && i < ac){
        if (av[i][1] == 's'){
            // printf("string len: %d\n", ft_strlen(av[i+1]));
            // printf("queue len: %d\n", queueLen);
            queue = realloc(queue, (queueLen+2) * sizeof(char *));
            queue[queueLen] = (char *)malloc(sizeof(char) * ft_strlen(av[i+1]));
            ft_strcpy(queue[queueLen], av[i+1]);
            queue[queueLen+1] = (char *)malloc(sizeof(char) * (ft_strlen(av[i+1])+3));
            ft_strcpy(queue[queueLen+1], "\"");
            ft_strcat(queue[queueLen+1], av[i+1]);
            ft_strcat(queue[queueLen+1], "\"\0");
            i++;
            queueLen+=2;
        }
        i++;
    }
    // generated
    // printf("ac %d\n", ac);
    // printf("i %d\n", i);
    while (i < ac){
        int fd = open(av[i], O_RDONLY);
        if (fd == -1){
            printf("ft_ssl: %s: No such file or directory\n", av[i]);
            exit(1);
        }
        int continueReaning = 1;
        while (continueReaning)
        {
            continueReaning = read(fd, str, 1);
            buffer = (char *)realloc(buffer, sizeof(char)*(ft_strlen(str) + bufflen));
            if (buffer != NULL){
                ft_strcat(buffer, str);
                bufflen += continueReaning;
                // printf("buffer len: %d\n", bufflen);
            }
        }
        buffer[bufflen - 1] = '\0';
        // printf("buffer len: %d\n", ft_strlen(buffer));
        queue = realloc(queue, (queueLen+2) * sizeof(char *));
        // printf("buffer %s", buffer);
        queue[queueLen] = (char *)malloc(sizeof(char) * ft_strlen(buffer));
        ft_strcpy(queue[queueLen], buffer);
        queue[queueLen+1] = (char *)malloc(sizeof(char) * (ft_strlen(av[i])+1));
        ft_strcpy(queue[queueLen+1], av[i]);
        ft_strcat(queue[queueLen+1], "\0");
        queueLen+=2;
        i++;
    }
    i = 0;
    int selector = 0;
    int offset = 1;
    if (g_flags.r == 1){
        selector = queueLen-2;
        offset = -1;
    }
    while (i < queueLen){
        if (g_flags.algo == 1)
            md5(queue[abs(selector - i)], queue[abs(selector - (i+offset))]);
        i+=2;
    }
}



int main(int ac, char **av)
{
    g_flags.p = 0;
    g_flags.q = 0;
    g_flags.r = 0;
    if(ac < 2)
	{
		usage(av[0]);
	}
    if (ft_strcmp(av[1], "md5") == 0)
        g_flags.algo = 1;
    else if (ft_strcmp(av[1], "sha256") == 0)
        g_flags.algo = 2;
    else
        usage(av[0]);
    RUN(ac, av);
    return(0);
} 