#include<Windows.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
 
// 后方函数申明
void restart();
void gotoxy(int x,int y);
 
// 方向对应值
enum MoveDir { RIGHT = 0, UP = 1, LEFT = 2, DOWN = 3  };
 
// 开始时间戳, 结束时间戳
time_t start,end;
 
int food[25][20] = {0};  // 果实对应数组
int snakel[25][20] = {0};// 蛇身对应数组
 
int score = 0;      // 得分
int x = 0, y = 0;   // 坐标
int direct = RIGHT; // 移动方向
int mark = 0;       // 标记原方向
 
int length = 0;     // 蛇身链表长度
int slength = 1;    // 蛇身记录长度
 
// 方向数组
int  dir[4][2]={
        { 1,  0 }, // 0 向右  x坐标 +1  y坐标 +0
        { 0, -1 }, // 1 向上  x坐标 +0  y坐标 -1
        {-1,  0 }, // 2 向左  x坐标 -1  y坐标 +0
        { 0,  1 }  // 3 向下  x坐标 +0  y坐标 +1
    };
 
/*
    snake 结构体 用于构建贪吃蛇链表
*/
struct snake
{
    int x,y;
    struct snake *next,*pre;
} *head, *tail, *p; // 声明结构体的同时定义头指针、尾指针、临时指针
 
 
DWORD WINAPI ThreadProc(LPVOID lpPraram)
{
    SYSTEMTIME sys; // 系统时间结构体
 
    // 线程启动时, 头尾指针均为空
    head = tail = NULL;
    int a , b;
 
    // 随即获取果实坐标 (a,b)
    a=(rand()+start)%25; // [0,24]
    b=(rand()+start)%20; // [0,19]
 
    /* Note 起始时间 start + 返回的随机值 rand() = 一个不规律的随机值
     *      随后 % 求模 25 即将这个书限制在0到25之内 */
 
    // 子线程循环打印蛇身和果实
    while(1)
    {
        //打印已耗游戏时间;
        end = time(NULL);// 当前时间
        gotoxy(35,4);
        printf("%03d", (int)difftime(end,start)); // 当前时间与开始时间的差值
         
        GetLocalTime(&sys); // 获取当前时间
 
        //打印系统时间;
        gotoxy(28,18);      
        printf("%4d/%02d/%02d", sys.wYear, sys.wMonth, sys.wDay );
        gotoxy(29,19);
        printf("%02d:%02d:%02d", sys.wHour, sys.wMinute, sys.wSecond);
 
        //判断果实是否被吃了
        if(food[a][b] != '*' || snakel[a][b] == 1)
        {
            a=(rand()+start)%25; // [0,24]
            b=(rand()+start)%20; // [0,19]
            food[a][b]='*';
        }
 
        // 到屏幕的(a,b)坐标打印果实
        gotoxy(a,b); printf("*");
 
        //获取下一个坐标
        x += dir[direct][0];
        y += dir[direct][1];
        x += 25; x %= 25;
        y += 20; y %= 20;
 
        // 如果果实(food)数组中当前坐标对应为果实
        if(food[x][y]=='*')
        {           
            slength++;  // 蛇身长度自增
            score++;    // 分数自增
            // 刷新分数
            gotoxy(35,3); printf("%03d",score);
            // 清理果实(food)数组
            food[x][y]=0;
        }
        // 若不是果实则，判断当前坐标是否为蛇身
        else if(snakel[x][y]==1)
        {
            // 如果是蛇身即玩家吃到自己，游戏重启
            restart();
        }
 
        snakel[x][y]=1; // 蛇身对应新坐标置1
         
        // 创建新坐标对应的链表节点
        p = (snake*)malloc(sizeof(snake));
        p->x = x;
        p->y = y;
        p->next = p->pre = NULL;
                 
        if(head == NULL) {
        // 若只有一个节点（即蛇的长度为1，链表长度为0）
            head = tail = p;
        }
        else
        {
        // 若不只一个节点
            head->pre=p; // 头结点的前一个指向 p 节点
            p->next=head;    // p 节点下一个指向当前头结点
            head=p;         // 新的 p 变成头结点变成
        }
 
        length++; // 链表长度加1 
 
        // 到新坐标，也就是头部打印 #
        gotoxy(head->x,head->y);
        printf("#");
 
        // 输出调试信息
        gotoxy(49, 10); printf("length: %d slength: %d", length, slength);
 
        // 删除蛇尾
        if(length > slength)
        {
            // 清空蛇尾数组对应值
            snakel[tail->x][tail->y]=0;
            // 控制台输出流指针移动到蛇尾
            gotoxy(tail->x,tail->y);
            // 输出空格
            printf(" ");
 
            // 临时指针指向蛇尾
            p = tail;
            // 尾指针前移
            tail = tail->pre;
            // 释放原本的尾指针
            free(p);
            // 蛇身链表长度减1
            length--;
        }
 
        /* 
         * 调控速度暂时休眠
         * 如果需要控制游戏速度只需要修改休眠的值即可
         */
        _sleep(50);
 
        // 标记当前方向
        mark = direct;
    }
}
 
