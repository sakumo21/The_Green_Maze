/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:03:48 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/25 10:16:16 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strtrim(char const *s1, char const *set)
// {
// 	size_t	size;
// 	size_t	start;
// 	size_t	end;
// 	char	*p;

// 	size = 0;
// 	start = 0;
// 	printf("s1 : (%s)\n", s1);
// 	if (!s1 || !set)
// 		return (NULL);
// 	end = ft_strlen(s1) - 1;
// 	while (s1[start] && ft_strchr(set, (char)s1[start]))
// 		start++;
// 	while (s1[end] && ft_strrchr(set, s1[end]))
// 		end--;
// 	size = end - start + 1;
// 	printf("size : %zu\n", size);
// 	p = ft_substr(s1, start, size);
// 	if (!p)
// 		return (0);
// 	return (p);
// }

char    *ft_strtrim(char const *s1, char const *set)
{
    size_t    start;
    size_t    end;
    size_t    ns1;
    char    *str;

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