
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define NUMBER 50
#define LEN sizeof(struct movie_info)
struct movie_info {
    int id;
    char name[20];
    long long date;
    int price;
    int remain_ticket = 40;
    int room_num;
    int rank;
};
struct admin_info {
    int admin_id;
    char password[20];
};
struct user_info{
    int user_id;
    char password[20];
};
struct order_info {

    char name[20];
    long long date;
    int user_id;
    int ordered_seat_x = 0;
    int ordered_seat_y = 0;
    int room_num;
};
movie_info movies[50];
order_info orders[200];
void add_admin();
void add_user();
void login_admin();
void login_user();
void change_pwd_admin();
void change_pwd_user();
void welcome_menu();
void login_menu();
void admin_menu();
void user_menu();

//可能需要共用的功能
int print_movies();//说明，该函数用于打印电影信息，需要两个文件movie_info.txt ， order_info.txt 编码格式均为ANSI。该函数返回值为电影的总数量，如果部分文件没找到则会返回 -1 同时打印出错消息。
void wait();

//admin部分功能
void add_movie();
void delete_movie();
void sort_movie();
void modify_movie();
void check_ticket();
void display_list();
void back();

//user部分功能
void buy_ticket(user_info user);
void refund_ticket(user_info user);
//void print_movies();


void wait() 
{
    char ch;
    while ((ch = getchar()) != '\n');
    printf("任意键继续……");
    getchar();
}
int main()
{
    sort_movie();
    
    /*user_info user;
    user.user_id = 1;
    buy_ticket(user);*/
 
}


void add_movie() {
    char c[2];
    int i = 0;
    int k = 0;
    FILE* p;
    p = fopen("movie_info.txt", "a+");
    if (p == NULL) {
        printf("影片文件不存在！\n");
        return;
    }

    while (!feof(p)) {

        if (fread(&movies[k], LEN, 1, p) == 1) {
            ++k;
        }
    }
    fclose(p);
    if (k == 0) {
        printf("无加入影片！\n");
    }
    for (int k = 0; k < NUMBER; k++) {
        FILE* p;
        p = fopen("movie_info.txt", "a");
        printf("输入电影序号：");
        scanf("%d", &movies[k].id);
        printf("电影名:");
        scanf("%s", &movies[k].name);
        printf("放映时间:");
        scanf("%lld", &movies[k].date);
        printf("电影票价:");
        scanf("%d", &movies[k].price);
        fprintf(p, "%d %s %lld %d 40\n", movies[k].id, &movies[k].name, movies[k].date, movies[k].price);
            printf("%s已被加入！\n", &movies[k].name);
            k++;
            wait();
        printf("是否继续增加影片？（y/n)");
        scanf("%s", &c);
        if (strcmp(c, "N") == 0 || strcmp(c, "n") == 0) {
            fclose(p);
            return;
        }
        fclose(p);
    }


    printf("结束增加影片的操作！");
}

void delete_movie() {
    int k = 0;
    int number = 0;//
    int i = 0;
    int j;
    char c[2];
    FILE* p;
   
        FILE* fp = fopen("movie_info.txt", "r");
        if (fp == NULL) {
            printf("电影信息加载失败！\n");
            wait();
            return;
        }
        int num_movies = 0;
        while ((fscanf(fp, "%d %s %lld %d %d", &movies[num_movies].id, &movies[num_movies].name, &movies[num_movies].date, &movies[num_movies].price, &movies[num_movies].remain_ticket)) == 5) {
            num_movies++;
        }
        fclose(fp);
        k = print_movies();
    printf("输入删除的电影序号：");
    scanf("%d", &number);
    for (i = 0; i < k; i++)
    {
        if (number == movies[i].id)
        {
            printf("找到该电影，是否删除？（y/n)\n");
            scanf("%s", &c);
            if (strcmp(c, "Y") == 0 || strcmp(c, "y") == 0)
            {
                for (j = i; j < k; j++)
                {
                    movies[j] = movies[j + 1];//将后一个记录前移
                }
                k--;
            }
            else
            {
                printf("找到电影，不删除。\n");
                return;
            }
            if ((p = fopen("movie_info.txt", "w")) == NULL)
            {
                printf("文件不存在！\n");
                return;
            }
            for (j = 0; j < k; j++)
            {
                fprintf(p, "%d %s %lld %d 40\n", movies[j].id, &movies[j].name, movies[j].date, movies[j].price);
               
            }
            fclose(p);
            printf("删除成功\n");
            break;
        }
        if (i == k)
        {
            printf("没有找到该电影\n");
        }
    }
}

