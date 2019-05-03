/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_o.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:37:23 by oivanyts          #+#    #+#             */
/*   Updated: 2019/01/14 16:27:16 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 150

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <wchar.h>
# include <stdbool.h>
# include <float.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct	{
	char			flag[5];
	int				whidth;
	int				precs;
	char			mods;
	char			type;
}					t_format;

typedef struct {
	unsigned int	y;
	unsigned int	x;
}					t_dot;

union				u_some{
	char			str[16];
	double			d;
	long double		l_d;
	long long int	l_i;
}					u_ni;

extern const char	*g_colortab[9];

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strndup(const char *s1, size_t n);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
		size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isprint(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isalpha(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(long long int n);
int					ft_putchar(wchar_t c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstaddback(t_list **alst, t_list *new);
void				ft_lstaddhere(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_isspace(char c);
size_t				ft_countletter(const char *s, char c);
size_t				ft_countwords(const	char *s, char c);
char				*ft_itoa_base(int n, int base);
void				ft_swap(int *a, int *b);
void				**ft_matrixalloc(size_t width, size_t length, size_t buf);
int					get_next_line(const int fd, char **line);
int					ft_num_size(long long int num);
unsigned int		ft_atoi_hex(const char *str);
void				ft_swap_d(double *a, double *b);

int					ft_max_number(int a, int b, int c);
int					ft_printf(const char *format, ...);
char				*ft_strnum_base(unsigned long long int n, int base,
									t_format fx);
size_t				ft_strlen_u(wchar_t *str);
char				*ft_itoa_prntf(long long int n, t_format fx);
char				*ft_itoa_double(long double num, t_format fx);
long double			ft_round_double(long double num, int precision);
long double			ft_exp(int num, int exp);
int					ft_putchar_u(int c, int fd);
int					ft_putstr_u(wchar_t *s, int fd);
wchar_t				*ft_strndup_u(wchar_t *src, size_t n);
int					ft_charlen(wchar_t c);
int					ft_parcer_printf(const char **str, va_list arg, int fd);
void				zero_struct(t_format *list);
int					formated_print(va_list arg, t_format fx, int fd);
int					format_char(va_list arg, t_format fx, int fd);
char				*form_numbers(va_list arg, t_format fx);
char				*ft_printbits(char *str, t_format fx);
char				*ft_check_color(const char *str);
void				ft_color_input(char *color);
int					ft_printf_fd(int fd, const char *format, ...);
void				ft_print_list(t_list *list);

#endif
