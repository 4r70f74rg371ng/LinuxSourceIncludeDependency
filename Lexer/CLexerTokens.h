#ifndef _C_LEXER_TOKENS_H_
#define _C_LEXER_TOKENS_H_
#pragma once

typedef struct _Tokens {
	unsigned int type;
	unsigned int token_id;
	char* token_name;
	void* token_pointer;
} Tokens;

#define TOKEN_TYPE_KEYWORD 0
#define TOKEN_TYPE_HANDLER 1
#define TOKEN_TYPE_CHARSET 2

typedef unsigned char* (*clexer_handler)(unsigned char*);

unsigned char* token_string_handler(unsigned char* org_pointer);
unsigned char* token_char_handler(unsigned char* org_pointer);
unsigned char* token_comment_multiline_handler(unsigned char* org_pointer);
unsigned char* token_comment_singleline_handler(unsigned char* org_pointer);
unsigned char* token_id_handler(unsigned char* org_pointer);
unsigned char* token_number(unsigned char* org_pointer);
unsigned char* token_preprocessor_handler(unsigned char* org_pointer);

#define TOKEN_SIZE 79
extern Tokens tokens[TOKEN_SIZE];

#define TOKEN_ATTRIBUTE                          0
#define TOKEN_VOLATILE_                          1
#define TOKEN_UNSIGNED                           2
#define TOKEN_REGISTER                           3
#define TOKEN_VOLATILE                           4
#define TOKEN_IOMEM                              5
#define TOKEN_INCLUDE                            6
#define TOKEN_VIRTUAL                            7
#define TOKEN_TYPEDEF                            8
#define TOKEN_ASM                                9
#define TOKEN_DOUBLE                             10
#define TOKEN_DEFINE                             11
#define TOKEN_SWITCH                             12
#define TOKEN_SIGNED                             13
#define TOKEN_EXTERN                             14
#define TOKEN_STATIC                             15
#define TOKEN_INLINE                             16
#define TOKEN_STRUCT                             17
#define TOKEN_SIZEOF                             18
#define TOKEN_RETURN                             19
#define TOKEN_SHORT                              20
#define TOKEN_CONST                              21
#define TOKEN_UNDEF                              22
#define TOKEN_WHILE                              23
#define TOKEN_UNION                              24
#define TOKEN_FLOAT                              25
#define TOKEN_ELSE                               26
#define TOKEN_CASE                               27
#define TOKEN_THIS                               28
#define TOKEN_CHAR                               29
#define TOKEN_VOID                               30
#define TOKEN_LONG                               31
#define TOKEN_INT                                32
#define TOKEN_FOR                                33
#define TOKEN_SHIFTRIGHTEQUAL                    34
#define TOKEN_SHIFTLEFTEQUAL                     35
#define TOKEN_BIGGEREQUAL                        36
#define TOKEN_SMALLGEREQUAL                      37
#define TOKEN_IF                                 38
#define TOKEN_DO                                 39
#define TOKEN_SHIFTRIGHT                         40
#define TOKEN_SHIFTLEFT                          41
#define TOKEN_AND                                42
#define TOKEN_EQUAL                              43
#define TOKEN_LOGICOREQUAL                       44
#define TOKEN_OR                                 45
#define TOKEN_DEL                                46
#define TOKEN_MUL                                47
#define TOKEN_DIV                                48
#define TOKEN_GETPOINTER_LOGICAND                49
#define TOKEN_SMALLER                            50
#define TOKEN_BIGGER                             51 
#define TOKEN_ADD                                52
#define TOKEN_ASIGN                              53
#define TOKEN_BLOCKSTART                         54
#define TOKEN_BLOCKEND                           55
#define TOKEN_LOGICOR                            56
#define TOKEN_OPENPARENTHESES                    57
#define TOKEN_CLOSEPARENTHESES                   58
#define TOKEN_SEMICOLON                          59
#define TOKEN_LOGICNOT                           60
#define TOKEN_QUESTIONMARK                       61
#define TOKEN_COLON                              62
#define TOKEN_ARRAYSIZESTART                     63
#define TOKEN_ARRAYSIZEEND                       64
#define TOKEN_COMMA                              65
#define TOKEN_DOT                                66
#define TOKEN_CHANGELINE                         67
#define TOKEN_BITWISENOT                         68
#define TOKEN_MOD                                69
#define TOKEN_XOR                                70
#define TOKEN_PREPROCESSOR                       71
#define TOKEN_STRING                             72
#define TOKEN_CHARLITERAL                        73
#define TOKEN_COMMENT_MULTILINE                  74
#define TOKEN_COMMENT_SINGLELINE                 75
#define TOKEN_ID                                 76
#define TOKEN_NUMBER                             77
#define TOKEN_SPACE                              78

#endif //_C_LEXER_TOKENS_H_

