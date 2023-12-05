#include "minishell.h"

void ft_sigint(int signum)
{
    (void)signum;
    printf("\n");
	rl_on_new_line();
    rl_redisplay();
}

void ft_sigquit(int signum) {
    printf("\nSIGQUIT received. Cleaning up...\n");
    // Add your cleanup code here
    (void)signum;
    exit(EXIT_FAILURE);
}

void ft_signals(void) {
    struct sigaction sa;
    sa.sa_handler = ft_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error setting up SIGINT handler");
        exit(EXIT_FAILURE);
    }

    sa.sa_handler = ft_sigquit;
    if (sigaction(SIGQUIT, &sa, NULL) == -1) {
        perror("Error setting up SIGQUIT handler");
        exit(EXIT_FAILURE);
    }
}

