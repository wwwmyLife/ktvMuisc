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

int login()//����Ա�˺�������֤
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
        printf("  \t*******����Ա��¼*******\t\n");
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
            printf("\n\t�˺ų��Ȳ��ܴ���10��������%d�ε�¼����\n\n\t",denglucounter);
            printf("����ESC�˳�����������������¼\n\t");
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
            printf("\n\t���볤�Ȳ��ܴ���6��������%d�ε�¼����\n\n\t",denglucounter);
                printf("����ESC�˳�����������������¼\n\t");
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
                printf("\n\t�˺Ŵ���������%d�ε�¼����\n\n\t",denglucounter);
                printf("����ESC�˳�����������������¼\n\t");
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
                    printf("\n\t�������������%d�ε�¼����\n\n\t",denglucounter);
                    printf("����ESC�˳�����������������¼\n\t");
                    ch=getch();
                    if(27==ch)
                        return;
                    else
                        continue;
                }
                else
                {
                    printf("\n\t��¼�ɹ�������Ϊ����תҳ��....");
                    Sleep(1300);
                    return 1;
                }
            }
    }
    if(denglucounter==0)
    {
        printf("\n\n\t��¼�����þ�����¼ʧ�ܣ�����Ϊ������");
        Sleep(1200);
        return -1;
    }
}

song readsongfile()//���ļ��ж�ȡ�ļ������ϣ�����ͷ����ַ
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
admin readadminfile()//���ļ���ȡ����Ա�˺�������Ϣ
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
    printf("\n�ļ���ȡ����");
}
void writeadmintofile(admin head2)  //������Ա�˺�������Ϣд���ļ�
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
    printf("\n�ļ���ȡ����");
    fclose(fp);
}
void yiaddsong(song head)//�����Ӹ���
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
        printf("СV-->��Ӹ���");
        gotox(3);
        printf("  ������\n");
    do
    {
        s=(song)malloc(sizeof(strsong));
        printf("  ����\t����\tƴ��\n  ");
        s->songID=++p->songID;
        scanf("%s",s->songname);
        scanf("%s",s->singer);
        scanf("%s",s->pingyin);
        s->status=1;
        s->next=NULL;
        if(!ScarchSameSong(s->songname,s->singer))
            printf("  �������ʧ�ܣ��������������д��ڣ����ͣ�");
        else
        {
            p->next=s;
            p=s;
            printf("  ������ӳɹ�����̫���ˣ�");
        }
        printf("\n\n  ��������������ӣ�����0����");
        getchar();
        c=getchar();
    }while(c!='0');
}
int ScarchSameSong(char songnsme[],char singer[])//�����Ƿ�����ͬ����
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
void duoaddsong(song head)//������Ӹ���
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
    printf("СV-->�����������");
    gotox(3);
    printf("  �����뵼����ļ���,����1����\n  ");
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
        printf("  ������ɣ��ܹ�����%d�׸���\n    %d�׵���ɹ���\n    %d�׸�������ʧ��!\n",counter1+counter2,counter2,counter1);
        if(counter1>0)
            printf("  ԭ�����������д��ڣ�\n");
        printf("  ");
        system("pause");
        fclose(fp);
    }
    else
    {
        printf("\n  ��Ǹ���ļ���ʧ��!\n  ");
        system("pause");
    }
}
void writesongtofile(song head)//�����������Ϣд���ļ�
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
        printf("\n��Ǹ���ļ���ʧ�ܣ�");
    fclose(fp);
}

void adminsystem(int c,song head)       //����Աģ��
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
            printf("�װ��Ĺ���Ա! ����^v^");
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

void usersystem(song head)      //�û�ģ��
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
        printf("�װ����û���������ܸ���^v^");
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


