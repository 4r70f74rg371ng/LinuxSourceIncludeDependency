#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "CLexerTokenStringMap.h"
#include "CLexerLexer.h"
#include "CLexerFile.h"
#include "CLexerResult.h"

void clexer_handle_c_file(char* fullpath, char* path, char* filename, char* ext, clexer_handler_tokens_maps_func handler_tokens_maps, void* parameter) {
	PSimpleLinkedList tokensmap;
	FILE* fp = NULL;
	int c = NULL;
	unsigned long long size = 0, i = 0;
	unsigned char* strcontent = NULL;

	fp = fopen(fullpath, "rb");
	if (fp) {

		while (!feof(fp)) {
			c = fgetc(fp);
			if (c == EOF) {
				break;
			}
			size++;
		}


		strcontent = (unsigned char*)malloc(sizeof(unsigned char)*size);

		if (strcontent) {

			fseek(fp, 0, SEEK_SET);

			while (!feof(fp)) {
				c = fgetc(fp);
				if (c == EOF) {
					break;
				}
				strcontent[i] = c;
				i++;
			}

			tokensmap = clexer_handle_c_file_content(fullpath, path, filename, ext, strcontent, size);

			if (tokensmap && handler_tokens_maps) {
				handler_tokens_maps(fullpath, path, filename, ext, strcontent, size, tokensmap, parameter);
			}

			Clean_Map(tokensmap);

			free(strcontent);
		}

		fclose(fp);
	}
}



void clexer_handle_file(char* sPath, clexer_handler_tokens_maps_func handler_tokens_maps, void* parameter) {
	char path[1025] = "", filename[1025] = "", ext[1025] = "";
	int dot, slash, length;
	int i;
	length = strlen(sPath);

	slash = dot = -1;
	for (i = length - 1; i >= 0; i--) {
		if (sPath[i] == '\\') {
			slash = i;
			break;
		}
	}
	if (slash != -1) {
		for (i = length - 1; i > slash; i--) {
			if (sPath[i] == '.') {
				dot = i;
				break;
			}
		}
	}
	else {
		for (i = length - 1; i >= 0; i--) {
			if (sPath[i] == '.') {
				dot = i;
				break;
			}
		}
	}


	// filter no extension file
	if (dot != -1) {
		if (slash != -1) {
			for (i = 0; i < slash; i++) {
				path[i] = sPath[i];
			}
			path[i] = '\0';

			for (i = slash + 1; i < dot; i++) {
				filename[i - slash - 1] = sPath[i];
			}
			filename[i - slash - 1] = '\0';
		}
		else {
			for (i = 0; i < dot; i++) {
				filename[i] = sPath[i];
			}
			filename[dot] = '\0';
		}

		for (i = 0; i < (length - dot - 1); i++) {
			ext[i] = sPath[dot + 1 + i];
		}
		ext[i] = '\0';
		//printf("> Full Path: %s\n", sPath);
		//printf("Path: %s Filename: %s, ext: %s\n", path, filename, ext);
		if (strcmp(ext, "c") == 0 || strcmp(ext, "h") == 0 || strcmp(ext, "cpp") == 0 || strcmp(ext, "hpp") == 0) {
			clexer_handle_c_file(sPath, path, filename, ext, handler_tokens_maps, parameter);
		}
		else {
			//printf("> Full Path: %s\n", sPath);
			//printf("Path: %s Filename: %s ext: %s\n", path, filename, ext);
		}
	}
	else {
		for (i = 0; i < slash; i++) {
			path[i] = sPath[i];
		}
		path[i] = '\0';
		for (i = 0; i < (length - slash - 1); i++) {
			filename[i] = sPath[slash + 1 + i];
		}
		filename[i] = '\0';

		//printf("> Full Path: %s\n", sPath);
		//printf("Path: %s Filename: %s ext: %s\n", path, filename, ext);
	}

}

