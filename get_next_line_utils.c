#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t len;

	if(!s)
		return (0);
	len = 0;
	while(s[len] != '\0')
		len++;
	return len;
}

char	*ft_strchr(char *s, int c)
{
	int i;

	if(!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if(s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	if(c == '\0')
		return (&s[i]);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3 = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!s3)
		return(NULL);
	i = 0;
	while (*s1)
		s3[i++] = *s1++;
	while (*s2)
		s3[i++] = *s2++;
	s3[i] = '\0';
	return (s3);
}


