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
• -t, God mode verbose\n",
           str);
    exit(0);
}

void flag_p() { g_flags.p = 1; }
void flag_q() { g_flags.q = 1; }
void flag_r()
{
    g_flags.r = 1;
    g_flags.q = 1;
}
void flag_s() {}
void flag_t() { g_flags.verbose = 1; }
void algo_md5(char *str, char *title) { md5(str, title); }
void algo_sha256(char *str, char *title) { sha256(str, title); }

// #include <sys/select.h>
void RUN(int ac, char **av)
{
    char *buffer;
    char **queue;
    char str[2];

    void (*dispatch_flags[])() = {flag_p, flag_q, flag_r, flag_s, flag_t};
    void (*dispatch_algo[])(char *str, char *title) = {algo_md5, algo_sha256};

    int bufferLen = 1000;
    int queueLenMalloc = 100;
    int i = 2;
    int queueLen = 0;
    int continueReaning;
    int selector;
    int offset;
    int ret;
    int bufflen = 0;
    int nfds = 1;

    FILE *fd;
    fd_set readfds;
    struct timeval tv = {0, 100000};

    ft_bzero(str, 2);
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);
    ret = select(nfds, &readfds, NULL, NULL, &tv);
    buffer = (char *)malloc(sizeof(char) * bufferLen);
    if (buffer == NULL)
        halt_and_catch_fire("Error: malloc failed");
    queue = (char **)malloc(sizeof(char *) * queueLenMalloc);
    if (queue == NULL)
        halt_and_catch_fire("Error: malloc failed");
    while (i < ac && av[i] && av[i][0] == '-' && av[i][1] - 'p' < 5)
    {
        dispatch_flags[av[i][1] - 'p'](i); // dispatch flags
        i++;
    }
    if (ret != 0)
    {
        g_flags.Stdin = 1;
        continueReaning = 1;
        while (continueReaning)
        {
            continueReaning = read(0, str, 16);
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
        // queue = realloc(queue, (queueLen + 2) * sizeof(char *));
        // if (queue == NULL)
        //     halt_and_catch_fire("Error: malloc failed 1");

        queue[queueLen] = (char *)malloc(sizeof(char) * ft_strlen(buffer));
        // ft_bzero(queue[queueLen], ft_strlen(buffer));
        ft_strcpy(queue[queueLen], buffer);
        if (g_flags.p == 1)
        {
            queue[queueLen + 1] = (char *)malloc(sizeof(char) * (ft_strlen(buffer) + 3));

            if (buffer[bufflen - 1] == '\n')
                buffer[bufflen - 1] = '\0';
            ft_strcat(queue[queueLen + 1], buffer);
        }
        else
        {
            queue[queueLen + 1] = (char *)malloc(sizeof(char) * (ft_strlen("stdin") + 1));
            ft_strcpy(queue[queueLen + 1], "stdin");
            // ft_strcat(queue[queueLen + 1], "\n");
        }
        queueLen += 2;
    }
    i = 2;
    while (i < ac && av[i] && av[i][0] == '-' && av[i][1] - 'p' < 5)
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
            // queue = realloc(queue, (queueLen + 2) * sizeof(char *));
            if (queue == NULL)
                halt_and_catch_fire("Error: malloc failed2");
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
        if ((fd = open(av[i], O_RDONLY)) == NULL)
        {
            printf("ft_ssl: %s: No such file or directory\n", av[i]);
            // exit(1);
        }
        else
        {
            continueReaning = 1;
            while (continueReaning)
            {
                // continueReaning = fread(str, 1, 1, fd);
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
            // queue = realloc(queue, (queueLen + 2) * sizeof(char *));
            if (queue == NULL)
                halt_and_catch_fire("Error: malloc failed3");

            queue[queueLen] = (char *)malloc(sizeof(char) * ft_strlen(buffer));
            // displaybits(queue[queueLen], ft_strlen(buffer), "DEBUG AFTER MALLOC");
            ft_bzero(queue[queueLen], ft_strlen(buffer) + 1); // Don't trust malloc to give you a zeroed out buffer
            // displaybits(queue[queueLen], ft_strlen(buffer), "DEBUG AFTER BZERO");
            ft_strncpy(queue[queueLen], buffer, bufflen);
            queue[queueLen + 1] = (char *)malloc(sizeof(char) * (ft_strlen(av[i]) + 1));
            ft_bzero(queue[queueLen + 1], ft_strlen(av[i]) + 2); // Don't trust malloc to give you a zeroed out buffer
            ft_strcpy(queue[queueLen + 1], av[i]);
            ft_strcat(queue[queueLen + 1], "\0");
            queueLen += 2;
        }
        i++;
    }
    i = 0;
    selector = 0;
    offset = 1;
    if (g_flags.r == 1)
    {
        selector = queueLen - 2;
        offset = -1;
    }
    // int qw = -1;
    // while (++qw < queueLen)
    //     displaybits(queue[qw], ft_strlen(queue[qw]) + 10, "queue DEBUG");
    while (i < queueLen)
    {
        dispatch_algo[g_flags.algo - 1](queue[abs(selector - i)], queue[abs(selector - (i + offset))]);
        i += 2;
    }
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
    g_flags.read_string = 0;
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