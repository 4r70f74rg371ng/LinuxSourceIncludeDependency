#include <stdio.h>
#include <stdlib.h>
#include "CLexerTokens.h"

Tokens tokens[TOKEN_SIZE] = {
	{ 0, TOKEN_ATTRIBUTE,                         "TOKEN_ATTRIBUTE",                        (void*)"__attribute__" },
	{ 0, TOKEN_VOLATILE_,                         "TOKEN_VOLATILE_",                        (void*)"__volatile__" },
	{ 0, TOKEN_UNSIGNED,                          "TOKEN_UNSIGNED",                         (void*)"unsigned" },
	{ 0, TOKEN_REGISTER,                          "TOKEN_REGISTER",                         (void*)"register" },
	{ 0, TOKEN_VOLATILE,                          "TOKEN_VOLATILE",                         (void*)"volatile" },
	{ 0, TOKEN_IOMEM,                             "TOKEN_IOMEM",                            (void*)"__iomem" },
	{ 0, TOKEN_INCLUDE,                           "TOKEN_INCLUDE",                          (void*)"include" },
	{ 0, TOKEN_VIRTUAL,                           "TOKEN_VIRTUAL",                          (void*)"virtual" },
	{ 0, TOKEN_TYPEDEF,                           "TOKEN_TYPEDEF",                          (void*)"typedef" },
	{ 0, TOKEN_ASM,                               "TOKEN_ASM",                              (void*)"__asm__" },
	{ 0, TOKEN_DOUBLE,                            "TOKEN_DOUBLE",                           (void*)"double" },
	{ 0, TOKEN_DEFINE,                            "TOKEN_DEFINE",                           (void*)"define" },
	{ 0, TOKEN_SWITCH,                            "TOKEN_SWITCH",                           (void*)"switch" },
	{ 0, TOKEN_SIGNED,                            "TOKEN_SIGNED",                           (void*)"signed" },
	{ 0, TOKEN_EXTERN,                            "TOKEN_EXTERN",                           (void*)"extern" },
	{ 0, TOKEN_STATIC,                            "TOKEN_STATIC",                           (void*)"static" },
	{ 0, TOKEN_INLINE,                            "TOKEN_INLINE",                           (void*)"inline" },
	{ 0, TOKEN_STRUCT,                            "TOKEN_STRUCT",                           (void*)"struct" },
	{ 0, TOKEN_SIZEOF,                            "TOKEN_SIZEOF",                           (void*)"sizeof" },
	{ 0, TOKEN_RETURN,                            "TOKEN_RETURN",                           (void*)"return" },
	{ 0, TOKEN_SHORT,                             "TOKEN_SHORT",                            (void*)"short" },
	{ 0, TOKEN_CONST,                             "TOKEN_CONST",                            (void*)"const" },
	{ 0, TOKEN_UNDEF,                             "TOKEN_UNDEF",                            (void*)"undef" },
	{ 0, TOKEN_WHILE,                             "TOKEN_WHILE",                            (void*)"while" },
	{ 0, TOKEN_UNION,                             "TOKEN_UNION",                            (void*)"union" },
	{ 0, TOKEN_FLOAT,                             "TOKEN_FLOAT",                            (void*)"float" },
	{ 0, TOKEN_ELSE,                              "TOKEN_ELSE",                             (void*)"else" },
	{ 0, TOKEN_CASE,                              "TOKEN_CASE",                             (void*)"case" },
	{ 0, TOKEN_THIS,                              "TOKEN_THIS",                             (void*)"this" },
	{ 0, TOKEN_CHAR,                              "TOKEN_CHAR",                             (void*)"char" },
	{ 0, TOKEN_VOID,                              "TOKEN_VOID",                             (void*)"void" },
	{ 0, TOKEN_LONG,                              "TOKEN_LONG",                             (void*)"long" },
	{ 0, TOKEN_INT,                               "TOKEN_INT",                              (void*)"int" },
	{ 0, TOKEN_FOR,                               "TOKEN_FOR",                              (void*)"for" },
	{ 0, TOKEN_SHIFTRIGHTEQUAL,                   "TOKEN_SHIFTRIGHTEQUAL",                  (void*)">>=" },
	{ 0, TOKEN_SHIFTLEFTEQUAL,                    "TOKEN_SHIFTLEFTEQUAL",                   (void*)"<<=" },
	{ 0, TOKEN_BIGGEREQUAL,                       "TOKEN_BIGGEREQUAL",                      (void*)">=" },
	{ 0, TOKEN_SMALLGEREQUAL,                     "TOKEN_SMALLGEREQUAL",                    (void*)"<=" },
	{ 0, TOKEN_IF,                                "TOKEN_IF",                               (void*)"if" },
	{ 0, TOKEN_DO,                                "TOKEN_DO",                               (void*)"do" },
	{ 0, TOKEN_SHIFTRIGHT,                        "TOKEN_SHIFTRIGHT",                       (void*)">>" },
	{ 0, TOKEN_SHIFTLEFT,                         "TOKEN_SHIFTLEFT",                        (void*)"<<" },
	{ 0, TOKEN_AND,                               "TOKEN_AND",                              (void*)"&&" },
	{ 0, TOKEN_EQUAL,                             "TOKEN_EQUAL",                            (void*)"==" },
	{ 0, TOKEN_LOGICOREQUAL,                      "TOKEN_LOGICOREQUAL",                     (void*)"|=" },
	{ 0, TOKEN_OR,                                "TOKEN_OR",                               (void*)"||" },
	{ 0, TOKEN_DEL,                               "TOKEN_DEL",                              (void*)"-" },
	{ 0, TOKEN_MUL,                               "TOKEN_MUL",                              (void*)"*" },
	{ 0, TOKEN_DIV,                               "TOKEN_DIV",                              (void*)"/" },
	{ 0, TOKEN_GETPOINTER_LOGICAND,               "TOKEN_GETPOINTER_LOGICAND",              (void*)"&" },
	{ 0, TOKEN_SMALLER,                           "TOKEN_SMALLER",                          (void*)"<" },
	{ 0, TOKEN_BIGGER,                            "TOKEN_BIGGER",                           (void*)">" },
	{ 0, TOKEN_ADD,                               "TOKEN_ADD",                              (void*)"+" },
	{ 0, TOKEN_ASIGN,                             "TOKEN_ASIGN",                            (void*)"=" },
	{ 0, TOKEN_BLOCKSTART,                        "TOKEN_BLOCKSTART",                       (void*)"{" },
	{ 0, TOKEN_BLOCKEND,                          "TOKEN_BLOCKEND",                         (void*)"}" },
	{ 0, TOKEN_LOGICOR,                           "TOKEN_LOGICOR",                          (void*)"|" },
	{ 0, TOKEN_OPENPARENTHESES,                   "TOKEN_OPENPARENTHESES",                  (void*)"(" },
	{ 0, TOKEN_CLOSEPARENTHESES,                  "TOKEN_CLOSEPARENTHESES",                 (void*)")" },
	{ 0, TOKEN_SEMICOLON,                         "TOKEN_SEMICOLON",                        (void*)";" },
	{ 0, TOKEN_LOGICNOT,                          "TOKEN_LOGICNOT",                         (void*)"!" },
	{ 0, TOKEN_QUESTIONMARK,                      "TOKEN_QUESTIONMARK",                     (void*)"?" },
	{ 0, TOKEN_COLON,                             "TOKEN_COLON",                            (void*)":" },
	{ 0, TOKEN_ARRAYSIZESTART,                    "TOKEN_ARRAYSIZESTART",                   (void*)"[" },
	{ 0, TOKEN_ARRAYSIZEEND,                      "TOKEN_ARRAYSIZEEND",                     (void*)"]" },
	{ 0, TOKEN_COMMA,                             "TOKEN_COMMA",                            (void*)"," },
	{ 0, TOKEN_DOT,                               "TOKEN_DOT",                              (void*)"." },
	{ 0, TOKEN_CHANGELINE,                        "TOKEN_CHANGELINE",                       (void*)"\\" },
	{ 0, TOKEN_BITWISENOT,                        "TOKEN_BITWISENOT",                       (void*)"~" },
	{ 0, TOKEN_MOD,                               "TOKEN_MOD",                              (void*)"%" },
	{ 0, TOKEN_XOR,                               "TOKEN_XOR",                              (void*)"^" },
	{ 1, TOKEN_PREPROCESSOR,                      "TOKEN_PREPROCESSOR",                     (void*)(clexer_handler)token_preprocessor_handler },
	{ 1, TOKEN_STRING,                            "TOKEN_STRING",                           (void*)(clexer_handler)token_string_handler },
	{ 1, TOKEN_CHARLITERAL,                       "TOKEN_CHARLITERAL",                      (void*)(clexer_handler)token_char_handler },
	{ 1, TOKEN_COMMENT_MULTILINE,                 "TOKEN_COMMENT_MULTILINE",                (void*)(clexer_handler)token_comment_multiline_handler },
	{ 1, TOKEN_COMMENT_SINGLELINE,                "TOKEN_COMMENT_SINGLELINE",               (void*)(clexer_handler)token_comment_singleline_handler },
	{ 1, TOKEN_ID,                                "TOKEN_ID",                               (void*)(clexer_handler)token_id_handler },
	{ 1, TOKEN_NUMBER,                            "TOKEN_NUMBER",                           (void*)(clexer_handler)token_number },
	{ 2, TOKEN_SPACE,                             "TOKEN_SPACE",                            (void*)"\v\f\t\r\n\x20" } // for beautifier
};

