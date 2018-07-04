#ifndef _C_LEXER_RESULT_H_
#define _C_LEXER_RESULT_H_

#include "../DataStructure/CustomableSimpleLinkedList.h"

typedef struct _clexer_result_file{
	SimpleLinkedListElement linked_list;
	unsigned long           magic;
	int                     id;
	char*                   fullpath;
	char*                   path;
	char*                   filename;
	char*                   ext;
	PSimpleLinkedList       tokensmap;
}clexer_result_file, *pclexer_result_file;

#define _clexer_result_file_magic 0x434c5246 // 'CLRF'

typedef struct _clexer_result_dir{
	unsigned long           magic;
	char*                   dir;
	PSimpleLinkedList files_lexer_result;
}clexer_result_dir, *pclexer_result_dir;

#define _clexer_result_dir_magic 0x434c5244 // 'CLRD'

BOOL clexer_result_file_initial(SimpleLinkedList* linked_list, SimpleLinkedListElement* pointer, void* data, void* param);
void clexer_result_file_free(SimpleLinkedList* linked_list, SimpleLinkedListElement* pointer, void* param);

#define Initial_Result(_presult) (SimpleLinkedList_Custom_Initial_Macro_Func(_presult, clexer_result_file, clexer_result_file_initial, clexer_result_file_free))

#define Append_Result(_presult, _fullpath, _path, _filename, _ext, _tokensmap)  {   \
	clexer_result_file __append_result_internal_var;                                 \
	__append_result_internal_var.magic     = _clexer_result_file_magic;              \
	__append_result_internal_var.fullpath  = _fullpath;                              \
	__append_result_internal_var.path      = _path;                                  \
	__append_result_internal_var.filename  = _filename;                              \
	__append_result_internal_var.ext       = _ext;                                   \
	__append_result_internal_var.tokensmap = _tokensmap;                             \
	SimpleLinkedList_Append(_presult, NULL, (void*)&__append_result_internal_var);   \
}

#define Clean_Result(_pmap) SimpleLinkedList_Cleanup(_pmap, NULL)

#define Foreach_Result(_pmap, _var) for(pclexer_result_file _var = ((pclexer_result_file)(_pmap)->pointer);_var; _var = ((pclexer_result_file)_var->linked_list.next))


void clexer_result_dir_initial(pclexer_result_dir result, char* sdir);
void clexer_result_dir_cleanup(pclexer_result_dir result);


#endif // _C_LEXER_RESULT_H_


