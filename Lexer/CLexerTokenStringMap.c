#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CLexerTokenStringMap.h"

// fill structrue you extend (ex: MyStructStringMapElement)
BOOL initial_mymap(SimpleLinkedList* linked_list, SimpleLinkedListElement* pointer, void* data, void* param) {
	PTokenStringMapElement mparam = (PTokenStringMapElement)param;
	int len = 0;

	if (param) {
		((PTokenStringMap)(pointer))->map_element.id = linked_list->maximum + 1;
		((PTokenStringMap)(pointer))->map_element.index = mparam->index;

		((PTokenStringMap)(pointer))->map_element.value = NULL;
		if (mparam->value) {
			len = strlen(mparam->value);
			((PTokenStringMap)(pointer))->map_element.value = (char*)malloc(sizeof(char)*(len + 1));
			if(((PTokenStringMap)(pointer))->map_element.value){
				strcpy(((PTokenStringMap)(pointer))->map_element.value, (const char*)mparam->value);
				return TRUE;
			}
		}
	}
	return FALSE;
}

void free_mymap(SimpleLinkedList* linked_list, SimpleLinkedListElement* pointer, void* param) {
	if (pointer && (((PTokenStringMap)(pointer))->map_element.value)) {
		free(((PTokenStringMap)(pointer))->map_element.value);
	}
}

