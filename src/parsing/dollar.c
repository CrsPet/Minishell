# include "minishell.h"

int	ifkey(char c)
{
	if (c == '_' || ft_isalnum(c) || c == '*' || c == '!')
		return (1);
	return 0;
}

char	*concat_str_value(char *str, char *value, int j, int *i)
{
	char	*line_new;
	char	*tmp1;
	char	*tmp2;
	void	*tmp3;

	if (!value)
	{
		tmp1 = ft_substr(str, 0, j);
		tmp2 = ft_strdup(&str[*i]);
		line_new = ft_strjoin(tmp1, tmp2);
		*i = j - 1;
	}
	else
	{
		tmp1 = ft_substr(str, 0, j);
		tmp2 = ft_strjoin(tmp1, value);
		tmp3 = (char *)ft_strdup(&str[*i]);
		line_new = ft_strjoin(tmp2, tmp3);
		*i = j + ft_strlen(value) - 1;
		free(tmp3);
	}
	free(tmp1);
	free(tmp2);
	free(str);
	return (line_new);
}

char *envp_value(char *key, char **envp)
{
	int z = 0;
	int	k = -1;
	char *value;

	while (envp[++k])
	{
		z = 0;
		if (ft_strnstr(envp[k], key, ft_strlen(key)))
		{
			while (envp[k][z] && envp[k][z] != '=')
				z++;
			value = ft_substr(envp[k], 0, z);
			if (z == (int)ft_strlen(key))
			{
				value = ft_substr(envp[k], z + 1, ft_strlen(envp[k]) - z);
				return value;
			}
		}
	}
	return NULL;
}

char	*ft_dollar(char *str, int *i, char **envp)
{
	char	*key;
	char	*value;
	int		j;

	j = *i;
	while (str[++(*i)])
	{
		if (!ifkey(str[*i]))
			break ;
	}
	if (*i == j + 1)
		return (str);
	key = ft_substr(str, j + 1, *i - j - 1);
	value = envp_value(key, envp);
	value = concat_str_value(str, value, j, i);
	free(key);
	return (value);
}