void xiugaiadmin(admin head2)//�޸�����
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
        printf("СV-->�����޸�");
        gotox(3);
        printf("   \t*******�����޸�*******");
        printf("\n\n\tԭ����: [          ]\b\b\b\b\b\b\b\b\b\b\b");
        scanf("%s",inputpassword);
        if(strcmp(p->password,inputpassword)!=0)
        {
            printf("\n\t�����������ESC�˳���������������..\n\t");
            ch=getch();
            if(27==ch)
                return;
            else
                continue;
        }
        else
        {
            printf("\t������: [          ]\b\b\b\b\b\b\b\b\b\b\b");
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
            printf("\n\t���볤�Ȳ��ܴ���6��\n\n\t");
            printf("����ESC�˳�����������������¼\n\t");
                ch=getch();
                    if(27==ch)
                        return;
                    else
                        continue;
        }
        i=0;
        printf("\n");
            printf("\t���ٴ�����: [          ]\b\b\b\b\b\b\b\b\b\b\b");
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
            printf("\n\t���볤�Ȳ��ܴ���6��������%d�ε�¼����\n\n\t",denglucounter);
                printf("����ESC�˳�����������������¼\n\t");
                ch=getch();
                    if(27==ch)
                        return;
                    else
                        continue;
        }
            if(strcmp(againinputpassword1,againinputpassword2)!=0)
            {
                printf("\n\t�������벻һ�£�����ESC�˳���������������..\n\t");
                ch=getch();
                if(27==ch)
                    return;
                else
                    continue;
            }
            else
            {
                strcpy(p->password,againinputpassword2);
                printf("\n\t��ϲ�������޸ĳɹ���\n\t���������޸�Ϊ:%s\n\t",againinputpassword2);
                system("pause");
                return;
            }
        }
    }
}

void printSong(int c,song head)              //��ҳ��ʾ���и���
{
    song p=head;
    int songtotal=0,page=0,totalpage;
    int counter=1,i,j,k,x=0,aim,t;
    unsigned short ch;
    while(p->next)      //�����������
    {
        songtotal++;
        p=p->next;
    }
    if(songtotal>0)
    {
        totalpage=(songtotal-1)/10;//ÿ10�׻�һҳ
        if(totalpage*10<songtotal)
            totalpage++;
        while(1)
        {
            system("cls");
            gotox(3);
            if(c==1)      //ͨ������Ĳ���ʵ�ֲ�ͬ�ĵ�����ʾ
            printf("СV-->���и���");
            if(c==4)
            printf("СV-->ɾ������");
            if(c==5)
            printf("СV-->��������");
            gotox(3);
            t=0;
            aim=page*10+1;
            p=head;
            while(t!=aim)  //�ҳ�����ĳҳ�ĵ�һ���ṹ��
            {
                p=p->next;
                t++;
            }
            printf("  ");
            if(c==5)
            printf("%8s","����ĸ");
            printf("%8s%20s%20s\n","���","������","������");
            printf("  ");
            for(i=0;i<55;i++)
                putchar('-');
                printf("\n");
            for(j=0;j<10 && x<songtotal;j++)
            {
                printf("\n  ");
                if(c==5)    //ͨ������Ĳ���ʵ�ֲ�ͬ�ĵ�����ʾ
                printf("%8c",p->pingyin[0]);
                printf("%8d",p->songID);
                printf("%20s",p->songname);
                printf("%20s",p->singer);
                x++;
                p=p->next;
            }
            printf("\n\n");
            printf("  ��%dҳ,��%dҳ,��һҳ������,��һҳ������,����ESC������ҳ\n\n",page+1,totalpage);
            printf("  ");
            if(c==4)printf("����0����ɾ������\n  ");    //ͨ������Ĳ���ʵ�ֲ�ͬ�ĵ�����ʾ
                ch=getch();     //���벻ͬ�ķ���ʵ�ֲ�ͬ��ת
            if(27==ch)          //������ҳ
            {
                system("cls");
                return;
            }
            if(48==ch)          //�ڲ���5�����������0ʵ��ɾ������
            {
                deletesong(head);
                continue;
            }
            if(0==ch || 0xe0==ch) ch|=getch()<<8;
            if(0x48e0==ch) //��һҳ
            {
                if(page>0)
                {
                    page-=1;
                    x=x-10;
                }
                else
                {
                    printf("�Ѿ��ǵ�һҳ�ˣ�");
                    Sleep(600);
                    page=0;
                    x=0;
                }
            }
            if(0x50e0==ch)  //��һҳ
            {
                if(page<totalpage-1)
                {
                    page++;
                    x=page*10;
                }
                else
                {
                    printf("�Ѿ������һҳ�ˣ�");
                    Sleep(600);
                    page=totalpage-1;
                    x=page*10;
                }
            }
        }
    }
}

