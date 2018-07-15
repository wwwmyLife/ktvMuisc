#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#define MAX_SONG     10000   //最大歌曲数
#define LENGTH_OF_ADMIN  10    //账号最大长度
#define LENGTH_OF_PASS  6    //密码最大长度
char songfile[10]="song.txt";
char adminfile[10]="admin.txt";
int denglucounter=5;
struct adminnode    //管理员结构体定义
{
    char ad_min[LENGTH_OF_ADMIN+1];     //管理员名
    char password[LENGTH_OF_PASS+1];    //密码
    struct adminnode *next;             //定义结构体指针
};
typedef struct adminnode *admin;
struct songnode     //歌曲结构体定义
{
    int songID;             //歌曲编号
    char songname[20];      //歌曲名
    char singer[16];        //歌手姓名
    int status;         //歌曲状态，0表示正在播放，1表示未播放
    char pingyin[10];    //歌曲名每个字首字母
    struct songnode *next;
};
typedef struct songnode strsong;  //歌曲结构体类型
typedef strsong *song;             //定义结构体指针

int mainMenu();                 //主菜单
int menuuser();                 //用户主菜单
int menuadmin();                //管理员菜单
void bofanglan(song head1);     //播放栏

void usersystem(song head);              //用户模块
void adminsystem(int c,song head);       //管理员模块

song readsongfile();                     //从文件中读取文件到链上，返回头结点地址
admin readadminfile();                   //从文件读取管理员账号密码信息
void writesongtofile(song head);         //将链表歌曲信息写入文件
void writeadmintofile(admin head2);      //将管理员账号密码信息写入文件
int login();                             //管理员账号密码验证
void searchsongID(song head1,song head); //通过歌曲编号查找歌曲，并加入已点队列
void addsongtoplay(song head1,song p);   //添加歌曲进入播放队列
void printsinger(song head);             //显示所有歌手
void indexsearchsinger(song head1,song head);//模糊查询歌手
void searchsongName(song head1,song head);   //通过歌曲名查找歌曲
void searchpingyin(song head1,song head);    //通过歌曲名拼音查找歌曲
void printSong(int c,song head);             //分页显示所有歌曲
void printplaySong(song head1);              //显示播放队列的歌曲
void playsong(song head1);                   //播放第一首已点歌曲
void nextsong(song head1);                   //切歌，下一首
void sticksong(song head1);                  //置顶已点歌曲
void deleteplaysong(song head1);             //删除播放队列歌曲
void yiaddsong(song head);                   //逐个添加歌曲
int ScarchSameSong(char songnsme[],char singer[]);//查找是否含有相同歌曲
void duoaddsong(song head);                  //批量添加歌曲
void deletesong(song head);                  //删除歌曲
void sortsong(song head);                    //通过歌曲名拼音进行排序
void xiugaiadmin(admin head2);               //修改密码
void gotox(int x);                        //光标跳转函数

void gotox(int x)       //光标跳转函数
{
    int i;
    for (i=0;i<x-1;i++)
        putchar('\n');
}

int mainMenu()         //主菜单
{
    int c,i;
    gotox(6);
    printf("\t\t\t        KTV点歌系统--小V\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*         1  用户直达\t\t*\n");
    printf("\t\t\t*         2  管理员登录\t\t*\n");
    printf("\t\t\t*         0  退出系统\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t请输入选项[ ]\b\b");
    scanf("%d",&c);
    return c;
}

int menuuser()         //用户主菜单
{
    int c,i;
    gotox(3);
    printf("\t\t\t        KTV点歌系统--小V\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*         1  歌手点歌\t\t*\n");
    printf("\t\t\t*         2  歌曲搜素\t\t*\n");
    printf("\t\t\t*         3  拼音点歌\t\t*\n");
    printf("\t\t\t*         4  所有歌曲\t\t*\n");
    printf("\t\t\t*         5  已点歌曲\t\t*\n");
    printf("\t\t\t*         6  切    歌\t\t*\n");
    printf("\t\t\t*         0  退    出\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t请输入选项[ ]\b\b");
    scanf("%d",&c);
    return c;
}

int menuadmin()        //管理员菜单
{
    int c,i;
    gotox(3);
    printf("\t\t\t         KTV点歌系统--小V\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*         1  所有歌曲\t\t*\n");
    printf("\t\t\t*         2  添加歌曲\t\t*\n");
    printf("\t\t\t*         3  批量导入歌曲\t*\n");
    printf("\t\t\t*         4  删除歌曲\t\t*\n");
    printf("\t\t\t*         5  歌曲排序\t\t*\n");
    printf("\t\t\t*         6  修改密码\t\t*\n");
    printf("\t\t\t*         0  退    出\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t请输入选项[ ]\b\b");
    scanf("%d",&c);
    return c;
}

void bofanglan(song head1)      //播放栏
{
    song p;
    p=head1->next;
    int counter=0;
    while(p)
        {
            p=p->next;
            counter++;
        }
        p=head1->next;
        gotox(4);
        if(counter>=2)
        {
            printf("\t    正在播放： %s--%s",p->songname,p->singer);
            printf("\t下一首： %s--%s",p->next->songname,p->next->singer);
            printf("\t已点 %d 首",counter);
        }
        else
        {
            if(counter==1)
            {
                printf("\t    正在播放： %s--%s",p->songname,p->singer);
                printf("\t下一首： 请点歌曲！");
                printf("\t已点 %d 首",counter);
            }
            else
            {
                printf("\t    正在播放： 请点歌曲！");
                printf("\t下一首： 请点歌曲！");
                printf("\t已点 %d 首",counter);
            }
        }
}








