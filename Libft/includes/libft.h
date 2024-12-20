/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:01:12 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/12/08 17:16:03 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>

# define STR_START 1
# define STR_MIDDLE 2
# define STR_END 4

/*	string functions	*/
int		ft_strncmp(char *str1, char *str2, int bytes);
int		ft_strlcat(char *dst, char *src, int dstsize);
int		ft_strfcat(char *dst, char *src, int dstsize, int from);
//void	ft_memset(void *dir, int c, size_t bytes);
void	ft_bzero(void *dir, size_t bytes);
char	*ft_strchr(char *str, int c);
char	*ft_strrchr(char *str, int c);
char	*ft_itoa(int num);
char	*ft_substr(char *str, int start, int bytes);
/*	length	functions	*/
int		ft_intlen(int nbr);
int		ft_splitlen(char **split);
int		ft_strlen(char *str);
int		ft_arraylen(void *array);
int		get_length_array(char *var);
/*	mallocers functions	*/
void	*ft_calloc(int count, int size);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *str1, char *str2);
char	*ft_threejoin(char *str1, char *str2, char *str3);
char	*ft_splitjoin(char **split);
char	*ft_multiplejoin(int num, ...);
/*	array functions		*/
void	*add_dir(void *array, void *dir);
int		*add_integer(int *array, int len, int to_add);
void	*add_array_to_array(void *array, void *to_add, void *position);
void	*remove_dir(void *array, void *to_remove);
/*	search functions	*/
char	*search_word_in_split(char *word, char **split, int bytes);
char	*search_word_in_str(char *word, char *str, int bytes);
char	*search_word_in_start(char *word, char *str, int bytes);
char	*search_word_in_middle(char *word, char *str, int bytes);
char	*search_word_in_end(char *word, char *str);
/*	is_identifiers functions	*/
int		ft_isdigit(int c);
int		ft_isupper(int c);
int		ft_islower(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isspace(int c);
int		ft_isprint(int c);
int		ft_isacsii(int c);
/*	split functions	*/
void	print_split(char **split);
char	**split_for_each(char **split, char *(*fun)(char *));
char	**split_for_each_aux(char **split, void *aux,
			char *(*fun)(char *, void *));
char	**ultra_split_for_each_aux(char **split, void *aux,
			char **(*fun)(char *, void *));
void	free_split(char **split);
void	free_split_save(char **split, char *save);
char	*no_skip(char *str);
char	*skip_spaces(char *str);
char	*next_string(char *str);
char	*next_word(char *str);
char	*next_simple_word(char *str);
char	**ultra_split(char *str, char *(*skip)(char *), char *(*next)(char *));
char	**ft_split(char *str);
char	**ft_split_char(char *str, char *separator);
char	**ft_splitdup(char **split);
/*	list functions	*/
void	lst_add_back(void *list, void *node);
void	lst_add_front(void *list, void *node);
void	lst_clear(void *list, void (*del)(void *));
void	lst_for_each(void *list, void (*func)(void *));
/*	extra functions	*/
int		fd_printf(int fd, const char *str, ...);
void	error_printf(int error, char *str, ...);
char	*get_next_line(int fd);
void	dont(char null, ...);

#endif
