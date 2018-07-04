#include "CustomableSimpleLinkedList.h"

BOOL SimpleLinkedList_Initial(PSimpleLinkedList linked_list) {
	if (!_SimpleLinkedList_Assert(linked_list)) {
		linked_list->magic = _SimpleLinkedList_Magic;
		linked_list->maximum = 0;
		linked_list->length = 0;
		linked_list->pointer = NULL;
		linked_list->extsize = 0;
		linked_list->initialfunc = NULL;
		linked_list->freefunc = NULL;
		return TRUE;
	}
	return FALSE;
}

BOOL SimpleLinkedList_Custom_Initial(PSimpleLinkedList linked_list, int extsize, SimpleLinkedListElementInitialFunc initialfunc, SimpleLinkedListElementFreeFunc freefunc) {
	if ((!_SimpleLinkedList_Assert(linked_list)) && (extsize >= 0)) {
		linked_list->magic = _SimpleLinkedList_Magic;
		linked_list->maximum = 0;
		linked_list->length = 0;
		linked_list->pointer = NULL;
		if (extsize < 0) {
			linked_list->extsize = 0;
		}
		else {
			linked_list->extsize = extsize;
		}
		linked_list->initialfunc = initialfunc;
		linked_list->freefunc = freefunc;
		return TRUE;
	}
	return FALSE;
}

// changes => size of allocation
BOOL SimpleLinkedList_Append(PSimpleLinkedList linked_list, void* data, void* param) {
	PSimpleLinkedListElement newone = NULL;
	BOOL bret = FALSE;
	
	if (_SimpleLinkedList_Assert(linked_list)) {

		if (_SimpleLinkedListElement_Assert(linked_list->pointer)) {
			newone = (PSimpleLinkedListElement)malloc(sizeof(SimpleLinkedListElement) + linked_list->extsize);
			if (linked_list->initialfunc) {
				bret = linked_list->initialfunc(linked_list, newone, data, param);
				
				if(!bret){
					free(newone);
					return FALSE;
				}
			}
			linked_list->pointer->before->next = linked_list->pointer->before->after = newone;
			if (linked_list->pointer->before->next) {
				linked_list->pointer->before->next->magic = _SimpleLinkedListElement_Magic;
				linked_list->pointer->before->next->id = linked_list->maximum;
				linked_list->pointer->before->next->data = data;

				linked_list->pointer->before->next->before = linked_list->pointer->before->next->last = linked_list->pointer->before;
				linked_list->pointer->before->next->next = NULL;
				linked_list->pointer->before->next->after = linked_list->pointer;

				linked_list->pointer->before->next->parent = linked_list;
				linked_list->pointer->before = linked_list->pointer->before->next;

				linked_list->length++;
				linked_list->maximum++;

				return TRUE;
			}
		}
		else {
			newone = (PSimpleLinkedListElement)malloc(sizeof(SimpleLinkedListElement) + linked_list->extsize);
			if (linked_list->initialfunc) {
				bret = linked_list->initialfunc(linked_list, newone, data, param);
				
				if(!bret){
					free(newone);
					return FALSE;
				}
			}
			linked_list->pointer = newone;
			if (linked_list->pointer) {
				linked_list->pointer->after = linked_list->pointer->before = linked_list->pointer;
				linked_list->pointer->last = linked_list->pointer->next = NULL;
				linked_list->pointer->magic = _SimpleLinkedListElement_Magic;
				linked_list->pointer->id = linked_list->maximum;
				linked_list->pointer->data = data;

				linked_list->pointer->parent = linked_list;

				linked_list->length++;
				linked_list->maximum++;

				return TRUE;
			}
		}

	}
	return FALSE;
}

