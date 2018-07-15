#include "KTV_head.h"

int main()
{
    song head;
    head=readsongfile();
    int c,loop=1;
    while(loop==1)
    {
       system("cls");
       c=mainMenu();
       switch(c)
       {
           case 1:  usersystem(head);
                    break;
           case 2:  c=login();
                    adminsystem(c,head);
                    break;
           default:loop=0;
                    break;
       }
    }
    return 0;
}

int login()//管理员账号密码验证
{
    int i;
    char c;
    admin p,head2;
    unsigned short ch;
    char inputadmin[LENGTH_OF_ADMIN+1];
    char inputpassword[LENGTH_OF_PASS+1];
    head2=readadminfile();
    p=head2->next;
    while(denglucounter>0)
    {
        system("cls");
        denglucounter--;
        i=0;
        gotox(3);
        printf("  \t*******管理员登录*******\t\n");
        printf("\n\t admin:    [          ]\b\b\b\b\b\b\b\b\b\b\b");
        while(i<=LENGTH_OF_ADMIN)
        {
            c=getch();
            printf("%c",c);
            if(c=='\r')
                break;
            if(i==LENGTH_OF_ADMIN)
                break;
            inputadmin[i]=c;
            i++;
        }
        inputadmin[i]='\0';
        if(i==LENGTH_OF_ADMIN)
        {
            printf("\n\t账号长度不能大于10！您还有%d次登录机会\n\n\t",denglucounter);
            printf("输入ESC退出，输入其它继续登录\n\t");
            ch=getch();
                if(27==ch)
                    return;
                else
                    continue;
        }
        i=0;
        printf("\n");
        printf("  \t password: [          ]\b\b\b\b\b\b\b\b\b\b\b");
        while(i<=LENGTH_OF_PASS)
        {
            c=getch();
            if(c=='\r')
                break;
            printf("*");
            if(i==LENGTH_OF_PASS)
                break;
            inputpassword[i]=c;
            i++;
        }
        inputpassword[i]='\0';
        if(i==LENGTH_OF_PASS)
        {
            printf("\n\t密码长度不能大于6！您还有%d次登录机会\n\n\t",denglucounter);
                printf("输入ESC退出，输入其它继续登录\n\t");
                ch=getch();
                    if(27==ch)
                        return;
                    else
                        continue;
        }
        printf("\n");
            if(strcmp(p->ad_min,inputadmin)!=0)
            {
                printf("%s",p->ad_min);
                printf("\n\t账号错误！您还有%d次登录机会\n\n\t",denglucounter);
                printf("输入ESC退出，输入其它继续登录\n\t");
                ch=getch();
                    if(27==ch)
                        return;
                    else
                        continue;
            }
            else
            {
                if(strcmp(p->password,inputpassword)!=0)
                {
                    printf("\n\t密码错误！您还有%d次登录机会\n\n\t",denglucounter);
                    printf("输入ESC退出，输入其它继续登录\n\t");
                    ch=getch();
                    if(27==ch)
                        return;
                    else
                        continue;
                }
                else
                {
                    printf("\n\t登录成功！即将为您跳转页面....");
                    Sleep(1300);
                    return 1;
                }
            }
    }
    if(denglucounter==0)
    {
        printf("\n\n\t登录机会用尽，登录失败！即将为您返回");
        Sleep(1200);
        return -1;
    }
}

