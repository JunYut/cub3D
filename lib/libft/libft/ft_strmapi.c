/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:36:31 by tjun-yu           #+#    #+#             */
/*   Updated: 2025/01/02 14:55:02 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_str;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	new_str = (char *)mem_alloc((ft_strlen(s) + 1) * sizeof(char));
	if (new_str == NULL || f == NULL)
		return (NULL);
	i = -1;
	while (++i < ft_strlen(s))
		new_str[i] = f(i, s[i]);
	new_str[i] = 0;
	return (new_str);
}

/*
int	main(void)
{

}
*/