BOOL SimpleLinkedList_AttachHead(PSimpleLinkedList linked_list, void* data, void* param) {
	PSimpleLinkedListElement newone = NULL;
	BOOL bret = FALSE;
	
	if (_SimpleLinkedList_Assert(linked_list)) {

		if (_SimpleLinkedListElement_Assert(linked_list->pointer)) {
			newone = (PSimpleLinkedListElement)malloc(sizeof(SimpleLinkedListElement) + linked_list->extsize);
			if (linked_list->initialfunc) {
				bret = linked_list->initialfunc(linked_list, newone, data, param);
				
				if(!bret){
					free(newone);
					return FALSE;
				}
			}
			linked_list->pointer->last = newone;
			if (linked_list->pointer->last) {
				linked_list->pointer->last->magic = _SimpleLinkedListElement_Magic;
				linked_list->pointer->last->id = linked_list->maximum;
				linked_list->pointer->last->data = data;

				linked_list->pointer->last->last = NULL;
				linked_list->pointer->last->before = linked_list->pointer->before;
				linked_list->pointer->last->next = linked_list->pointer->last->after = linked_list->pointer;

				linked_list->pointer->last->parent = linked_list;
				linked_list->pointer = linked_list->pointer->before = linked_list->pointer->last;

				linked_list->length++;
				linked_list->maximum++;
				return TRUE;
			}
		}
		else {
			newone = (PSimpleLinkedListElement)malloc(sizeof(SimpleLinkedListElement) + linked_list->extsize);
			if (linked_list->initialfunc) {
				bret = linked_list->initialfunc(linked_list, newone, data, param);
				
				if(!bret){
					free(newone);
					return FALSE;
				}
			}
			linked_list->pointer = newone;
			if (linked_list->pointer) {
				linked_list->pointer->after = linked_list->pointer->before = linked_list->pointer;
				linked_list->pointer->last = linked_list->pointer->next = NULL;
				linked_list->pointer->magic = _SimpleLinkedListElement_Magic;
				linked_list->pointer->id = linked_list->maximum;
				linked_list->pointer->data = data;

				linked_list->pointer->parent = linked_list;

				linked_list->length++;
				linked_list->maximum++;
				return TRUE;
			}
		}

	}
	return FALSE;
}

PSimpleLinkedListElement SimpleLinkedList_GetFirst(PSimpleLinkedList linked_list) {
	if (_SimpleLinkedList_Assert(linked_list) && _SimpleLinkedListElement_Assert(linked_list->pointer)) {
		return linked_list->pointer;
	}
	return (PSimpleLinkedListElement)NULL;
}

PSimpleLinkedListElement SimpleLinkedList_GetEnd(PSimpleLinkedList linked_list) {
	if (_SimpleLinkedList_Assert(linked_list) && _SimpleLinkedListElement_Assert(linked_list->pointer)) {
		return linked_list->pointer->before;
	}
	return (PSimpleLinkedListElement)NULL;
}

PSimpleLinkedListElement SimpleLinkedList_GetNext(PSimpleLinkedListElement pointer) {
	if (_SimpleLinkedListElement_Assert(pointer)) {
		return pointer->next;
	}
	return (PSimpleLinkedListElement)NULL;
}

PSimpleLinkedListElement SimpleLinkedList_GetLast(PSimpleLinkedListElement pointer) {
	if (_SimpleLinkedListElement_Assert(pointer)) {
		return pointer->last;
	}
	return (PSimpleLinkedListElement)NULL;
}

PSimpleLinkedListElement SimpleLinkedList_GetBefore(PSimpleLinkedListElement pointer) {
	if (_SimpleLinkedListElement_Assert(pointer)) {
		return pointer->before;
	}
	return (PSimpleLinkedListElement)NULL;
}

PSimpleLinkedListElement SimpleLinkedList_GetAfter(PSimpleLinkedListElement pointer) {
	if (_SimpleLinkedListElement_Assert(pointer)) {
		return pointer->after;
	}
	return (PSimpleLinkedListElement)NULL;
}

BOOL SimpleLinkedList_InsertAfter(PSimpleLinkedListElement pointer, void* data,  void* param) {
	PSimpleLinkedListElement newone = NULL;
	BOOL bret = FALSE;
	
	if (_SimpleLinkedListElement_Assert(pointer)) {
		newone = (PSimpleLinkedListElement)malloc(sizeof(SimpleLinkedListElement) + pointer->parent->extsize);
		if (pointer->parent->initialfunc) {
			bret = pointer->parent->initialfunc(pointer->parent, newone, data, param);
			
			if(!bret){
				free(newone);
				return FALSE;
			}
		}
		if (newone) {
			newone->magic = _SimpleLinkedListElement_Magic;
			newone->id = pointer->parent->maximum;
			newone->data = data;
			newone->parent = pointer->parent;
			newone->next = pointer->next;
			newone->after = pointer->after;
			newone->before = newone->last = pointer;

			pointer->next = pointer->after = newone;
			newone->after->before = newone;

			if (newone->next) {
				newone->next->last = newone;
			}

			pointer->parent->maximum++;
			pointer->parent->length++;

			return TRUE;
		}
	}
	return FALSE;
}