song readsongfile()//从文件中读取文件到链上，返回头结点地址
{
    FILE *fp;
    song head,p,s;
    head=(song)malloc(sizeof(strsong));
    p=head;
    fp=fopen(songfile,"r");
    if(fp!=NULL)
    {
        while(!feof(fp))
        {
            s=(song)malloc(sizeof(strsong));
            fscanf(fp,"%d",&s->songID);
            fscanf(fp,"%s",s->songname);
            fscanf(fp,"%s",s->singer);
            fscanf(fp,"%s",s->pingyin);
            fscanf(fp,"%d",&s->status);
            if(s->songID==0)
            break;
            p->next=s;
            p=s;
        }
        p->next=NULL;
        fclose(fp);
        return head;
    }
    else
    return NULL;
}
admin readadminfile()//从文件读取管理员账号密码信息
{
    admin head2,s;
    head2=(admin)malloc(sizeof(struct adminnode));
    FILE *fp;
    fp=fopen(adminfile,"r");
    if(fp!=NULL)
    {
        while(!feof(fp))
        {
            s=(admin)malloc(sizeof(struct adminnode));
            fscanf(fp,"%s",s->ad_min);
            fscanf(fp,"%s",s->password);
            s->next=NULL;
            head2->next=s;
        }
        fclose(fp);
        return head2;
    }
    else
    printf("\n文件读取错误！");
}
void writeadmintofile(admin head2)  //将管理员账号密码信息写入文件
{
    FILE *fp;
    admin p;
    p=head2->next;
    fp=fopen(adminfile,"w");
    if(fp!=NULL)
    {
        while(p)
        {
            fprintf(fp,"%s",p->ad_min);
            fputc(' ',fp);
            fprintf(fp,"%s",p->password);
            p=p->next;
        }
    }
    else
    printf("\n文件读取错误！");
    fclose(fp);
}
void yiaddsong(song head)//逐个添加歌曲
{
    char c;
    song p,s;
    p=head;
    system("cls");
    while(p->next)
    {
        p=p->next;
    }
        gotox(3);
        printf("小V-->添加歌曲");
        gotox(3);
        printf("  请输入\n");
    do
    {
        s=(song)malloc(sizeof(strsong));
        printf("  歌名\t歌手\t拼音\n  ");
        s->songID=++p->songID;
        scanf("%s",s->songname);
        scanf("%s",s->singer);
        scanf("%s",s->pingyin);
        s->status=1;
        s->next=NULL;
        if(!ScarchSameSong(s->songname,s->singer))
            printf("  歌曲添加失败，歌曲已在曲库中存在，加油！");
        else
        {
            p->next=s;
            p=s;
            printf("  歌曲添加成功，你太棒了！");
        }
        printf("\n\n  输入其它继续添加，输入0返回");
        getchar();
        c=getchar();
    }while(c!='0');
}
int ScarchSameSong(char songnsme[],char singer[])//查找是否含有相同歌曲
{
    int flag=1;
    song head,p;
    head=readsongfile();
    p=head->next;
    while(p&&flag)
    {
        if(!strcmp(p->songname,songnsme)&&!strcmp(p->singer,singer))
        flag=0;
        else
        p=p->next;
    }
    return flag;
}
void duoaddsong(song head)//批量添加歌曲
{
    FILE *fp;
    song p,s;
    char file[20];
    int counter1=0;
    int counter2=0;
    int counter;
    p=head->next;
    while(p->next)
    {
        p=p->next;
    }
    counter=p->songID;
    system("cls");
    gotox(3);
    printf("小V-->批量导入歌曲");
    gotox(3);
    printf("  请输入导入的文件名,输入1返回\n  ");
    scanf("%s",file);
    if(file[0]=='1')
        return;
    fp=fopen(file,"r");
    if(fp!=NULL)
    {
        while(!feof(fp))
        {
            s=(song)malloc(sizeof(strsong));
            s->songID=++counter;
            fscanf(fp,"%s",s->songname);
            fscanf(fp,"%s",s->singer);
            fscanf(fp,"%s",s->pingyin);
            s->status=1;
            s->next=NULL;
                if(!ScarchSameSong(s->songname,s->singer))
                    counter1++;
                else
                {
                    counter2++;
                    p->next=s;
                    p=s;
                }
        }
        printf("  导入完成！总共导入%d首歌曲\n    %d首导入成功！\n    %d首歌曲导入失败!\n",counter1+counter2,counter2,counter1);
        if(counter1>0)
            printf("  原因：已在曲库中存在！\n");
        printf("  ");
        system("pause");
        fclose(fp);
    }
    else
    {
        printf("\n  抱歉，文件打开失败!\n  ");
        system("pause");
    }
}
void writesongtofile(song head)//将链表歌曲信息写入文件
{
    FILE *fp;
    song p;
    p=head->next;
    fp=fopen(songfile,"w");
    if(fp!=NULL)
    {
        while(p)
        {
            fprintf(fp,"%d",p->songID);
            fputc(' ',fp);
            fprintf(fp,"%s",p->songname);
            fputc(' ',fp);
            fprintf(fp,"%s",p->singer);
            fputc(' ',fp);
            fprintf(fp,"%s",p->pingyin);
            fputc(' ',fp);
            fprintf(fp,"%d",p->status);
            fputc('\n',fp);
            p=p->next;
            if(!p)
               fputc('0',fp);
        }
    }
    else
        printf("\n抱歉，文件打开失败！");
    fclose(fp);
}

