#include "minishell.h"
void sigHandler(int sig)
{
	rl_on_new_line();
	printf("\n");
	rl_replace_line("",0);
	rl_redisplay();
	get_ms()->status = sig + 128;
	//get_env_ld(get_ms()->env_ld,"?")->value = ft_itoa(get_ms()->status);
}
void handle_signals(void)
{
	signal(SIGINT,sigHandler);
	signal(SIGQUIT,SIG_IGN);
	//signal(SIGPIPE,SIG_IGN);
}
//---------------------------------------------------------------------//


void sigChildHandler(int sig)
{
	ft_putstr_fd("handling child", 2);
	if (sig == SIGINT)
	{
		//ft_putstr_fd("\n", 2);
		clean_exit(130);
	}
	else if (sig == SIGQUIT)
	{
		//ft_putstr_fd("Quit2\n", 2);
		clean_exit(2);
		//exit(3);
	}
}
void handle_child_signals(void)
{
	signal(SIGINT,sigChildHandler);
	signal(SIGQUIT,sigChildHandler);
}
void parentSig(int sig)
{	
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped) \n", 2);
		//exit(3);
	}
}

void sigHandler_parent(int sig)
{
	if (sig == SIGINT)
	{
		update_status(130);
	}
}
void handle_parent_in_childs(void)
{
	signal(SIGINT,parentSig);
	signal(SIGQUIT,parentSig);
}
void handle_parent_signals(void)
{
	signal(SIGINT, sigHandler_parent);
	signal(SIGQUIT, SIG_IGN);
}
