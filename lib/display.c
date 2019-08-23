#include "display.H"
#include "key.H"
#include "log_in.H"
char gameArea[ROW][COL] = {0};   	// 游戏区域数据
/*******************************************************************************
* 函  数  名      : Terminal_ettings
* 描      述      : 设置终端.
* 输      入      : 0、其它.
* 返      回      : .
*******************************************************************************/
void Terminal_ettings(int select)
{
    if(select == 0)
    {
        system("stty -icanon");		  // 关缓冲
        system("stty -echo");		  // 关回显
        fprintf(stdout,"\033[?25l");  // 关闭鼠标显示
    }
    else
    {
        /* 恢复终端设置 */
        system("stty icanon");          // 恢复缓冲
        system("stty echo");            // 恢复回显
        fprintf(stdout,"\033[?25h");    // 恢复鼠标显示
    }
    
}
/*******************************************************************************
* 函  数  名      : Initialization_window
* 描      述      : 初始化显示数据.
* 输      入      : .
* 返      回      : .
*******************************************************************************/
void Initialization_window(void)
{
    int i;

	/* 屏幕设置 */
	printf("\033[2J");			  // 清屏

    Terminal_ettings(0);
    /* 初始化行 */
    for (i = 0; i < COL; i++)
    {
        gameArea[0][i]     = 8;   // 第0行
        gameArea[ROW-1][i] = 8;   // 最后一行
    }
    /* 初始化列 */
    for (i = 0; i < ROW; i++)
    {
        gameArea[i][0]     = 8;  // 第0列
        gameArea[i][COL-1] = 8;  // 最后一列
    }

}
/*******************************************************************************
* 函  数  名      : Clear_data
* 描      述      : 清除窗口的数据.
* 输      入      : .
* 返      回      : .
*******************************************************************************/
void Clear_data(void)
{
    for(int i = 1; i < ROW-1; i++)
    {
        for (int j = 1; j < COL-1; j++)
        {
            gameArea[i][j]     = 0;  
        }    
    }
}
/*******************************************************************************
* 函  数  名      : Print_data
* 描      述      : 把数据打印出来了.
* 输      入      : .
* 返      回      : .
*******************************************************************************/
void Print_data(void)
{
    /* 定位到第一行第一列 */
    fprintf(stdout,"\033[1;1H");
    fflush(stdout);

    /* 打印所有数据 */
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
    	{
            if (gameArea[i][j] == 0)       // 空白区域
            {
                fprintf(stdout,"  ");
            }
    	    else if (gameArea[i][j] == 8)  // 边界区域
            {
                fprintf(stdout,"\033[40m  \033[0m");
            }
            else                           // 方块区域
            {
                fprintf(stdout,"\033[%dm[]\033[0m",gameArea[i][j]+40);
            }
    	}
	    fputc('\n',stdout);
    }
    fprintf(stdout,"\n\n");
}
/*******************************************************************************
* 函  数  名      : Redisplay
* 描      述      : 清空界面后打印.
* 输      入      :行、列，字符 .
* 返      回      : .
*******************************************************************************/
void Redisplay(int row, int col,char *s)
{
    Clear_data();

    Print_data();

    fprintf(stdout,"\033[%d;%dH%s\n",row,col,s);
}
/*******************************************************************************
* 函  数  名      : show_log
* 描      述      : 登录和注册的选择界面.
* 输      入      : .
* 返      回      : 注册返回DOWN 、登录返回UNDER.
*******************************************************************************/
int show_log(void)
{
    Print_data();

    /* 打印提示信息 */
    fprintf(stdout,"\033[4;%dH登录界面",MID);
    fprintf(stdout,"\033[8;%dH->注册",MID);
    fprintf(stdout,"\033[12;%dH  登录",MID);

    int key,select = DOWN;
    while (1)
    {
        key = getInput();
        switch (key)
    	{
    	    case DOWN  : 
                        fprintf(stdout,"\033[8;%dH->注册",MID);
                        fprintf(stdout,"\033[12;%dH  登录",MID);
                        select = key;
    	                break;
    	    case UNDER:
                        fprintf(stdout,"\033[8;%dH  注册",MID);
                        fprintf(stdout,"\033[12;%dH->登录",MID);
                        select = key;
    	                break;
            case ENTER:
                        return select;//回车结束输入，返回结果
            case EXIT:
                        Terminal_ettings(1);
                        printf("\n");
                        exit(0);
    	    case UNKNOW: continue;
    	}
    }
    return 0;
}
/*******************************************************************************
* 函  数  名      : show_Registration_interface
* 描      述      : 注册的窗口.
* 输      入      : .
* 返      回      : .
*******************************************************************************/
void show_Registration_interface()
{
    Clear_data();

    Print_data();

    /* 打印提示信息 */
    fprintf(stdout,"\033[4;%dH注册",MID);
    fprintf(stdout,"\033[8;%dH账号:",MID-10);
    fprintf(stdout,"\033[10;%dH密码:",MID-10);

}
/*******************************************************************************
* 函  数  名      : login_interface
* 描      述      : 登录的窗口.
* 输      入      : .
* 返      回      : .
*******************************************************************************/
void login_interface()
{
    Clear_data();

    Print_data();

    /* 打印提示信息 */
    fprintf(stdout,"\033[4;%dH登录",MID);
    fprintf(stdout,"\033[8;%dH账号:",MID-10);
    fprintf(stdout,"\033[10;%dH密码:",MID-10);
}

void gameEnd(void)
{


    /* 恢复终端设置 */
    system("stty icanon");          // 恢复缓冲
    system("stty echo");            // 恢复回显
    fprintf(stdout,"\033[?25h");    // 恢复鼠标显示

    /* 尾部处理 */
    fprintf(stdout,"\033[200;1H");  // 定位光标到最后一行
    exit(0);                        // 退出程序
}
void Main_interface()
{
    Redisplay(10,MID,"欢迎登录");
    Terminal_ettings(1);
    sleep(3);
}