/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esraa <esraa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:12:22 by ealshorm          #+#    #+#             */
/*   Updated: 2025/06/03 14:34:14 by esraa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	parse_digits(const char *str, int sign, long long *result)
{
	long long	res;
	int			i;
	int			digit;

	res = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		digit = str[i++] - '0';
		if (res > (LLONG_MAX - digit) / 10)
			return (0);
		res = res * 10 + digit;
	}
	*result = res * sign;
	return (1);
}

int	ft_atoll_safe(const char *str, long long *result)
{
	int	sign;
	int	i;

	sign = 1;
	i = 0;
	*result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (ft_strcmp((char *)(str + i), "-9223372036854775808") == 0)
	{
		*result = LLONG_MIN;
		return (1);
	}
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	if (!str[i])
		return (0);
	return (parse_digits(str + i, sign, result));
}

static int	ft_is_numeric(const char *str, long long *result)
{
	int	i;

	i = 0;
	if (!ft_atoll_safe(str, result))
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_no_args(char **args, t_env **env, t_cmd *cmd)
{
	int	status;

	status = (*env)->shell->exit_status;
	if (!args[1])
	{
		clean_all(cmd, *env);
		printf("exit\n");
		exit(status);
	}
}

void	my_exit(char **args, t_env **env, t_cmd *cmd)
{
	long long	exit_code;

	exit_code = 0;
	exit_no_args(args, env, cmd);
	if (args[1])
	{
		if (!ft_is_numeric(args[1], &exit_code))
		{
			printf("exit\n");
			ft_putendl_fd("minishell: exit: numeric argument required", 2);
			clean_all(cmd, *env);
			exit(2);
		}
		if (args[2])
		{
			printf("exit\n");
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			(*env)->shell->exit_status = 1;
			return ;
		}
	}
	clean_all(cmd, *env);
	printf("exit\n");
	exit((unsigned char)exit_code);
}
