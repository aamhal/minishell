/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 07:29:01 by aamhal            #+#    #+#             */
/*   Updated: 2023/12/01 18:34:24 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

typedef struct s_list
{
	struct s_list	*next;
	char			*command;
	char			type;
	int				sep_type;
	char			*buffer;
	int				pipes[2];
	int				flag;
}	t_list;

typedef struct s_exec
{
	char			**command;
	struct s_exec	*next;
	int				infile;
	int				outfile;
	int				flag;
	int				flag2;
	int				flag3;
}	t_exec;

typedef struct s_env
{
	int				f_expand;
	int				flagcd;
	int				flag;
	int				flag2;
	char			**envir;
	char			*c;
	char			*v;
	int				es;
	int				seg_flag;
	int				her_flag;
	int				f_env;
	struct s_env	*next;
}	t_env;

typedef struct s_var1
{
	char	*x;
	char	*p;
	int		flag;
}	t_var1;

typedef struct s_var2
{
	int	i;
	int	len;
	int	s;
}	t_var2;

typedef struct s_var3
{
	char			*v2;
	char			*c;
	char			*v;
	char			*equal;
	int				i;
	struct s_var3	*next;
}	t_var3;

void	print_nodes2(t_list *s);
void	print_nodes(t_env *s, int data);
void	print_node_export(t_env *s, int data);

//parsing
void	ft_free_lst(t_list **list);
void	parsing(t_list **list, t_env **envp, char **envc, int flag);
void	tokenizer(t_list **list, char *p, t_env **envp);
int		error_case(t_list **list, t_env **envp, int i, char *p);
void	tokinizer_norm(t_list **list, t_env **envp);
//check_input
int		is_quote(t_list **list, char *cmd, int i);
int		is_separ(t_list **list, char *cmd, int i);
int		is_char(t_list **list, char *cmd, int i);

// liked list function
t_list	*ft_lstnew(char *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);

//erorr_hundle
void	specifie_type(t_list **list);
int		syntax_error(t_list **list);
int		cont_char(char *str);
int		case_error(t_list **tmp);
void	specifie_type_norm(t_list **tmp);

//quotes_hundle
char	*q_remouve(char *str, int i, int j);
int		q_remouve_norm(char *str);
int		quot_norm(char *cmd, int i, int *j, char **p);
int		char_quot_norm(char *cmd, int i, int j, char *c);

//free.c
int		fun(char *str);
int		only_alnum(char *str);

//env.c
t_env	*fill_list(char **envp);
void	env_norm(t_env **new_env, char **envp, int *i, int *j);
void	env_norm2(t_env **head, t_env **current, t_env **new_env);
//util_func
int		ft_strcmp(char *s1, char *s2);
char	*ft_strncpy(char *dst, char *src, int n);
void	ft_lstadd_back1(t_env **lst, t_env *new);
int		find_index(char *p, int i);
char	*ft_strcpy(char *s1, char *s2);

//export.c
void	update_or_add_env(t_env **envp, char **p);
t_env	*find_node(t_env *head, char *command);
char	*command_ret(char *str);
char	*value_ret(char *str);

//unset.c
void	delete_from_env(t_env **envp, char **p);
void	delete_from_env(t_env **envp, char **p);

//expand
void	expand(t_list **list, t_env **env);
void	check_expand(t_list *tmp, t_env **env);
void	normal_expand(t_list *tmp, t_env **env);
char	*check_env(char *p, t_env **env);
char	*check_env_q(char *p, t_env **env);
void	separ_expand(t_list *tmp, t_env **env);
char	*normal_expand_helper1(char *s, t_env **env);
char	*normal_expand_helper2(char *s, t_env **env);
char	*special_expand(char *p, int *in);
char	*special_expand2(char *p, int *in, t_var1 *var);
int		ft_check_ex(char *p);
void	separ_expand_norm(t_list **list, t_env **env, t_var1 *var, int *i);
char	*special_expand_norm(char *p, int *i);
void	normal_expand_helper1_norm(char *s, int *i, t_var1 *var, char **p);
void	normal_expand_helper2_norm(char *s, t_var1 *var, t_env **env, int *i);

//echo
void	echo_command(char **command, int fd, t_env **env);
int		check_echo_n(char *str);
int		check_option_echo(char **command);
void	echo_norm(char **command, int fd);

//cd
void	cd_command(char **command, t_env **env);
void	cd_home(t_env **env);
void	cd_back(t_env **env);
void	cd_next(char *command, t_env **env);
char	*ft_path(t_env **env);
void	free_split(char **p);
void	cd_slash(t_env **env);
char	*last_slash(char *p);
int		cd_error(char *p, int f, t_env **env);
void	cd_next_env(t_env *envp, t_env **env);
char	*cd_back_free(char *p);

//pwd
void	pwd_command(char *command, t_env **env, int fd);
int		pwd_lc(char *p);
void	execution_part(t_list **list, t_env **envp);

//exection_part
void	builting(t_exec **list, t_env **envp, int data);
void	read_from_pipe(int pipes, t_env **env, t_list **list);
void	open_pipe(t_list **list, t_env **envp);
char	*concatenate_path_len(char *directory \
		, size_t dir_length, char *command);
char	**check_path_for_command(char *path_var, char *command);
void	execute_command(char **executable_info);

//exec utils
int		check_if_separ(t_list **list, char *separ);
// void exec_command(t_list **list, t_env **envp);
// char *delimiter(t_list **list);
// char *searching_path(char *command, t_env **envp);

//signals

void	hundler(int signal);
void	ignore_signals(void);
void	catch_signals(void);
void	default_signals(void);
//execution2.c
int		redirection_in(char *file);
int		redirection_out(char *file);
int		redirection_append(char *file);
int		here_doc(char *Delim, t_env **env);
int		list_size(t_exec *exec_val);
//execution3.c
char	*searching_path(char *command, t_env **envp);
int		builting_check(char *command);
void	simple_command(t_exec *exec_val, t_env **envp);
//execution4.c
int		**make_fd(int n);
pid_t	first_child(t_exec *exec_val, t_env **envp, int **fd);
pid_t	middle_child(t_exec *exec_val, t_env **envp, int **fd, size_t i);
pid_t	last_child(t_exec *exec_val, t_env **envp, int **fd, int n);
void	free_double(int **fd);
//execution5.
void	multiple_command(t_exec *exec_val, t_env **envp, int i);
void	free_list_exe(t_exec **list);
void	exec_func(t_exec *exec_val, t_env **envp);
char	*command_slash(char *command, t_env **env);
void	free_doublep(char **command);
//heredoc.c
// int check_heredoc(t_list **list);
// void    open_heredoc(t_list **list);
//exec_norm1.c
void	printf_error(char *s, t_env **env);
void	for_here_doc(char *Delim, int fd, t_env **env);
void	simple_cmd(t_exec **exec_val);
void	first(t_exec *exec_val, int **fd);
//exec_norm2.c
void	second(t_exec *exec_val, int **fd, size_t i);
void	last(t_exec *exec_val, int **fd, int n);
void	multi_cmd_fd(int **fd);
void	multi_cmd_fd_close(int **fd);
char	**executable_ret(char *path, int dir_length, char *command);
//exec_norm3.c
void	b_norm(t_exec *tmp, t_env **envp, int data);
void	b_norm2(t_exec *tmp, t_env **envp, int data);
int		exec_norm(t_list **head, t_exec **n, t_env **envp);
void	exec_norm2(t_list	**head, t_exec **n);
void	exec_norm3(t_list **list, t_exec **n);
//exec_norm4.c
int		exec_norm4(t_list **head, t_exec **n);
void	exec_norm5(t_list **head, t_exec **n);
void	exec_norm6(t_list **head, t_exec **n, t_exec **exec_val, t_env **env);
void	exec_norm7(t_exec **n);
int		exec_norm8(t_exec **n, t_list **list, int s);
//exec_norm5.c
void	initialination(t_exec **n, t_exec *exec_val, t_var2 *vars);
void	simple_c(t_exec *exec_val);
int		initialination3(t_list **head, t_exec **n, \
		t_exec **exec_val, t_env **envp);
//exit 
int		check_exit(char *p);
void	exit_command(char **command);
int		exit_status(int status);
//export_norm2.c
void	free_export2(char *p, t_env **envp);
char	**u_a_envnorm(t_var3 **vars, t_env **new_env, char **p);
//export_norm.c
void	existing_norm(char **p, t_var3 **vars, t_env **existing);
int		not_exesting(char **p, t_env **new_env, t_var3 **vars, t_env **envp);
int		not_exesting2(t_env **new_env, t_var3 **vars, \
		t_env **envp, char **p);
int		not_exesting_norm(t_env *new_env, t_var3 **vars, \
		char **p, t_env **envp);
void	export_initialisation(char **p, t_var3 **vars, \
		t_env **envp, t_env **existing);
void	r_q(t_list **list);
void	exit_norm(char **command, int *ex);
void	r_q_norm(char *str, char **p, int *i, int *j);
void	minishell_case(t_env **env, t_list **list, char **envc, int flag);
void	while_expand(t_list **tmp, t_env **env);
char	*check_env_cd(char *p, t_env **env);
int		access_confirm(char **p, t_env **env);
void	cd_loop(char **p, t_env **env);
int		char_quote(char *cmd, int i);
void	cdhome_norm(t_env *tmp, char **home, t_env **env);
void	cdback_norm(t_env *envp, char **opwd);
void	cdnext_norm(t_env *envp, char *command);
int		access_confirm1(char **p, t_env **env, int i);
char	*ft_path2(char *path);
char	*check_ex(char *p);
//export_parsing.c
int		export_parsing(t_env *list, t_env **envp, t_var3 **vars, char **p);
void	free_env(t_env **list);
void	free_var(t_var3 **list);
void	export_fail_free(t_env *new_env, t_var3 **vars);
//cd5.c
void	printf_error2(char *s, t_env **env);
int		check_split(char **p);
int		cd_command_norm(int flag, char **p);
char	*her_fill(char *p, t_env **env);
void	initialination3_norm(t_list **head, t_exec **n);
int		check_if_her(t_list **list, char *separ);
void	init_expand(int *i, int *j, t_var1 **var, char *s);
void	free_empty_c(t_exec **exec_val);
void	closing_fds(t_exec **n);
void	norm_shito(t_exec **n, t_exec **exec_val, t_env *envp);
char	**resize_char(char **p);
int		check_s(char *p);

#endif