#include "../inc/ft_ssl.h"

struct flags g_flags;

void usage(char *str)
{
    printf("usage: %s command [flags] [file/string]\n\n\
Commands:\n\
md5\n\
sha256\n\n\
Flags:\n\
• -p, echo STDIN to STDOUT and append the checksum to STDOUT\n\
• -q, quiet mode\n\
• -r, reverse the format of the output.\n\
• -s, print the sum of the given string\n\
• -v, God mode verbose\n",
           str);
    exit(0);
}

void flag_p() { g_flags.p = 1; }
void flag_q() { g_flags.q = 1; }
void flag_r() { g_flags.r = 1; }
void flag_s() {}
void flag_t() {}
void flag_u() {}
void flag_v() { g_flags.verbose = 1; }
void algo_md5(char *str, char *title) { md5(str, title); }
void algo_sha256(char *str, char *title) { sha256(str, title); }

void RUN(int ac, char **av)
{
    char *buffer;
    char **queue;
    char str[2];

    void (*dispatch_flags[])() = {flag_p, flag_q, flag_r, flag_s, flag_t, flag_u, flag_v};
    void (*dispatch_algo[])(char *str, char *title) = {algo_md5, algo_sha256};

    int bufferLen = 100;
    int queueLenMalloc = 100;
    int i = 2;
    int queueLen = 0;
    int continueReaning;
    int ret;
    int bufflen = 0;
    int nfds = 1;

    int fd;
    fd_set readfds;
    struct timeval tv = {0, 100000};

    ft_bzero(str, 2);
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);
    ret = select(nfds, &readfds, NULL, NULL, &tv);
    buffer = (char *)malloc(sizeof(char) * bufferLen);
    ft_bzero(buffer, bufferLen);
    if (buffer == NULL)
        halt_and_catch_fire("Error: malloc failed");
    queue = (char **)malloc(sizeof(char *) * queueLenMalloc);
    if (queue == NULL)
        halt_and_catch_fire("Error: malloc failed");
    while (i < ac && av[i] && av[i][0] == '-')
    {
        if (av[i][1] - 'p' < 7)
            dispatch_flags[av[i][1] - 'p'](i); // dispatch flags
        i++;
    }
    if (ret != 0)
    {
        g_flags.Stdin = 1;
        continueReaning = 1;
        while (continueReaning)
        {
            continueReaning = read(0, str, 1);
            if (bufflen + continueReaning > bufferLen)
            {
                buffer = realloc(buffer, sizeof(char) * (bufferLen + 1000));
                bufferLen += 1000;
                if (buffer == NULL)
                    halt_and_catch_fire("Error: malloc failed");
            }
            if (buffer != NULL)
            {
                ft_strcat(buffer, str);
                bufflen += continueReaning;
            }
        }
        buffer[bufflen] = '\0';
        if (queueLen > queueLenMalloc)
        {
            queue = realloc(queue, sizeof(char *) * (queueLen + 20));
            queueLenMalloc = queueLen + 20;
            if (queue == NULL)
                halt_and_catch_fire("Error: malloc failed");
        }
        queue[queueLen] = (char *)malloc(sizeof(char) * ft_strlen(buffer));
        // ft_bzero(queue[queueLen], ft_strlen(buffer));
        ft_strcpy(queue[queueLen], buffer);
        if (g_flags.p == 1)
        {
            queue[queueLen + 1] = (char *)malloc(sizeof(char) * (ft_strlen(buffer)));

            if (buffer[bufflen - 1] == '\n')
                buffer[bufflen - 1] = '\0';
            ft_strcat(queue[queueLen + 1], buffer);
        }
        else
        {
            queue[queueLen + 1] = (char *)malloc(sizeof(char) * (ft_strlen("stdin") + 1));
            ft_strcpy(queue[queueLen + 1], "stdin");
        }
        queueLen += 2;
    }
    i = 2;
    while (i < ac && av[i] && av[i][0] == '-')
    {
        if (av[i][1] == 's' && av[i + 1] && av[i + 1][0] != '-')
        {
            if (queueLen > queueLenMalloc)
            {
                queue = realloc(queue, sizeof(char *) * (queueLen + 20));
                queueLenMalloc = queueLen + 20;
                if (queue == NULL)
                    halt_and_catch_fire("Error: malloc failed");
            }
            queue[queueLen] = (char *)malloc(sizeof(char) * ft_strlen(av[i + 1]));
            ft_strcpy(queue[queueLen], av[i + 1]);
            queue[queueLen + 1] = (char *)malloc(sizeof(char) * (ft_strlen(av[i + 1]) + 3));
            ft_strcpy(queue[queueLen + 1], "\"");
            ft_strcat(queue[queueLen + 1], av[i + 1]);
            ft_strcat(queue[queueLen + 1], "\"\0");
            i++;
            queueLen += 2;
        }
        i++;
    }
    while (i < ac)
    {
        fd = open(av[i], O_RDONLY);
        if (fd == -1)
            printf("ft_ssl: %s: No such file or directory\n", av[i]);
        else
        {
            ft_bzero(buffer, bufflen);
            bufflen = 0;
            continueReaning = 1;
            while (continueReaning)
            {
                continueReaning = read(fd, str, 1);
                if (bufflen + continueReaning > bufferLen)
                {
                    buffer = realloc(buffer, sizeof(char) * (bufferLen + 1000));
                    bufferLen += 1000;
                    if (buffer == NULL)
                        halt_and_catch_fire("Error: malloc failed");
                }
                if (buffer != NULL)
                {
                    ft_strcat(buffer, str);
                    bufflen += continueReaning;
                }
            }
            if (queueLen > queueLenMalloc)
            {
                queue = realloc(queue, sizeof(char *) * (queueLen + 20));
                queueLenMalloc = queueLen + 20;
                if (queue == NULL)
                    halt_and_catch_fire("Error: malloc failed");
            }
            queue[queueLen] = (char *)malloc(sizeof(char) * ft_strlen(buffer));
            ft_bzero(queue[queueLen], ft_strlen(buffer) + 1); //IDK why but it works
            ft_strncpy(queue[queueLen], buffer, bufflen);
            queue[queueLen + 1] = (char *)malloc(sizeof(char) * (ft_strlen(av[i])));
            // ft_bzero(queue[queueLen + 1], ft_strlen(av[i]) + 2);
            ft_strcpy(queue[queueLen + 1], av[i]);
            ft_strcat(queue[queueLen + 1], "\0");
            queueLen += 2;
        }
        i++;
    }
    i = 0;
    while (i < queueLen)
    {
        dispatch_algo[g_flags.algo - 1](queue[i], queue[i + 1]);
        i += 2;
    }
    free(buffer);
    i = -1;
    while (queue[++i])
        free(queue[i]);
    free(queue);
    close(fd);
}

int main(int ac, char **av)
{
    int i = -1;
    char *algos[] = {"md5", "sha256", NULL};
    g_flags.Stdin = 0;
    g_flags.p = 0;
    g_flags.q = 0;
    g_flags.r = 0;
    g_flags.algo = 0;
    if (ac < 2)
        usage(av[0]);
    while (algos[++i])
        if (ft_strcmp(av[1], algos[i]) == 0)
        {
            g_flags.algo = i + 1;
            break;
        }
    if (g_flags.algo == 0)
        usage(av[0]);
    RUN(ac, av);
    return (0);
}