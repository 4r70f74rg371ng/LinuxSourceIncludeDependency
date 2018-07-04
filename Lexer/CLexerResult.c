#include <string.h>
#include "CLexerTokenStringMap.h"
#include "CLexerResult.h"

#define _clexer_result_file_fill_string(_field) {                                                       \
	((pclexer_result_file)pointer)->_field = (char*)malloc(sizeof(char)*(strlen(fileresult->_field)+1));\
	if(!((pclexer_result_file)pointer)->_field){                                                        \
		return FALSE;                                                                                   \
	}                                                                                                   \
	strcpy(((pclexer_result_file)pointer)->_field, fileresult->_field);                                 \
}

BOOL clexer_result_file_initial(SimpleLinkedList* linked_list, SimpleLinkedListElement* pointer, void* data, void* param){
	pclexer_result_file fileresult = (pclexer_result_file)param;

	if(param && (fileresult->magic == _clexer_result_file_magic)){
		((pclexer_result_file)pointer)->id = linked_list->maximum + 1; // start with 1
		_clexer_result_file_fill_string(fullpath);
		_clexer_result_file_fill_string(path);
		_clexer_result_file_fill_string(filename);
		_clexer_result_file_fill_string(ext);

		// check all string fill sucessfully, then we sucessfully fill this structure
		// we can simply check by magic, if we put it after fill all strings
		((pclexer_result_file)pointer)->magic = _clexer_result_file_magic;
		((pclexer_result_file)pointer)->tokensmap = fileresult->tokensmap;
		return TRUE;
	}
	return FALSE;
}

void clexer_result_file_free(SimpleLinkedList* linked_list, SimpleLinkedListElement* pointer, void* param){
	if(pointer){
		if(((pclexer_result_file)pointer)->fullpath){
			free(((pclexer_result_file)pointer)->fullpath);
		}
		if(((pclexer_result_file)pointer)->path){
			free(((pclexer_result_file)pointer)->path);
		}
		if(((pclexer_result_file)pointer)->filename){
			free(((pclexer_result_file)pointer)->filename);
		}
		if(((pclexer_result_file)pointer)->ext){
			free(((pclexer_result_file)pointer)->ext);
		}
		if(((pclexer_result_file)pointer)->tokensmap){
			Clean_Map(((pclexer_result_file)pointer)->tokensmap);
		}
		((pclexer_result_file)pointer)->magic = 0;
	}
}

void clexer_result_dir_initial(pclexer_result_dir result, char* sdir) {
	int len;
	if(result) {
		len = strlen(sdir);

		result->dir = (char*)malloc(sizeof(char)*(len+1));
		result->files_lexer_result = NULL;

		if(result->dir) {
			strcpy(result->dir, sdir);

			result->files_lexer_result = (PSimpleLinkedList)malloc(sizeof(SimpleLinkedList));

			if(result->files_lexer_result) {
				Initial_Result(result->files_lexer_result);
				result->magic = _clexer_result_dir_magic; // mark as initialized.
			} else {
				free(result->dir);
				result->dir = NULL;
			}
		}
	}
}

void clexer_result_dir_cleanup(pclexer_result_dir result){
   if(result && (result->magic == _clexer_result_dir_magic)){
         if(result->dir){
            free(result->dir);
            result->dir = NULL;
         }
         Clean_Result(result->files_lexer_result);
   }
}


