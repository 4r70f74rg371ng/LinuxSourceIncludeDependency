#include "Common.h"
#include "PathGraph.h"

BOOL initial_filenodes(SimpleLinkedList* linked_list, SimpleLinkedListElement* pointer, void* data, void* param){
	// check whether linked list 
	PFileNodes pargfilenode = (PFileNodes)param;
	PFileNodes fnpointer = ((PFileNodes)(pointer));
	
	if(pointer && param) {
		fnpointer->id = linked_list->maximum + 1;
		fnpointer->isunix = pargfilenode->isunix;
		fnpointer->type = pargfilenode->type;
		if(pargfilenode->type == 0){
			fnpointer->fullpath = concat_path(pargfilenode->path, pargfilenode->filename, 0);
			if(fnpointer->fullpath == NULL){
				return FALSE;
			}
			fnpointer->exist = is_file_exist(fnpointer->fullpath);
		}else{
			fnpointer->fullpath = (char*)malloc(sizeof(char)*(strlen(pargfilenode->filename)+1));
			if(fnpointer->fullpath == NULL){
				return FALSE;
			}
			strcpy(fnpointer->fullpath, pargfilenode->filename);
			
			fnpointer->exist = 0;
		}
		fnpointer->path = (char*)malloc(sizeof(char)*(strlen(pargfilenode->path)+1));
		if(fnpointer->path == NULL){
			return FALSE;
		}
		strcpy(fnpointer->path, pargfilenode->path);
		
		fnpointer->filename = (char*)malloc(sizeof(char)*(strlen(pargfilenode->filename)+1));
		if(fnpointer->filename == NULL){
			return FALSE;
		}
		strcpy(fnpointer->filename, pargfilenode->filename);
		return TRUE;
	}
	return FALSE;
}

void free_filenodes(SimpleLinkedList* linked_list, SimpleLinkedListElement* pointer, void* param){
	PFileNodes fnpointer = ((PFileNodes)(pointer));
	if(pointer){
		if(fnpointer->filename){
			free(fnpointer->filename);
		}
		
		if(fnpointer->path){
			free(fnpointer->path);
		}
		
		if(fnpointer->fullpath){
			free(fnpointer->fullpath);
		}
	}
}

BOOL initial_includelinks(SimpleLinkedList* linked_list, SimpleLinkedListElement* pointer, void* data, void* param){
	PIncludeLinks parg = (PIncludeLinks)param;
	PIncludeLinks ilpointer = (PIncludeLinks)pointer;
	
	if(parg && ilpointer){
		ilpointer->type = parg->type;
		ilpointer->start = parg->start;
		ilpointer->end = parg->end;
		return TRUE;
	}
	
	return FALSE;
}

void free_includelinks(SimpleLinkedList* linked_list, SimpleLinkedListElement* pointer, void*param){
	// do nothing ...
}

void InitGraph(PPathGraph graph) {
	if (graph) {
		Initial_FileNodes(&(graph->nodes));
		Initial_IncludeLinks(&(graph->links));
	}
}

void CleanupGraph(PPathGraph graph) {
	if (graph) {
		Clean_FileNodes(&(graph->nodes));
		Clean_IncludeLinks(&(graph->links));
	}
}

int GetNodeId(PPathGraph graph, char* fullpath) {
	PSimpleLinkedListElement ptr = NULL;
	int id = -1;

	if (graph && fullpath) {
		Foreach_FileNodes(&(graph->nodes), pnode) {
			if(((pnode->isunix != 0) && (strcmp(pnode->fullpath, fullpath) == 0)) ||
				((pnode->isunix == 0) && (stricmp(pnode->fullpath, fullpath) == 0))) {
				id = pnode->id;
				break;
			}
		}
	}
	return id;
}

int GetNodeIdFromSplit(PPathGraph graph, char* path, char* filename, int isunix) {
	PSimpleLinkedListElement ptr = NULL;
	char* fullpath = NULL;
	int id = -1;

	if (graph && fullpath) {
		fullpath = concat_path(path, filename, isunix);
		
		if(fullpath) {
			Foreach_FileNodes(&(graph->nodes), pnode){
				if(((isunix != 0) && (strcmp(pnode->fullpath, fullpath) == 0)) ||
					((isunix == 0) && (stricmp(pnode->fullpath, fullpath) == 0))) {
					id = pnode->id;
					break;
				}
			}
			
			free(fullpath);
		}
	}
	return id;
}

