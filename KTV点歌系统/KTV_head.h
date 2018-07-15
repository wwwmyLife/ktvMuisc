#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#define MAX_SONG     10000   //��������
#define LENGTH_OF_ADMIN  10    //�˺���󳤶�
#define LENGTH_OF_PASS  6    //������󳤶�
char songfile[10]="song.txt";
char adminfile[10]="admin.txt";
int denglucounter=5;
struct adminnode    //����Ա�ṹ�嶨��
{
    char ad_min[LENGTH_OF_ADMIN+1];     //����Ա��
    char password[LENGTH_OF_PASS+1];    //����
    struct adminnode *next;             //����ṹ��ָ��
};
typedef struct adminnode *admin;
struct songnode     //�����ṹ�嶨��
{
    int songID;             //�������
    char songname[20];      //������
    char singer[16];        //��������
    int status;         //����״̬��0��ʾ���ڲ��ţ�1��ʾδ����
    char pingyin[10];    //������ÿ��������ĸ
    struct songnode *next;
};
typedef struct songnode strsong;  //�����ṹ������
typedef strsong *song;             //����ṹ��ָ��

int mainMenu();                 //���˵�
int menuuser();                 //�û����˵�
int menuadmin();                //����Ա�˵�
void bofanglan(song head1);     //������

void usersystem(song head);              //�û�ģ��
void adminsystem(int c,song head);       //����Աģ��

song readsongfile();                     //���ļ��ж�ȡ�ļ������ϣ�����ͷ����ַ
admin readadminfile();                   //���ļ���ȡ����Ա�˺�������Ϣ
void writesongtofile(song head);         //�����������Ϣд���ļ�
void writeadmintofile(admin head2);      //������Ա�˺�������Ϣд���ļ�
int login();                             //����Ա�˺�������֤
void searchsongID(song head1,song head); //ͨ��������Ų��Ҹ������������ѵ����
void addsongtoplay(song head1,song p);   //��Ӹ������벥�Ŷ���
void printsinger(song head);             //��ʾ���и���
void indexsearchsinger(song head1,song head);//ģ����ѯ����
void searchsongName(song head1,song head);   //ͨ�����������Ҹ���
void searchpingyin(song head1,song head);    //ͨ��������ƴ�����Ҹ���
void printSong(int c,song head);             //��ҳ��ʾ���и���
void printplaySong(song head1);              //��ʾ���Ŷ��еĸ���
void playsong(song head1);                   //���ŵ�һ���ѵ����
void nextsong(song head1);                   //�и裬��һ��
void sticksong(song head1);                  //�ö��ѵ����
void deleteplaysong(song head1);             //ɾ�����Ŷ��и���
void yiaddsong(song head);                   //�����Ӹ���
int ScarchSameSong(char songnsme[],char singer[]);//�����Ƿ�����ͬ����
void duoaddsong(song head);                  //������Ӹ���
void deletesong(song head);                  //ɾ������
void sortsong(song head);                    //ͨ��������ƴ����������
void xiugaiadmin(admin head2);               //�޸�����
void gotox(int x);                        //�����ת����

void gotox(int x)       //�����ת����
{
    int i;
    for (i=0;i<x-1;i++)
        putchar('\n');
}

int mainMenu()         //���˵�
{
    int c,i;
    gotox(6);
    printf("\t\t\t        KTV���ϵͳ--СV\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*         1  �û�ֱ��\t\t*\n");
    printf("\t\t\t*         2  ����Ա��¼\t\t*\n");
    printf("\t\t\t*         0  �˳�ϵͳ\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t������ѡ��[ ]\b\b");
    scanf("%d",&c);
    return c;
}

int menuuser()         //�û����˵�
{
    int c,i;
    gotox(3);
    printf("\t\t\t        KTV���ϵͳ--СV\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*         1  ���ֵ��\t\t*\n");
    printf("\t\t\t*         2  ��������\t\t*\n");
    printf("\t\t\t*         3  ƴ�����\t\t*\n");
    printf("\t\t\t*         4  ���и���\t\t*\n");
    printf("\t\t\t*         5  �ѵ����\t\t*\n");
    printf("\t\t\t*         6  ��    ��\t\t*\n");
    printf("\t\t\t*         0  ��    ��\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t������ѡ��[ ]\b\b");
    scanf("%d",&c);
    return c;
}

int menuadmin()        //����Ա�˵�
{
    int c,i;
    gotox(3);
    printf("\t\t\t         KTV���ϵͳ--СV\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*         1  ���и���\t\t*\n");
    printf("\t\t\t*         2  ��Ӹ���\t\t*\n");
    printf("\t\t\t*         3  �����������\t*\n");
    printf("\t\t\t*         4  ɾ������\t\t*\n");
    printf("\t\t\t*         5  ��������\t\t*\n");
    printf("\t\t\t*         6  �޸�����\t\t*\n");
    printf("\t\t\t*         0  ��    ��\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t������ѡ��[ ]\b\b");
    scanf("%d",&c);
    return c;
}

void bofanglan(song head1)      //������
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
            printf("\t    ���ڲ��ţ� %s--%s",p->songname,p->singer);
            printf("\t��һ�ף� %s--%s",p->next->songname,p->next->singer);
            printf("\t�ѵ� %d ��",counter);
        }
        else
        {
            if(counter==1)
            {
                printf("\t    ���ڲ��ţ� %s--%s",p->songname,p->singer);
                printf("\t��һ�ף� ��������");
                printf("\t�ѵ� %d ��",counter);
            }
            else
            {
                printf("\t    ���ڲ��ţ� ��������");
                printf("\t��һ�ף� ��������");
                printf("\t�ѵ� %d ��",counter);
            }
        }
}








