#ifndef _COMMON_H_
#define _COMMON_H_
#pragma once

int is_file_exist(char* path);
char* concat_path(char* dir, char* rpath, int isunix);

#endif // _COMMON_H_
