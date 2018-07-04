#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lexer/CLexerTokens.h"
#include "Lexer/CLexerFile.h"
#include "Lexer/CLexerTokenStringMap.h"
#include "Common.h"
#include "DataStructure/PathGraph.h"

PathGraph graph;

void handle_include(char* fullpath,
	char* path,
	char* filename,
	char* ext,
	unsigned char* strcontent,
	unsigned long long size,
	PSimpleLinkedList tokensmap,
	char* preprocessorcontent,
	char* keyword) {
	char* ptr = NULL;
	char* buffer = NULL;
	char* start = NULL, *end = NULL;
	int status = 0;
	int c, i;
	int type = 0;

	for (ptr = preprocessorcontent + strlen(keyword); *ptr; ptr++) {
		c = *ptr;
		switch (status) {
		case 0:
			// unmark will add external include
			/*if (c == '<') {
				status = 1;
				start = ptr + 1;
				type = 1;
			}
			else */if (c == '\"') {
				start = ptr + 1;
				status = 3;
				type = 0;
			}
			break;
		case 1:
			if (c == '>') {
				end = ptr - 1;
				status = 2;
			}
		case 3:
			if (c == '\"') {
				end = ptr - 1;
				status = 4;
			}
		}
		if ((status == 2) || (status == 4)) {
			break;
		}
	}
	if (end == NULL) {
		end = ptr - 1;
	}

	if (start != NULL) {
		buffer = (char*)malloc(sizeof(char)*(end - start + 2));
		for (i = 0; i < (end - start + 1); i++) {
			buffer[i] = start[i];
		}
		buffer[i] = '\0';
		//printf("%s: [+] '%s'\n", fullpath, preprocessorcontent);
		//printf("include file '%s'\n", buffer);

		char* ptr1 = fullpath + strlen(path) + 1, *ptr2 = buffer;
		char* ptr1end = ptr1 + strlen(ptr1)-1, *ptr2end = ptr2 + strlen(ptr2)-1;

		while ((ptr1 < ptr1end) && (*ptr1end) && ((*ptr1end) != '\\') && ((*ptr1end) != '/')) {
			ptr1end--;
			//ptr1--;
		}
		if ((*ptr1end == '\\') || (*ptr1end == '/')) {
			ptr1 = ptr1end + 1;
		}

		while ((ptr2 < ptr2end) && (*ptr2end) && ((*ptr2end) != '\\') && ((*ptr2end) != '/')) {
			ptr2end--;
			// ptr2--;
		}
		if (((*ptr2end) == '\\') || ((*ptr2end) == '/')) {
			ptr2 = ptr2end + 1;
		}

		//printf("%s -> %s\n", ptr1, ptr2);

		/*char* path1, *path2;

		path1 = concat_path(path, ptr1, 0);
		path2 = concat_path(path, ptr2, 0);


		// printf("%s -> %s\n", path1, path2);

		if(!is_file_exist(path2)){

			//system("pause");
		}

		free(path1);
		free(path2);*/
		//InsertLink(&graph, path, ptr1, ptr2);

		InsertLink(&graph, path, ptr1, ptr2, type, 0);

		//system("pause");
		//InsertLink(&graph, path, ptr1, ptr2);
		free(buffer);
	}
}