BOOL SimpleLinkedList_InsertBefore(PSimpleLinkedListElement pointer, void* data, void* param) {
	PSimpleLinkedListElement newone = NULL;
	BOOL bret = FALSE;
	
	if (_SimpleLinkedListElement_Assert(pointer)) {
		newone = (PSimpleLinkedListElement)malloc(sizeof(SimpleLinkedListElement) + pointer->parent->extsize);
		if (pointer->parent->initialfunc) {
			bret = pointer->parent->initialfunc(pointer->parent, newone, data, param);
			
			if(!bret){
				free(newone);
				return FALSE;
			}
		}
		if (newone) {
			newone->magic = _SimpleLinkedListElement_Magic;
			newone->id = pointer->parent->maximum;
			newone->data = data;
			newone->parent = pointer->parent;
			newone->last = pointer->last;
			newone->before = pointer->before;
			newone->next = newone->after = pointer;
			newone->before->after = newone;

			if (newone->last) {
				newone->last->next = newone;
			}

			pointer->last = pointer->before = newone;

			if (pointer == newone->parent->pointer) {
				newone->parent->pointer = newone;
			}

			return TRUE;
		}
	}

	return FALSE;
}

// length info is in linked_list->length
BOOL SimpleLinkedList_ConvertArray(PSimpleLinkedList linked_list, void*** pdatapointers, unsigned long long* plength) {
	PSimpleLinkedListElement pointer = NULL;
	int i;
	if (_SimpleLinkedList_Assert(linked_list)) {
		if (pdatapointers) {
			*pdatapointers = (void**)malloc(sizeof(void*)*linked_list->length);
			if (*pdatapointers) {
				i = 0;
				for (pointer = linked_list->pointer; _SimpleLinkedListElement_Assert(pointer); pointer = pointer->next) {
					(*pdatapointers)[i++] = pointer->data;
				}
				if (plength) {
					*plength = linked_list->length;
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL SimpleLinkedList_Delete(PSimpleLinkedListElement pointer, void** datapointer, void* param) {
	if (_SimpleLinkedListElement_Assert(pointer)) {
		if (datapointer) {
			*datapointer = pointer->data;
		}

		// 1. make dangling pointer
		pointer->after->before = pointer->before;
		if (pointer->next) {
			pointer->next->last = pointer->last;
		}
		pointer->before->after = pointer->after;
		if (pointer->last) {
			pointer->last->next = pointer->next;
		}

		// 2. adjust main structure
		pointer->parent->length--;

		// 3. test is head
		if (pointer == pointer->parent->pointer) {
			pointer->parent->pointer = pointer->next;
		}

		// 4. free
		if (pointer->parent->freefunc) {
			pointer->parent->freefunc(pointer->parent, pointer, param);
		}
		free(pointer);
		return TRUE;
	}
	else {
		if (datapointer) {
			*datapointer = NULL;
		}
	}
	return FALSE;
}

BOOL SimpleLinkedList_Cleanup(PSimpleLinkedList linked_list, void* param) {
	PSimpleLinkedListElement pointer = NULL, forfree = NULL;
	if (_SimpleLinkedList_Assert(linked_list)) {
		pointer = linked_list->pointer;
		while (_SimpleLinkedListElement_Assert(pointer)) {
			forfree = pointer;
			pointer = pointer->next;
			if (linked_list->freefunc) {
				linked_list->freefunc(linked_list, forfree, param);
			}
			free(forfree);
		}
		linked_list->pointer = NULL;
		linked_list->length = 0;
		linked_list->maximum = 0;
		return TRUE;
	}
	return FALSE;
}

// need provide right array pointer (pdatapointers)
BOOL SimpleLinkedList_ConvertArrayAndCleanup(PSimpleLinkedList linked_list, void*** pdatapointers, unsigned long long* plength) {
	PSimpleLinkedListElement pointer = NULL, forfree = NULL;
	int i;
	if (_SimpleLinkedList_Assert(linked_list)) {
		if (pdatapointers) {
			*pdatapointers = (void**)malloc(sizeof(void*)*linked_list->length);
			if (*pdatapointers) {
				i = 0;
				for (pointer = linked_list->pointer; _SimpleLinkedListElement_Assert(pointer); ) {
					(*pdatapointers)[i++] = pointer->data;
					forfree = pointer;
					pointer = pointer->next;
					free(forfree);
				}
				linked_list->pointer = NULL;
				if (plength) {
					*plength = linked_list->length;
				}
				linked_list->length = 0;
				linked_list->maximum = 0;
				return TRUE;
			}
		}
	}
	return FALSE;
}

// start from 0
void* SimpleLinkedList_GetByIndex(PSimpleLinkedList linked_list, int index) {
	PSimpleLinkedListElement pointer = NULL;
	int i = 0;
	if (_SimpleLinkedList_Assert(linked_list)) {
		for (pointer = linked_list->pointer; _SimpleLinkedListElement_Assert(pointer); pointer = pointer->next) {
			if (i == index) {
				return pointer->data;
			}
			i++;
		}
	}
	return NULL;
}

void* SimpleLinkedList_GetById(PSimpleLinkedList linked_list, int id) {
	PSimpleLinkedListElement pointer = NULL;
	if (_SimpleLinkedList_Assert(linked_list)) {
		for (pointer = linked_list->pointer; _SimpleLinkedListElement_Assert(pointer); pointer = pointer->next) {
			if (pointer->id == id) {
				return pointer->data;
			}
		}
	}
	return NULL;
}

void SimpleLinkedList_PrintByNext(PSimpleLinkedList linked_list) {
	PSimpleLinkedListElement pointer = NULL;
	if (_SimpleLinkedList_Assert(linked_list)) {
		printf("linked list(next) = {");
		for (pointer = linked_list->pointer; _SimpleLinkedListElement_Assert(pointer); pointer = pointer->next) {
			if (pointer != linked_list->pointer) {
				printf(", ");
			}
			printf("%X", pointer->data);
		}
		printf("}\n");
	}
}

void SimpleLinkedList_PrintByAfter(PSimpleLinkedList linked_list) {
	PSimpleLinkedListElement pointer = NULL;
	if (_SimpleLinkedList_Assert(linked_list)) {
		printf("linked list(after) = {");
		if (_SimpleLinkedListElement_Assert(linked_list->pointer)) {
			printf("%X", linked_list->pointer->data);
			for (pointer = linked_list->pointer->after; _SimpleLinkedListElement_Assert(pointer) && (pointer != linked_list->pointer); pointer = pointer->after) {
				printf(", %X", pointer->data);
			}
		}
		printf("}\n");
	}
}

void SimpleLinkedList_PrintReverseByLast(PSimpleLinkedList linked_list) {
	PSimpleLinkedListElement pointer = NULL;
	if (_SimpleLinkedList_Assert(linked_list)) {
		printf("linked list(last, reverse) = {");
		if (_SimpleLinkedListElement_Assert(linked_list->pointer)) {
			pointer = linked_list->pointer->before;
			printf("%X", pointer->data);
			for (pointer = pointer->last; _SimpleLinkedListElement_Assert(pointer) && (pointer != linked_list->pointer->before); pointer = pointer->last) {
				printf(", %X", pointer->data);
			}
		}
		printf("}\n");
	}
}

void SimpleLinkedList_PrintReverseByBefore(PSimpleLinkedList linked_list) {
	PSimpleLinkedListElement pointer = NULL;
	if (_SimpleLinkedList_Assert(linked_list)) {
		printf("linked list(before, reverse) = {");
		if (_SimpleLinkedListElement_Assert(linked_list->pointer)) {
			pointer = linked_list->pointer->before;
			printf("%X", pointer->data);
			for (pointer = pointer->before; _SimpleLinkedListElement_Assert(pointer) && (pointer != linked_list->pointer->before); pointer = pointer->before) {
				printf(", %X", pointer->data);
			}
		}
		printf("}\n");
	}
}

