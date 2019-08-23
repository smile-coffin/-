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
int main(void)
{
    //初始化系统
    initialization_system();

    //登录和注册
    Login_and_registration_interface();

    Main_interface();

    return 0;
}
