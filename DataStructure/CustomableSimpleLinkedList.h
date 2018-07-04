#ifndef _CUSTOMABLE_SIMPLE_LINKED_LIST_H_
#define _CUSTOMABLE_SIMPLE_LINKED_LIST_H_
#pragma once

// SOME defination & inclusion
#include <stdio.h>
#include <stdlib.h>

#ifndef BOOL
#define BOOL int
#endif // BOOL

#ifndef FALSE
#define FALSE 0
#endif // FALSE

#ifndef TRUE
#define TRUE 1
#endif // TRUE

#ifndef NULL
#define NULL ((void*)0)
#endif // NULL

// by using same data structure of simple linked list
typedef struct _SimpleLinkedList SimpleLinkedList, *PSimpleLinkedList;

typedef struct _SimpleLinkedListElement {
	unsigned long magic;
	int id;
	void* data; // no use in here
	SimpleLinkedList* parent;
	struct _SimpleLinkedListElement *last, *next;
	struct _SimpleLinkedListElement *before, *after;
}SimpleLinkedListElement, *PSimpleLinkedListElement;

struct _SimpleLinkedList;

typedef BOOL (*SimpleLinkedListElementInitialFunc)(struct _SimpleLinkedList* linked_list, SimpleLinkedListElement* pointer, void* data, void* param);
typedef void(*SimpleLinkedListElementFreeFunc)(struct _SimpleLinkedList* linked_list, SimpleLinkedListElement* pointer, void*param);

typedef struct _SimpleLinkedList {
	unsigned long magic;
	int length;
	int maximum;
	int extsize;
	SimpleLinkedListElementInitialFunc initialfunc;
	SimpleLinkedListElementFreeFunc freefunc;
	PSimpleLinkedListElement pointer;
}SimpleLinkedList, *PSimpleLinkedList;

#define SimpleLinkedList_GetExtSize(type) (sizeof(type)-sizeof(SimpleLinkedListElement))

#define _SimpleLinkedListElement_Magic (0x534c4c45) // 'SLLE'
#define _SimpleLinkedList_Magic (0x5f534c4c) // '_SLL'

#define _SimpleLinkedListElement_Assert(SimpleLinkedListElementPointer) (((SimpleLinkedListElementPointer) != NULL) && ((SimpleLinkedListElementPointer)->magic == _SimpleLinkedListElement_Magic))
#define _SimpleLinkedList_Assert(SimpleLinkedListPointer) (((SimpleLinkedListPointer) != NULL) && ((SimpleLinkedListPointer)->magic == _SimpleLinkedList_Magic))

BOOL SimpleLinkedList_Initial(PSimpleLinkedList linked_list);
//BOOL SimpleLinkedList_Custom_Initial(PSimpleLinkedList linked_list, int extsize = 0, SimpleLinkedListElementInitialFunc initialfunc = NULL, SimpleLinkedListElementFreeFunc freefunc = NULL);
BOOL SimpleLinkedList_Custom_Initial(PSimpleLinkedList linked_list, int extsize, SimpleLinkedListElementInitialFunc initialfunc, SimpleLinkedListElementFreeFunc freefunc);

#define SimpleLinkedList_Custom_Initial_Macro_Func(linked_list, type, initialfunc, freefunc) SimpleLinkedList_Custom_Initial(linked_list, SimpleLinkedList_GetExtSize(type), initialfunc, freefunc)
#define SimpleLinkedList_Custom_Initial_Macro(linked_list, type) SimpleLinkedList_Custom_Initial(linked_list, SimpleLinkedList_GetExtSize(type))

//BOOL SimpleLinkedList_Append(PSimpleLinkedList linked_list, void* data, void* param = NULL);
BOOL SimpleLinkedList_Append(PSimpleLinkedList linked_list, void* data, void* param);
BOOL SimpleLinkedList_AttachHead(PSimpleLinkedList linked_list, void* data, void* param);

PSimpleLinkedListElement SimpleLinkedList_GetFirst(PSimpleLinkedList linked_list);
PSimpleLinkedListElement SimpleLinkedList_GetEnd(PSimpleLinkedList linked_list);

PSimpleLinkedListElement SimpleLinkedList_GetNext(PSimpleLinkedListElement pointer);
PSimpleLinkedListElement SimpleLinkedList_GetLast(PSimpleLinkedListElement pointer);
PSimpleLinkedListElement SimpleLinkedList_GetBefore(PSimpleLinkedListElement pointer);
PSimpleLinkedListElement SimpleLinkedList_GetAfter(PSimpleLinkedListElement pointer);

BOOL SimpleLinkedList_InsertAfter(PSimpleLinkedListElement pointer, void* data, void* param);
BOOL SimpleLinkedList_InsertBefore(PSimpleLinkedListElement pointer, void* data, void* param);

// length info is in linked_list->length
BOOL SimpleLinkedList_ConvertArray(PSimpleLinkedList linked_list, void*** pdatapointers, size_t* plength);

BOOL SimpleLinkedList_Delete(PSimpleLinkedListElement pointer, void** datapointer, void* param);
BOOL SimpleLinkedList_Cleanup(PSimpleLinkedList linked_list, void* param);

// need provide right array pointer (pdatapointers)
// used for data pointer
BOOL SimpleLinkedList_ConvertArrayAndCleanup(PSimpleLinkedList linked_list, void*** pdatapointers, size_t* plength);

// start from 0
void* SimpleLinkedList_GetByIndex(PSimpleLinkedList linked_list, int index);
void* SimpleLinkedList_GetById(PSimpleLinkedList linked_list, int id);

// print test linked list
void SimpleLinkedList_PrintByNext(PSimpleLinkedList linked_list);
void SimpleLinkedList_PrintByAfter(PSimpleLinkedList linked_list);
void SimpleLinkedList_PrintReverseByLast(PSimpleLinkedList linked_list);
void SimpleLinkedList_PrintReverseByBefore(PSimpleLinkedList linked_list);

#endif // _CUSTOMABLE_SIMPLE_LINKED_LIST_H_
