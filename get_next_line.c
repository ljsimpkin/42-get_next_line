/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimpkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 08:20:47 by lsimpkin          #+#    #+#             */
/*   Updated: 2019/01/25 08:20:49 by lsimpkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_newline(char **str, int ret, char **place, int fd)
{
	int		rd;
	char	*tmp;
	char	*buf;

	rd = 0;
	buf = ft_strnew(BUFF_SIZE + 1);
	while ((ft_strchr(*str, '\n') == 0) && (rd = read(fd, buf, BUFF_SIZE)) != 0)
	{
		buf[rd] = '\0';
		tmp = *str;
		*str = ft_strjoin(*str, buf);
		ft_strdel(&tmp);
		ret = 1;
		if (rd == -1)
			return (-1);
	}
	if ((*place = ft_strchr(*str, '\n')) != NULL)
	{
		**place = '\0';
		*place += 1;
		ret = 1;
	}
	free(buf);
	return (ret);
}

int	get_next_line(const int fd, char **line)
{
	int			ret;
	char		*str;
	static char	*place[FD_SIZE];

	ret = 0;
	str = ft_strnew(BUFF_SIZE + 1);
	if (!line || 0 > fd || fd > FD_SIZE || BUFF_SIZE < 0)
		return (-1);
	if (place[fd])
	{
		str = ft_strcpy(str, place[fd]);
		if (place[fd][0] != '\0')
			ret = 1;
	}
	ret = ft_newline(&str, ret, &place[fd], fd);
	*line = (str);
	return (ret);
}
