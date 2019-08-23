#include "File_io.H"
#include "display.H"
#include "log_in.H"

//int amount_users;
struct user {
    char user_name[30];
    char password[30];
}w,r,*pw = &w,*pr = &r;

void init_log()
{
   Create_directory("./user",0755);
}
/*******************************************************************************
* 函  数  名      : Judge_the_application
* 描      述      : 判断用户是否存在或密码是否正确.
* 输      入      : 用户名.
* 返      回      : 账号和密码正确返回2，账号存在返回1，.
*******************************************************************************/
int Judge_the_application(char *user_name,char *password)
{
    FILE *fp;
    //char name[30] = user_name;
    if((fp = fopen("./user/Ulogin","ab+")) == NULL)
    {
        printf("打开文件失败\n");
        //打开失败
        return -1;
    }
    //遍历文件
    while (1)
    {
        fread(pr,sizeof(struct user),1,fp);
 
        if(r.user_name[0] == '\0')break;  

        if(strcmp(user_name,r.user_name) == 0)
        {
            if(strcmp(password,r.password) == 0)
                return 2;  
            else return 1; 
        }
           
        bzero(r.user_name,30);
        bzero(r.password,30);     
    }

    bzero(r.user_name,30);
    bzero(r.password,30);
    fclose(fp);

    return 0;
}
/*******************************************************************************
* 函  数  名      : Read_user
* 描      述      : 读以注册用户.
* 输      入      : .
* 返      回      : 成功返回0.
*******************************************************************************/
int Read_user()
{
    FILE *fp;
    if((fp = fopen("./user/Ulogin","ab+")) == NULL)
    {
        printf("打开文件失败\n");
        //打开失败
        return -1;
    }
    //遍历文件
    while (1)
    {
        fread(pr,sizeof(struct user),1,fp);
 
        if(r.user_name[0] == '\0')break;  

        printf("账号：%s\n",r.user_name);

        printf("密码：%s\n",r.password);

        bzero(r.user_name,30);
        bzero(r.password,30);     
    }
    fclose(fp);

    return 0;
}
/*******************************************************************************
* 函  数  名      : Input_monitoring
* 描      述      : 获取一个以上的字符（数字或字母）.
* 输      入      : 显示的行坐标和纵坐标\输入的最小长度和最大长度\字符串存放的地址 .
* 返      回      : 成功返回0.
*******************************************************************************/
int Input_monitoring(int coordinate_h,int coordinate_l,int length_short, int length_long, char *Storage)
{
    char buf_cache[30];
    bzero(buf_cache,30);
    int Subscript = 0;

    //恢复终端设置
    Terminal_ettings(1);

    char First_character;
    //bzero(First_character,3);
    char next_character;
    fprintf(stdout,"\033[%d;%dH",coordinate_h,coordinate_l);
    //更新缓冲
    fflush(stdout);
        
    system("stty -echo");		  // 关回显
    system("stty -icanon");		  // 关缓冲

        while(1)
        {
            next_character = fgetc(stdin);           //获取第二个以上的字符              

            if(next_character == 27)                //Esc键退出
            {
                Terminal_ettings(0);
                return -1;
            }

            if(next_character == '\n') 
            {
                if(strlen(buf_cache) >= length_short)
                    break;       //回车结束输入
            }
            else if(next_character == '\033')//判断是否是方向键
            {
                //清除并重新输入
                getchar(); getchar();
                continue;
            }
            else if(next_character == 127)
            {
                if(strlen(buf_cache) >= 1)
                {
                    Subscript--;
                    buf_cache[Subscript] = '\0';

                    fprintf(stdout,"\033[%d;%dH%c",coordinate_h,coordinate_l+Subscript,' ');
                    fprintf(stdout,"\033[%d;%dH",coordinate_h,coordinate_l+Subscript); 
                }
                else continue;               
            }

            else if(strlen(buf_cache) >= length_long)
                continue; 

            else if(isalnum(next_character))
            {
                buf_cache[Subscript] = next_character;
                fprintf(stdout,"\033[%d;%dH%c",coordinate_h,coordinate_l+Subscript,next_character);
                Subscript++;                 
            }               
        }
        sprintf(Storage,"%s",buf_cache);
        /* 
        if(mod == 0)
            sprintf(pw->user_name,"%s",buf_cache);
        else
            sprintf(pw->password,"%s",buf_cache);
        */
        Terminal_ettings(1);      
    return 0;
}
/*******************************************************************************
* 函  数  名      : registered
* 描      述      : 注册.
* 输      入      : .
* 返      回      : 成功返回0.
*******************************************************************************/
int registered()
{
    FILE *fp;
    char user_cache[30];
    char password_cache[30];
    
    if((fp = fopen("./user/Ulogin","ab+")) == NULL)
    {
        printf("打开文件失败\n");
        //打开失败
        return -1;
    }
    while (1)
    {
        //显示注册界面
        show_Registration_interface();

       // while(1);
        //获取账户名
        if(Input_monitoring(8,MID-5,1,8,pw->user_name) == -1) return -1;
       //获取密码
        if(Input_monitoring(10,MID-5,1,8,pw->password) == -1) return -1;

        //设置终端
        Terminal_ettings(0);

        if(Judge_the_application(pw->user_name,""))
        {
            Redisplay(10,MID,"用户已存在");
            sleep(3);
           // while(getchar() != '\n');
            continue;
        }
        break;
    }
      
    //读写的数据指针，字节数，多少个字节数，文件指针
    fwrite(pw,sizeof(struct user),1,fp);

    Redisplay(10,MID,"注册成功");

    sleep(3);

    system("stty -icanon");		  // 关缓冲
    fprintf(stdout,"\033[?25l");  // 关闭鼠标显示

    fclose(fp);

    return 0;
}
/*******************************************************************************
* 函  数  名      : log_in
* 描      述      : 登录操作界面.
* 输      入      : .
* 返      回      :true.
*******************************************************************************/
bool log_in()
{
    while (1)
    {
        //显示登录界面
        login_interface();

        //获取账户名
        if(Input_monitoring(8,MID-5,1,8,pw->user_name) == -1) return false;
       //获取密码
        if(Input_monitoring(10,MID-5,1,8,pw->password) == -1) return false;

        //设置终端
        Terminal_ettings(0);

        int status = 0;
        status = Judge_the_application(pw->user_name,pw->password);

        if(status == 2)
        {
                Redisplay(10,MID,"登录成功");
                sleep(3);
                system("stty -icanon");		  // 关缓冲
                return true;
        }
        else if(status == 1)
        {
            Redisplay(10,MID,"密码错误");
            sleep(3);
            continue;
        }   
        else
        {
            Redisplay(10,MID,"用户不存在");
            sleep(3);
            continue;
        }
    }
    return false;
}