#include "minishell.h"

void ft_sigint(int signum)
{
    (void)signum;
    printf("\n");
	rl_on_new_line();
    rl_redisplay();
}

void ft_sigquit(int signum)
{
    if (signum == SIGQUIT)
	{
        printf("\nSIGQUIT received. Cleaning up...\n");
        exit(EXIT_FAILURE);
    }
}

void ft_signals(void)
{
    struct sigaction sa;

    sa.sa_handler = ft_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1)
	{
        perror("Error setting up SIGINT handler");
        exit(EXIT_FAILURE);
    }

    sa.sa_handler = SIG_IGN;
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
        perror("Error setting up SIGQUIT handler for CTRL+4");
        exit(EXIT_FAILURE);
    }

    sa.sa_handler = ft_sigquit;
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
        perror("Error setting up SIGQUIT handler for CTRL+\\");
        exit(EXIT_FAILURE);
    }
}

