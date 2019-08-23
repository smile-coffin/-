#ifndef __FILE_IO_H
#define __FILE_IO_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

extern int Create_file(const char * pathname, int mode_tmode);

extern int Print_file_content(char *file_name);

extern int data_input(char *file_name,char *mode,char *content);

extern int Copy_file(char *file_name,char *file_name1);

extern int Create_directory(char *Path,int mode);

extern int Read_directory(char *directory);

extern int Find_file(char *directory,char *file_name);

extern void Copy_directory(char *c_directory,char *p_directory);

extern int Encrypted_decoding(char *file_name,char operating);

extern bool is_special_dir(const char *path);

extern bool is_dir(char *file_name);


#endif 
