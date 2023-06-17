#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<stdbool.h>
#include <Mmsystem.h>
#include<math.h>


#define CROSS "\033[33mʮ\033[0m"
bool isStandard = 1;//�Ƿ���Ϲ��򣬳�ʼֵ1������
bool gameOverSign = 1;//��Ϸ�Ƿ������0����
bool restart = 0;
int xi, yi = 0;//Ҫ�ƶ�����������
int xj, yj = 0;//Ŀ�ĵ�����




typedef struct _version {
    double firstversion;//��ǰ�汾����
    char* information;//������Ա��Ϣ
}version;
typedef struct _chesssetup {
    int countdown;//����ʱ��
    int background;//������ɫ
    int music;//����
    int changecheckmate;//ת����˧
}chesssetup;
version q;
chesssetup p;
char* chess[11][9] = {
{ "܇","�R","��","��","��","��","��","�R","܇" },
{ CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS },
{ CROSS,"�h",CROSS,CROSS,CROSS,CROSS,CROSS,"�h",CROSS },
{ "��",CROSS, "��",CROSS, "��",CROSS,"��",CROSS, "��" },
{ CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS },
{ "��","��","��","��","��","��","��","��","��" },
{ CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS },
{ "��",CROSS,"��",CROSS,"��",CROSS,"��",CROSS,"��" },
{ CROSS,"��",CROSS,CROSS,CROSS,CROSS,CROSS,"��",CROSS },
{ CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS },
{"��","��","��","ʿ","��","ʿ","��","��","��" }
};

int countdown=10;
int _kbhit();
void Move();
//void Move();
int back();
void setversion(version* q);
void showversion(version* q);