#define ERROR_NO         0
#define ERROR_STRING     1
#define ERROR_CHAR       2

int error = ERROR_NO;

#define TOKENIDHANDLER_FLAG_NORMAL               0
#define TOKENIDHANDLER_FLAG_START                1
#define TOKENIDHANDLER_FLAG_EXIT                -1
#define TOKENIDHANDLER_FLAG_ERROR               -2

unsigned char* token_id_handler(unsigned char* org_pointer) {
	unsigned char* pointer = NULL, c;
	int status = TOKENIDHANDLER_FLAG_NORMAL;

	if (org_pointer) {
		pointer = org_pointer;
		while (status >= 0) {
			c = *pointer;
			switch (status) { /**/
			case TOKENIDHANDLER_FLAG_NORMAL:
			{
				if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || (c == '_')) {
					status = TOKENIDHANDLER_FLAG_START;
				}
				else {
					status = TOKENIDHANDLER_FLAG_ERROR;
				}
			}break;
			case TOKENIDHANDLER_FLAG_START:
			{
				if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || (c == '_') || ((c >= '0') && (c <= '9'))) {
					//status = TOKENIDHANDLER_FLAG_START;
				}
				else {
					status = TOKENIDHANDLER_FLAG_EXIT;
				}
			}break;
			}
			if (status == TOKENIDHANDLER_FLAG_EXIT) {
				break;
			}
			pointer++;
		}
		if (status == TOKENIDHANDLER_FLAG_ERROR) {
			pointer = org_pointer;
		}
	}

	return pointer;
}