void handle_preprocessor(char* fullpath,
	char* path,
	char* filename,
	char* ext,
	unsigned char* strcontent,
	unsigned long long size,
	PSimpleLinkedList tokensmap,
	char* preprocessorcontent) {
	char* ptr,*start = NULL, *end = NULL, *buffer = NULL;
	int status = 0;
	int i;

	for (ptr = preprocessorcontent; *ptr; ptr++) {
		switch (status) {
		case 0:
		{
			if ((*ptr) == '#') {
				status = 1;
			}
		}break;
		case 1:
		{
			if ((((*ptr) >= 'a') && ((*ptr) <= 'z')) || (((*ptr) >= 'A') && ((*ptr) <= 'Z'))) {
				start = ptr;
				status = 2;
			}
		}break;
		case 2:
		{
			if (!((((*ptr) >= 'a') && ((*ptr) <= 'z')) || (((*ptr) >= 'A') && ((*ptr) <= 'Z')))) {
				end = ptr - 1;
				status = 3;
			}
		}break;
		}
		if (status == 3) {
			break;
		}
	}
	if (status == 2) {
		end = ptr - 1;
	}

	if (start && end) {

		buffer = (char*)malloc(sizeof(char) * (end - start + 2));

		//printf("handle: %s\n", preprocessorcontent);

		for (i = 0; i < (end - start + 1); i++) {
			buffer[i] = start[i];
		}
		buffer[i] = '\0';
		//printf("'%s'\n", buffer);

		if (strcasecmp(buffer, "include")==0) {
			handle_include(fullpath,path,filename,ext,strcontent,size,tokensmap, preprocessorcontent, buffer);
		}

		free(buffer);
	}
}

int count = 0;

// start doing preprocessor
void my_c_lexer_handler(
		char* fullpath,
		char* path,
		char* filename,
		char* ext,
		unsigned char* strcontent,
		unsigned long long size,
		PSimpleLinkedList tokensmap,
		void* parameter) {
	TokenStringMap* pointer = NULL;
	//printf("[+] lexer %s...%d\n", fullpath, (int)parameter);
	printf("[+] lexer %s...%d\n", fullpath, ++count);

	for (pointer = (TokenStringMap*)tokensmap->pointer; pointer; pointer = (TokenStringMap*)pointer->linked_list.next) {
		// printf("'%s',", pointer->map_element.value);
		if (tokens[pointer->map_element.index].token_id == TOKEN_PREPROCESSOR) {
			//printf("preprocessor value: '%s'\n", pointer->map_element.value);

			// print all preprocess keyword
			handle_preprocessor(fullpath, path, filename, ext, strcontent, size, tokensmap, pointer->map_element.value);
		}
	}
}

void handle_preprocessor2(char* fullpath,
	char* path,
	char* filename,
	char* ext,
	PSimpleLinkedList tokensmap,
	char* preprocessorcontent) {
	char* ptr,*start = NULL, *end = NULL, *buffer = NULL;
	int status = 0;
	int i;

	for (ptr = preprocessorcontent; *ptr; ptr++) {
		switch (status) {
		case 0:
		{
			if ((*ptr) == '#') {
				status = 1;
			}
		}break;
		case 1:
		{
			if ((((*ptr) >= 'a') && ((*ptr) <= 'z')) || (((*ptr) >= 'A') && ((*ptr) <= 'Z'))) {
				start = ptr;
				status = 2;
			}
		}break;
		case 2:
		{
			if (!((((*ptr) >= 'a') && ((*ptr) <= 'z')) || (((*ptr) >= 'A') && ((*ptr) <= 'Z')))) {
				end = ptr - 1;
				status = 3;
			}
		}break;
		}
		if (status == 3) {
			break;
		}
	}
	if (status == 2) {
		end = ptr - 1;
	}

	if (start && end) {

		buffer = (char*)malloc(sizeof(char) * (end - start + 2));

		//printf("handle: %s\n", preprocessorcontent);

		for (i = 0; i < (end - start + 1); i++) {
			buffer[i] = start[i];
		}
		buffer[i] = '\0';
		printf("'%s'\n", buffer);

		free(buffer);
	}
}