void clexer_enum_cfile_directory(char* sdir, clexer_handler_tokens_maps_func handler_tokens_maps, void* parameter) {
	WIN32_FIND_DATAA fdFile;
	HANDLE hFind = NULL;

	char sPath[2048];

	//Specify a file mask. *.* = We want everything!
	snprintf(sPath, 2048, "%s\\*.*", sdir);

	if ((hFind = FindFirstFileA(sPath, &fdFile)) != INVALID_HANDLE_VALUE) {
		do{
			//Find first file will always return "."
			//    and ".." as the first two directories.
			if (strcmp(fdFile.cFileName, ".") != 0
				&& strcmp(fdFile.cFileName, "..") != 0) {
				//Build up our file path using the passed in
				//  [sDir] and the file/foldername we just found:
				snprintf(sPath, 2048, "%s\\%s", sdir, fdFile.cFileName);

				//Is the entity a File or Folder?
				if (fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY) {
					//printf("Dir: %s\n", sPath);
					clexer_enum_cfile_directory(sPath, handler_tokens_maps, parameter);
				} else {
					//printf("File %s\n", sPath);
					clexer_handle_file(sPath, handler_tokens_maps, parameter);
				}
			}
		} while (FindNextFileA(hFind, &fdFile)); //Find the next file.

		FindClose(hFind); //Always, Always, clean things up!
	}
}

void clexer_handle_c_file_return(pclexer_result_dir result, char* fullpath, char* path, char* filename, char* ext){
	PSimpleLinkedList tokensmap;
	FILE* fp = NULL;
	int c = NULL;
	unsigned long long size = 0, i = 0;
	unsigned char* strcontent = NULL;

	fp = fopen(fullpath, "rb");
	if (fp) {

		while (!feof(fp)) {
			c = fgetc(fp);
			if (c == EOF) {
				break;
			}
			size++;
		}


		strcontent = (unsigned char*)malloc(sizeof(unsigned char)*size);

		if (strcontent) {

			fseek(fp, 0, SEEK_SET);

			while (!feof(fp)) {
				c = fgetc(fp);
				if (c == EOF) {
					break;
				}
				strcontent[i] = c;
				i++;
			}

			tokensmap = clexer_handle_c_file_content(fullpath, path, filename, ext, strcontent, size);

			if (tokensmap && result) {
				Append_Result(result->files_lexer_result, fullpath, path, filename, ext, tokensmap);
			}

			// Clean_Map(tokensmap);

			free(strcontent);
		}

		fclose(fp);
	}
}

void clexer_handle_file_return(pclexer_result_dir result, char* sdir, char* spath){
   char path[1025] = "", filename[1025] = "", ext[1025] = "";
	int dot, slash, length;
	int i;
	length = strlen(spath);

	slash = dot = -1;

	// find last slash position
	for (i = length - 1; i >= 0; i--) {
		if (spath[i] == '\\') {
			slash = i;
			break;
		}
	}

	// find last dot position
	if (slash != -1) {
		for (i = length - 1; i > slash; i--) {
			if (spath[i] == '.') {
				dot = i;
				break;
			}
		}
	}
	else {
		for (i = length - 1; i >= 0; i--) {
			if (spath[i] == '.') {
				dot = i;
				break;
			}
		}
	}


	// filter no extension file
	if (dot != -1) {
      // has slash, has dot
		if (slash != -1) {
			for (i = 0; i < slash; i++) {
				path[i] = spath[i];
			}
			path[i] = '\0';

			for (i = slash + 1; i < dot; i++) {
				filename[i - slash - 1] = spath[i];
			}
			filename[i - slash - 1] = '\0';
		} else { // no slash, has dot (only filename)
			for (i = 0; i < dot; i++) {
				filename[i] = spath[i];
			}
			filename[dot] = '\0';
		}

		for (i = 0; i < (length - dot - 1); i++) {
			ext[i] = spath[dot + 1 + i];
		}
		ext[i] = '\0';
		//printf("> Full Path: %s\n", spath);
		//printf("Path: %s Filename: %s, ext: %s\n", path, filename, ext);
		if (strcmp(ext, "c") == 0 || strcmp(ext, "h") == 0 || strcmp(ext, "cpp") == 0 || strcmp(ext, "hpp") == 0) {
			printf("Path: %s Filename: %s, ext: %s\n", path, filename, ext);
			clexer_handle_c_file_return(result, spath, path, filename, ext);
		}
		else {
			//printf("> Full Path: %s\n", spath);
			//printf("Path: %s Filename: %s ext: %s\n", path, filename, ext);
		}
	}
	else {
		for (i = 0; i < slash; i++) {
			path[i] = spath[i];
		}
		path[i] = '\0';
		for (i = 0; i < (length - slash - 1); i++) {
			filename[i] = spath[slash + 1 + i];
		}
		filename[i] = '\0';

		//printf("> Full Path: %s\n", spath);
		//printf("Path: %s Filename: %s ext: %s\n", path, filename, ext);
	}
}

