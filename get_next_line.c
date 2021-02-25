# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# define BUFFER_SIZE 25

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > (unsigned int)strlen(s))
		len = 0;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

int			check_line(char *str)
{
	int i;

	i = 0;
	if (str != 0)
		while (str[i] != '\0')
		{
			if (str[i] == '\n')
				return (1);
			i++;
		}
	return (0);
}

int			make_line(char **grd, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	if (check_line(*grd) != 0)
	{
		while ((*grd)[i] != '\n')
			i++;
	}
	if (check_line(*grd))
	{
		tmp = *line;
		*line = ft_substr(*grd, 0, i);
		tmp = *grd;
		*grd = strdup(*grd + i + 1);
		free(tmp);
		return (1);
	}
	*line = strdup(*grd);
	free(*grd);
	*grd = NULL;
	return (0);
}

char		*ft_resize(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s2 != 0)
	{
		s = (char *)malloc(strlen(s2) + BUFFER_SIZE + 1);
		while (s2[i] != '\0')
		{
			s[i] = s2[i];
			i++;
		}
	}
	else
		s = (char *)malloc(BUFFER_SIZE + 1);
	while (s1[j] != '\0')
	{
		s[i] = s1[j];
		i++;
		j++;
	}
	s[i] = '\0';
	return (s);
}



int			get_next_line(int fd, char **line)
{
	char			*str;
	static char		*grd = 0;
	int				r;
	char			*tmp;

	str = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (grd == 0)
		grd = strdup("");
	while (!(check_line(grd)))
	{
		r = read(fd, str, BUFFER_SIZE);
		str[r] = '\0';
		tmp = grd;
		grd = ft_resize(str, grd);
		free(tmp);
		tmp = NULL;
		if (r == 0)
			break ;
	}
	free(str);
	str = NULL;
	return (make_line(&grd, line));
}
