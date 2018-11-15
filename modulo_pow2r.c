/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modulo_pow2r.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 17:52:11 by mbeilles          #+#    #+#             */
/*   Updated: 2018/11/15 11:14:11 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * This function there is rather intresting but we need to explain it visualy:
 *
 * If let `i` be an int and imagine that it is a power of 2.
 *    Considering the way that a discrete number is encoded in most languages
 *    there should only be one bit set to 1.
 *
 * If `i` is not a power of 2 then there will be more than one bit set to 1 and
 *    so masking it by itself - 1 will make the `more` part appear and that's
 *    why we compare to 0.
 */


uint32_t		is_pow_2(int32_t n)
{
	return ((n & (n - 1)) == 0);
	// That comparison to 0 is not really mandatory
	// but improves the readability of your code and a decent compiler will
	// optimize that for you.
}

/*
 * Now if we want to make a pow 2 modulus this is not very different because
 *     we only want the part that is below the pow 2 so masking it with the
 *     pow 2 number - 1 makes that for us.
 */

int32_t				main(int32_t c, char **v)
{
	int32_t			n;
	int32_t			m;

	if (c < 3)
		return (-1);

	n = atoi(v[1]);
	m = atoi(v[2]);

	if (is_pow_2(m))
		printf("%i %% %i = %i\n", n, m, n & (m - 1));
	else
		printf("Arg [ 2 ] is not to the pow of 2\n");
}
