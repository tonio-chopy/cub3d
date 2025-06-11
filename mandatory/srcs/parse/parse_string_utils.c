/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio-chopy <tonio-chopy@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 07:07:00 by tonio-chopy       #+#    #+#             */
/*   Updated: 2025/06/11 07:07:00 by tonio-chopy      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char	*trim_whitespace(char *str)
{
	char	*end;

	if (!str)
		return (NULL);
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == 0)
		return (str);
	end = str + ft_strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t'))
		end--;
	end[1] = '\0';
	return (str);
}