#define TOKENPREPROCESSORHANDLER_FLAG_NORMAL   0
#define TOKENPREPROCESSORHANDLER_FLAG_START    1
#define TOKENPREPROCESSORHANDLER_FLAG_ESCAPE   2
#define TOKENPREPROCESSORHANDLER_FLAG_NEWLINE  3
#define TOKENPREPROCESSORHANDLER_FLAG_EXIT    -1
#define TOKENPREPROCESSORHANDLER_FLAG_ERROR   -2

unsigned char* token_preprocessor_handler(unsigned char* org_pointer) {
	unsigned char* pointer = NULL, c;
	int status = TOKENPREPROCESSORHANDLER_FLAG_NORMAL;

	if (org_pointer) {
		pointer = org_pointer;

		while ((*pointer) && (status >= 0)) {
			c = *pointer;

			switch (status) {
			case TOKENPREPROCESSORHANDLER_FLAG_NORMAL:
			{
				if (c == '#') {
					status = TOKENPREPROCESSORHANDLER_FLAG_START;
				}
				else {
					status = TOKENPREPROCESSORHANDLER_FLAG_ERROR;
				}
			}break;
			case TOKENPREPROCESSORHANDLER_FLAG_START:
			{
				if (c == '\\') {
					status = TOKENPREPROCESSORHANDLER_FLAG_ESCAPE;
				}
				else if (c == '\r') {
					status = TOKENPREPROCESSORHANDLER_FLAG_EXIT;
					pointer--;
				}
				else if (c == '\n') {
					status = TOKENPREPROCESSORHANDLER_FLAG_EXIT;
					pointer--;
				}
			}break;
			case TOKENPREPROCESSORHANDLER_FLAG_ESCAPE:
			{
				if (c == '\r') {
					status = TOKENPREPROCESSORHANDLER_FLAG_NEWLINE;
				}
				else if (c == '\n') {
					status = TOKENPREPROCESSORHANDLER_FLAG_START;
				}
				else {
					status = TOKENPREPROCESSORHANDLER_FLAG_START;
				}
			}break;
			case TOKENPREPROCESSORHANDLER_FLAG_NEWLINE:
			{
				if (c == '\n') {
					status = TOKENPREPROCESSORHANDLER_FLAG_START;
				}
				else if (c == '\r') { //twice \r => two line
					status = TOKENPREPROCESSORHANDLER_FLAG_EXIT;
				}
				else {
					status = TOKENPREPROCESSORHANDLER_FLAG_START;
				}
			}break;
			}
			pointer++;
		}

		if (status != TOKENPREPROCESSORHANDLER_FLAG_EXIT) {
			pointer = org_pointer;
		}
	}

	return pointer;
}

