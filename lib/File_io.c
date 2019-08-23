#include "File_io.H"

/*******************************************************************************
* 函  数  名      : Create_file
* 描      述      : 创建文件.
* 输      入      : 路径名/777.
* 返      回      : 成功返回0，失败返回-1.
*******************************************************************************/
int Create_file(const char * pathname, int mode_tmode)
{
    return creat(pathname,mode_tmode);
}

//可打印下个路劲的文件内容 列：p/t.txt
//../返回 上级路劲
/*******************************************************************************
* 函  数  名      : Print_file_content
* 描      述      : 打印文件内容.
* 输      入      : file_name.
* 返      回      : 0.
*******************************************************************************/
int Print_file_content(char *file_name)
{
    FILE *fp;
    char c;
    if((fp = fopen(file_name,"r")) == NULL)
    {
        //打开失败
        return -1;
    }
    //fgetc 由文件中读取一个字符
    while ((c = fgetc(fp)) != EOF)
    {
        printf("%c",c);
    }   
    fclose(fp);
    return 0;
}
/*******************************************************************************
* 函  数  名      : data_input
* 描      述      : 向指定文件写入内容.
* 输      入      : 文件名\打开模式\写入的内容.
* 返      回      : 0.
*******************************************************************************/
int data_input(char *file_name,char *mode,char *content)
{
    FILE *fp;
    if((fp = fopen(file_name,mode)) == NULL)
    {
        //打开失败
        return -1;
    }
    //fputc 将指定字符写入文件流中
    while (*content != '\0')
    {
        if(fputc(*content,fp) == EOF)
            return -1;
        content ++;
    }   
    fclose(fp);
    return 0;
}
/*******************************************************************************
* 函  数  名      : Copy_file
* 描      述      : 复制文件.
* 输      入      : file_name\file_name1.
* 返      回      : 0.
*******************************************************************************/
int Copy_file(char *file_name,char *file_name1)
{
    FILE *fp;
    char c[10000] = {'\0'};
    int i = 0;
    if((fp = fopen(file_name,"r")) == NULL)
    {
        //打开失败
        printf("文件打开失败\n");
        return -1;
    }
    //fgetc 由文件中读取一个字符
    while ((c[i] = fgetc(fp)) != EOF)
    {
        i++;
    }
    fclose(fp);  
     
    if(data_input(file_name1,"w",c) != 0)
    {
        printf("复制失败\n");
    }
    else
    {
        printf("复制成功\n");
    }    
    return 0;
}
/*******************************************************************************
* 函  数  名      : Create_directory
* 描      述      : 创建目录.
* 输      入      : 目录名\777.
* 返      回      : 0.
*******************************************************************************/
int Create_directory(char *Path,int mode)
{
    if(access(Path,F_OK) == 0)
    {
        //printf("目录已存在\n");
        return 0;
    }
    //成功返回0
    return mkdir(Path,mode);
}

//判断是否是".."目录和"."目录,是返回真
bool is_special_dir(const char *path)
{
    if(strcmp(path, "..") == 0 || strcmp(path, ".") == 0)
        return 0;
    else return -1;
    
}