void adminsystem(int c,song head)       //管理员模块
{
    if(c==1)
    {
        int loop=1;
        admin head2;
        head2=readadminfile("admin.txt");
        while(loop==1)
        {
            system("cls");
            gotox(3);
            printf("亲爱的管理员! 您好^v^");
            c=menuadmin();
            switch(c)
            {
                case 1: printSong(c,head);
                        break;
                case 2: yiaddsong(head);
                        writesongtofile(head);
                        break;
                case 3: duoaddsong(head);
                        writesongtofile(head);
                        break;
                case 4: printSong(c,head);
                        writesongtofile(head);
                        break;
                case 5: sortsong(head);
                        printSong(c,head);
                        break;
                case 6: xiugaiadmin(head2);
                        writeadmintofile(head2);
                        break;
                default:
                        loop=0;
                        break;
            }
        }
    }
}

void usersystem(song head)      //用户模块
{
    int c,loop=1;
    song p;
    song head1;
    head1=(song)malloc(sizeof(strsong));
    head1->next=NULL;
    while(loop==1)
    {
        system("cls");
        gotox(3);
        printf("亲爱的用户！遇见你很高兴^v^");
        bofanglan(head1);
        c=menuuser();
        switch(c)
        {
                case 1: printsinger(head);
                        indexsearchsinger(head1,head);
                        break;
                case 2: searchsongName(head1,head);
                        break;
                case 3: searchpingyin(head1,head);
                        break;
                case 4: printSong(1,head);
                        break;
                case 5: printplaySong(head1);
                        break;
                case 6: nextsong(head1);
                        break;
                default:
                        loop=0;
                        break;
        }
    }
}


void xiugaiadmin(admin head2)//修改密码
{
    admin p;
    char c;
    unsigned short ch;
    char inputpassword[LENGTH_OF_PASS+1];
    char againinputpassword1[LENGTH_OF_PASS+1];
    char againinputpassword2[LENGTH_OF_PASS+1];
    p=head2->next;
    while(1)
    {
        system("cls");
        gotox(3);
        int i=0;
        printf("小V-->密码修改");
        gotox(3);
        printf("   \t*******密码修改*******");
        printf("\n\n\t原密码: [          ]\b\b\b\b\b\b\b\b\b\b\b");
        scanf("%s",inputpassword);
        if(strcmp(p->password,inputpassword)!=0)
        {
            printf("\n\t密码错误！输入ESC退出，输入其它继续..\n\t");
            ch=getch();
            if(27==ch)
                return;
            else
                continue;
        }
        else
        {
            printf("\t新密码: [          ]\b\b\b\b\b\b\b\b\b\b\b");
            while(i<=LENGTH_OF_PASS)
        {
            c=getch();
            printf("%c",c);
            if(c=='\r')
                break;
            if(i==LENGTH_OF_PASS)
                break;
            againinputpassword1[i]=c;
            i++;
        }
        againinputpassword1[i]='\0';
        if(i==LENGTH_OF_PASS)
        {
            printf("\n\t密码长度不能大于6！\n\n\t");
            printf("输入ESC退出，输入其它继续登录\n\t");
                ch=getch();
                    if(27==ch)
                        return;
                    else
                        continue;
        }
        i=0;
        printf("\n");
            printf("\t请再次输入: [          ]\b\b\b\b\b\b\b\b\b\b\b");
            while(i<=LENGTH_OF_PASS)
        {
            c=getch();
            if(c=='\r')
                break;
            printf("*");
            if(i==LENGTH_OF_PASS)
                break;
            againinputpassword2[i]=c;
            i++;
        }
        againinputpassword2[i]='\0';
        if(i==LENGTH_OF_PASS)
        {
            printf("\n\t密码长度不能大于6！您还有%d次登录机会\n\n\t",denglucounter);
                printf("输入ESC退出，输入其它继续登录\n\t");
                ch=getch();
                    if(27==ch)
                        return;
                    else
                        continue;
        }
            if(strcmp(againinputpassword1,againinputpassword2)!=0)
            {
                printf("\n\t两次输入不一致！输入ESC退出，输入其它继续..\n\t");
                ch=getch();
                if(27==ch)
                    return;
                else
                    continue;
            }
            else
            {
                strcpy(p->password,againinputpassword2);
                printf("\n\t恭喜！密码修改成功！\n\t您的密码修改为:%s\n\t",againinputpassword2);
                system("pause");
                return;
            }
        }
    }
}