#define TOKENSINGLELINECOMMENTHANDLER_FLAG_NORMAL         0
#define TOKENSINGLELINECOMMENTHANDLER_FLAG_STARTSLASH     1
#define TOKENSINGLELINECOMMENTHANDLER_FLAG_STARTCONTENT   2
#define TOKENSINGLELINECOMMENTHANDLER_FLAG_EXIT          -1
#define TOKENSINGLELINECOMMENTHANDLER_FLAG_ERROR         -2

// /* ... */
unsigned char* token_comment_singleline_handler(unsigned char* org_pointer) {
	unsigned char* pointer = NULL, c;
	int status = TOKENSINGLELINECOMMENTHANDLER_FLAG_NORMAL;

	if (org_pointer) {
		pointer = org_pointer;

		while ((*pointer) && (status >= 0)) {
			c = *pointer;
			switch (status) { /**/
			case TOKENSINGLELINECOMMENTHANDLER_FLAG_NORMAL:
			{
				if (c == '/') {
					status = TOKENSINGLELINECOMMENTHANDLER_FLAG_STARTSLASH;
				}
				else {
					status = TOKENSINGLELINECOMMENTHANDLER_FLAG_ERROR;
				}
			}break;
			case TOKENSINGLELINECOMMENTHANDLER_FLAG_STARTSLASH:
			{
				if (c == '/') {
					status = TOKENSINGLELINECOMMENTHANDLER_FLAG_STARTCONTENT;
				}
				else {
					status = TOKENSINGLELINECOMMENTHANDLER_FLAG_ERROR;
				}
			}break;
			case TOKENSINGLELINECOMMENTHANDLER_FLAG_STARTCONTENT:
			{
				if ((c == '\r') || (c == '\n')) {
					status = TOKENSINGLELINECOMMENTHANDLER_FLAG_EXIT;
				}
			}break;
			}
			if (status == TOKENSINGLELINECOMMENTHANDLER_FLAG_EXIT) { //end before \n, \r
				break;
			}
			pointer++;
		}
	}

	if (status != TOKENSINGLELINECOMMENTHANDLER_FLAG_EXIT) {
		pointer = org_pointer;
	}

	return pointer;
}

