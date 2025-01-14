/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziel-hac <ziel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:03:48 by mlamrani          #+#    #+#             */
/*   Updated: 2025/01/10 16:03:59 by ziel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	ns1;
	char	*str;

	if (!s1 || !set)
		return (0);
	start = 0;
	end = ft_strlen(s1);
	ns1 = 0;
	while (end > start && ft_strchr(set, s1[start]) != 0)
		start++;
	if (end == start)
		return (ft_strdup(""));
	while (end > start && ft_strchr(set, s1[end]) != 0)
		end--;
	ns1 = end - start + 1;
	str = malloc(ns1 * sizeof(char) + 1);
	if (!str)
		return (0);
	while (str && start <= end)
		*str++ = s1[start++];
	*str = '\0';
	return (str - ns1);
}
// int main()
// {
//     // char space = " ";
//     char s1[] = "lorem \n ipsum \t dolor \n sit \t amet";
//     printf("%s", ft_strtrim(s1, " " ));
// }