void printSong(int c,song head)              //分页显示所有歌曲
{
    song p=head;
    int songtotal=0,page=0,totalpage;
    int counter=1,i,j,k,x=0,aim,t;
    unsigned short ch;
    while(p->next)      //计算歌曲总数
    {
        songtotal++;
        p=p->next;
    }
    if(songtotal>0)
    {
        totalpage=(songtotal-1)/10;//每10首换一页
        if(totalpage*10<songtotal)
            totalpage++;
        while(1)
        {
            system("cls");
            gotox(3);
            if(c==1)      //通过传入的参数实现不同的调用显示
            printf("小V-->所有歌曲");
            if(c==4)
            printf("小V-->删除歌曲");
            if(c==5)
            printf("小V-->歌曲排序");
            gotox(3);
            t=0;
            aim=page*10+1;
            p=head;
            while(t!=aim)  //找出输入某页的第一个结构体
            {
                p=p->next;
                t++;
            }
            printf("  ");
            if(c==5)
            printf("%8s","首字母");
            printf("%8s%20s%20s\n","编号","歌曲名","歌手名");
            printf("  ");
            for(i=0;i<55;i++)
                putchar('-');
                printf("\n");
            for(j=0;j<10 && x<songtotal;j++)
            {
                printf("\n  ");
                if(c==5)    //通过传入的参数实现不同的调用显示
                printf("%8c",p->pingyin[0]);
                printf("%8d",p->songID);
                printf("%20s",p->songname);
                printf("%20s",p->singer);
                x++;
                p=p->next;
            }
            printf("\n\n");
            printf("  第%d页,共%d页,上一页（↑）,下一页（↓）,输入ESC返回主页\n\n",page+1,totalpage);
            printf("  ");
            if(c==4)printf("输入0进行删除操作\n  ");    //通过传入的参数实现不同的调用显示
                ch=getch();     //输入不同的符号实现不同跳转
            if(27==ch)          //返回主页
            {
                system("cls");
                return;
            }
            if(48==ch)          //在参数5的情况下输入0实现删除操作
            {
                deletesong(head);
                continue;
            }
            if(0==ch || 0xe0==ch) ch|=getch()<<8;
            if(0x48e0==ch) //上一页
            {
                if(page>0)
                {
                    page-=1;
                    x=x-10;
                }
                else
                {
                    printf("已经是第一页了！");
                    Sleep(600);
                    page=0;
                    x=0;
                }
            }
            if(0x50e0==ch)  //下一页
            {
                if(page<totalpage-1)
                {
                    page++;
                    x=page*10;
                }
                else
                {
                    printf("已经是最后一页了！");
                    Sleep(600);
                    page=totalpage-1;
                    x=page*10;
                }
            }
        }
    }
}

void printsinger(song head)           //显示所有歌手
{
    song p=head->next,q;
    q=p;
    system("cls");
    gotox(3);
    printf("小V-->歌手点歌\n");
    printf("\n  歌手:\n");
    int counter=0;
    while(p)
    {
        q=head->next;
        while(q!=p)
        {
            if(strcmp(p->singer,q->singer)==0)  //一个歌手不能出现两次
            {
                break;
            }
            q=q->next;
        }
        if(q==p)
        {
            printf("%15s",p->singer);
            counter++;
            if(counter%5==0)
            {
                printf("\n");
            }
        }
        p=p->next;
    }
    printf("\n\n");
}

