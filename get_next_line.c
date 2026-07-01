#include "get_next_line.h"

static char	*read_file(int fd)
{
	int bytes_read;
	char *tmp_buffer;

	tmp_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if(!tmp_buffer)
		return (NULL);
	bytes_read = read(fd, tmp_buffer, BUFFER_SIZE);
	if(bytes_read <= 0)
		return (free(tmp_buffer), NULL);
	tmp_buffer[bytes_read] = '\0';
	return tmp_buffer;
}

static char *extract_line(char *static_buf)
{
	size_t	i;
	size_t	line_len;
	char	*line;
	char	*newline;
	
	if(!static_buf)
		return (NULL);
	newline = ft_strchr(static_buf, '\n');
	if(newline)
		line_len = newline - static_buf + 1;
	else 
		line_len = ft_strlen(static_buf);
	line = malloc(sizeof(char) * (line_len + 1));
	if(!line)
		return (NULL);
	i = 0;
	while(i < line_len)
		line[i++] = *static_buf++;
	line[i] = '\0';
	return (line);
}

static char *update_rest(char *static_buf)
{
	size_t	i;
	size_t	rest_size;
	char	*start;
	char	*newline;
	char	*rest;

	if (!static_buf)
		return (NULL);
	newline = ft_strchr(static_buf, '\n');
	if (!newline)
		return (free(static_buf), NULL);
	start = newline + 1;
	rest_size = ft_strlen(start);
	rest = malloc(sizeof(char) * (rest_size + 1));
	if (!rest)
		return (free(static_buf), NULL);
	i = 0;
	while (*start)
		rest[i++] = *start++; 
	rest[i] = '\0';
	return (free(static_buf), rest);
}

char *get_next_line(int fd)
{
    static char *static_buf;
    char        *tmp;
    char        *line;

	if(fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (ft_strchr(static_buf, '\n') == NULL)
	{
        tmp = read_file(fd);
        if (tmp == NULL)
            break ;
	if (!static_buf)
		static_buf = ft_strjoin("", tmp);
	else
        	static_buf = ft_strjoin(static_buf, tmp);
        free(tmp);
    }
    if (!static_buf)
        return (NULL);
    line = extract_line(static_buf);
    static_buf = update_rest(static_buf);
    return (line);
}
