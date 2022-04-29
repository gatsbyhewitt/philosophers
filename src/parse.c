#include "philosopher.h"

int ft_atoi(char *nptr)
{
    int i;
    int n;

    i = 0;
    n = 1;
    while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
        nptr++;
    if (*nptr == '-' || *nptr == '+')
    {
        if (*nptr == '-')
            n = -1;
        nptr++;
    }
    while (*nptr >= '0' && *nptr <= '9')
    {
        i *= 10;
        i += *nptr - '0';
        nptr++;
    }
    i = i * n;
    return (i);
}

int ft_only_digit(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (1);
        i++;
    }
    return (0);
}

int ft_check_args(int argc, char **argv)
{
    int i;

    i = 1;

    if (argc != 5 && argc != 6)
        return (1);
    while (i <= argc)
    {
        if (ft_only_digit(argv[i]))
            return (1); 
        i++;
    }
    return (0);
}