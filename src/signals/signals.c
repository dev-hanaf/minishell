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
void sigHandler_child(int sig)
{
	ft_putstr_fd("alooohaaaaaaaaaa",2);
	dprintf(2,"^\\Quit (core dumped)\n");
	exit(sig + 1000);
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
	// ft_putstr_fd("alooohaaaaaaaaaa22",2);
	// signal(SIGINT,sigHandler_child);
	// signal(SIGQUIT,sigHandler_child); 
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