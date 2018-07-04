#include "SimpleGraph.h"
#incldue "Common.h"

BOOL initial_filenodes(SimpleLinkedList* linked_list, SimpleLinkedListElement* pointer, void* data, void* param){
	// check whether linked list 
	PFileNodes pargfilenode = (PFileNodes)param;
	PFileNodes fnpointer = ((PFileNodes)(pointer));
	
	if(pointer && param) {
		fnpointer->id = linked_list->maximum + 1;
		fnpointer->isunix = pargfilenode->isunix;
		fnpointer->fullpath = concat_path(pargfilenode->path, pargfilenode->filename, 0);
		if(fnpointer->fullpath == NULL){
			return FALSE;
		}
		fnpointer->exist = is_file_exist(fnpointer->fullpath);
		fnpointer->path = (char*)malloc(sizeof(char)*(strlen(pargfilenode->path)+1));
		if(fnpointer->path == FALSE){
			return FALSE;
		}
		strcpy(fnpointer->path, strlen(pargfilenode->path));
		
		fnpointer->filename = (char*)malloc(sizeof(char)*(strlen(pargfilenode->filename)+1));
		if(fnpointer->filename == FALSE){
			return FALSE;
		}
		strcpy(fnpointer->filename, strlen(pargfilenode->filename));
		return TRUE;
	}
	return FALSE;
}

void free_filenodes(SimpleLinkedList* linked_list, SimpleLinkedListElement* pointer, void*param){
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
	}
}

void free_includelinks(SimpleLinkedList* linked_list, SimpleLinkedListElement* pointer, void*param){
	// do nothing ...
}


void InitGraph(PGraph graph) {
	if (graph) {
		Initial_FileNodes(&(graph->nodes));
		Initial_IncludeLinks(&(graph->links));
	}
}

void CleanupGraph(PGraph graph) {
	if (graph) {
		Clean_FileNodes(&(graph->nodes));
		Clean_IncludeLinks(&(graph->links));
	}
}

void InsertNode(PGraph graph, char* path, char* data) {
	char* fullpath = NULL;

	if (graph) {
		
		fullpath = concat_path(path, data, 0);
		
		if(fullpath) {
			
			Foreach_FileNodes(graph->nodes, ptr){
				if(stricmp(ptr->fullpath, ))
			} 
		}
	}
}

void InsertLink(PGraph graph, int start, int end) {
	PIntLink newlink = NULL;
	PSimpleLinkedListElement ptr = NULL;
	int found = 0;

	if (graph) {
		for (ptr = graph->nodes.pointer; ptr; ptr = ptr->next) {
			if ((((PIntLink)(ptr->data))->start == start) && (((PIntLink)(ptr->data))->end == end)) {
				found = 1;
				break;
			}
		}

		if (found == 0) {
			// comfirm node in node list
			InsertNode(graph, start);
			InsertNode(graph, end);

			newlink = (PIntLink)malloc(sizeof(IntLink));
			newlink->start = start;
			newlink->end = end;
			SimpleLinkedList_Append(&(graph->links), (void*)newlink, NULL);
		}
	}
}

void WriteDotFileGraph(PGraph graph, char* filename) {
	PIntNode* nodes;
	FILE* fp = NULL;
	int* nodedatas;
	size_t lennodes;
	int i, j;

	PSimpleLinkedListElement ptr = NULL;
	if (graph && filename) {
		fopen_s(&fp, filename, "w");

		if (fp) {

			fprintf(fp, "digraph g {\n   node[shape = plaintext]; \n");

			for (ptr = graph->links.pointer; ptr; ptr = ptr->next) {
				fprintf(fp, "   A%d -> A%d ;\n", ((PIntLink)ptr->data)->start, ((PIntLink)ptr->data)->end);
			}

			// convert to native int array
			SimpleLinkedList_ConvertArray((&graph->nodes), (void***)&nodes, &lennodes);
			nodedatas = (int*)malloc(sizeof(int)*(lennodes));
			for (i = 0; i < lennodes; i++) {
				nodedatas[i] = nodes[i]->data;
			}
			free(nodes);

			// sorting (selection sort)
			for (i = 0; i < (lennodes - 1); i++) {
				for (j = i + 1; j < lennodes; j++) {
					if (nodedatas[i] > nodedatas[j]) {
						nodedatas[i] ^= nodedatas[j];
						nodedatas[j] ^= nodedatas[i];
						nodedatas[i] ^= nodedatas[j];
					}
				}
			}

			fprintf(fp, "   { rank=same; ");
			for (i = 0; i < lennodes; i++) {
				fprintf(fp, "A%d ", nodedatas[i]);
			}
			fprintf(fp, "}\n}");
		}
		fclose(fp);
	}
}

void WriteDotFileGraph2(PGraph graph, char* filename) {
	PIntNode* nodes;
	FILE* fp = NULL;
	int* nodedatas;
	size_t lennodes;
	int i, j;

	PSimpleLinkedListElement ptr = NULL;
	if (graph && filename) {
		fopen_s(&fp, filename, "w");

		if (fp) {

			fprintf(fp, "digraph g {\n   node[shape = plaintext]; \n");

			for (ptr = graph->links.pointer; ptr; ptr = ptr->next) {
				fprintf(fp, "   A%d -> A%d ;\n", ((PIntLink)ptr->data)->start, ((PIntLink)ptr->data)->end);
			}

			// convert to native int array
			SimpleLinkedList_ConvertArray((&graph->nodes), (void***)&nodes, &lennodes);
			nodedatas = (int*)malloc(sizeof(int)*(lennodes));
			for (i = 0; i < lennodes; i++) {
				nodedatas[i] = nodes[i]->data;
			}
			free(nodes);

			// sorting (selection sort)
			for (i = 0; i < (lennodes - 1); i++) {
				for (j = i + 1; j < lennodes; j++) {
					if (nodedatas[i] > nodedatas[j]) {
						nodedatas[i] ^= nodedatas[j];
						nodedatas[j] ^= nodedatas[i];
						nodedatas[i] ^= nodedatas[j];
					}
				}
			}

			fprintf(fp, "   { rank=same; ");
			for (i = 0; i < lennodes; i++) {
				fprintf(fp, "A%d ", nodedatas[i]);
			}
			fprintf(fp, "}\n}");
		}
		fclose(fp);
	}
}


