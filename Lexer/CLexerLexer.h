#ifndef _C_LEXER_LEXER_H_
#define _C_LEXER_LEXER_H_
#pragma once

typedef struct _SimpleLinkedList* PSimpleLinkedList;

unsigned char* clexer_handle_token_type0_keyword(unsigned char* strcontent, unsigned char* keyword);
unsigned char* clexer_handle_token_type2_charset(unsigned char* strcontent, unsigned char* charset);
void clexer_print_escape(unsigned char* strs);
void clexer_handle_token(int index_token, char* value, char* name);
PSimpleLinkedList clexer_handle_c_file_content(char* fullpath, char* path, char* filename, char* ext, unsigned char* strcontent, unsigned long long size);

#endif //_C_LEXER_LEXER_H_
