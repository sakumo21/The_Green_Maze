#include "../cub3D.h"

int	only_num(char *s)
{
	int	i;
	int	num;

	i = 0;
    if (s[i] == '+' || s[i] == '-')
    {
        return (printf("Error: No sign allowed!\n"), 1);
    }
	num = ft_atoi(&s[i]);
	if (num == -1)
	{
		return (printf("Error : (%s), Only digits!\n", s), 1);
	}
	return (0);
}

int validate_values(char **p)
{
    int i = 0;

    while (i <= 2)
    {
        if (only_num(p[i]))
            return (free_range(p, 0), 1);
        i++;
    }
    return (0);
}

int check_value_range(char **p)
{
    if ((ft_atoi(p[0]) < 0 || ft_atoi(p[0]) > 255) ||
        (ft_atoi(p[1]) < 0 || ft_atoi(p[1]) > 255) ||
        (ft_atoi(p[2]) < 0 || ft_atoi(p[2]) > 255))
    {
        free_range(p, 0);
        printf("Error : RGB range is between 0 and 255\n");
        return (1);
    }
    return (0);
}

int check_extra_values(char **p)
{
    if (p[3] || p[2][0] == '\n' || p[2][0] == '\0')
    {
        free_range(p, 0);
        printf("Error : Expected 3 RGB values [..., ..., ...].\n");
        return (1);
    }
    return (0);
}

char *ft_strjoin_three(char *s1, char *s2, char *s3)
{
    char *tmp;
    char *result;

    tmp = ft_strjoin(s1, s2);
    if (!tmp)
        return (NULL);
    result = ft_strjoin(tmp, s3);
    free(tmp);
    return (result);
}


void set_set(char *line, char **p, t_data *img)
{
    char *tmp;

    if (line[0] == 'F')
    {
        tmp = ft_strjoin_three(p[0], ",", p[1]);
        img->floor = ft_strjoin_three(tmp, ",", p[2]);
        free(tmp);
    }
    else if (line[0] == 'C')
    {
        tmp = ft_strjoin_three(p[0], ",", p[1]);
        img->ceiling = ft_strjoin_three(tmp, ",", p[2]);
        free(tmp);
    }
}


int check_range(char *line, t_data *img)
{
    char **p;
    char *trimmed;
    char *tmp;
    char *new;
    new = line + 2;
    p = ft_split(new, ',');
    if (!p || !p[0] || !p[1] || !p[2] || (!p[2] && !p[2][0]) || (p[2] && p[2][0] == '\n'))
    {
        free_range(p, 0);
        printf("Error : Expected 3 RGB values [..., ..., ...].\n");
        return (1);
    }
    //if(p[0] && p[1] && p[2] )
        tmp = p[2];
        p[2] = ft_strtrim(p[2], "\n");
        free(tmp);
    // printf("p[2] = (%s)\n", p[2]);
    if (p[2][0] != '\0')
    {
        trimmed = ft_strtrim(p[2], "\n");
        if (!trimmed)
            return (free_range(p, 0), 1);
        free(p[2]);
        p[2] = trimmed;
    }

    if (validate_values(p) || check_extra_values(p) || check_value_range(p))
        return (1);
    set_set(line, p, img);
    free_range(p, 0);
    return (0);
}