void _rule()
{
    //R��܇��----------------------------------------
    if (chess[xi][yi] == "܇")
    {
        if (yi == yj)//�����겻�䣬ͬ���ƶ�
        {
            for (int i = xi + 1; i < xj; i++)
            {
                if (i == 5)
                    continue;//����е���5������
                if (chess[i][yi] != CROSS)
                    isStandard = 0;//�����ʼλ�ú�Ŀ��λ��֮�������ӣ��򲻷��Ϲ���
            }
            for (int i = xi - 1; i > xj; i--)
            {
                if (i == 5)
                    continue;//����е���5������
                if (chess[xi][yi] != CROSS)
                    isStandard = 0;
            }
        }
        else if (xi == xj)//�����겻�䣬ͬ���ƶ�
        {
            for (int i = yi + 1; i < yj; i++)
                if (chess[xi][i] != CROSS)
                    isStandard = 0;
            for (int i = yi - 1; i > yj; i--)
                if (chess[xi][i] != CROSS)
                    isStandard = 0;
        }

        if ((xi == xj || yi == yj) && isStandard && (redOrBlack(xj, yj) != 1))//�������ֱ�С�û�з�������㲻�Ǻ��壬�����ƶ�
        {

            chess[xi][yi] = CROSS;
            chess[xj][yj] = "܇";
        }
        else
        {
            restart = 1;
        }
    }

    //B��܇��----------------------------------------
    else if (chess[xi][yi] == "��")
    {

        if (yi == yj)//�����겻�䣬ͬ���ƶ�
        {
            for (int i = xi + 1; i < xj; i++)
            {
                if (i == 5)
                    continue;//����е���5������
                if (chess[i][yi] != CROSS)
                    isStandard = 0;//�����ʼλ�ú�Ŀ��λ��֮�������ӣ��򲻷��Ϲ���
            }
            for (int i = xi - 1; i > xj; i--)
            {
                if (i == 5)
                    continue;//����е���5������
                if (chess[i][yi] != CROSS)
                    isStandard = 0;
            }
        }
        else if (xi == xj)//�����겻�䣬ͬ���ƶ�
        {
            for (int i = yi + 1; i < yj; i++)
                if (chess[xi][i] != CROSS)
                    isStandard = 0;
            for (int i = yi - 1; i > yj; i--)
                if (chess[xi][i] != CROSS)
                    isStandard = 0;
        }
        if ((xi == xj || yi == yj) && isStandard && redOrBlack(xj, yj) != -1)//�������ֱ�С�û�з�������㲻�Ǻ��壬�����ƶ�
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "��";
        }
        else
        {
            restart = 1;
        }
    }

    //R����----------------------------------------
    else if (chess[xi][yi] == "�R")
    {
        if ((redOrBlack(xj, yj) != 1) && ((xj == xi - 2 && yj == yi - 1 && redOrBlack(xi - 1, yi) == 0) || (xj == xi - 2 && yj == yi + 1 && redOrBlack(xi - 1, yi) == 0) || (xj == xi - 1 && yj == yi - 2 && redOrBlack(xi, yi - 1) == 0) || (xj == xi - 1 && yj == yi + 2 && redOrBlack(xi, yi + 1) == 0) || (xj == xi + 1 && yj == yi - 2 && redOrBlack(xi, yi - 1) == 0) || (xj == xi + 1 && yj == yi + 2 && redOrBlack(xi, yi + 1) == 0) || (xj == xi + 2 && yj == yi - 1 && redOrBlack(xi + 1, yi) == 0) || (xj == xi + 2 && yj == yi + 1 && redOrBlack(xi + 1, yi) == 0)))
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "�R";
        }
        else
        {
            restart = 1;
        }
    }

    //B����----------------------------------------
    else if (chess[xi][yi] == "��")
    {
        if ((redOrBlack(xj, yj) != -1) && ((xj == xi - 2 && yj == yi - 1 && redOrBlack(xi - 1, yi) == 0) || (xj == xi - 2 && yj == yi + 1 && redOrBlack(xi - 1, yi) == 0) || (xj == xi - 1 && yj == yi - 2 && redOrBlack(xi, yi - 1) == 0) || (xj == xi - 1 && yj == yi + 2 && redOrBlack(xi, yi + 1) == 0) || (xj == xi + 1 && yj == yi - 2 && redOrBlack(xi, yi - 1) == 0) || (xj == xi + 1 && yj == yi + 2 && redOrBlack(xi, yi + 1) == 0) || (xj == xi + 2 && yj == yi - 1 && redOrBlack(xi + 1, yi) == 0) || (xj == xi + 2 && yj == yi + 1 && redOrBlack(xi + 1, yi) == 0)))
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "��";
        }
        else
        {
            restart = 1;
        }
    }

    //R���ڣ�----------------------------------------
    else if (chess[xi][yi] == "�h")
    {
        int count = 0;//��ʼλ�ü����ӵĸ���
        if (yi == yj)//�����겻�䣬ͬ���ƶ�
        {
            for (int i = xi + 1; i < xj; i++)
            {
                if (i == 5)
                    continue;//����е���5������
                if (redOrBlack(i, yi) != 0)
                    count++;

            }
            for (int i = xi - 1; i > xj; i--)
            {
                if (i == 5)
                    continue;//����е���5������
                if (redOrBlack(i, yi) != 0)
                    count++;
            }
        }
        else if (xi == xj)//�����겻�䣬ͬ���ƶ�
        {
            for (int i = yi + 1; i < yj; i++)
                if (redOrBlack(xi, i) != 0)
                    count++;
            for (int i = yi - 1; i > yj; i--)
                if (redOrBlack(xi, i) != 0)
                    count++;
        }
        if ((xi == xj || yi == yj) && (count <= 1) && redOrBlack(xj, yj) != 1)//�������ֱ�С�û�з�������㲻�Ǻ��壬�����ƶ�
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "�h";
        }
        else
        {
            restart = 1;
        }
    }

    //B���ڣ�----------------------------------------
    else if (chess[xi][yi] == "��")
    {
        int count = 0;//��ʼλ�ü����ӵĸ���
        if (yi == yj)//�����겻�䣬ͬ���ƶ�
        {
            for (int i = xi + 1; i < xj; i++)
            {
                if (i == 5)
                    continue;//����е���5������
                if (redOrBlack(i, yi) != 0)
                    count++;

            }
            for (int i = xi - 1; i > xj; i--)
            {
                if (i == 5)
                    continue;//����е���5������
                if (redOrBlack(i, yi) != 0)
                    count++;
            }
        }
        else if (xi == xj)//�����겻�䣬ͬ���ƶ�
        {
            for (int i = yi + 1; i < yj; i++)
                if (redOrBlack(xi, i) != 0)
                    count++;
            for (int i = yi - 1; i > yj; i--)
                if (redOrBlack(xi, i) != 0)
                    count++;
        }

        if ((xi == xj || yi == yj) && (count <= 1) && redOrBlack(xj, yj) != -1)//�������ֱ�С�û�з�������㲻�Ǻ��壬�����ƶ�
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "��";
        }
        else
        {
            restart = 1;
        }
    }

    //R������----------------------------------------
    else if (chess[xi][yi] == "��")
    {
        if (xi > xj)
            isStandard = 0;//������ˣ��򲻷��Ϲ淶
        if (xi == 3)
            if ((xj != xi + 1) || (yi != yj))
                isStandard = 0;//��3��ʱֻ��ǰ��һ��
        if (xi == 4)
            if ((xj != xi + 2) || (yi != yj))
                isStandard = 0;//��4��ʱֻ��ǰ������
        if (xi > 4) {
            if ((xj == xi + 1 && yi == yj) || (xj == xi && yi == yj + 1) || (xj == xi && yi == yj - 1))
            {

            }
            else
                isStandard = 0;
        }
        if ((xi == xj || yi == yj) && isStandard && redOrBlack(xj, yj) != 1)//
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "��";
        }
        else
        {
            restart = 1;
        }
    }

    //B���䣩----------------------------------------
    else if (chess[xi][yi] == "��")
    {
        if (xi < xj)
            isStandard = 0;//������ˣ��򲻷��Ϲ淶
        if (xi == 7)
            if ((xj != xi - 1) || (yi != yj))
                isStandard = 0;//��3��ʱֻ��ǰ��һ��
        if (xi == 6)
            if ((xj != xi - 2) || (yi != yj))
                isStandard = 0;//��4��ʱֻ��ǰ������
        if (xi < 4) {
            if ((xj == xi - 1 && yi == yj) || (xj == xi && yi == yj + 1) || (xj == xi && yi == yj - 1))
            {

            }
            else
                isStandard = 0;
        }
        if (isStandard && redOrBlack(xj, yj) != -1)//
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "��";
        }
        else
        {
            restart = 1;
        }
    }

    //R���ࣩ----------------------------------------
    else if (chess[xi][yi] == "��")
    {
        if ((xj <= 4) && (redOrBlack(xj, yj) != 1) && ((xj == xi - 2 && yj == yi - 2 && redOrBlack(xi - 1, yi - 1) == 0) || (xj == xi - 2 && yj == yi + 2 && redOrBlack(xi - 1, yi + 1) == 0) || (xj == xi + 2 && yj == yi - 2 && redOrBlack(xi + 1, yi - 1) == 0) || (xj == xi + 2 && yj == yi + 2 && redOrBlack(xi + 1, yi + 1) == 0)))
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "��";
        }
        else
        {
            restart = 1;
        }
    }

    //B����----------------------------------------
    else if (chess[xi][yi] == "��")
    {
        if ((xj >= 6) && (redOrBlack(xj, yj) != -1) && ((xj == xi - 2 && yj == yi - 2 && redOrBlack(xi - 1, yi - 1) == 0) || (xj == xi - 2 && yj == yi + 2 && redOrBlack(xi - 1, yi + 1) == 0) || (xj == xi + 2 && yj == yi - 2 && redOrBlack(xi + 1, yi - 1) == 0) || (xj == xi + 2 && yj == yi + 2 && redOrBlack(xi + 1, yi + 1) == 0)))
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "��";
        }
        else
        {
            restart = 1;
        }
    }

    //R���ˣ�----------------------------------------
    else if (chess[xi][yi] == "��")
    {
        if ((xj <= 2) && (redOrBlack(xj, yj) != 1) && ((xj == xi - 1 && yj == yi - 1) || (xj == xi - 1 && yj == yi + 1) || (xj == xi + 1 && yj == yi - 1) || (xj == xi + 1 && yj == yi + 1)))
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "��";
        }
        else
        {
            restart = 1;
        }
    }

    //B��ʿ��----------------------------------------
    else if (chess[xi][yi] == "ʿ")
    {
        if ((xj >= 8) && (redOrBlack(xj, yj) != 1) && ((xj == xi - 1 && yj == yi - 1) || (xj == xi - 1 && yj == yi + 1) || (xj == xi + 1 && yj == yi - 1) || (xj == xi + 1 && yj == yi + 1)))
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "ʿ";
        }
        else
        {
            restart = 1;
        }
    }

    //R��˧��----------------------------------------
    else if (chess[xi][yi] == "��")
    {
        if ((xj <= 2 && yj <= 5 && yj >= 3) && (redOrBlack(xj, yj) != 1) && (((xj == xi) && (yj == yi + 1 || yj == yi - 1)) || ((yj == yi) && (xj == xi + 1 || xj == xi - 1))))
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "��";
        }
        else
        {
            restart = 1;
        }
    }

    //B������----------------------------------------
    else if (chess[xi][yi] == "��")
    {
        if ((xj >= 8 && yj <= 5 && yj >= 3) && (redOrBlack(xj, yj) != -1) && (((xj == xi) && (yj == yi + 1 || yj == yi - 1)) || ((yj == yi) && (xj == xi + 1 || xj == xi - 1))))
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "��";
        }
        else
        {
            restart = 1;
        }
    }
    else {
        restart = 1;
    }
}
void _isGameOver()
{
    bool sign_r = 0;
    bool sign_b = 0;
   
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 9; j++) {
            if (chess[i][j] == "��") {
                sign_r = 1;
            }
            else if (chess[i][j] == "��")
            {
                sign_b = 1;
            }
        }
    }
    if ((sign_r == 0) || (sign_b == 0)) {
        gameOverSign = 0;
        showgameoverpage();
    }
}

