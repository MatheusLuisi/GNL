#include "get_next_line.h"

static char	*read_file(int fd)
{
	int		bytes_read;
	char	*tmp_buffer;

	tmp_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp_buffer)
		return (NULL);
	bytes_read = read(fd, tmp_buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(tmp_buffer);
		return (NULL);
	}
	tmp_buffer[bytes_read] = '\0';
	return (tmp_buffer);
}

static char	*extract_line(char *static_buf)
{
	size_t	i;
	size_t	line_len;
	char	*line;
	char	*newline;

	if (!static_buf)
		return (NULL);
	newline = ft_strchr(static_buf, '\n');
	if (newline)
		line_len = newline - static_buf + 1;
	else
		line_len = ft_strlen(static_buf);
	line = malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < line_len)
	{
		line[i] = static_buf[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*update_rest(char *static_buf)
{
	char	*start;
	char	*rest;

	if (!static_buf)
		return (NULL);
	start = ft_strchr(static_buf, '\n');
	if (!start)
	{
		free(static_buf);
		return (NULL);
	}
	rest = ft_strjoin("", ++start);
	free(static_buf);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*static_buf;
	char		*tmp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (ft_strchr(static_buf, '\n') == NULL)
	{
		tmp = read_file(fd);
		if (!tmp)
			break ;
		line = ft_strjoin(static_buf, tmp);
		free(tmp);
		if (static_buf)
			free(static_buf);
		static_buf = line;
	}
	if (!static_buf)
		return (NULL);
	line = extract_line(static_buf);
	static_buf = update_rest(static_buf);
	return (line);
}
