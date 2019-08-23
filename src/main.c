#include "File_io.H"
#include "log_in.H"
#include "display.H"
#include "key.H"

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