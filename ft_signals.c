#include "minishell.h"

t_global g_global;

void sigint_handler(int sig)
{
    (void)sig;
    if (!g_global.in_hd)
	{
        ft_putstr_fd("\n", STDERR_FILENO);
    } 
    if (g_global.in_cmd)
    {
        rl_replace_line("", 0);
        rl_redisplay();
        return;
    }
    else if (g_global.in_hd)
    {
        g_global.stop_hd = 1; // Set a flag to indicate heredoc termination
		rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
		return ;
    }
	else
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void sigquit_handler(int sig)
{
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

