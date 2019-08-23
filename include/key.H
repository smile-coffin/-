#ifndef __KEY_H
#define __KEY_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

extern int getInput(void);

/* 按键枚举 */
enum key {
   DOWN,    			// 上
   UNDER,                //下
   LEFT,    			// 左
   RIGHT,   			// 右
   ENTER,               // 回车
   CHANGE,  			// 变化
   STOP,    			// 停止
   EXIT,    			// 退出
   UNKNOW,  			// 未知
};

#endif