void printsinger(song head)           //��ʾ���и���
{
    song p=head->next,q;
    q=p;
    system("cls");
    gotox(3);
    printf("СV-->���ֵ��\n");
    printf("\n  ����:\n");
    int counter=0;
    while(p)
    {
        q=head->next;
        while(q!=p)
        {
            if(strcmp(p->singer,q->singer)==0)  //һ�����ֲ��ܳ�������
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

void sortsong(song head)   //ͨ��������ƴ����������
{
    song p,pre,q,s;
    p=head->next;
    head->next=NULL;       //��ȡ��ͷ���
    while(p)
    {
        //ȡ�ڵ�
        pre=p;
        p=p->next;
        pre->next=NULL;
        q=head->next;
        s=head;
        //��¼q��ǰ���ڵ�
        while(q && strcmp(q->pingyin,pre->pingyin)<0)   //�˴��õ�ǿ����ַ����ȽϺ���
        {
            s=q;
            q=q->next;
        }
        pre->next=q;
        s->next=pre;
    }
    if(!p)
    {
        printf("\n\t\t\t����ɹ���");
        Sleep(1000);
    }
}
void printplaySong(song head1)              //��ʾ���Ŷ��еĸ���
{
    while(1)
    {
        song p=head1;
        if(!p->next)
        {
            unsigned short ch;
            printf("\n\t\t\t����û���Ŷ����ǰ�����");
            Sleep(1000);
            break;
        }
        else
        {
            system("cls");
            playsong(head1);    //����һ�׸�״̬��Ϊ���ڲ���
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
                    printf("СV-->�ѵ����");
                    gotox(3);
                    t=0;
                    aim=page*10+1;
                    p=head1;
                    while(t!=aim)  //�ҳ�����ĳҳ�ĵ�һ���ṹ��
                    {
                        p=p->next;
                        t++;
                    }
                    printf("  ");
                    printf("%5s%20s%20s\n","���","������","������");
                    printf("  ");
                    for(i=0;i<55;i++)
                        putchar('-');
                    printf("\n");
                    for(j=0;j<10 && x<songtotal;j++)
                    {
                        printf("\n  ");
                        printf("%5d%20s%20s",p->songID,p->songname,p->singer);
                        if(p->status==0)
                        printf("-----���ڲ���");
                        x++;
                        p=p->next;
                    }
                    printf("\n\n");
                    printf("  ��%dҳ,��%dҳ,��һҳ������,��һҳ������,����ESC������ҳ\n\n",page+1,totalpage);
                    printf("  ����1-->�ö�����\n");
                    printf("  ����2-->�Ƴ�����\n");
                    printf("  ����3-->�и�\n");
                    printf("  ");
                    ch=getch();
                    if(27==ch)  //������ҳ
                    {
                        system("cls");
                        return;
                    }
                    if(49==ch)  //�ö�����
                    {
                        sticksong(head1);
                        break;
                    }
                    if(50==ch)  //�Ƴ��ѵ����
                    {
                        deleteplaysong(head1);
                        break;
                    }
                    if(51==ch)  //�и�
                    {
                        nextsong(head1);
                        break;
                    }
                    if(0==ch || 0xe0==ch) ch|=getch()<<8;
                    if(0x48e0==ch) //��һҳ
                    {
                        if(page>0)
                        {
                            page-=1;
                            x=x-10;
                        }
                        else
                        {
                            printf("�Ѿ��ǵ�һҳ�ˣ�");
                            Sleep(600);
                            page=0;
                            x=0;
                        }
                    }
                    if(0x50e0==ch)  //��һҳ
                    {
                        if(page<totalpage-1)
                        {
                            page++;
                            x=page*10;
                        }
                        else
                        {
                            printf("�Ѿ������һҳ�ˣ�");
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

void searchpingyin(song head1,song head)    //ͨ��������ƴ�����Ҹ���
{
    char str1[20];
    char str2[20];
    system("cls");
    gotox(3);
    printf("СV-->ƴ������\n\n");
    while(1)
    {
        int flag=0,counter;
        song p=head->next;
        printf("  ������Ҫ���Ҹ���������ƴ��,����1����: ");
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
        printf("  ��Ǹ����ϵͳ���޸ø���\n");
    else
    {
        searchsongID(head1,head);
        break;
    }
    }
}

void searchsongName(song head1,song head)    //ͨ�����������Ҹ���
{
    char str1[20];
    char str2[20];
    system("cls");
    gotox(3);
    printf("СV-->��������\n\n");
    while(1)
    {
        int flag=0,counter;
        song p=head->next;
        printf("  ������Ҫ���ҵĸ�����������1���أ�");
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
            printf("  ��Ǹ����ϵͳ���޸ø���\n");
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
                printf("  ��Ǹ����ϵͳ���޸ø���\n");
            else
            {
                searchsongID(head1,head);
                break;
            }
        }
        }
    }
}

void indexsearchsinger(song head1,song head)        //ģ����ѯ����
{
    char str1[20];
    char str2[20];
    while(1)
    {
        int flag=0,counter;
        song p=head->next;
        printf("  ������Ҫ���Ҹ�����,����1���أ�");
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
            printf("  ��Ǹ����ϵͳ���޸ø���,���������\n");
        else
        {
            searchsongID(head1,head);
            break;
        }
    }
}

void searchsongID(song head1,song head) //ͨ��������Ų��Ҹ���
{
    int b;
    while(1)
    {
        song p=head->next;
        printf("  ������Ҫ��Ӹ����ı��,����0������");
        scanf("%d",&b);
        if(b==0)
        {
            printf("\n  ��ӽ���������Ϊ�������û������档����");
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
            printf("  ��Ǹ����ϵͳ���޸ø���,���������\n");
        }
    }
}

void deleteplaysong(song head1)  //ɾ�����Ŷ��и���
{
    int b;
    char h;
    while(1)
    {
        song p=head1->next,q;
        q=p;
        song pre,s;
        printf("������Ҫ�Ƴ������ı��,����0����:  ");
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
        if(p)                            //�����Ƿ����
        {
            if(p->songID==1)
            {
                printf("  �޷��Ƴ����������ڲ��ţ����и�\n  ");
                system("pause");
                return;
            }
        else
        {
            printf("  ���Ҫ�Ƴ���(y/n)");
            scanf(" %c",&h);
            if(h=='y' || h=='Y')    //ȷ��ɾ��
            {
                pre->next=p->next;
                free(p);
                printf("  �Ƴ��ɹ�\n");
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
        printf("  ���������׸�������������ȷ�ĸ������\n  ");
    }
}

void deletesong(song head) //ɾ������
{
    int b;
    char h;
    while(1)
    {
        song p=head->next;
        song pre,s;
        printf("������Ҫɾ�������ı��,����0����ɾ���� ");
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
        if(p)                            //�����Ƿ����
        {
            if(p->status==1)             //���������ڲ������޷�ɾ��
            {
                printf("  ���Ҫɾ����(y/n)");
                scanf(" %c",&h);
                if(h=='y' || h=='Y')    //ȷ��ɾ��
                {
                    pre->next=p->next;
                    free(p);
                    printf("  ɾ���ɹ�!\n  ");
                }
            }
            else
            {
                printf("  �������ڲ��ţ��޷�ɾ��\n  ");
            }
        }
        else
        {
            printf("  ���������׸�������������ȷ�ĸ������\n  ");
        }
    }
}

void sticksong(song head1) //�ö�����
{
    int b;
    song p=head1->next,q;
    q=p;
    song pre;
    if(p->next&&p->next->next)
    {
        printf("������Ҫ�ö����������: ");
        scanf("%d",&b);
        pre=head1;
    while(p)         //�жϸ����治����
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
          printf("  �޷��ö��������ٴӵ����׿�ʼ\n  ");
          system("pause");
          return;
        }
        else
        {
           pre->next=p->next;
            p->next=q->next;
            q->next=p;
            printf("  �����ö��ɹ�\n");
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
        printf("  ���������׸�������������ȷ�ĸ������\n  ");
        system("pause");
        return;
    }
    }
    else
    {
        printf("�ѵ�����������ٴ���2�ף��޷��ö�!\n  ");
        system("pause");
    }
}

void addsongtoplay(song head1,song p)  //��Ӹ������벥�Ŷ���
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
        printf("  ��ӳɹ�!\n");
    }
}

void statuschange(song head1)     //�ı䲥��״̬
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

void playsong(song head1)    //���Ÿ���
{
    if(head1->next)
    {
        song p;
        p=head1->next;
        p->status=0;
    }
}

void nextsong(song head1)     //�и裬��һ��
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
            printf("\n\t\t\t��ϲ���и�ɹ���");
            Sleep(900);
        }
        else
        {
            printf("\n\t\t\t�Ѿ������һ�׸���Ŷ���޷�������һ��");
            Sleep(1000);
        }
     }
     else
     {
        printf("\n\t\t\t����δ���Ŷ����ǰ�����");
        Sleep(1000);
     }
}


