#ifndef __LOG_IN_H
#define __LOG_IN_H

#include <stdbool.h>
#include <ctype.h>

extern void init_log();

extern int registered();

extern int Read_user();

extern int Judge_the_application(char *user_name,char *password);

extern bool log_in();

//extern void login_interface();

#endif