/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_tok_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:02:58 by lporoshi          #+#    #+#             */
/*   Updated: 2024/01/23 14:48:09 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logic_tokenizer.h"
#include "libft.h"

void	show_ltres(t_logic_token **tokens)
{
	int	i;

	i = 0;
	if (tokens == NULL)
	{
		ft_printf("(null)");
		return ;
	}
	while (tokens[i] != NULL)
	{
		if (tokens[i]->type != SCRIPT_STR)
			ft_printf("ø");
		else
			ft_printf("%s", tokens[i]->strrepr);
		i++;
	}
	ft_printf("\n");
}

int	main(void)
{
	char *s[] = {
"echo \"> >> < * ? [ ] | ; [ ] || && ( ) & # $ \\ <<",
"echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $ \\ <<'",
"mkdir testdirtest;cd testdirtest;bash;cd .. && rm -rf testdirtest && exit;pwd;cd .;pwd@rm -rf actual dir and cd .",
"(cat < noperm && echo hi);echo $?",
"(cat < noperm && echo hi)",
"(cat < noperm || echo hi);echo $?",
"(cat < noperm || echo hi)",
"(cat && echo hi) < noperm;echo $?",
"(cat && echo hi) < noperm",
"(cat || echo hi) < noperm;echo $?",
"(cat || echo hi) < noperm;",
"(cat || echo hi) < noperm && echo hii;echo $?",
"(cat || echo hi) < noperm && echo hii;",
"(cat || echo hi) < noperm || echo hii;echo $?",
"(cat || echo hi) < noperm || echo hii;",
"(echo hola | cat -e) > file1;cat file1;rm file1@(echo hola | cat -e) > file1",
"(echo hola && echo adios) > file1;cat file1;rm file1@(echo hola && echo adios) > file1",
"echo hola && (echo adios) >> file1;cat file1;rm file1@echo hola && (echo adios) >> file1",
"(echo hola) > file1;cat file1;rm file1@(echo hola) > file1",
"(echo hola) > file1 >> file2 > file3;ls;cat file3;rm file1 file2 file3@(echo hola) > file1 >> file2 > file3",
"(echo hola > file1 && echo adios | cat -e) > file1;ls;cat file1@(echo hola > file1 && echo adios | cat -e) > file1 ",
"(echo hola > file1) > file2;ls;cat file1;rm file1 file2@(echo hola > file1) > file2",
"(echo hola > file1 && asdfs) 2> file2;cat file2 | rev | cut -c 1-20 | rev@(echo hola > file1 && asdfs) 2> file2",
"(echo hola > file1 && asdfs) 2>file2;cat file2 | rev | cut -c 1-20 | rev@(echo hola > file1 && asdfs) 2>file2",
"(echo hola > file1 && asdfs)2> file2;cat file2 | rev | cut -c 1-20 | rev@(echo hola > file1 && asdfs)2> file2",
"(echo hola > file1 && asdfs)2>file2;cat file2 | rev | cut -c 1-20 | rev@(echo hola > file1 && asdfs)2>file2",
"(echo hola > file1) a> file2@(echo hola > file1) a> file2",
"echo hola && echo adios || echo noejecuta && echo si ejecuta",
"echo hola && echon adios || echo siejecuta && echo fin",
"ls | ( cat -e && cat -n ) | cat -n",
"(ls | ( cata -e && cat -n ) | cat -e) && echo success",
"export A=mivalor && echo $A",
"(export A=mivalor) && echo $A",
"export A=mivalor && (unset A) && echo$A",
"echo hola | (cat -n | (cat -e && echo inception) && echo adios | (cat -n | (cat -e)))@mix () || && and &",
"echo \"&&\"  echo hi",
"echo \"&&\"  echo hi",
"echo \"||\"  echo hi",
"echo \"|\"|  echo hi",
"echo \" |\"|  echo hi",
"echo \"()|&&))(\"",
"	echo hi		||	echo hi@\\techo hi\\t\\t||\\techo hi",
"	echo hi		&&	echo hi@\\techo hi\\t\\t&&\\techo hi",
"	echo hi		&&	(		echo hi&&          echo hi)@\\techo hi\\t\\t&&\\t(\\t\\techo hi&&          echo hi)",
"< | a",
"> | a",
">> | a",
"| < a",
"| > a",
"| >> a",
"< && a",
"> && a",
">> && a",
"(echo hi && exit)",
"(exit && echo hi)",
"(cmdnotfound || exit)",
"(exit || echo hi)",
"(echo hola) && exit",
"(echo hola) && exit",
"(echo hola && (exit))",
"((exit) && echo hola)",
"export A=\"adios\" && (export A=\"hola\" && echo $A) && echo $A",
"export A=\"adios\" && (unset A) && echo $A",
"ls && (unset PATH) && ls",
"echo hola&& echo adios",
"echo hola &&echo adios",
"echo hola && echo adios",
"echo a&& b&&echo c&& echo k&& echo z",
"echo a && echo b&& echo c &&echo d  &&   echo e   &&echo f&&   echo g@&& with spaces",
"ls doesnotexists&& echo adios",
"echo hola&& ls doesnotexists",
"export _TEST=\"=\\| >> << | '' < > && ||\" \n unset _TEST \n export | grep _TEST",
NULL}
;
	t_logic_token	**toks;
	
	int i = 0;
	while (s[i] != NULL)
	{
		ft_printf("----------\n[%s]->\n", s[i]);
		toks = logic_split(s[i]);
		show_ltres(toks);
		ft_printf("---------\n");
		i++;
	}
	return (0);
}
