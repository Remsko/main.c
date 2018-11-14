/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poly_pocket.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 16:40:11 by mbeilles          #+#    #+#             */
/*   Updated: 2018/11/14 17:38:16 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef enum			e_type {
	E_STRUCT_TYPE_DEF	= 0,
	E_STRUCT_TYPE_OTHER
}						t_type;

typedef struct			s_default {
	t_type				type;
	void				*data;
	uint32_t			different_data;
}						t_default;

typedef struct			s_other {
	t_type				type;
	void				*data;
	uint32_t			footer;
	float				some_other_data;
}						t_other;

typedef union			u_what {
	t_default			def;
	t_other				other;
	t_type				type;
}						t_what;


/*
 * Disclaimer: This kinda advanced
 *
 * One of the main fascination in C for me is the fact that any data is just some
 * chain of number that you choose to understand the way you want.
 * And tagged union are a good way to summerise this.
 *
 * But there is a caveat the union always takes up the size of the biggest member.
 *
 * If you want a way to visualize `t_what`:
 *    t_type:     { type }
 *    t_default:  { type | data }
 *    t_other:    { type | data | footer | some_other_data}
 *
 * So it takes up the size of `t_other` (check it with sizeof comparison)
 * And so it's effectively the same thing as to do (float)((void*)int)
 * to get what the raw data from an int is in a float interpretation.
 *
 * It's really useful in graphs btw.
*/

void					print_what_array(t_what whats[], uint32_t len) {
	for (uint32_t i = 0; i < len; i++)
		switch (whats[i].type) {
			case E_STRUCT_TYPE_DEF:
				printf("\tElem [%i]: default: '%u' '%p' '%u'\n", i, whats[i].def.type, whats[i].def.data, whats[i].def.different_data);
				break;
			case E_STRUCT_TYPE_OTHER:
				printf("\tElem [%i]: other: '%u' '%p' '%u' '%f'\n", i, whats[i].other.type, whats[i].other.data, whats[i].other.footer, whats[i].other.some_other_data);
				break;
		}
}

int						main(int c, char **v) {
	static t_what		whats[2] = {
		(t_what){(t_default){E_STRUCT_TYPE_DEF, NULL}},
		(t_what){.other=(t_other){E_STRUCT_TYPE_OTHER, (void*)0x33, 23u, 12u}}
	};

	/* There we print the value of the tagged union */
	printf("Printing array");
	print_what_array(whats, sizeof(whats) / sizeof(t_what));
	printf("\n");

	printf("Modifying some data\n");
	whats[0].other.footer = 42u;
	whats[0].other.some_other_data = 21.0f;
	print_what_array(whats, sizeof(whats) / sizeof(t_what));
	printf("\n");

	printf("Printing the array interpreted as `t_default`\n");
	for (uint32_t i = 0; i < sizeof(whats) / sizeof(t_what); i++)
		printf("\tElem [%i]: default: '%u' '%p' '%u'\n", i, whats[i].def.type, whats[i].def.data, whats[i].def.different_data);
	printf("\n");

	printf("Printing the array interpreted as `t_other`\n");
	for (uint32_t i = 0; i < sizeof(whats) / sizeof(t_what); i++)
		printf("\tElem [%i]: other: '%u' '%p' '%u' '%f'\n", i, whats[i].other.type, whats[i].other.data, whats[i].other.footer, whats[i].other.some_other_data);
	printf("\n");

	printf("Show the modification by changing type\n");
	whats[0].type = E_STRUCT_TYPE_OTHER;
	print_what_array(whats, sizeof(whats) / sizeof(t_what));
}
