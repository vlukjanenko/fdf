/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:43:15 by majosue           #+#    #+#             */
/*   Updated: 2020/01/12 19:09:02 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi_base(const char *nbr, unsigned int base)
{
	long	r;
	int		sign;
	char	d;

	if (base > 16 || base < 2)
		return (0);
	r = 0;
	while (*nbr == '\t' || *nbr == '\n' || *nbr == '\v' || *nbr == '\f' ||\
	*nbr == '\r' || *nbr == ' ')
		nbr++;
	sign = (*nbr == '+' || *nbr == '-') ? 44 - *nbr++ : 1;
	if (base <= 10)
		while ((d = *nbr++) >= '0' && d <= '0' + (int)base)
			r = r * base + d - '0';
	if (base > 10)
	{
		while (((d = *nbr++) >= '0' && d <= '9') || (d >= 'A' && d <= 'A' +\
		((int)base - 10)) || (d >= 'a' && d <= 'a' + ((int)base - 10)))
		{
			r = (d <= '9') ? r * base + d - '0' : r;
			r = (d >= 'A' && d <= 'F') ? r * base + d - 'A' + 10 : r;
			r = (d >= 'a' && d <= 'f') ? r * base + d - 'a' + 10 : r;
		}
	}
	return (r * sign);
}