int startpage() {
    for (float y = 1.5f; y > -1.5f; y -= 0.1f)
    {
        for (float x = -1.5f; x < 1.5f; x += 0.05f)
        {
            float a = x * x + y * y - 1;
            putchar(a * a * a - x * x * y * y * y < 0.0f ? '*' : ' ');
        }
        Sleep(100);
        putchar('\n');
    }
    printf("                Hello!��ӭ����ţ�����塪��byţ����\n");
    printf("       ��������Ǽ�����Ŷ��Don��t say much��enjoy this little game��\n");
    printf("                            1.��ʼ��Ϸ\n");
    printf("                            2.��������\n");
    printf("                            3.��������\n");
    printf("                            4.����ʱ����\n");
    printf("                            5.�汾��ѯ\n");
    printf("                            6.�˳���Ϸ\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    return 0;
}
int startpagechoose()
{
    int choose;
    printf("��ѡ��:");
    scanf_s("%d", &choose);
    switch (choose)
    {
    case 1:
    {
        showchessmap();
       
       
        int start = firststart();
        while (gameOverSign != 0) {
            isStandard = 1;
            start *= (-1);//˫����������
            switch (start) {
            case 1:
                showcountdown();
               //Move();
                
                start = (restart) ? (start * -1) : start;
                break;
            case -1:
                showcountdown();
               
                //Move();
                start = (restart) ? (start * -1) : start;
                break;
            }
          
        }

    }
    break;
    case 2:
    {
        setmusic();
        back();
    }
    break;
    case 3:
    {
        setbackground();
       
    }
    break;
    case 4: {
        setcountdown();
        back();

    }
    case 5:
    {

        setversion(&q);
        showversion(&q);
        back();
    }
    break;
    case 6:
    {
        printf("                       ��ӭ������");
        break;
    }
    default:
        printf("����ֵ��Ч\n");
        switch (choose);
        break;
    }
}
/*
int setcountdown()
{

    printf("����������:");
    scanf_s("%d", &p.countdown);
   
    
    return 0;
}
*/
int setcountdown() {
    
    printf("�����뵹��ʱʱ��:");
    scanf_s("%d", &countdown);
   
    return 0;
}
int showcountdown() {
    char input;
    int j = countdown;
   
    while (countdown>=0) {

        
        if (_kbhit()) {
            //input = _getch();
            //if (input == 27) break;
            printf("��������Ҫ�ƶ�������\n");
            Move();
            countdown = j;
            _isGameOver();
       }
       else if (countdown >= 0) {
            Sleep(1000);
            printf("����ʱ:%d\n", countdown);
            countdown--;
       }

    }
    
    return 0;
}
int setmusic()
{
    int chooseone;
    printf("��ѡ�񲥷Ÿ���1��2��3��4��������������ѡ��5:");  //ѡ������
    scanf_s("%d", &chooseone);
    switch (chooseone) {
    case 1:
        mciSendString(L"stop D:/FFOutput/1.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/2.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/3.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/4.mp3", NULL, 0, NULL);
        printf("Ϊ�㲥�ŵ�һ�׸���\n");
        mciSendString(L"open D:/FFOutput/1.mp3", NULL, 0, NULL);
        mciSendString(L"play  D:/FFOutput/1.mp3", NULL, 0, NULL);
        //ѭ��1.mp3��������
        
        break;
    case 2:
        mciSendString(L"stop D:/FFOutput/1.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/2.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/3.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/4.mp3", NULL, 0, NULL);
        printf("Ϊ�㲥�ŵڶ��׸���\n");
        mciSendString(L"open  D:/FFOutput/2.mp3", NULL, 0, NULL);
        mciSendString(L"play  D:/FFOutput/2.mp3", NULL, 0, NULL);     //ѭ��2.mp3��������
        system("pause");
       
        break;
    case 3:
        mciSendString(L"stop D:/FFOutput/1.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/2.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/3.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/4.mp3", NULL, 0, NULL);
        printf("Ϊ�㲥�ŵ����׸���\n");
        mciSendString(L"open D:/FFOutput/3.mp3", NULL, 0, NULL);
        mciSendString(L"play D:/FFOutput/3.mp3", NULL, 0, NULL);     //ѭ��3.mp3��������
        system("pause");
       
        break;
    case 4:
        mciSendString(L"stop D:/FFOutput/1.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/2.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/3.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/4.mp3", NULL, 0, NULL);
        printf("Ϊ�㲥�ŵ����׸���\n");
        mciSendString(L"open  D:/FFOutput/4.mp3", NULL, 0, NULL);
        mciSendString(L"play D:/FFOutput/4.mp3", NULL, 0, NULL);     //ѭ��4.mps��������
        system("pause");
       
        break;
    case 5:                                                        //����������
        break;
    }
    back();
    return 0;
}

SetSize(unsigned uCol, unsigned uLine)
{
    char cmd[64];
    wsprintf( cmd,"mode con cols=%d lines=%d", uCol, uLine);
    system(cmd);
}
void setColor(unsigned short backColor)
{
    char command[9] = "color 07";		//Ĭ����ɫ
    command[6] = '0' + backColor;		//��backColor������Ϊ�ַ���
    system(command);				//����ϵͳ����
}

int setbackground()
{
    
    
    SetSize(80, 40);//�ı����̨��С
    system("Pause");
   
    
    int i;
    printf("0 = ��ɫ ,1 = ��ɫ ,2 = ��ɫ ,3 = ����ɫ ,4 = ��ɫ, 5 = ��ɫ, 6 = ��ɫ,8 = ��ɫ  ,9 = ����ɫ \n");
    printf("��������ѡ����ɫ���:");
    scanf_s("%d", &i);
    setColor(i);
    back();
        
    return 0;
}

int back()
{
    int choice1;

     printf("1.������ҳ��\n");
        
        printf("2.�˳�\n");
        printf("�����룺\n");
        scanf_s("%d", &choice1);
        system("cls");
       
        switch (choice1)
        {
        case 1:
            startpage();
            startpagechoose();
            break;
        case 2:
            printf("                        ��ӭ������");
            break;

        }
 return 0;
}
void setversion(version* q) {

    q->firstversion = 3.0;
    q->information = "�鳤��Сΰ\t\n���鳤:����\t\n��Ʒ����С�ܡ�С��\t\n�ල�٣��Ŵ���\t\n�����¼��:����\t\n�����٣�����\t\n��������Ա��ͮͮ��С���硢����\t\n";

}
void showversion(version* q) {
    printf("%lf\n", q->firstversion);
    printf("%s", q->information);
}

int showchessmap() {



    int i, j;
    int l = 0;
    printf("\t\t\t\t\t  ");
    for (i = 0; i < 9; i++) {
        printf(" %d", i);
    }
    printf("\n");
    for (i = 0; i < 11; i++) {
        printf("\t\t\t\t");
        printf("%d\t  ", i);
        for (j = 0; j < 9; j++) {

            printf("%s", chess[i][j]);
            l++;
            if (l % 9 == 0) {
                printf("\n");
                l = 0;
            }
        }
        printf("\n");
    }


    return 0;
}
//δ����
/*
int showrestart()
{
    int chose;
    do
    {
        //��Ϸ����

        printf("                                                ���롰1�����¿�ʼ\n                                                ����������˳���Ϸ\n                                                       ");
        scanf_s("%d", &chose);
        if (chose != 1)
            ;
    }     while (chose == 1);

    return 0;
}
*/
int backtostart()
{
    printf("1.��ӡ���ؿ�ʼҳ��\n");
    int i;
    printf("�û�����в���");
    scanf_s("%d", &i);
    switch (i)
    {
    case 1:
        backtostart();
        break;
    case 2:
        printf("�������������²�����\n");
        switch (i);
        break;
    }
    return 0;
}
int   firststart()
{
    int start;
    printf("���û���������-1��1��\n");
    scanf_s("%d", &start);

    if (start == 1) {
        printf("˧������\n");
        return start;
    }
    else if (start == -1) {
        printf("��������\n");
        return start;
    }
    return 0;
}
//�����ƶ�
//�����ƶ�
void Move()
{
    if (restart) {
        printf("Υ����Ϸ��������������\n");
        restart = 0;
    }
    scanf_s("%d %d", &xi, &yi);
    printf("��������Ҫ���õ�λ��:\n");
    scanf_s("%d %d", &xj, &yj);
    _rule();
    showchessmap();
}
//�����ƶ�
/*
void Move()
{
    if (restart) {
        printf("Υ����Ϸ��������������\n");
        restart = 0;
    }
    printf("[����]��������Ҫ�ƶ�������:\n");
    scanf_s("%d %d", &xi, &yi);
    printf("[����]��������Ҫ���õ�λ��:\n");
    scanf_s("%d %d", &xj, &yj);
    _rule();
    showchessmap();
}
*/
int redOrBlack(int x, int y)
{
    if (chess[x][y] == "܇" || chess[x][y] == "�R" || chess[x][y] == "��" || chess[x][y] == "��" || chess[x][y] == "��" || chess[x][y] == "�h" || chess[x][y] == "��")
    {
        return  1;
    }
    else if (chess[x][y] == "��" || chess[x][y] == "��" || chess[x][y] == "��" || chess[x][y] == "ʿ" || chess[x][y] == "��" || chess[x][y] == "��" || chess[x][y] == "��")
    {
        return -1;
    }
    else
        return 0;
}
//int showwin(int win);
int showgameoverpage() {
    int showgameoverpage = 1;
    system("color c0");

   
        printf("--------------------------------\n");
        printf("\t����Ϸ������\n");
        printf("\t1.����һ��\n");
        printf("\t2.���ؿ�ʼ����\n");
        printf("\t3.�˳���Ϸ\n");
        printf("-------------------------------\n");
        printf("������ǰ�����ֽ�����һ��\n");
        //��Ϸ����������ʾ

        scanf_s("%d", &showgameoverpage);
        switch (showgameoverpage) {
        case 1:
            showchessmap();
            setcountdown();

            int start = firststart();
            while (gameOverSign != 0) {
                isStandard = 1;
                start *= (-1);//˫����������
                switch (start) {
                case 1:
                    showcountdown();
                   
                    start = (restart) ? (start * -1) : start;
                    break;
                case -1:
                    showcountdown();
                    
                    start = (restart) ? (start * -1) : start;
                    break;
                }
                _isGameOver();
               
            }
            break;
        case 2:
            startpage();
            startpagechoose();
            break;
        case 3:
            printf("                        ��ӭ������");
            break;
        default:
            printf("������ѡ��ǰ������\n");
        }


        system("pause");
        system("cls");
    
    return 0;
};
//int overpagechoose();
//int end(int lastnum);

int main() {
    //mciSendString(L"play  D:/FFOutput/5.wav", NULL, 0, NULL);
    startpage();
    startpagechoose();
   
    return 0;
}