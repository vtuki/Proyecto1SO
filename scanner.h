#ifndef SCANNER_H
#define SCANNER_H

struct token_s
{
    struct source_s *src;       // fuente del input
    int    text_len;            // largo del texto de token
    char   *text;               // texto de token
};

// EOF indica el fin del token
extern struct token_s eof_token;

struct token_s *tokenize(struct source_s *src);
void free_token(struct token_s *tok);

#endif
