/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:44:40 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/02 13:05:52 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>
# include <fcntl.h>

struct s_data
{
	size_t	i;
	size_t	j;
	size_t	start;
};
struct s_joinvars
{
	int		full_len;
	int		i;
	int		j;
	char	*res;
};
struct s_data1
{
	int		i;
	int		j;
	int		len;
	char	*line;
	char	*buffer;
	int		read;
	char	*ln;
	int		k;
	int		b;
};

/*LIBFT*/
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/*FT_PRINTF*/

# ifdef __linux__
#  define PTRNULL "(nil)"
# endif

# ifdef __APPLE__
#  define PTRNULL "0x0"
# endif

int		ft_which(va_list args, const char type);
int		ft_printf(const char *str, ...);
int		ft_putstr(char *str);
int		ft_putchar(int c);
int		ft_putnbr_dec(int n);
int		ft_putnbr_int(int n);
int		ft_putnbr_base_hex_low(unsigned int nbr, const char type);
int		ft_putnbr_base_hex_up(unsigned int nbr, const char type);
int		ft_putpercent(void);
int		ft_putptr(unsigned long long ptr);
int		ft_putunsigned(unsigned int nbr);

/*GET_NEXT_LINE*/

# define BUFFER_SIZE 4096

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *leftov_str, char *line);

int		ft_strlen2(char *str);
char	*ft_strchr2(char *str, int c);
char	*ft_strjoin4(char *str, char *buf);
char	*ft_new(char *str);
char	*ft_helper_strhoin(char *str);

#endif
