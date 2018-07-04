#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CLexerTokenStringMap.h"
#include "CLexerTokens.h"
#include "CLexerLexer.h"

unsigned char* clexer_handle_token_type0_keyword(unsigned char* strcontent, unsigned char* keyword) {
	unsigned char* pointer = strcontent;
	int i;

	for (i = 0; keyword[i]; i++) {
		if (strcontent[i] != keyword[i]) {
			break;
		}
	}

	if (keyword[i] == '\0') {
		pointer = &strcontent[i];
	}

	return pointer;
}

unsigned char* clexer_handle_token_type2_charset(unsigned char* strcontent, unsigned char* charset) {
	unsigned char* pointer = strcontent;
	int i;

	while (*pointer) {
		for (i = 0; charset[i]; i++) {
			if (*pointer == charset[i]) {
				break;
			}
		}
		if (charset[i] == '\0') {
			break;
		}
		pointer++;
	}

	return pointer;
}

void clexer_print_escape(unsigned char* strs) {
	unsigned char *pointer = strs;
	if (strs) {
		for (; *pointer; pointer = pointer + 1) {
			switch (*pointer) {
			case '\a':putchar('\\'); putchar('a'); break;
			case '\b':putchar('\\'); putchar('b'); break;
			case '\r':putchar('\\'); putchar('r'); break;
			case '\n':putchar('\\'); putchar('n'); break;
			case '\v':putchar('\\'); putchar('v'); break;
			case '\f':putchar('\\'); putchar('f'); break;
			case '\t':putchar('\\'); putchar('t'); break;
			case '\\':putchar('\\'); putchar('\\'); break;
			default:putchar(*pointer); break;
			}
		}
	}
}

int status = 0;
char str1[100][100] = { "" };
int top1 = 0;
char str2[100][100] = { "" };
int top2 = 0;

void clexer_handle_token(int index_token, char* value, char* name) {
	int len = 0;
	int i;
	char* localvalue = NULL;

	len = strlen(value);
	localvalue = (char*)malloc(sizeof(char)*(len + 1));
	strcpy(localvalue, value);

	// printf("%s: %s\n", name, value);
	printf("\'%s\',", value);

	/*if (index_token == TOKEN_ARRAYSIZESTART) {
	top1 = 0;
	strcpy_s(str1[top1++], 100, localvalue);
	}
	else if (index_token == TOKEN_ARRAYSIZEEND) {

	if (top1 > 0) {

	strcpy_s(str2[top2++], 100, localvalue);

	while ((top1 > 0) && (strcmp(str1[--top1],"[") != 0)) {
	strcpy_s(str2[top2++], 100, str1[top1]);
	}

	if (top1 == 0) {
	printf("[");
	for (i = top2; i >= 0; i--) {
	printf("%s ", str2[i]);
	}
	printf("\n");
	//system("pause");
	top2 = 0;
	}
	}

	} else if(top1 != 0) {
	strcpy_s(str1[top1++], 100, localvalue);
	}*/

	free(localvalue);

}

PSimpleLinkedList clexer_handle_c_file_content(char* fullpath, char* path, char* filename, char* ext, unsigned char* strcontent, unsigned long long size) {
	PSimpleLinkedList tokenmap;
	PTokenStringMap mappointer = NULL;
	unsigned char* pointer = NULL;
	unsigned char* tmppointer = NULL, tmpc;
	int found = 0;
	int i;
	int max = 0;

	tokenmap = (PSimpleLinkedList)malloc(sizeof(SimpleLinkedList));

	Initial_Map(tokenmap);

	if (strcontent) {
		//printf("[+] lexer %s...\n", fullpath);
		for (pointer = strcontent; pointer < (strcontent + size);) {
			for (found = 0, i = (TOKEN_SIZE - 1); (i >= 0) && (found == 0); i--) {
				switch (tokens[i].type) {
				case 0:
					tmppointer = clexer_handle_token_type0_keyword(pointer, (unsigned char*)tokens[i].token_pointer);
					if (tmppointer != pointer) {
						tmpc = *tmppointer;
						*tmppointer = '\0';
						//printf("keyword: '%s'\n", (char*)tokens[i].token_name);
						//printf("%s", pointer);
						//handle_token(i, (char*)pointer, (char*)tokens[i].token_name);
						Append_Map(tokenmap, i, (char*)pointer);
						*tmppointer = tmpc;
						pointer = tmppointer;
						found = 1;
					}
					break;
				case 1:
					tmppointer = ((clexer_handler)tokens[i].token_pointer)(pointer);
					if (tmppointer != pointer) {
						tmpc = *tmppointer;
						*tmppointer = '\0';
						//printf("handler: '%s'\n", (char*)tokens[i].token_name);
						//printf("%s", pointer);
						//handle_token(i, (char*)pointer, (char*)tokens[i].token_name);
						Append_Map(tokenmap, i, (char*)pointer);
						*tmppointer = tmpc;
						pointer = tmppointer;
						found = 1;
					}
					break;
				case 2:
					tmppointer = clexer_handle_token_type2_charset(pointer, (unsigned char*)tokens[i].token_pointer);
					if (tmppointer != pointer) {
						/*tmpc = *tmppointer;
						*tmppointer = '\0';
						printf("space: '");
						print_escape(pointer);
						printf("'\n");
						*tmppointer = tmpc;*/
						tmpc = *tmppointer;
						*tmppointer = '\0';
						//handle_token(i, (char*)pointer, (char*)tokens[i].token_name);
						Append_Map(tokenmap, i, (char*)pointer);
						*tmppointer = tmpc;
						pointer = tmppointer;
						found = 1;
					}
					break;
				}
			}
			if (found == 0) {
				//printf("Error: %d %c\n", *pointer, *pointer);
				//system("pause");
				tmppointer = (pointer + 1);
				tmpc = *tmppointer;
				*tmppointer = '\0';
				Append_Map(tokenmap, -1, (char*)pointer);
				*tmppointer = tmpc;
				pointer++;
			}
		}
	}
	return tokenmap;
}