//判断文件属性是目录还是文件
bool is_dir(char *file_name)
{
    DIR *dir;
    if((dir = opendir(file_name)) == NULL)
    {   
        //文件返回-1  
        return -1;    
    }
    else
    {
        closedir(dir);
         //目录返回0  
        return 0;
    }    
}
/*******************************************************************************
* 函  数  名      : Find_file
* 描      述      : 查找文件.
* 输      入      : 在此目录中/查找的文件名.
* 返      回      : 存在返回1.
*******************************************************************************/
int Find_file(char *directory,char *file_name)
{
    DIR *dir;
    struct dirent *ptr;
    //打开目录
    dir = opendir(directory);

    while ((ptr = readdir(dir)) != NULL)
    {
       
        if(is_dir(ptr->d_name))
        { 
            //printf("d_name:%s\n",ptr->d_name);
            if(strcmp(file_name,ptr->d_name))
            {
                //printf("文件已存在\n");
                return 1;//存在返回1
                
            }
        }                   
    }
    //关闭目录
    closedir(dir);
    return 0;
}
/*******************************************************************************
* 函  数  名      : Read_directory
* 描      述      : 读取目录.
* 输      入      : directory.
* 返      回      : 0.
*******************************************************************************/
int Read_directory(char *directory)
{
    DIR *dir;
    struct dirent *ptr;
    //打开目录
    dir = opendir(directory);

    while ((ptr = readdir(dir)) != NULL)
    {
        if(is_special_dir(ptr->d_name) != 0 )
        {
            if(is_dir(ptr->d_name))
                printf("d_name:%s\n",ptr->d_name);
        }        
    }
    //关闭目录
    closedir(dir);
    return 0;
}
/*******************************************************************************
* 函  数  名      : Copy_directory
* 描      述      : 复制目录.
* 输      入      : c_directory/p_directory.
* 返      回      : 无.
*******************************************************************************/
void Copy_directory(char *c_directory,char *p_directory)
{
    DIR *dir;
    struct dirent *ptr;
    char p_path[255];
    char c_path[255];
    //创建一个目录
    Create_directory(p_directory,0777);

    //打开目录
    dir = opendir(c_directory);

    while ((ptr = readdir(dir)) != NULL)
    {           
            sprintf(p_path,"%s/%s",p_directory,ptr->d_name);
            sprintf(c_path,"%s/%s",c_directory,ptr->d_name);
            printf("d_name:%s\n",ptr->d_name);
            printf("p_path:%s\n",p_path);
            printf("c_path:%s\n",c_path);
            if(is_dir(ptr->d_name))
            {
                if(strcmp(ptr->d_name, "File_io") != 0)
                    Copy_file(c_path,p_path);
            }
            else
            {
                if(strcmp(ptr->d_name,p_directory) != 0)
                    if(is_special_dir(ptr->d_name))
                        Copy_directory(c_path,p_path);
                        //Create_directory(p_path,0777);
            }        
    }
    //关闭目录
    closedir(dir);
}
/*******************************************************************************
* 函  数  名      : Encrypted_decoding
* 描      述      : 加密文件.
* 输      入      : 文件名/+-操作.
* 返      回      : 0.
*******************************************************************************/
int Encrypted_decoding(char *file_name,char operating)
{
	FILE *fpr,*fpw;//注意  FILE 为全大写 
	
	char ch,key=0xf7;//初始密钥 
	//命令行参数必须是3个，且第3个参数必须是+/-
    /*
    if(argc!=3 || *argv[2]!='+'&& *argv[2]!='-') 
	{
		printf("usage: 可执行文件名  文件名  +/-");
		return 0; 
	} 
     */

	//以读二进制文件的方式打开指定文件 
	if((fpr=fopen(file_name,"rb"))==NULL)
	{
		printf("cannot open this file");
		return 0;
	 } 
	 //以读写二进制文件的方式打开指定文件
	 //因为会不断对fpw进行写操作【逐字符写】，
	 //为避免后一次写操作覆盖了前一次内容，不可使用"w+" 
	 if((fpw=fopen(file_name,"rb+"))==NULL) 
	 {
	 	printf("cannot open file");
	 	return 0;
	 }
	 
	 //逐字符读取文件fpr中，直至到达文件尾（EOF表示文件尾，值为-1）
	 while((ch=fgetc(fpr))!=EOF) 
	 {
	 	//将读取到的字符加密【与k按位异或】后写到文件fpw中 
	 	fputc(ch^key,fpw);
		/*
		当第三个参数为+【加密】时，
		更新密钥key=ch,使对下一个字符的加密密钥总是前一个字符
		当第3个参数为-【解密】时，
		更新key=ch^k，反向操作，使fputc（）中有(ch^k)^k=ch,达到解密的目的 
		*/ 
		key=(operating== '+')?ch:ch^key;
	 } 
	 fclose(fpr);
	 fclose(fpw);
	 return 0;
 }
#if 0
int main()
{
    //Create_directory("u",0777);
    //Copy_file("tt.txt","te.txt");
    Read_directory("./");
    //data_input("../ma.c","ewwevEFWECJGejvygWJU\n");
    //Print_file_content("te.txt");
    return 0;
}
#endif