void clexer_enum_cfile_directory_return_internal(pclexer_result_dir result, char* sdir){
	WIN32_FIND_DATAA fdFile;
	HANDLE hFind = NULL;
	// clexer_result_dir result;
	char spath[2048] = "";

	//Specify a file mask. *.* = We want everything!
	snprintf(spath, 2048, "%s\\*.*", sdir);
	if ((hFind = FindFirstFileA(spath, &fdFile)) != INVALID_HANDLE_VALUE) {
		do {
			//Find first file will always return "."
			//    and ".." as the first two directories.
			if (strcmp(fdFile.cFileName, ".") != 0
				&& strcmp(fdFile.cFileName, "..") != 0) {
				//Build up our file path using the passed in
				//  [sDir] and the file/foldername we just found:
				snprintf(spath, 2048, "%s\\%s", sdir, fdFile.cFileName);
				//Is the entity a File or Folder?
				if (fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY) {
					//printf("Dir: %s\n", spath);
					clexer_enum_cfile_directory_return_internal(result, spath);
				} else {
					//printf("File %s\n", spath);
					clexer_handle_file_return(result, sdir, spath);
				}
			}
		} while (FindNextFileA(hFind, &fdFile)); //Find the next file.
		FindClose(hFind); //Always, Always, clean things up!
	}
}

pclexer_result_dir clexer_enum_cfile_directory_return(char* sdir){
	WIN32_FIND_DATAA fdFile;
	HANDLE hFind = NULL;
	char spath[2048] = "";
	pclexer_result_dir result = NULL;

	result = (pclexer_result_dir)malloc(sizeof(clexer_result_dir));

	if(result) {
      clexer_result_dir_initial(result, sdir);
      //Specify a file mask. *.* = We want everything!
      snprintf(spath, 2048, "%s\\*.*", sdir);
      if ((hFind = FindFirstFileA(spath, &fdFile)) != INVALID_HANDLE_VALUE) {
         do {
            //Find first file will always return "."
            //    and ".." as the first two directories.
            if (strcmp(fdFile.cFileName, ".") != 0
               && strcmp(fdFile.cFileName, "..") != 0) {
               //Build up our file path using the passed in
               //  [sDir] and the file/foldername we just found:
               snprintf(spath, 2048, "%s\\%s", sdir, fdFile.cFileName);
               //Is the entity a File or Folder?
               if (fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY) {
                  //printf("Dir: %s\n", spath);
                  clexer_enum_cfile_directory_return_internal(result, spath);
               } else {
                  //printf("File %s\n", spath);
                  clexer_handle_file_return(result, sdir, spath);
               }
            }
         } while (FindNextFileA(hFind, &fdFile)); //Find the next file.
         FindClose(hFind); //Always, Always, clean things up!
      }
	}
	return result;
}