#define TOKENMULTILINECOMMENTHANDLER_FLAG_NORMAL         0
#define TOKENMULTILINECOMMENTHANDLER_FLAG_STARTSLASH     1
#define TOKENMULTILINECOMMENTHANDLER_FLAG_STARTCONTENT   2
#define TOKENMULTILINECOMMENTHANDLER_FLAG_GUESSEND       3
#define TOKENMULTILINECOMMENTHANDLER_FLAG_EXIT          -1
#define TOKENMULTILINECOMMENTHANDLER_FLAG_ERROR         -2

// /* ... */
unsigned char* token_comment_multiline_handler(unsigned char* org_pointer) {
	unsigned char* pointer = NULL, c;
	int status = TOKENMULTILINECOMMENTHANDLER_FLAG_NORMAL;

	if (org_pointer) {
		pointer = org_pointer;

		while ((*pointer) && (status >= 0)) {
			c = *pointer;
			switch (status) { /**/
			case TOKENMULTILINECOMMENTHANDLER_FLAG_NORMAL:
			{
				if (c == '/') {
					//printf("start slash");
					//system("pause");
					status = TOKENMULTILINECOMMENTHANDLER_FLAG_STARTSLASH;
				}
				else {
					status = TOKENMULTILINECOMMENTHANDLER_FLAG_ERROR;
				}
			}break;
			case TOKENMULTILINECOMMENTHANDLER_FLAG_STARTSLASH:
			{
				if (c == '*') {
					//printf("start star");
					//system("pause");
					status = TOKENMULTILINECOMMENTHANDLER_FLAG_STARTCONTENT;
				}
				else {
					status = TOKENMULTILINECOMMENTHANDLER_FLAG_ERROR;
				}
			}break;
			case TOKENMULTILINECOMMENTHANDLER_FLAG_STARTCONTENT:
			{
				if (c == '*') {
					//printf("guess end");
					//system("pause");
					status = TOKENMULTILINECOMMENTHANDLER_FLAG_GUESSEND;
				}
			}break;
			case TOKENMULTILINECOMMENTHANDLER_FLAG_GUESSEND:
			{
				if (c == '*') {
					//printf("guess end");
					//system("pause");
					status = TOKENMULTILINECOMMENTHANDLER_FLAG_GUESSEND;
				}
				else if (c == '/') {
					//printf("end");
					//system("pause");
					status = TOKENMULTILINECOMMENTHANDLER_FLAG_EXIT;
				}
				else {
					status = TOKENMULTILINECOMMENTHANDLER_FLAG_STARTCONTENT;
				}
			}break;
			}
			pointer++;
		}
	}

	if (status != TOKENMULTILINECOMMENTHANDLER_FLAG_EXIT) {
		pointer = org_pointer;
	}

	return pointer;
}

#define TOKENSTRHANDLER_FLAG_NORMAL       0
#define TOKENSTRHANDLER_FLAG_START        1
#define TOKENSTRHANDLER_FLAG_ESCAPE       2
#define TOKENSTRHANDLER_FLAG_OCTNUMBER    3
#define TOKENSTRHANDLER_FLAG_HEXNUMBER    4
#define TOKENSTRHANDLER_FLAG_UNICODE4     5
#define TOKENSTRHANDLER_FLAG_UNICODE8     6
#define TOKENSTRHANDLER_FLAG_EXIT        -1
#define TOKENSTRHANDLER_FLAG_ERROR       -2