int InsertNode(PPathGraph graph, char* path, char* filename, int type, int isunix) {
	int found = 0;
	char* fullpath = NULL;
	int id = -1;
	
	if(graph && path && filename) {
		
		if(type == 1) {
			Foreach_FileNodes(&(graph->nodes), pnode) {
				if(((isunix != 0) && (strcmp(pnode->fullpath, filename) == 0)) ||
					((isunix == 0) && (stricmp(pnode->fullpath, filename) == 0))) {
					found = 1;
					break;
				}
			}
			
			if(found == 0) {
				Append_FileNodes(&(graph->nodes), path, filename, type, isunix);
				
				id = GetNodeId(graph, filename);
			}
		} else {
			//printf("%p\n", ((PFileNodes)((&(graph->nodes))->pointer)));
			fullpath = concat_path(path, filename, isunix);
			
			if(fullpath) {
				// printf("%p\n", ((PFileNodes)((&(graph->nodes))->pointer)));
				Foreach_FileNodes(&(graph->nodes), pnode) {
					// printf("%p\n", pnode);
					// printf("%s\n", pnode->fullpath);
					// printf("%s\n", fullpath);
					if(((isunix != 0) && ((strcmp(pnode->fullpath, fullpath) == 0)||
											(strcmp(pnode->fullpath, filename) == 0))) ||
						((isunix == 0) && ((stricmp(pnode->fullpath, fullpath) == 0)||
											(stricmp(pnode->fullpath, filename) == 0)))) {
						found = 1;
						break;
					}
				}
				
				if(found == 0) {
					Append_FileNodes(&(graph->nodes), path, filename, type, isunix);
					
					id = GetNodeId(graph, fullpath);
				}
				free(fullpath);
			}
		}
	}
	
	if(id == -1){
		fullpath = concat_path(path, filename, isunix);
		
		if(fullpath) {
			id = GetNodeId(graph, fullpath);
			free(fullpath);
		}
		if(id == -1) {
			id = GetNodeId(graph, filename);
		}
	}
	
	return id;
}

const char* GetNodeFullPath(PPathGraph graph, int id) {
	PSimpleLinkedListElement ptr = NULL;
	char* str = NULL;

	if (graph) {
		Foreach_FileNodes(&(graph->nodes), pnode){
			if (pnode->id == id) {
				str = pnode->fullpath;
				break;
			}
		}
	}
	return str;
}

void InsertLink(PPathGraph graph, char* path, char* start, char* end, int type, int isunix) {
	PIncludeLinks newlink = NULL;
	PSimpleLinkedListElement ptr = NULL;
	int found = 0;
	int id_start, id_end;
	
	if (graph) {
		//printf("%p\n", ((PFileNodes)(graph->nodes.pointer)));
		id_start = InsertNode(graph, path, start, 0, isunix);
		id_end = InsertNode(graph, path, end, type, isunix);

		if ((id_start != -1) && (id_end != -1)) {
			Foreach_IncludeLinks(&(graph->links), plink) {
				// find start in Nodes
				if ((plink->start == id_start) && (plink->end == id_end)) {
					found = 1;
					break;
				}
			}
		}

		if (found == 0) {
			// comfirm node in node list
			if(id_start == -1) {
				id_start = InsertNode(graph, path, start, 0, isunix);
			}
			
			if(id_end == -1) {
				id_end = InsertNode(graph, path, end, type, isunix);
			}
			
			if ((id_start != -1) && (id_end != -1)) {
				Append_IncludeLinks(&(graph->links), type, id_start, id_end);
			}
		}
	}
}

void _estrcpy(char* target, char* source) {
	int i, top = 0;
	for(i=0;source[i];i++){
		if(source[i] == '\\'){
			target[top++] = '\\'; // double that
		}
		target[top++] = source[i];
	}
	target[top] = '\0';
}

void WriteDotFileGraph(PPathGraph graph, char* filename) {
	PFileNodes* nodes;
	FILE* fp = NULL;
	int i, j = -1;
	char* fullpath = NULL, * pointer = NULL;
	char escapedpath[1025] = "", escapedfile[1025] = ""; 
	
	if (graph && filename) {
		fp = fopen(filename, "w");
		
		if (fp) {
			fprintf(fp, "digraph g {\n");
			
			Foreach_IncludeLinks(&(graph->links), ptr) {
				_estrcpy(escapedpath, GetNodeFullPath(graph, ptr->start));
				_estrcpy(escapedfile, GetNodeFullPath(graph, ptr->end));
				fprintf(fp, "   \"%s\" -> \"%s\" [color=%s];\n", escapedpath, escapedfile, ptr->type?"blue":"red");
			}
			
			Foreach_FileNodes(&(graph->nodes), ptr) {
				fullpath = GetNodeFullPath(graph, ptr->id);
				j=-1;
				for(i=0;fullpath[i];i++) {
					if(fullpath[i] == '\\' || fullpath[i] == '/') {
						j = i;
					}
				}
				
				if(j == -1) {
					pointer = fullpath;
				} else {
					pointer = &fullpath[j+1];
				}
				
				_estrcpy(escapedpath, fullpath);
				_estrcpy(escapedfile, pointer);
				fprintf(fp, "   \"%s\" [label=\"%s\" color=%s];\n", escapedpath, escapedfile, ptr->exist?"blue":"red");
			}
			fprintf(fp, "}\n");
			fclose(fp);
		}
	}
}

