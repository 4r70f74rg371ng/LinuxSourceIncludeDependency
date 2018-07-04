#ifndef _C_LEXER_TOKEN_STRING_MAP_H_
#define _C_LEXER_TOKEN_STRING_MAP_H_
#pragma once

#include "../DataStructure/CustomableSimpleLinkedList.h"

typedef struct _TokenStringMapElement {
	int id;
	int index;
	char* value;
}TokenStringMapElement, *PTokenStringMapElement;

typedef struct _TokenStringMap {
	SimpleLinkedListElement linked_list;
	TokenStringMapElement map_element;
}TokenStringMap, *PTokenStringMap;

BOOL initial_mymap(SimpleLinkedList* linked_list, SimpleLinkedListElement* pointer, void* data, void* param);
void free_mymap(SimpleLinkedList* linked_list, SimpleLinkedListElement* pointer, void*param);

#define Initial_Map(_pmap) (SimpleLinkedList_Custom_Initial_Macro_Func(_pmap, TokenStringMap, initial_mymap, free_mymap))

#define Append_Map(_pmap, _index, _value)  {                                     \
	TokenStringMapElement __append_map_internal_var;                             \
	__append_map_internal_var.index = _index;                                    \
	__append_map_internal_var.value = _value;                                    \
	SimpleLinkedList_Append(_pmap, NULL, (void*)&__append_map_internal_var);     \
}

#define Clean_Map(_pmap) SimpleLinkedList_Cleanup(_pmap, NULL)

#define Foreach_Map(_pmap, _var) for(PTokenStringMap _var = ((PTokenStringMap)(_pmap)->pointer);_var; _var = ((PTokenStringMap)_var->linked_list.next))

#endif //_C_LEXER_TOKEN_STRING_MAP_H_