// https://en.wikipedia.org/wiki/Escape_sequences_in_C
unsigned char* token_string_handler(unsigned char* org_pointer) {
	unsigned char* pointer = NULL, c;
	int count = 0;
	int status = TOKENSTRHANDLER_FLAG_NORMAL;

	if (org_pointer) {
		pointer = org_pointer;

		while (status >= 0) {
			c = *pointer;


			if ((c == '\r') || (c == '\n')) { // cannot have any new line in string
				if (status == TOKENSTRHANDLER_FLAG_ESCAPE) {
					status = TOKENSTRHANDLER_FLAG_START;
					pointer++;
				}
				else {
					status = TOKENSTRHANDLER_FLAG_ERROR;
					break;
				}
			}
			else if (c == '\0') {
				status = TOKENSTRHANDLER_FLAG_ERROR;
				break;
			}
			else {
				switch (status) {
				case TOKENSTRHANDLER_FLAG_NORMAL:
				{
					if (c == '"') {
						status = TOKENSTRHANDLER_FLAG_START;
					}
					else {
						status = TOKENSTRHANDLER_FLAG_ERROR;
					}
				}break;
				case TOKENSTRHANDLER_FLAG_START:
				{
					if (c == '\\') {
						status = TOKENSTRHANDLER_FLAG_ESCAPE;
					}
					else if (c == '"') {
						status = TOKENSTRHANDLER_FLAG_EXIT;
					}
				}break;
				case TOKENSTRHANDLER_FLAG_ESCAPE:
				{
					if ((c == 'a') || (c == 'b') || (c == 'e') || (c == 'f') || (c == 'v') || (c == 'r') || (c == 'n') || (c == 't') || (c == '\\') || (c == '\'') || (c == '"')) {
						status = TOKENSTRHANDLER_FLAG_START;
					}
					else if ((c == '0') || (c == '1')) {
						status = TOKENSTRHANDLER_FLAG_OCTNUMBER;
					}
					else if (c == 'x') {
						status = TOKENSTRHANDLER_FLAG_HEXNUMBER;
					}
					else if (c == 'u') {
						status = TOKENSTRHANDLER_FLAG_UNICODE4;
						count = 0;
					}
					else if (c == 'U') {
						status = TOKENSTRHANDLER_FLAG_UNICODE8;
						count = 0;
					}
					else {
						status = TOKENSTRHANDLER_FLAG_ERROR;
					}
				}break;
				case TOKENSTRHANDLER_FLAG_OCTNUMBER:
				{
					if ((c >= '0') && (c <= '7')) {
						if ((*(pointer + 1) < '0') || (*(pointer + 1) > '7')) {
							status = TOKENSTRHANDLER_FLAG_START;
						}
					}
					else if (c == '\\') { // it's \0
						status = TOKENSTRHANDLER_FLAG_ESCAPE;
					}
					else if (c == '"') {
						status = TOKENSTRHANDLER_FLAG_EXIT;
					}
					else { // it's \0
						status = TOKENSTRHANDLER_FLAG_START;
					}
				}break;
				case TOKENSTRHANDLER_FLAG_HEXNUMBER:
				{
					if (((c >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'f')) || ((c >= 'A') && (c <= 'F'))) {
						if (((*(pointer + 1) < '0') || (*(pointer + 1) > '9')) && ((*(pointer + 1) < 'a') || (*(pointer + 1) > 'f')) && ((*(pointer + 1) < 'A') || (*(pointer + 1) > 'F'))) {
							status = TOKENSTRHANDLER_FLAG_START;
						}
					}
					else {
						status = TOKENSTRHANDLER_FLAG_ERROR;
					}
				}break;
				case TOKENSTRHANDLER_FLAG_UNICODE4:
				{
					count++;
					if (count < 4) {
						if (((c < '0') || (c > '9')) && ((c < 'a') || (c > 'f')) && ((c < 'A') || (c > 'F'))) {
							status = TOKENSTRHANDLER_FLAG_ERROR;
						}
					}
					else {
						if (((c < '0') || (c > '9')) && ((c < 'a') || (c > 'f')) && ((c < 'A') || (c > 'F'))) {
							status = TOKENSTRHANDLER_FLAG_ERROR;
						}
						else {
							status = TOKENSTRHANDLER_FLAG_START;
						}
					}
				}break;
				case TOKENSTRHANDLER_FLAG_UNICODE8:
				{
					count++;
					if (count < 8) {
						if (((c < '0') || (c > '9')) && ((c < 'a') || (c > 'f')) && ((c < 'A') || (c > 'F'))) {
							status = TOKENSTRHANDLER_FLAG_ERROR;
						}
					}
					else {
						if (((c < '0') || (c > '9')) && ((c < 'a') || (c > 'f')) && ((c < 'A') || (c > 'F'))) {
							status = TOKENSTRHANDLER_FLAG_ERROR;
						}
						else {
							status = TOKENSTRHANDLER_FLAG_START;
						}
					}
				}break;
				default:
					status = TOKENSTRHANDLER_FLAG_ERROR;
					break;
				}
				pointer++;
			}
		}
		if (status != TOKENSTRHANDLER_FLAG_EXIT) {
			pointer = org_pointer;
			// error detection
			if (*pointer == '"') {
				error = ERROR_STRING;
			}
		}
	}
	return pointer;
}

