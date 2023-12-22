#include "unity.h"
#include "lexer.h"
#include "libft.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_lexer(void) {
	TEST_ASSERT_EQUAL(NULL, line_to_tokens(NULL));
	char	*line = "echo ./*";
	t_list	*res = line_to_tokens(line);
	TEST_ASSERT_NOT_EQUAL(NULL, res);
	t_token	*tok = (t_token *)(res->content);
	TEST_ASSERT_NOT_EQUAL(NULL, tok);
	TEST_ASSERT_TRUE(0 == ft_strcmp("echo", tok->token_string));
	TEST_ASSERT_EQUAL(tok->type, TOK_WORD);
	TEST_ASSERT_EQUAL(tok->token_len, 4);
	tok = (t_token *)(res->next->content);
	TEST_ASSERT_TRUE(0 == ft_strcmp("./*", tok->token_string));
	TEST_ASSERT_EQUAL(tok->type, TOK_WORD);
	TEST_ASSERT_EQUAL(tok->token_len, 3);
	TEST_ASSERT_NOT_EQUAL(NULL, line_to_tokens("non-null line"));
}
