#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define   ROW    24     // 登录区域的行数
#define   COL    40     // 登录区域的列数

#define MID 40-5        //中间 

extern void Terminal_ettings(int select);

extern void Initialization_window(void);

extern void Clear_data(void);

extern void Print_data(void);

extern void Redisplay(int row, int col,char *s);

extern int show_log(void);

extern void show_Registration_interface();

extern void login_interface();

extern void Main_interface();


#endif