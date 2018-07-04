#ifndef _PATH_GRAPH_H_
#define _PATH_GRAPH_H_
#pragma once

#include "CustomableSimpleLinkedList.h"

typedef struct _FileNodes {
	SimpleLinkedListElement linked_list;
	int id;
	int type;
	int exist;
	int isunix;
	char* fullpath;
	char* path;
	char* filename;
}FileNodes, *PFileNodes;

BOOL initial_filenodes(SimpleLinkedList* linked_list, SimpleLinkedListElement* pointer, void* data, void* param);
void free_filenodes(SimpleLinkedList* linked_list, SimpleLinkedListElement* pointer, void*param);

#define Initial_FileNodes(_pfnode) (SimpleLinkedList_Custom_Initial_Macro_Func(_pfnode, FileNodes, initial_filenodes, free_filenodes))

#define Append_FileNodes(_pfnode, _path, _filename, _type, _isunix)  {                 \
	FileNodes __append_filenodes_internal_var;                                         \
	__append_filenodes_internal_var.isunix = _isunix;                                  \
	__append_filenodes_internal_var.type = _type;                                      \
	__append_filenodes_internal_var.path = _path;                                      \
	__append_filenodes_internal_var.filename = _filename;                              \
	SimpleLinkedList_Append(_pfnode, NULL, (void*)&__append_filenodes_internal_var);   \
}

#define Clean_FileNodes(_pfnode) SimpleLinkedList_Cleanup(_pfnode, NULL)

#define Foreach_FileNodes(_pfnode, _var) for(PFileNodes _var = ((PFileNodes)(_pfnode)->pointer);_var; _var = ((PFileNodes)_var->linked_list.next))

typedef struct _IncludeLinks {
	SimpleLinkedListElement linked_list;
	
	// 0: internal inclusion: #include "header.h"
	// 1: external inclusion: #include <header.h>
	int type;
	int start;
	int end;
}IncludeLinks,*PIncludeLinks;

BOOL initial_includelinks(SimpleLinkedList* linked_list, SimpleLinkedListElement* pointer, void* data, void* param);
void free_includelinks(SimpleLinkedList* linked_list, SimpleLinkedListElement* pointer, void*param);

#define Initial_IncludeLinks(_pilinks) (SimpleLinkedList_Custom_Initial_Macro_Func(_pilinks, IncludeLinks, initial_includelinks, free_includelinks))

#define Append_IncludeLinks(_pilinks, _type, _start, _end)  {                             \
	IncludeLinks __append_includelinks_internal_var;                                      \
	__append_includelinks_internal_var.type = _type;                                      \
	__append_includelinks_internal_var.start = _start;                                    \
	__append_includelinks_internal_var.end = _end;                                        \
	SimpleLinkedList_Append(_pilinks, NULL, (void*)&__append_includelinks_internal_var);   \
}

#define Clean_IncludeLinks(_pilinks) SimpleLinkedList_Cleanup(_pilinks, NULL)

#define Foreach_IncludeLinks(_pilinks, _var) for(PIncludeLinks _var = ((PIncludeLinks)(_pilinks)->pointer);_var; _var = ((PIncludeLinks)_var->linked_list.next))

typedef struct _PathGraph {
	SimpleLinkedList nodes;
	SimpleLinkedList links;
}PathGraph, *PPathGraph;

void InitGraph(PPathGraph graph);
void CleanupGraph(PPathGraph graph);
int GetNodeId(PPathGraph graph, char* fullpath);
int GetNodeIdFromSplit(PPathGraph graph, char* path, char* filename, int isunix);
int InsertNode(PPathGraph graph, char* path, char* filename, int type, int isunix);
const char* GetNodeFullPath(PPathGraph graph, int id);
void InsertLink(PPathGraph graph, char* path, char* start, char* end, int type, int isunix);
void WriteDotFileGraph(PPathGraph graph, char* filename);

#endif // _PATH_GRAPH_H_