unsigned char* token_char_handler(unsigned char* org_pointer) {
	unsigned char* pointer = NULL, c;
	int count = 0;
	int status = TOKENSTRHANDLER_FLAG_NORMAL;

	if (org_pointer) {
		pointer = org_pointer;

		while (status >= 0) {
			c = *pointer;

			if ((c == '\r') || (c == '\n')) { // cannot have any new line in string
				status = TOKENSTRHANDLER_FLAG_ERROR;
				break;
			}
			else if (c == '\0') {
				status = TOKENSTRHANDLER_FLAG_EXIT;
				break;
			}
			else {
				switch (status) {
				case TOKENSTRHANDLER_FLAG_NORMAL:
				{
					if (c == '\'') {
						status = TOKENSTRHANDLER_FLAG_START;
					}
					else {
						status = TOKENSTRHANDLER_FLAG_ERROR;
					}
				}break;
				case TOKENSTRHANDLER_FLAG_START:
				{
					if (c == '\\') {
						status = TOKENSTRHANDLER_FLAG_ESCAPE;
					}
					else if (c == '\'') {
						status = TOKENSTRHANDLER_FLAG_EXIT;
					}
				}break;
				case TOKENSTRHANDLER_FLAG_ESCAPE:
				{
					if ((c == 'a') || (c == 'b') || (c == 'e') || (c == 'f') || (c == 'v') || (c == 'r') || (c == 'n') || (c == 't') || (c == '\\') || (c == '\'') || (c == '"')) {
						status = TOKENSTRHANDLER_FLAG_START;
					}
					else if ((c == '0') || (c == '1')) {
						status = TOKENSTRHANDLER_FLAG_OCTNUMBER;
					}
					else if (c == 'x') {
						status = TOKENSTRHANDLER_FLAG_HEXNUMBER;
					}
					else if (c == 'u') {
						status = TOKENSTRHANDLER_FLAG_UNICODE4;
						count = 0;
					}
					else if (c == 'U') {
						status = TOKENSTRHANDLER_FLAG_UNICODE8;
						count = 0;
					}
					else {
						status = TOKENSTRHANDLER_FLAG_ERROR;
					}
				}break;
				case TOKENSTRHANDLER_FLAG_OCTNUMBER:
				{
					if ((c >= '0') && (c <= '7')) {
						if ((*(pointer + 1) < '0') || (*(pointer + 1) > '7')) {
							status = TOKENSTRHANDLER_FLAG_START;
						}
					}
					else if (c == '\\') { // it's \0
						status = TOKENSTRHANDLER_FLAG_ESCAPE;
					}
					else if (c == '\'') {
						status = TOKENSTRHANDLER_FLAG_EXIT;
					}
					else { // it's \0
						status = TOKENSTRHANDLER_FLAG_START;
					}
				}break;
				case TOKENSTRHANDLER_FLAG_HEXNUMBER:
				{
					if (((c >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'f')) || ((c >= 'A') && (c <= 'F'))) {
						if (((*(pointer + 1) < '0') || (*(pointer + 1) > '9')) && ((*(pointer + 1) < 'a') || (*(pointer + 1) > 'f')) && ((*(pointer + 1) < 'A') || (*(pointer + 1) > 'F'))) {
							status = TOKENSTRHANDLER_FLAG_START;
						}
					}
					else {
						status = TOKENSTRHANDLER_FLAG_ERROR;
					}
				}break;
				case TOKENSTRHANDLER_FLAG_UNICODE4:
				{
					count++;
					if (count < 4) {
						if (((c < '0') || (c > '9')) && ((c < 'a') || (c > 'f')) && ((c < 'A') || (c > 'F'))) {
							status = TOKENSTRHANDLER_FLAG_ERROR;
						}
					}
					else {
						if (((c < '0') || (c > '9')) && ((c < 'a') || (c > 'f')) && ((c < 'A') || (c > 'F'))) {
							status = TOKENSTRHANDLER_FLAG_ERROR;
						}
						else {
							status = TOKENSTRHANDLER_FLAG_START;
						}
					}
				}break;
				case TOKENSTRHANDLER_FLAG_UNICODE8:
				{
					count++;
					if (count < 8) {
						if (((c < '0') || (c > '9')) && ((c < 'a') || (c > 'f')) && ((c < 'A') || (c > 'F'))) {
							status = TOKENSTRHANDLER_FLAG_ERROR;
						}
					}
					else {
						if (((c < '0') || (c > '9')) && ((c < 'a') || (c > 'f')) && ((c < 'A') || (c > 'F'))) {
							status = TOKENSTRHANDLER_FLAG_ERROR;
						}
						else {
							status = TOKENSTRHANDLER_FLAG_START;
						}
					}
				}break;
				default:
					status = TOKENSTRHANDLER_FLAG_ERROR;
					break;
				}
				pointer++;
			}
		}
		if (status != TOKENSTRHANDLER_FLAG_EXIT) {
			pointer = org_pointer;
			// error detection
			if (*pointer == '\'') {
				error = ERROR_CHAR;
			}
		}
	}
	return pointer;
}

