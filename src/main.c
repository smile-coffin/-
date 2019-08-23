#include "file_io.h"
#include "log_in.h"
#include "display.h"
#include "key.h"

//#define b

void initialization_system()
{

    init_log();

    Read_user();
  
    Initialization_window();
}

void Login_and_registration_interface()
{
    int select;
    while (1)
    {
        select = show_log();
        if(select == DOWN)
        {
            registered();
            continue;
        }
        if(select == UNDER)
        {
            if(log_in()) break;
            else continue;
        }
    }
}
void input_debugging()
{
    printf("033 = %d\n",'\033');
    system("stty -echo");		  // 关回显
    system("stty -icanon");		  // 关缓冲
    char c;
    //bzero(c,5);
    while(1)
    {
            printf("%d\n",getchar());
    }
}
int main(void)
{
    //input_debugging();

    //初始化系统
    initialization_system();

    //登录和注册
    Login_and_registration_interface();

    //成功登录后的窗口
    Main_interface();

    

    return 0;
}
