#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<stdbool.h>
#include <Mmsystem.h>
#include<math.h>


#define CROSS "\033[33m十\033[0m"
bool isStandard = 1;//是否符合规则，初始值1，符合
bool gameOverSign = 1;//游戏是否结束，0结束
bool restart = 0;
int xi, yi = 0;//要移动的棋子坐标
int xj, yj = 0;//目的地坐标




typedef struct _version {
    double firstversion;//当前版本数据
    char* information;//开发人员信息
}version;
typedef struct _chesssetup {
    int countdown;//落子时间
    int background;//背景颜色
    int music;//音乐
    int changecheckmate;//转换将帅
}chesssetup;
version q;
chesssetup p;
char* chess[11][9] = {
{ "車","馬","相","仕","帥","仕","相","馬","車" },
{ CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS },
{ CROSS,"砲",CROSS,CROSS,CROSS,CROSS,CROSS,"砲",CROSS },
{ "兵",CROSS, "兵",CROSS, "兵",CROSS,"兵",CROSS, "兵" },
{ CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS },
{ "－","－","楚","河","－","汉","界","－","－" },
{ CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS },
{ "卒",CROSS,"卒",CROSS,"卒",CROSS,"卒",CROSS,"卒" },
{ CROSS,"炮",CROSS,CROSS,CROSS,CROSS,CROSS,"炮",CROSS },
{ CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS,CROSS },
{"车","马","象","士","将","士","象","马","车" }
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
    //R（車）----------------------------------------
    if (chess[xi][yi] == "車")
    {
        if (yi == yj)//列坐标不变，同列移动
        {
            for (int i = xi + 1; i < xj; i++)
            {
                if (i == 5)
                    continue;//如果行等于5，跳过
                if (chess[i][yi] != CROSS)
                    isStandard = 0;//如果初始位置和目标位置之间有棋子，则不符合规则
            }
            for (int i = xi - 1; i > xj; i--)
            {
                if (i == 5)
                    continue;//如果行等于5，跳过
                if (chess[xi][yi] != CROSS)
                    isStandard = 0;
            }
        }
        else if (xi == xj)//行坐标不变，同行移动
        {
            for (int i = yi + 1; i < yj; i++)
                if (chess[xi][i] != CROSS)
                    isStandard = 0;
            for (int i = yi - 1; i > yj; i--)
                if (chess[xi][i] != CROSS)
                    isStandard = 0;
        }

        if ((xi == xj || yi == yj) && isStandard && (redOrBlack(xj, yj) != 1))//如果棋子直行、没有犯规且落点不是红棋，可以移动
        {

            chess[xi][yi] = CROSS;
            chess[xj][yj] = "車";
        }
        else
        {
            restart = 1;
        }
    }

    //B（車）----------------------------------------
    else if (chess[xi][yi] == "车")
    {

        if (yi == yj)//列坐标不变，同列移动
        {
            for (int i = xi + 1; i < xj; i++)
            {
                if (i == 5)
                    continue;//如果行等于5，跳过
                if (chess[i][yi] != CROSS)
                    isStandard = 0;//如果初始位置和目标位置之间有棋子，则不符合规则
            }
            for (int i = xi - 1; i > xj; i--)
            {
                if (i == 5)
                    continue;//如果行等于5，跳过
                if (chess[i][yi] != CROSS)
                    isStandard = 0;
            }
        }
        else if (xi == xj)//行坐标不变，同行移动
        {
            for (int i = yi + 1; i < yj; i++)
                if (chess[xi][i] != CROSS)
                    isStandard = 0;
            for (int i = yi - 1; i > yj; i--)
                if (chess[xi][i] != CROSS)
                    isStandard = 0;
        }
        if ((xi == xj || yi == yj) && isStandard && redOrBlack(xj, yj) != -1)//如果棋子直行、没有犯规且落点不是黑棋，可以移动
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "车";
        }
        else
        {
            restart = 1;
        }
    }

    //R（马）----------------------------------------
    else if (chess[xi][yi] == "馬")
    {
        if ((redOrBlack(xj, yj) != 1) && ((xj == xi - 2 && yj == yi - 1 && redOrBlack(xi - 1, yi) == 0) || (xj == xi - 2 && yj == yi + 1 && redOrBlack(xi - 1, yi) == 0) || (xj == xi - 1 && yj == yi - 2 && redOrBlack(xi, yi - 1) == 0) || (xj == xi - 1 && yj == yi + 2 && redOrBlack(xi, yi + 1) == 0) || (xj == xi + 1 && yj == yi - 2 && redOrBlack(xi, yi - 1) == 0) || (xj == xi + 1 && yj == yi + 2 && redOrBlack(xi, yi + 1) == 0) || (xj == xi + 2 && yj == yi - 1 && redOrBlack(xi + 1, yi) == 0) || (xj == xi + 2 && yj == yi + 1 && redOrBlack(xi + 1, yi) == 0)))
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "馬";
        }
        else
        {
            restart = 1;
        }
    }

    //B（马）----------------------------------------
    else if (chess[xi][yi] == "马")
    {
        if ((redOrBlack(xj, yj) != -1) && ((xj == xi - 2 && yj == yi - 1 && redOrBlack(xi - 1, yi) == 0) || (xj == xi - 2 && yj == yi + 1 && redOrBlack(xi - 1, yi) == 0) || (xj == xi - 1 && yj == yi - 2 && redOrBlack(xi, yi - 1) == 0) || (xj == xi - 1 && yj == yi + 2 && redOrBlack(xi, yi + 1) == 0) || (xj == xi + 1 && yj == yi - 2 && redOrBlack(xi, yi - 1) == 0) || (xj == xi + 1 && yj == yi + 2 && redOrBlack(xi, yi + 1) == 0) || (xj == xi + 2 && yj == yi - 1 && redOrBlack(xi + 1, yi) == 0) || (xj == xi + 2 && yj == yi + 1 && redOrBlack(xi + 1, yi) == 0)))
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "马";
        }
        else
        {
            restart = 1;
        }
    }

    //R（炮）----------------------------------------
    else if (chess[xi][yi] == "砲")
    {
        int count = 0;//起始位置间棋子的个数
        if (yi == yj)//列坐标不变，同列移动
        {
            for (int i = xi + 1; i < xj; i++)
            {
                if (i == 5)
                    continue;//如果行等于5，跳过
                if (redOrBlack(i, yi) != 0)
                    count++;

            }
            for (int i = xi - 1; i > xj; i--)
            {
                if (i == 5)
                    continue;//如果行等于5，跳过
                if (redOrBlack(i, yi) != 0)
                    count++;
            }
        }
        else if (xi == xj)//行坐标不变，同行移动
        {
            for (int i = yi + 1; i < yj; i++)
                if (redOrBlack(xi, i) != 0)
                    count++;
            for (int i = yi - 1; i > yj; i--)
                if (redOrBlack(xi, i) != 0)
                    count++;
        }
        if ((xi == xj || yi == yj) && (count <= 1) && redOrBlack(xj, yj) != 1)//如果棋子直行、没有犯规且落点不是红棋，可以移动
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "砲";
        }
        else
        {
            restart = 1;
        }
    }

    //B（炮）----------------------------------------
    else if (chess[xi][yi] == "炮")
    {
        int count = 0;//起始位置间棋子的个数
        if (yi == yj)//列坐标不变，同列移动
        {
            for (int i = xi + 1; i < xj; i++)
            {
                if (i == 5)
                    continue;//如果行等于5，跳过
                if (redOrBlack(i, yi) != 0)
                    count++;

            }
            for (int i = xi - 1; i > xj; i--)
            {
                if (i == 5)
                    continue;//如果行等于5，跳过
                if (redOrBlack(i, yi) != 0)
                    count++;
            }
        }
        else if (xi == xj)//行坐标不变，同行移动
        {
            for (int i = yi + 1; i < yj; i++)
                if (redOrBlack(xi, i) != 0)
                    count++;
            for (int i = yi - 1; i > yj; i--)
                if (redOrBlack(xi, i) != 0)
                    count++;
        }

        if ((xi == xj || yi == yj) && (count <= 1) && redOrBlack(xj, yj) != -1)//如果棋子直行、没有犯规且落点不是黑棋，可以移动
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "炮";
        }
        else
        {
            restart = 1;
        }
    }

    //R（兵）----------------------------------------
    else if (chess[xi][yi] == "兵")
    {
        if (xi > xj)
            isStandard = 0;//如果倒退，则不符合规范
        if (xi == 3)
            if ((xj != xi + 1) || (yi != yj))
                isStandard = 0;//第3行时只能前进一步
        if (xi == 4)
            if ((xj != xi + 2) || (yi != yj))
                isStandard = 0;//第4行时只能前进两步
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
            chess[xj][yj] = "兵";
        }
        else
        {
            restart = 1;
        }
    }

    //B（卒）----------------------------------------
    else if (chess[xi][yi] == "卒")
    {
        if (xi < xj)
            isStandard = 0;//如果倒退，则不符合规范
        if (xi == 7)
            if ((xj != xi - 1) || (yi != yj))
                isStandard = 0;//第3行时只能前进一步
        if (xi == 6)
            if ((xj != xi - 2) || (yi != yj))
                isStandard = 0;//第4行时只能前进两步
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
            chess[xj][yj] = "卒";
        }
        else
        {
            restart = 1;
        }
    }

    //R（相）----------------------------------------
    else if (chess[xi][yi] == "相")
    {
        if ((xj <= 4) && (redOrBlack(xj, yj) != 1) && ((xj == xi - 2 && yj == yi - 2 && redOrBlack(xi - 1, yi - 1) == 0) || (xj == xi - 2 && yj == yi + 2 && redOrBlack(xi - 1, yi + 1) == 0) || (xj == xi + 2 && yj == yi - 2 && redOrBlack(xi + 1, yi - 1) == 0) || (xj == xi + 2 && yj == yi + 2 && redOrBlack(xi + 1, yi + 1) == 0)))
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "相";
        }
        else
        {
            restart = 1;
        }
    }

    //B（象）----------------------------------------
    else if (chess[xi][yi] == "象")
    {
        if ((xj >= 6) && (redOrBlack(xj, yj) != -1) && ((xj == xi - 2 && yj == yi - 2 && redOrBlack(xi - 1, yi - 1) == 0) || (xj == xi - 2 && yj == yi + 2 && redOrBlack(xi - 1, yi + 1) == 0) || (xj == xi + 2 && yj == yi - 2 && redOrBlack(xi + 1, yi - 1) == 0) || (xj == xi + 2 && yj == yi + 2 && redOrBlack(xi + 1, yi + 1) == 0)))
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "象";
        }
        else
        {
            restart = 1;
        }
    }

    //R（仕）----------------------------------------
    else if (chess[xi][yi] == "仕")
    {
        if ((xj <= 2) && (redOrBlack(xj, yj) != 1) && ((xj == xi - 1 && yj == yi - 1) || (xj == xi - 1 && yj == yi + 1) || (xj == xi + 1 && yj == yi - 1) || (xj == xi + 1 && yj == yi + 1)))
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "仕";
        }
        else
        {
            restart = 1;
        }
    }

    //B（士）----------------------------------------
    else if (chess[xi][yi] == "士")
    {
        if ((xj >= 8) && (redOrBlack(xj, yj) != 1) && ((xj == xi - 1 && yj == yi - 1) || (xj == xi - 1 && yj == yi + 1) || (xj == xi + 1 && yj == yi - 1) || (xj == xi + 1 && yj == yi + 1)))
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "士";
        }
        else
        {
            restart = 1;
        }
    }

    //R（帅）----------------------------------------
    else if (chess[xi][yi] == "帥")
    {
        if ((xj <= 2 && yj <= 5 && yj >= 3) && (redOrBlack(xj, yj) != 1) && (((xj == xi) && (yj == yi + 1 || yj == yi - 1)) || ((yj == yi) && (xj == xi + 1 || xj == xi - 1))))
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "帥";
        }
        else
        {
            restart = 1;
        }
    }

    //B（将）----------------------------------------
    else if (chess[xi][yi] == "将")
    {
        if ((xj >= 8 && yj <= 5 && yj >= 3) && (redOrBlack(xj, yj) != -1) && (((xj == xi) && (yj == yi + 1 || yj == yi - 1)) || ((yj == yi) && (xj == xi + 1 || xj == xi - 1))))
        {
            chess[xi][yi] = CROSS;
            chess[xj][yj] = "将";
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
            if (chess[i][j] == "帥") {
                sign_r = 1;
            }
            else if (chess[i][j] == "将")
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
    printf("                Hello!欢迎来到牛客象棋——by牛客组\n");
    printf("       这个爱心是见面礼哦！Don’t say much，enjoy this little game！\n");
    printf("                            1.开始游戏\n");
    printf("                            2.声音设置\n");
    printf("                            3.背景设置\n");
    printf("                            4.倒计时设置\n");
    printf("                            5.版本查询\n");
    printf("                            6.退出游戏\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    return 0;
}
int startpagechoose()
{
    int choose;
    printf("请选择:");
    scanf_s("%d", &choose);
    switch (choose)
    {
    case 1:
    {
        showchessmap();
       
       
        int start = firststart();
        while (gameOverSign != 0) {
            isStandard = 1;
            start *= (-1);//双方交替下棋
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
        printf("                       欢迎再来！");
        break;
    }
    default:
        printf("输入值无效\n");
        switch (choose);
        break;
    }
}
/*
int setcountdown()
{

    printf("请输入秒数:");
    scanf_s("%d", &p.countdown);
   
    
    return 0;
}
*/
int setcountdown() {
    
    printf("请输入倒计时时间:");
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
            printf("请输入你要移动的棋子\n");
            Move();
            countdown = j;
            _isGameOver();
       }
       else if (countdown >= 0) {
            Sleep(1000);
            printf("倒计时:%d\n", countdown);
            countdown--;
       }

    }
    
    return 0;
}
int setmusic()
{
    int chooseone;
    printf("请选择播放歌曲1、2、3、4，不播放音乐请选择5:");  //选择音乐
    scanf_s("%d", &chooseone);
    switch (chooseone) {
    case 1:
        mciSendString(L"stop D:/FFOutput/1.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/2.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/3.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/4.mp3", NULL, 0, NULL);
        printf("为你播放第一首歌曲\n");
        mciSendString(L"open D:/FFOutput/1.mp3", NULL, 0, NULL);
        mciSendString(L"play  D:/FFOutput/1.mp3", NULL, 0, NULL);
        //循环1.mp3播放音乐
        
        break;
    case 2:
        mciSendString(L"stop D:/FFOutput/1.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/2.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/3.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/4.mp3", NULL, 0, NULL);
        printf("为你播放第二首歌曲\n");
        mciSendString(L"open  D:/FFOutput/2.mp3", NULL, 0, NULL);
        mciSendString(L"play  D:/FFOutput/2.mp3", NULL, 0, NULL);     //循环2.mp3播放音乐
        system("pause");
       
        break;
    case 3:
        mciSendString(L"stop D:/FFOutput/1.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/2.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/3.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/4.mp3", NULL, 0, NULL);
        printf("为你播放第三首歌曲\n");
        mciSendString(L"open D:/FFOutput/3.mp3", NULL, 0, NULL);
        mciSendString(L"play D:/FFOutput/3.mp3", NULL, 0, NULL);     //循环3.mp3播放音乐
        system("pause");
       
        break;
    case 4:
        mciSendString(L"stop D:/FFOutput/1.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/2.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/3.mp3", NULL, 0, NULL);
        mciSendString(L"stop D:/FFOutput/4.mp3", NULL, 0, NULL);
        printf("为你播放第四首歌曲\n");
        mciSendString(L"open  D:/FFOutput/4.mp3", NULL, 0, NULL);
        mciSendString(L"play D:/FFOutput/4.mp3", NULL, 0, NULL);     //循环4.mps播放音乐
        system("pause");
       
        break;
    case 5:                                                        //不播放音乐
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
    char command[9] = "color 07";		//默认颜色
    command[6] = '0' + backColor;		//将backColor变量改为字符型
    system(command);				//调用系统函数
}

int setbackground()
{
    
    
    SetSize(80, 40);//改变控制台大小
    system("Pause");
   
    
    int i;
    printf("0 = 黑色 ,1 = 蓝色 ,2 = 绿色 ,3 = 湖蓝色 ,4 = 红色, 5 = 紫色, 6 = 黄色,8 = 灰色  ,9 = 淡蓝色 \n");
    printf("请输入想选择颜色编号:");
    scanf_s("%d", &i);
    setColor(i);
    back();
        
    return 0;
}

int back()
{
    int choice1;

     printf("1.返回主页面\n");
        
        printf("2.退出\n");
        printf("请输入：\n");
        scanf_s("%d", &choice1);
        system("cls");
       
        switch (choice1)
        {
        case 1:
            startpage();
            startpagechoose();
            break;
        case 2:
            printf("                        欢迎再来！");
            break;

        }
 return 0;
}
void setversion(version* q) {

    q->firstversion = 3.0;
    q->information = "组长：小伟\t\n副组长:阿健\t\n产品经理：小杰、小粟\t\n监督官：张大炮\t\n会议记录官:佳乐\t\n技术官：鹏仔\t\n其他的组员：彤彤、小言午、鹏翔\t\n";

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
//未完善
/*
int showrestart()
{
    int chose;
    do
    {
        //游戏主体

        printf("                                                输入“1”重新开始\n                                                输入任意键退出游戏\n                                                       ");
        scanf_s("%d", &chose);
        if (chose != 1)
            ;
    }     while (chose == 1);

    return 0;
}
*/
int backtostart()
{
    printf("1.打印返回开始页面\n");
    int i;
    printf("用户请进行操作");
    scanf_s("%d", &i);
    switch (i)
    {
    case 1:
        backtostart();
        break;
    case 2:
        printf("操作有误，请重新操作！\n");
        switch (i);
        break;
    }
    return 0;
}
int   firststart()
{
    int start;
    printf("请用户输入数字-1或1：\n");
    scanf_s("%d", &start);

    if (start == 1) {
        printf("帅方先手\n");
        return start;
    }
    else if (start == -1) {
        printf("将方先手\n");
        return start;
    }
    return 0;
}
//红棋移动
//黑棋移动
void Move()
{
    if (restart) {
        printf("违反游戏规则，请重新输入\n");
        restart = 0;
    }
    scanf_s("%d %d", &xi, &yi);
    printf("请输入你要放置的位置:\n");
    scanf_s("%d %d", &xj, &yj);
    _rule();
    showchessmap();
}
//黑棋移动
/*
void Move()
{
    if (restart) {
        printf("违反游戏规则，请重新输入\n");
        restart = 0;
    }
    printf("[黑棋]请输入你要移动的棋子:\n");
    scanf_s("%d %d", &xi, &yi);
    printf("[黑棋]请输入你要放置的位置:\n");
    scanf_s("%d %d", &xj, &yj);
    _rule();
    showchessmap();
}
*/
int redOrBlack(int x, int y)
{
    if (chess[x][y] == "車" || chess[x][y] == "馬" || chess[x][y] == "相" || chess[x][y] == "仕" || chess[x][y] == "帥" || chess[x][y] == "砲" || chess[x][y] == "兵")
    {
        return  1;
    }
    else if (chess[x][y] == "车" || chess[x][y] == "马" || chess[x][y] == "象" || chess[x][y] == "士" || chess[x][y] == "将" || chess[x][y] == "炮" || chess[x][y] == "卒")
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
        printf("\t【游戏结束】\n");
        printf("\t1.再来一局\n");
        printf("\t2.返回开始界面\n");
        printf("\t3.退出游戏\n");
        printf("-------------------------------\n");
        printf("请输入前方数字进行下一步\n");
        //游戏结束界面显示

        scanf_s("%d", &showgameoverpage);
        switch (showgameoverpage) {
        case 1:
            showchessmap();
            setcountdown();

            int start = firststart();
            while (gameOverSign != 0) {
                isStandard = 1;
                start *= (-1);//双方交替下棋
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
            printf("                        欢迎再来！");
            break;
        default:
            printf("请输入选项前的数字\n");
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