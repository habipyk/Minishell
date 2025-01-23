
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "struct.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

# define S_QUOTES '\''
# define D_QUOTES '\"'
# define METACHAR_NUM 5
# define PIPE '|'
# define SOR '>'
# define SIR '<'
# define PIPE_S "|"
# define SOR_S ">"
# define SIR_S "<"
# define DIR "<<"
# define DOR ">>"
# define TEXT 0
# define SIGN_PIPE 1
# define SIGN_SOR 2
# define SIGN_SIR 3
# define HEREDOC 4
# define SIGN_DOR 5
# define EKHO 11
# define CD 12
# define PWD 13
# define ENV 14
# define UNSET 15
# define EXPORT 16
# define EXIT 17

//---MAIN----//

int		g_signal;

void	ft_readline(t_prime *data);
void	signal_init(void);
void	free_prime(t_prime *data);

void	env_init(t_prime *data, char **env);
t_env_l	*env_listnew(char *name, char *content);
void	env_lstadd_back(t_env_l **lst, t_env_l *new);
void	interrupt_here_document(int signal);

//*-------LEXER--------*//

void	lexer(t_prime *data);
int		quotes_check(char *line);
int		is_quotes(char c);
int		strchr_quotes(char *str);
t_list	*wspace_split(char *line, int start, int end, int quotes);
int		is_wspace(char c);
int		strchr_wspace(char *str);
t_list	*metachar_split(t_list *lex_slist);
int		is_metachar(char c);
int		check_metachar(char *content);
void	create_nodes(t_prime *data, t_list *lex_mlist);
void	lexer_add_node(t_lexer **lexer, char *str, int type);
int		syntax_check(t_prime *data);
void	type_init(t_prime *data);

void	free_lexer(t_lexer **lexer);
void	print_lexer(t_prime *data);

//*------EXPANDER-------*//

void	expander(t_prime *data);
char	*quotes_trim(char *content, int *end, char quotes);
char	*d_quotes_expand(t_prime *data, char *content, int *end, int *env);
char	*straight_expand(t_prime *data, char *content, int *end, int *env);
char	*dollar_analysis(char *content, int *end, t_prime *data, int *env);
int		special_chars(char c);
int		ret_null(char c);
int		put_directly(char c, int *i);
int		put_synerror(char c);
int		special_chars(char c);
void	expander_add_node(t_expander **expan, char *str, t_lexer *lex, int env);
int		null_check_substr(char *substr, char *joinedstr);

void	free_expander(t_expander **expander);
void	print_expander(t_prime *data);

//*------PARSER-----*//

void	parser(t_prime *data);
int		pipe_count(t_prime *data);
void	parser_addnode(t_parser **parser, int pipe_count);
void	heredoc_init(t_prime *data);
void	renew_parser(t_prime *data);
int		infile_init(t_expander *expander, t_parser *parser, t_prime *data);
int		outfile_init(t_expander *expander, t_prime *data, t_parser *parser);
void	files_add_node(t_files **files, char *name, int type, int fd);

void	free_parser(t_parser **parser);
void	print_parser(t_prime *data);

//*------EXEC-----*//

void	executer(t_prime *data, int i);
void	open_pipes(t_prime *data);
void	fd_closer(t_prime *data);
void	wait_all(t_prime *data, int builtin);
int		check_builtin(t_prime *data, t_parser *parser);

void	run_builtin(t_prime *data, t_parser *parser, int cmd_type, int i);
void	dup_stdio(t_prime *data, t_parser *parser, int i);
void	run_execve(t_prime *data, t_parser *parser, int i, int builtin);
char	*get_command(t_prime *data, t_parser *parser);
char	**get_env_cpy(t_prime *data);

void	run_echo(t_prime *data, t_parser *parser);
void	run_env(t_prime *data, t_parser *parser);
void	run_exit(t_prime *data, t_parser *parser);
void	run_pwd(t_prime *data, t_parser *parser);
void	run_export(t_prime *data, t_parser *parser);
void	run_unset(t_prime *data);
void	run_cd(t_prime *data);

void	cd_one_arg(t_prime *data);
void	cd_two_arg(t_prime *data);
int		change_dir(t_prime *data, char *parameters);
int		update_pwd_from_export(t_prime *data, char *pwd_name,
			char *pwd_content);
void	delete_env(t_prime *data, char *name);
int		get_env_name_count(char *env_arg);
char	*get_env_name(char *content);
void	single_export_arg(t_prime *data, t_parser *parser);
void	double_export_arg(t_prime *data, char *env_cmd);
int		change_env(t_prime *data, char *envname, char *arg, int is_equal);
int		env_arg_control(t_prime *data, char *env);
int		update_env(t_prime *data, char *env_name, char *new_arg);
int		env_name_control(char *env);
void	add_newenv(t_prime *data, char *env);
char	*get_oldpwd(t_env_l *env, char *path);
int		search_path(t_env_l *env_l, char *str);

//*---------UTILS------*//

int		synerr_print(t_prime *data, char *str, int f);
void	file_error(char *str, char *filename, int *fd, t_prime *data);
int		command_error(char *arg, char *cmd, char *str, t_prime *data);
int		ownstrcmp(char *s1, char *s2);
void	double_str_free(char **str);
char	**dynamic_malloc(char **path, char *new_str);
int		parameters_count(char **str);
void	*free_null(void *str);
int		stat_check(t_prime *data, char *cmd);
char	*get_line(int fd);

#endif