void WriteDotFileGraphSpecific(PPathGraph graph, char* filename, char* specific_root) {
	PFileNodes* nodes;
	FILE* fp = NULL;
	int i, j = -1;
	char* fullpath = NULL, * pointer = NULL;
	char escapedpath[1025] = "", escapedfile[1025] = "";
	int id = 0;
	int id_list = 0;

	int changed = 0;
	int *nodesarr = NULL;

	if (graph && filename) {
		fp = fopen(filename, "w");

		if (fp) {
         // find root
         id = -1;
         Foreach_FileNodes(&(graph->nodes), ptr) {
            if(strstr(ptr->filename, specific_root) != NULL) {
               id = ptr->id;
               break;
            }
         }
         // printf("id = %d\n", id);

         nodesarr = (int*)malloc(sizeof(int)*(graph->nodes.maximum+1));

         if(nodesarr && (id != -1)){

            for(i=0;i<=graph->nodes.maximum;i++) {
               nodesarr[i] = 0;
            }

            nodesarr[id] = 1;

            do {
               changed = 0;
               Foreach_IncludeLinks(&(graph->links), ptr) {
                  for(i = 0;i <= graph->nodes.maximum;i++) {
                     if(nodesarr[i] && ((ptr->start == i) || (ptr->end == i))) {
                        if(nodesarr[ptr->start] == 0) {
                           nodesarr[ptr->start] = 1;
                           changed = 1;
                        }
                        if(nodesarr[ptr->end] == 0) {
                           nodesarr[ptr->end] = 1;
                           changed = 1;
                        }
                     }
                  }
               }
            } while(changed);

            fprintf(fp, "digraph g {\n");

            Foreach_IncludeLinks(&(graph->links), ptr) {
               for(i = 0; i <= graph->nodes.maximum; i++) {
                  if(nodesarr[i] && (ptr->start == i)) {
                     _estrcpy(escapedpath, GetNodeFullPath(graph, ptr->start));
                     _estrcpy(escapedfile, GetNodeFullPath(graph, ptr->end));
                     fprintf(fp, "   \"%s\" -> \"%s\" [color=%s];\n", escapedpath, escapedfile, ptr->type?"blue":"red");
                     break;
                  }
               }
            }

            Foreach_FileNodes(&(graph->nodes), ptr) {
               for(i = 0; i <= graph->nodes.maximum; i++) {
                  if(nodesarr[i] && (ptr->id == i)) {
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
               }
            }
            fprintf(fp, "}\n");
            fclose(fp);
         }
         if(nodesarr){
            free(nodesarr);
         }
		}
	}
}

void Test(){
	InitGraph(&graph);

	clexer_enum_cfile_directory("D:\\LinuxSource\\linux-4.9.tar\\linux-4.9\\linux-4.9", my_c_lexer_handler, 1);
	//test_call();

	/*char* sdir = "D:\\LinuxSource\\linux-4.9.tar\\linux-4.9\\linux-4.9";
	clexer_result_dir* dir = clexer_enum_cfile_directory_return(sdir);

	printf("handling dir name: %s\n", dir->dir);
	clexer_result_file* file = NULL;

	TokenStringMap* token = NULL;

	for(file = (pclexer_result_file)dir->files_lexer_result->pointer; file; file = (pclexer_result_file)file->linked_list.next){
      printf("[+] lexer %s...\n", file->fullpath);
      for(token = (TokenStringMap*)file->tokensmap->pointer; token; token = (TokenStringMap*)token->linked_list.next){
         if(tokens[token->map_element.index].token_id == TOKEN_PREPROCESSOR){
            handle_preprocessor2(file->fullpath, file->path, file->filename, file->ext, file->tokensmap, token->map_element.value);
         }
      }
	}

	clexer_result_dir_cleanup(dir);*/

	//WriteDotFileGraph(&graph, "test.dot");
	WriteDotFileGraphSpecific(&graph, "test.dot", "main.c");

	CleanupGraph(&graph);
}

int main(int argc, char *argv[]) {
	InitGraph(&graph);
	clexer_enum_cfile_directory("D:\\LinuxSource\\linux-4.9.tar\\linux-4.9\\linux-4.9", my_c_lexer_handler, 1);
	WriteDotFileGraphSpecific(&graph, "test.dot", "main.c");
	CleanupGraph(&graph);
	return 0;
}

