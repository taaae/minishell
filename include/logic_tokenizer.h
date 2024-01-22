/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_tokenizer.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 20:46:15 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/22 21:22:37 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGIC_TOKENIZER
# define LOGIC_TOKENIZER

typedef enum e_logic_tok_type{
	OPEN_PAR = 1,
	CLOS_PAR = 2,
	OR_SYM = 3,
	AND_SYM = 4,
	SCRIPT_STR = 5
}	t_logic_tok_type;

typedef struct s_logic_token {
	t_logic_tok_type	type;
	char				*strrepr;
}	t_logic_token;

#endif

**