void sortsong(song head)   //通过歌曲名拼音进行排序
{
    song p,pre,q,s;
    p=head->next;
    head->next=NULL;       //将取下头结点
    while(p)
    {
        //取节点
        pre=p;
        p=p->next;
        pre->next=NULL;
        q=head->next;
        s=head;
        //计录q的前驱节点
        while(q && strcmp(q->pingyin,pre->pingyin)<0)   //此处用到强大的字符串比较函数
        {
            s=q;
            q=q->next;
        }
        pre->next=q;
        s->next=pre;
    }
    if(!p)
    {
        printf("\n\t\t\t排序成功！");
        Sleep(1000);
    }
}
void printplaySong(song head1)              //显示播放队列的歌曲
{
    while(1)
    {
        song p=head1;
        if(!p->next)
        {
            unsigned short ch;
            printf("\n\t\t\t您还没点歌哦，请前往点歌");
            Sleep(1000);
            break;
        }
        else
        {
            system("cls");
            playsong(head1);    //将第一首歌状态改为正在播放
            int songtotal=0,page=0,totalpage;
            int counter=1,i,j,k,x=0,aim,t;
            unsigned short ch;
            while(p->next)
            {
                songtotal++;
                p=p->next;
                //counter++;
            }
            if(songtotal>0)
            {
                totalpage=(songtotal-1)/10;
                if(totalpage*10<songtotal)
                    totalpage++;
                while(1)
                {
                    system("cls");
                    gotox(3);
                    printf("小V-->已点歌曲");
                    gotox(3);
                    t=0;
                    aim=page*10+1;
                    p=head1;
                    while(t!=aim)  //找出输入某页的第一个结构体
                    {
                        p=p->next;
                        t++;
                    }
                    printf("  ");
                    printf("%5s%20s%20s\n","序号","歌曲名","歌手名");
                    printf("  ");
                    for(i=0;i<55;i++)
                        putchar('-');
                    printf("\n");
                    for(j=0;j<10 && x<songtotal;j++)
                    {
                        printf("\n  ");
                        printf("%5d%20s%20s",p->songID,p->songname,p->singer);
                        if(p->status==0)
                        printf("-----正在播放");
                        x++;
                        p=p->next;
                    }
                    printf("\n\n");
                    printf("  第%d页,共%d页,上一页（↑）,下一页（↓）,输入ESC返回主页\n\n",page+1,totalpage);
                    printf("  输入1-->置顶歌曲\n");
                    printf("  输入2-->移除歌曲\n");
                    printf("  输入3-->切歌\n");
                    printf("  ");
                    ch=getch();
                    if(27==ch)  //返回主页
                    {
                        system("cls");
                        return;
                    }
                    if(49==ch)  //置顶歌曲
                    {
                        sticksong(head1);
                        break;
                    }
                    if(50==ch)  //移除已点歌曲
                    {
                        deleteplaysong(head1);
                        break;
                    }
                    if(51==ch)  //切歌
                    {
                        nextsong(head1);
                        break;
                    }
                    if(0==ch || 0xe0==ch) ch|=getch()<<8;
                    if(0x48e0==ch) //上一页
                    {
                        if(page>0)
                        {
                            page-=1;
                            x=x-10;
                        }
                        else
                        {
                            printf("已经是第一页了！");
                            Sleep(600);
                            page=0;
                            x=0;
                        }
                    }
                    if(0x50e0==ch)  //下一页
                    {
                        if(page<totalpage-1)
                        {
                            page++;
                            x=page*10;
                        }
                        else
                        {
                            printf("已经是最后一页了！");
                            Sleep(600);
                            page=totalpage-1;
                            x=page*10;
                        }
                    }
                }
            }
        }
    }
}

void searchpingyin(song head1,song head)    //通过歌曲名拼音查找歌曲
{
    char str1[20];
    char str2[20];
    system("cls");
    gotox(3);
    printf("小V-->拼音搜索\n\n");
    while(1)
    {
        int flag=0,counter;
        song p=head->next;
        printf("  请输入要查找歌曲名的首拼音,输入1返回: ");
        scanf("%s",str2);
    if(str2[0]=='1')
        break;
    int k;
    while(p)
    {
        strcpy(str1,p->pingyin);
        counter=0;
        for(k=0;k<strlen(str1);k++)
        {
            if(str1[k]==str2[counter])
                counter++;
        }
        if(counter==strlen(str2))
        {
            printf("%5d%20s%20s\n",p->songID,p->songname,p->singer);
            flag=1;
        }
        p=p->next;
    }
    if(flag==0)
        printf("  抱歉！本系统还无该歌曲\n");
    else
    {
        searchsongID(head1,head);
        break;
    }
    }
}

