#include "key.h"

int getInput(void)
{
    char key;

    key = fgetc(stdin);

    if (key == '\033' && fgetc(stdin) == '[') // 方向键
    {
        switch (fgetc(stdin))
    	{
    	    case 'A': return DOWN;
    	    case 'B': return UNDER;
    	    case 'C': return RIGHT;
    	    case 'D': return LEFT;
    	}
    }
    else if (key == 27)    // 退出键
    {
        return EXIT;
    }
    else if (key == ' ')    // 空格键-暂停游戏
    {
        return STOP;
    }
    else if(key == '\n')
    {
        return ENTER;
    }
    else                    // 其它不相关的键
        return UNKNOW;
}
