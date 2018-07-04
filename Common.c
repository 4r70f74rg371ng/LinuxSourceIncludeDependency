
#include "Common.h"
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <windows.h>

char* concat_path(char* dir, char* rpath, int isunix) {
	char* fpath = NULL;
	int len1, len2;
	int top, backtop;
	int i;

	if (dir && rpath) {
		len1 = strlen(dir);
		len2 = strlen(rpath);
		fpath = (char*)malloc(sizeof(char)*(len1 + len2 + 3));

		if (fpath) {
			// input first path
			for (top = i = 0; dir[i]; i++) {
				if ((dir[i] != '\\') && (dir[i] != '/')) {
					fpath[top++] = dir[i];
				}
				else if ((top > 0) && ((fpath[top - 1] != '\\') && (fpath[top - 1] != '/'))) {
					if (isunix) {
						fpath[top++] = '/';
					}
					else {
						fpath[top++] = '\\';
					}
				}
				else if (top == 0) {
					if (isunix) {
						fpath[top++] = '/';
					}
					else {
						fpath[top++] = '\\';
					}
				}
			}

			// make last is splitter
			if ((top > 0) && (fpath[top - 1] != '\\') && (fpath[top - 1] != '/')) {
				if (isunix) {
					fpath[top++] = '/';
				}
				else {
					fpath[top++] = '\\';
				}
			}

			if ((top == 0) || ((((rpath[0] >= 'a') && (rpath[0] <= 'z')) || ((rpath[0] >= 'A') && (rpath[0] <= 'Z'))) && rpath[1] && rpath[1] == ':')) {
				for (top = i = 0; rpath[i]; i++) {
					if ((rpath[i] != '\\') && (rpath[i] != '/')) {
						fpath[top++] = rpath[i];
					}
					else if ((top > 0) && ((fpath[top - 1] != '\\') && (fpath[top - 1] != '/'))) {
						if (isunix) {
							fpath[top++] = '/';
						}
						else {
							fpath[top++] = '\\';
						}
					}
					else if (top == 0) {
						if (isunix) {
							fpath[top++] = '/';
						}
						else {
							fpath[top++] = '\\';
						}
					}
				}
			}
			else {

				// concatenation
				for (i = 0; rpath[i]; i++) {
					if ((rpath[i] == '.') &&
						rpath[i + 1] && (rpath[i + 1] == '.') &&
						rpath[i + 2] && ((rpath[i + 2] == '/') || (rpath[i + 2] == '\\'))) {
						if (top > 0) {
							backtop = top;
							top--;
							// back one
							while ((top > 0) && (fpath[top - 1] != '/') && (fpath[top - 1] != '\\')) {
								top--;
							}

							if (top < 0) {
								top = 0;
							}

							if ((top == 0) && (backtop >= 2) && (((fpath[0] >= 'a') && (fpath[0] <= 'z')) || ((fpath[0] >= 'A') && (fpath[0] <= 'Z'))) && fpath[1] == ':') {
								top = 2;
								if (isunix) {
									fpath[top++] = '/';
								}
								else {
									fpath[top++] = '\\';
								}
							}
							else if ((top == 0) && isunix) {
								fpath[top++] = '/';
							}
						}

						i += 2;
					}
					else if ((top > 0) && (fpath[top - 1] != '\\') && (fpath[top - 1] != '/') &&
						((rpath[i] == '\\') || (rpath[i] == '/'))) {
						if (isunix) {
							fpath[top++] = '/';
						}
						else {
							fpath[top++] = '\\';
						}
					}
					else if ((rpath[i] == '.') &&
						rpath[i + 1] && ((rpath[i + 1] == '/') || (rpath[i + 1] == '\\'))) {
						// ./ => bypass
					}
					else if ((i == 1) && (rpath[i] == ':')) {
						fpath[top++] = rpath[i];
					}
					else  if (((rpath[i] >= 'a') && (rpath[i] <= 'z')) ||
						((rpath[i] >= 'A') && (rpath[i] <= 'Z')) ||
						((rpath[i] >= '0') && (rpath[i] <= '9')) ||
						(rpath[i] == '-') || (rpath[i] == '_') || (rpath[i] == '_') || (rpath[i] == '.')) {
						fpath[top++] = rpath[i];
					}
				}
			}

			fpath[top] = '\0';
		}
	}

	return fpath;
}

int is_file_exist(char* path) {
   DWORD       fileAttr;
   fileAttr = GetFileAttributesA(path);
   if (0xFFFFFFFF == fileAttr)
       return 0;
   return 1;
}

