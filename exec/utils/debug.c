
#include "util_exec.h"

void	test_print(t_data *data)
{
	int	i;

	i = 1;
	printf("[hello %p]\n", data->exec[i].stdin_st);
	if (data->exec && data->exec[i].stdin_st)
	{
		if (data->exec[i].cmd)
			printf("[%s]\n", data->exec->cmd[0]);
	}
	// printf("token_pipe == \n");
	// if (tmp[i].stdin_st->token == 2)
	//     printf("token_files == [%d]\n",tmp[i].stdin_st->token);
	// if (tmp[i].stdin_st->token == 3)
	//     printf("token_commande == [%d]\n",tmp[i].stdin_st->token);
	// if (tmp[i].stdin_st->token == 4)
	//     printf("token_redir_in == [%d]\n",tmp[i].stdin_st->token);
	// if (tmp[i].stdin_st->token == 5)
	//     printf("token_redir_append == [%d]\n",tmp[i].stdin_st->token);
	// if (tmp[i].stdin_st->token == 6)
	//     printf("token_out == [%d]\n",tmp[i].stdin_st->token);
	// if (tmp[i].stdin_st->token == 7)
	//     printf("token_here_doc == [%d]\n",tmp[i].stdin_st->token);
}
/*
	Bleu \033[0;34m
	Noir \033[0;30m
	Rouge \033[0;31m
	Vert \033[0;32m
	Jaune \033[0;33m
	Violet \033[0;35m
*/

void	print_debug(t_data *data)
{
	// for(int i = 0; i < data->nb_exec; i++)
	// {
	// 	printf("\033[0;34m---------- EXEC[%d] -----------\033[0m\n",i);
	// 	printf("	fd_in = \033[0;31m[%d]\033[0m\n",data->exec[i].fd_in);
	// 	printf("	fd_out = \033[0;31m[%d]\033[0m\n",data->exec[i].fd_out);
	// 	if(data->exec[i].cmd)
	// 	for (int i2 = 0; data->exec[i].cmd[i2]; i2++)
	// 		printf("Cmd[%d] = '%s'\n",i2,data->exec[i].cmd[i2]);
	// 	printf("\033[0;34mSTDIN _ IN\033[0m\n");
	// 	print_list(data->exec[i].stdin_st);
	// 	printf("\033[0;34mSTDIN _ OUT\033[0m\n");
	// 	print_list(data->exec[i].stdout_st);
	// }
	for (int i = 0; i < data->nb_exec; i++)
	{
		printf("\033[0;34m---------- EXEC_FOR_2[%d] -----------\033[0m\n\n", i);
		printf("\033[0;33m---------- CHECK_FD------------------\033[0m\n");
		printf("	fd_in = \033[0;31m[%d]\033[0m\n", data->exec[i].fd_in);
		printf("	fd_out = \033[0;31m[%d]\033[0m\n", data->exec[i].fd_out);
		printf("\033[0;33m---------- END_CHECK_FD------------------\033[0m\n");
		if (data->exec[i].cmd || data->exec[i].stdin_st->token == FILES
			|| data->exec[i].stdout_st->token == FILES)
			for (int i2 = 0; data->exec[i].cmd[i2]; i2++)
			{
				printf("Cmd[%d] = '%s'\n", i2, data->exec[i].cmd[i2]);
				if (data->exec[i].stdin_st)
				{
					printf("\033[0;33mStart stdin\033[0m\n");
					printf("Cmd_std_in[%d] = '%s' | file == [%s] | token == [%d]\n",
						i2, data->exec[i].cmd[i2],
						data->exec[i].stdin_st->content,
						data->exec[i].stdin_st->token);
				}
				if (data->exec[i].stdout_st)
				{
					printf("\033[0;33mStart stdout\033[0m\n");
					printf("Cmd_std_out[%d] = '%s' | file == [%s] | token == [%d]\n",
						i2, data->exec[i].cmd[i2],
						data->exec[i].stdout_st->content,
						data->exec[i].stdout_st->token);
				}
			}
		printf("\033[0;34m---------- END_EXEC_FOR_2 -----------\033[0m\n\n");
	}
}

void	print_bulding(t_data *data, char *str)
{
	int i = 0;
	printf("\033[0;33mTEST_FUNCTION_ENV\033[0m\n");
	printf("idx_var_path = [%d] | path_%s = \033[0;33m[%s]\033[0m\n", search_idx(data->env, str),
		str, ft_my_var(data, "PATH"));
    printf("env[idx_var = %d] = [%s]\n",search_idx(data->env,str), data->env[search_idx(data->env,str)]);
	printf("\n\033[0;33mTEST_FUNCTION_ENV\033[0m\n");
	for(i = 0; data->env[i]; i++){
		printf("env[%d] = [%s]\n",i, data->env[i]);
	}
}