void searchsongName(song head1,song head)    //通过歌曲名查找歌曲
{
    char str1[20];
    char str2[20];
    system("cls");
    gotox(3);
    printf("小V-->歌曲搜索\n\n");
    while(1)
    {
        int flag=0,counter;
        song p=head->next;
        printf("  请输入要查找的歌曲名，输入1返回：");
        scanf("%s",str2);
        if(str2[0]=='1')
            break;
        else
        {
            int k;
            while(p)
            {
                strcpy(str1,p->songname);
                counter=0;
                for(k=0;k<strlen(str1);k++)
                {
                    if(str1[k]==str2[counter])
                    counter++;
                }
            if(counter==strlen(str2))
            {
                printf("%5d%20s%20s\n",p->songID,p->songname,p->singer);
                flag=1;
            }
            p=p->next;
            }
        if(flag==0)
            printf("  抱歉！本系统还无该歌曲\n");
        else
        {
            int k;
            while(p)
            {
                strcpy(str1,p->songname);
                counter=0;
                for(k=0;k<strlen(str1);k++)
                {
                    if(str1[k]==str2[counter])
                    counter++;
                }
                if(counter==strlen(str2))
                {
                    printf("%5d%20s%20s\n",p->songID,p->songname,p->singer);
                    flag=1;
                }
            p=p->next;
            }
            if(flag==0)
                printf("  抱歉！本系统还无该歌曲\n");
            else
            {
                searchsongID(head1,head);
                break;
            }
        }
        }
    }
}

void indexsearchsinger(song head1,song head)        //模糊查询歌手
{
    char str1[20];
    char str2[20];
    while(1)
    {
        int flag=0,counter;
        song p=head->next;
        printf("  请输入要查找歌手名,输入1返回：");
        scanf("%s",str2);
        if(str2[0]=='1')
            break;
        int k;
        while(p)
        {
            strcpy(str1,p->singer);
            counter=0;
        for(k=0;k<strlen(str1);k++)
        {
            if(str1[k]==str2[counter])
            {
                counter++;
            }
        }
        if(counter==strlen(str2))
        {
            printf("%5d%20s%20s\n",p->songID,p->songname,p->singer);
            flag=1;
        }
        p=p->next;
        }
        if(flag==0)
            printf("  抱歉！本系统还无该歌手,请继续输入\n");
        else
        {
            searchsongID(head1,head);
            break;
        }
    }
}

void searchsongID(song head1,song head) //通过歌曲编号查找歌曲
{
    int b;
    while(1)
    {
        song p=head->next;
        printf("  请输入要添加歌曲的编号,输入0结束：");
        scanf("%d",&b);
        if(b==0)
        {
            printf("\n  添加结束，即将为您返回用户主界面。。。");
            Sleep(1000);
            break;
        }

        else
        {
         while(p)
         {
            if(b==p->songID)
            {
                printf("%5d%20s%20s\n",p->songID,p->songname,p->singer);
                addsongtoplay(head1,p);
                break;
            }
            p=p->next;
         }
            if(!p)
            printf("  抱歉！本系统还无该歌曲,请重新添加\n");
        }
    }
}

void deleteplaysong(song head1)  //删除播放队列歌曲
{
    int b;
    char h;
    while(1)
    {
        song p=head1->next,q;
        q=p;
        song pre,s;
        printf("请输入要移除歌曲的编号,输入0返回:  ");
        scanf("%d",&b);
        if(b==0)
            break;
        pre=head1;
        while(p)
        {
            if(b==p->songID)
            {
                break;
            }
            p=p->next;
            pre=pre->next;
        }
        if(p)                            //歌曲是否存在
        {
            if(p->songID==1)
            {
                printf("  无法移除，歌曲正在播放，请切歌\n  ");
                system("pause");
                return;
            }
        else
        {
            printf("  真的要移除吗？(y/n)");
            scanf(" %c",&h);
            if(h=='y' || h=='Y')    //确认删除
            {
                pre->next=p->next;
                free(p);
                printf("  移除成功\n");
                int i=1;
                while(q)
                {
                    q->songID=i;
                    q=q->next;
                    i++;
                }
                printf("  ");
                system("pause");
                return;
            }
            else
            {
                system("pause");
                return;
            }
        }
    }
    else
        printf("  不存在这首歌曲，请输入正确的歌曲序号\n  ");
    }
}