void sort_movie() {
    FILE* p;

    FILE* fp = fopen("movie_info.txt", "r");
    if (fp == NULL) {
        printf("电影信息加载失败！\n");
        wait();
        return;
    }
    int num_movies = 0;
    while ((fscanf(fp, "%d %s %lld %d %d", &movies[num_movies].id, &movies[num_movies].name, &movies[num_movies].date, &movies[num_movies].price, &movies[num_movies].remain_ticket)) == 5) {
        movies[num_movies].rank = num_movies;
        num_movies++;
    }
    fclose(fp);
    movie_info temp;
        int i, j;
    for (i = 0; i < num_movies-1; i++) {
        for (j = 0; j < num_movies -1- i;j++) {
            if (movies[j].date >movies[j + 1].date) {
                temp = movies[j];
                movies[j]= movies[j + 1];
                movies[j + 1] = temp;
            }
        }
    }
    int rank = 0;
    for (i = 0; i < num_movies; i++) {
        if (i > 0 && movies[i].date != movies[i - 1].date) {
            rank++;
        }
        movies[i].rank = rank;
    }
    p=fopen("movie_info.txt", "w");
    for (j = 0; j < num_movies; j++)
    {
        fprintf(p, "%d %s %lld %d 40\n", movies[j].id, &movies[j].name, movies[j].date, movies[j].price);

    }
    fclose(p);
    print_movies();
}