#define TOKENNUMHANDLER_FLAG_NORMAL  0
#define TOKENNUMHANDLER_FLAG_HEX     1
#define TOKENNUMHANDLER_FLAG_EXIT    2
#define TOKENNUMHANDLER_FLAG_ERROR  -1

unsigned char* token_number(unsigned char* org_pointer) {
	unsigned char* pointer = org_pointer;
	int status = TOKENNUMHANDLER_FLAG_NORMAL;
	int is_number = 0;

	if (pointer) {
		while (*pointer) {
			switch (status) {
			case TOKENNUMHANDLER_FLAG_NORMAL:
			{
				if (((*pointer) >= '0') && ((*pointer) <= '9')) {
					is_number = 1;
				}
				else if ((is_number == 1) && ((*pointer) == 'x')) {
					status = TOKENNUMHANDLER_FLAG_HEX;
				}
				else if (((*pointer) < '0') || ((*pointer) > '9')) {
					if (is_number) {
						status = TOKENNUMHANDLER_FLAG_EXIT;
					}
					else {
						status = TOKENNUMHANDLER_FLAG_ERROR;
					}
				}
			}break;
			case TOKENNUMHANDLER_FLAG_HEX:
			{
				if ((((*pointer) < '0') || ((*pointer) > '9')) && (((*pointer) < 'A') || ((*pointer) > 'F')) && (((*pointer) < 'a') || ((*pointer) > 'f'))) {
					status = TOKENNUMHANDLER_FLAG_EXIT;
				}
			}break;
			}

			if ((status == TOKENNUMHANDLER_FLAG_EXIT) || (status == TOKENNUMHANDLER_FLAG_ERROR)) {
				break;
			}

			pointer++;
		}
	}
	if (status == TOKENNUMHANDLER_FLAG_ERROR) {
		pointer = org_pointer;
	}

	return pointer;
}