void deletesong(song head) //删除歌曲
{
    int b;
    char h;
    while(1)
    {
        song p=head->next;
        song pre,s;
        printf("请输入要删除歌曲的编号,输入0结束删除： ");
        scanf("%d",&b);
        pre=head;
        if(b==0)
            break;
        while(p)
        {
            if(b==p->songID)
            {
                break;
            }
            p=p->next;
            pre=pre->next;
        }
        if(p)                            //歌曲是否存在
        {
            if(p->status==1)             //若歌曲正在播放则无法删除
            {
                printf("  真的要删除吗？(y/n)");
                scanf(" %c",&h);
                if(h=='y' || h=='Y')    //确认删除
                {
                    pre->next=p->next;
                    free(p);
                    printf("  删除成功!\n  ");
                }
            }
            else
            {
                printf("  歌曲正在播放，无法删除\n  ");
            }
        }
        else
        {
            printf("  不存在这首歌曲，请输入正确的歌曲编号\n  ");
        }
    }
}

void sticksong(song head1) //置顶歌曲
{
    int b;
    song p=head1->next,q;
    q=p;
    song pre;
    if(p->next&&p->next->next)
    {
        printf("请输入要置顶歌曲的序号: ");
        scanf("%d",&b);
        pre=head1;
    while(p)         //判断歌曲存不存在
    {
        if(b==p->songID)
        {
            break;
        }
        p=p->next;
        pre=pre->next;
    }
    if(p)
    {
        if(p->songID<3)
        {
          printf("  无法置顶，请至少从第三首开始\n  ");
          system("pause");
          return;
        }
        else
        {
           pre->next=p->next;
            p->next=q->next;
            q->next=p;
            printf("  歌曲置顶成功\n");
            int i=1;
            while(q)
            {
                q->songID=i;
                q=q->next;
                i++;
            }
            return;
        }
    }
    else
    {
        printf("  不存在这首歌曲，请输入正确的歌曲序号\n  ");
        system("pause");
        return;
    }
    }
    else
    {
        printf("已点歌曲数需至少大于2首，无法置顶!\n  ");
        system("pause");
    }
}

void addsongtoplay(song head1,song p)  //添加歌曲进入播放队列
{
    int i=1;
    song s,q,pre;
    q=head1;
    pre=head1->next;
    if(p)
    {
        while(pre)
        {
            pre=pre->next;
            q=q->next;
            i++;
        }
        s=(song)malloc(sizeof(strsong));
        strcpy(s->singer,p->singer);
        s->songID=i;
        strcpy(s->songname,p->songname);
        s->status=p->status;
        q->next=s;
        s->next=NULL;
        printf("  添加成功!\n");
    }
}

void statuschange(song head1)     //改变播放状态
{
    song p=head1->next;
    while(p)
    {
        if(p->status==0)
        {
            p->status=1;
            break;
        }
        p=p->next;
    }
    p->status=1;
}

void playsong(song head1)    //播放歌曲
{
    if(head1->next)
    {
        song p;
        p=head1->next;
        p->status=0;
    }
}

void nextsong(song head1)     //切歌，下一首
{
    song p,q;
    p=head1->next;
    if(p)
    {
        if(p->next)
        {
            head1->next=p->next;
            int i=1;
            q=head1->next;
            while(q)
            {
                q->songID=i;
                q=q->next;
                i++;
            }
            printf("\n\t\t\t恭喜，切歌成功！");
            Sleep(900);
        }
        else
        {
            printf("\n\t\t\t已经是最后一首歌了哦，无法播放下一首");
            Sleep(1000);
        }
     }
     else
     {
        printf("\n\t\t\t您还未点歌哦，请前往点歌");
        Sleep(1000);
     }
}