/*
    初始化配置
*/
void init()
{
    int i;
 
    // 绘制外围边框
    for( i=0; i<20; i++)
    {
        gotoxy(39,i); printf("|");
        gotoxy(25,i); printf("|");
    }
    for( i=0; i<40; i++)
    {
        gotoxy(i,20); printf("~");
    }
 
    // 右侧游戏记录, 规则说明
    gotoxy(26, 3); printf("游戏得分:%03d",score);
    gotoxy(26, 4); printf("游戏时间:");
    gotoxy(29,17); printf("系统时间");
 
    gotoxy(49, 1); printf("@lellansin");
    gotoxy(49, 2); printf("www.lellansin.com");
     
    gotoxy(49, 4); printf("一群  10191598");
    gotoxy(49, 5); printf("二群 163859361");
    gotoxy(49, 6); printf("三群  10366953");
 
    gotoxy(49, 8); printf("按ESC键退出");
 
    // 初始化游戏开始时间
    start = time(NULL);
}
 
int main()
{   
    int i = 0;
    HANDLE sonThreadHandle; // 子线程句柄
    DWORD dwThreadId;       // 子线程ID
 
    // 按键上半部分以及下半部分
    char keyCodePart1,keyCodePart2;
 
    // 执行初始化
    init(); 
     
    //创建线程
    sonThreadHandle = CreateThread(
        NULL,       // 不能被子进程继承
        0,          // 默认堆栈大小
        ThreadProc, // 线程调用函数过程
        NULL,       // 传递参数
        0,          // 创建后立即执行
        &dwThreadId // 保存创建后的线程ID
    );
 
    // 如果线程句柄为空，即新建线程失败
    if(sonThreadHandle == NULL)
    {
        ExitProcess(i); // 退进程, 程序结束
    }
 
    // 主线程循环获取按键
    while(1)
    {
        // getch 一次只能从输入流中读取一个字节
        // 不过一个按键通常是两个字节
        keyCodePart1 = getch(); // 获取第一个字节
 
        // 判断是否等于逃脱键(Esc)的第一个字节
        if(keyCodePart1 == 0x1b)
        {
            ExitProcess(2); // 是的话就退出进程
        }
 
        // 方向键第一个字节的值等于 -32
        if(keyCodePart1 == -32)
        {
            keyCodePart2 = getch(); // 获取第二个字节
            switch(keyCodePart2)
            {
                case(72):
                    // direct=1;
                    direct = UP;
                break;
                case(75):
                    // direct=2;
                    direct = LEFT;
                break;
                case(77):
                    // direct=0;
                    direct = RIGHT;
                break;
                case(80):
                    // direct=3;
                    direct = DOWN;
                break;
            }
            // 如果当前方向与原方向相反
            if( direct != mark && (direct+mark==RIGHT+LEFT||direct+mark==UP+DOWN) )
                direct=mark;
        }
        /*
            为什么是 0x1b 为什么是 -32 之类的值？
            这些都是原本用同样的办法，两次 getch 之后
            打印并记录下各个按键的值得到的判断
        */
    }
    return 0;
}
 
void restart()
{
    //判断死亡,重新开始游戏;
    MessageBox(NULL,(LPCSTR)"傻逼,死了吧!!!\Once More???",(LPCSTR)"GAME VOER!",MB_OK);
 
    // 分数清零
    score=0; gotoxy(35,3); printf("%03d",score);
    // 开始时间重记
    start = time(NULL);
    // 游戏已进行时间打印为0
    gotoxy(35,4); printf("%03d",0);
 
    // 从尾部开始循环消除蛇身
    while(tail)
    {
        // 休眠以延缓消除时间
        _sleep(200);
        snakel[tail->x][tail->y]=0;   // 清除当前蛇身表的值
        // 移动到屏幕对应坐标输出宫格
        gotoxy(tail->x,tail->y); printf(" ");
        // 临时指针指向尾指针的前一个节点
        p = tail->pre;
        // 释放最后一个节点
        free(tail);
        // 临时节点变成新的尾部
        tail = p;
    }
    // 所有节点释放完毕，头尾指针清空
    head = tail = NULL;
    slength = 1; // 蛇身长度置1
    length=0;    // 链表长度置0
}
 
 
/*
    跳至控制台的(x,y)坐标
*/
void gotoxy(int x,int y)
{
    COORD coord; // 控制台坐标结构体
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition( 
        GetStdHandle( STD_OUTPUT_HANDLE ), // 获取控制台输出流的句柄
        coord   // 设置输出位置的坐标
    );
}