#include "minishell.h"
void sigHandler(int sig)
{
	rl_on_new_line();
	printf("\n");
	rl_replace_line("",0);
	rl_redisplay();
	get_ms()->status = sig + 128;
	get_env_ld(get_ms()->env_ld,"?")->value = ft_itoa(get_ms()->status);
}
void handle_signals(void)
{
	signal(SIGINT,sigHandler);
	signal(SIGQUIT,SIG_IGN);
}
void handle_child_signals(void)
{
	signal(SIGINT,SIG_DFL);
	signal(SIGQUIT,SIG_DFL);
}

void sigHandler_parent(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", 2);
	}
}

void handle_parent_signals(void)
{
	signal(SIGINT, sigHandler_parent);
	signal(SIGQUIT, sigHandler_parent);
}