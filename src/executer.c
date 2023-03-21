#include "../inc/minishell.h"

void child_process(t_hold *hold, int32_t pipes[MAX_FD][2])
{
	//redirection

	// exec

	// close all file and pipediscriptors
}

void executer(t_hold *hold)
{
	t_parsed_chunk *p_tmp;
	// int32_t			pid[MAX_FD];
	int32_t			i;
	int32_t			pipes[MAX_FD][2];
	// print_parsed_list(hold->parsed_list);
	p_tmp = hold->parsed_list;
	i = 0;
	while (p_tmp)
	{
		fprintf(stderr, "lit shir\n");
		// pid[i] = fork();
		if (!fork())
		{
			fprintf(stderr, "%d child\n", i);
			child_process();
			exit(0);
		}
		else
		{
			fprintf(stderr, "%d parrent\n", i);
		// waitpid(-1, &error_code, 0);
			// waitpid(pid)
		}
		if (p_tmp->infile > 2)
			close(p_tmp->infile);
		if (p_tmp->outfile > 2)
			close(p_tmp->outfile);
		p_tmp = p_tmp->next;
		i++;
	}
	p_tmp = hold->parsed_list;
	i = 0;
	// sleep(1);
	while (p_tmp)
	{
		waitpid(-1, &error_code, 0);
		p_tmp = p_tmp->next;
		i++;
	}
	fprintf(stderr, "END\n");
	// close_all_pipe_fds(pipes);
}