void buy_ticket(user_info user)
{
    //打印电影信息 需要的文件：movie_info.txt ， order_info.txt 编码格式ANSI
    start:int num_movies = print_movies();
    //打印电影信息结束
    //开始选票 注意这里i变量作为电影定位符号不可以轻易更改！
    printf("\n\n请输入需要预约电影票的ID（请注意同一电影不同时间的ID不同）：");
    int choose_id;
    scanf("%d", &choose_id);
    for (int i = 0; i < num_movies; i++) {
        if (movies[i].id == choose_id)
        {
            if (movies[i].remain_ticket >= 1)
            {
                char ch;
                while ((ch = getchar()) != '\n');
                printf("您要预约 %lld时间段 ，名为《%s》的电影票，是否确认电影及时间段？（确认请输入Y）",movies[i].date,movies[i].name);
                char choice;
                scanf("%c", &choice);
                if (choice == 'Y' || choice == 'y')
                {
                    printf("请输入需要预约的电影票数量（单个用户最多预约五张电影票）：");
                    int ticket_num;
                    scanf("%d", &ticket_num);
                    while (ticket_num > 5 || ticket_num < 1)
                    {
                        printf("错误，请输入正确的电影票数量！\n请输入需要购买的电影票数量（单个用户最多预约五张电影票）：");
                        scanf("%d", &ticket_num);
                    }
                    FILE* order_info = fopen("order_info.txt", "r");
                    if (order_info == NULL) {
                        printf("预定信息加载失败！请联系管理员。\n");
                        wait();
                        return;
                    }
                    int order_num = 0;
                    system("cls");//开始打印座位信息
                    printf("\n\n");
                    while(fscanf(order_info, "%s %lld %d %d %d",orders[order_num].name, & orders[order_num].date, &orders[order_num].ordered_seat_x, &orders[order_num].ordered_seat_y, &orders[order_num].user_id)==5)
                        order_num++;
                    fclose(order_info);
                    int order[5][8] = {0};
                    printf("\n——————————————屏幕——————————————\n");
                    for (int k = 0; k < 5; k++)
                    {   
                        for (int j = 0; j < 8; j++)
                        {
                            for (int n = 0; n<order_num; n++)//该循环用于检测是否存在信息重合的情况，可复用
                            {
                                if (strcmp(orders[n].name, movies[i].name) == 0&& orders[n].date == movies[i].date && orders[n].ordered_seat_x - 1 == k && orders[n].ordered_seat_y - 1 == j) order[k][j] = 1;
                            }
                            
                        }
                    }
                    for (int k = 0; k < 5; k++)
                    {
                        printf("第%d排   ",k+1);
                        for (int j = 0; j < 8; j++)
                        {
                            if (order[k][j] == 1)printf("  *  ");
                            else printf("  0  ");
                        }
                        printf("\n");
                    }
                    
                    for (int k = 0; k < ticket_num; k++)
                    {
                       choose: printf("\n请为第%d张票选择座位！（0为可选座位，*为不可选或您已定座位)", k + 1);
                        printf("\n输入选定座位的行数和列数（例如：第一排第一位，输入”1 1“并回车）：");
                        int x, y = 0;
                        scanf("%d %d", &x, &y);
                        for (int k = 0; k < 5; k++)
                        {
                            for (int j = 0; j < 8; j++)
                            {
                                for (int n = 0; n < order_num; n++)
                                {
                                    if (strcmp(orders[n].name, movies[i].name) == 0 && orders[n].date == movies[i].date && orders[n].ordered_seat_x - 1 == k && orders[n].ordered_seat_y - 1 == j)
                                    {
                                        if (k == x && j == y)
                                        {
                                            printf("\n该座位已被预定！请重新选择！\n");
                                            goto choose;
                                        }
                                        if (x > 5 || y > 8)
                                        {
                                            printf("\n行数或列数超出范围！请重新输入！\n");
                                            goto choose;
                                        }
                                    }
                                }
                                
                                    
                                    
                            }
                        }
                        FILE* order = fopen("order_info.txt", "a");
                        if (order == NULL) {
                            printf("预定信息加载失败！请联系管理员。\n");
                            wait();
                            return;
                        }
                        fprintf(order, "%s %lld %d %d %d\n", &movies[i].name, movies[i].date, x, y, user.user_id);
                        fclose(order);
                    }
                    printf("您已成功预约 %lld时间段 ，名为《%s》的电影票，总价为%d！\n感谢您使用本程序！", movies[i].date, movies[i].name, ticket_num * movies[i].price);
                    wait();
                    return;
                }
                else goto start;

            }
            else {
                printf("您选择的电影在该场次的电影票已售罄，请选择其他场次或电影！");
                wait();
                goto start;
            }
        }
        
    }
    
        printf("没有找到该电影，请确认ID后重新输入！");
        wait();
        goto start;
    
}



int print_movies()
{
    system("cls");
    FILE* fp = fopen("movie_info.txt", "r");
    if (fp == NULL) {
        printf("电影信息加载失败！\n");
        wait();
        return-1;
    }
    int num_movies = 0;
    while ((fscanf(fp, "%d %s %lld %d %d", &movies[num_movies].id, &movies[num_movies].name, &movies[num_movies].date, &movies[num_movies].price, &movies[num_movies].remain_ticket)) == 5) {
        num_movies++;
    }
    fclose(fp);
    FILE* order_info = fopen("order_info.txt", "r");
    if (order_info == NULL) {
        printf("预定信息加载失败！请联系管理员。\n");
        wait();
        return-1;
    }
    int order_num = 0;
    while (fscanf(order_info, "%s %lld %d %d %d", orders[order_num].name, &orders[order_num].date, &orders[order_num].ordered_seat_x, &orders[order_num].ordered_seat_y, &orders[order_num].user_id) == 5)
        order_num++;
    fclose(order_info);
    printf("ID\t片名\t时间\t票价\t剩余座位\n");

    for (int i = 0; i < num_movies; i++) {
        for (int n = 0; n < order_num; n++)
        {
            if (strcmp(orders[n].name, movies[i].name) == 0 && orders[n].date == movies[i].date) movies->remain_ticket--;
        }
        printf("%-7d %s %lld %d    剩余%d个\n", movies[i].id, movies[i].name, movies[i].date, movies[i].price, movies[i].remain_ticket);
    }
    return num_movies;
}
