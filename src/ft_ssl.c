#include "../inc/ft_ssl.h"

struct flags g_flags;

void usage(char *str)
{
    printf("usage: %s [algo] [-s string] [files ...]", str);
    exit(0);
}

// #include <sys/select.h>
void RUN(int ac ,char **av){
    int i = 2;
    int queueLen = 0;
    
    printf("START\n");
    char **queue = (char **)malloc(sizeof(char *)* 1);
    if (queue == NULL)
        halt_and_catch_fire("Error: malloc failed");
    printf("START1\n");
    char *buffer = (char *)malloc(sizeof(char) * 1);
    if (buffer == NULL)
        halt_and_catch_fire("Error: malloc failed");
    char str[2];
    ft_bzero(str, 2);
    int bufflen = 0;
    struct timeval tv = {0, 100000};
    fd_set readfds;
    int nfds = 1;
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);
    int ret = select(nfds, &readfds, NULL, NULL, &tv);
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
        else if (av[i][1] == 'v'){
            g_flags.verbose = 1;
        }
        i++;
    }
    if (ret != 0){
        printf("GET StdIN\n");
        int continueReaning = 1;
        while (continueReaning)
        {
            continueReaning = read(0, str, 16);
            printf("poooo\n");
            buffer = realloc(buffer, sizeof(char)*(ft_strlen(str) + bufflen));
            printf("oups\n");

            if (buffer == NULL)
                halt_and_catch_fire("Error: malloc failed");
            if (buffer != NULL){
                ft_strcat(buffer, str);
                bufflen += continueReaning;
            }
        }
        printf("out of loop\n");
        buffer[bufflen - 1] = '\0';
        queue = realloc(queue, (queueLen+2) * sizeof(char *));
        if (queue == NULL)
            halt_and_catch_fire("Error: malloc failed 1");
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
            queue = realloc(queue, (queueLen+2) * sizeof(char *));
            if (queue == NULL)
                halt_and_catch_fire("Error: malloc failed2");
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
            }
        }
        buffer[bufflen - 1] = '\0';
        queue = realloc(queue, (queueLen+2) * sizeof(char *));
        if (queue == NULL)
            halt_and_catch_fire("Error: malloc failed3");
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
        if (g_flags.algo == 2)
            sha256(queue[abs(selector - i)], queue[abs(selector - (i+offset))]);
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