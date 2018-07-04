#ifndef _C_LEXER_FILE_H_
#define _C_LEXER_FILE_H_
#pragma once

typedef struct _SimpleLinkedList* PSimpleLinkedList;

typedef void (*clexer_handler_tokens_maps_func)(char* fullpath, char* path, char* filename, char* ext, unsigned char* strcontent, unsigned long long size, PSimpleLinkedList tokensmap, void* parameter);

void clexer_handle_c_file(char* fullpath, char* path, char* filename, char* ext, clexer_handler_tokens_maps_func handler_tokens_maps, void* parameter);
void clexer_handle_file(char* sPath, clexer_handler_tokens_maps_func handler_tokens_maps, void* parameter);
void clexer_enum_cfile_directory(char* sdir, clexer_handler_tokens_maps_func handler_tokens_maps, void* parameter);

// return data structure
#include "CLexerResult.h"

void clexer_handle_c_file_return(pclexer_result_dir result, char* fullpath, char* path, char* filename, char* ext);
void clexer_handle_file_return(pclexer_result_dir result, char* sdir, char* spath);
pclexer_result_dir clexer_enum_cfile_directory_return(char* sdir);

#endif //_C_LEXER_FILE_H_
