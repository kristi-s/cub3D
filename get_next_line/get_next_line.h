/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 19:28:46 by droslyn           #+#    #+#             */
/*   Updated: 2020/11/13 16:17:01 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define BUFFER_SIZE 16

int			get_next_line(int fd, char **line);
char		*ft_get_line(char *str);
int			ft_findpref(char *str);
char		*ft_get_remem(char *str);
int			ft_strsepar(char **line, char **remem, int n_rd);
int			ft_memsearch(char *mem);
int			ft_free(char *mem1, char *mem2);
size_t		ft_strlen(char *s);
char		*ft_strjoin(char *s1, char *s2);

#endif
