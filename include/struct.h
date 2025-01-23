
#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_env_l
{
	char			*name;
	char			*content;
	struct s_env_l	*next;
}					t_env_l;

typedef struct s_lexer
{
	char			*content;
	int				type;
	struct s_lexer	*next;
}					t_lexer;

typedef struct s_expander
{
	char				*content;
	int					type;
	int					env;
	char				*ex_content;
	struct s_expander	*next;
}						t_expander;

typedef struct s_fd
{
	int	infile;
	int	outfile;
}		t_fd;

typedef struct s_files
{
	char				*filename;
	int					re_type;
	int					fd;
	struct s_files		*next;
}						t_files;

typedef struct s_parser
{
	char			*command;
	char			**parameters;
	char			*heredoc;
	int				infile;
	int				outfile;
	pid_t			pid;
	t_files			*file;
	struct s_parser	*next;
}					t_parser;

typedef struct s_prime
{
	char		*line;
	char		**path;
	t_lexer		*lexer;
	t_env_l		*env_l;
	t_expander	*expander;
	t_parser	*parser;
	int			exit_code;
	int			cmd_count;
	int			**fd;
}				t_prime;

#endif
