
#include <string.h>
#include <stdio.h>
#include<conio.h>
#include <stdlib.h>
#define NUMBER 50
#define MAX_ADMIN 50
#define LEN sizeof(struct movie_info)
struct movie_info 
{
    int id;
    char name[20];
    long long date;
    int price;
    int remain_ticket = 40;
    int room_num;
    int rank;
};
struct admin_info 
{
    int admin_id;
    char password[20];
};
struct user_info 
{
    int user_id;
    char password[20];
};
struct order_info 
{
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
void admin_menu();
void user_menu(user_info user);
void login_admin_menu();
void login_user_menu();


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
void back() { welcome_menu(); }

//user部分功能
void buy_ticket(user_info user);
//void refund_ticket(user_info user);
//void search_movies();


void wait()
{
    char ch;
    while ((ch = getchar()) != '\n');
    printf("任意键继续……");
    getchar();
}

void welcome_menu()//初始菜单栏
{
    system("cls");
    int n;
    printf("--------MOVIE MANAGER--------\n");
    printf("----------1.管理员-----------\n");
    printf("----------2.用户-------------\n");
    printf("----------0.退出-------------\n");
    printf("---输入（1/2),选择你的身份---\n");
    scanf("%d", &n);
    while (n)
    {
        switch (n)
        {
        case 1:login_admin_menu();
            break;
        case 2:login_user_menu();
            break;
        case 0:return;
        default:printf("-----无效的选项！-----\n");
            wait();
            break;
        }
        _getch();
        welcome_menu();
    }
    
}

void login_user_menu()
{
    system("cls");
    int n;
    printf("-------LOGIN USER MENU-------\n");
    printf("-----------1.登录-------------\n");
    printf("-----------2.注册-------------\n");
    printf("-----------3.修改密码---------\n");
    printf("-----------0.退出-------------\n");
    printf("--输入数字选择您要进行的操作--\n");
    scanf("%d", &n);
    while (n)
    {
        switch (n)
        {
        case 1:login_user();
            break;
        case 2:add_user();
            break;
        case 3:change_pwd_user();
            break;
        case 0:welcome_menu();
            break;
        default:printf("-----无效的选项！-----\n");
            break;
        }
        _getch();
        printf("--------LOGIN ADMIN MENU--------\n");
        printf("-----------1.登录-------------\n");
        printf("-----------2.注册-------------\n");
        printf("-----------3.修改密码---------\n");
        printf("-----------0.退出-------------\n");
        printf("--输入数字选择您要进行的操作--\n");
        scanf("%d", &n);
    }
    return;
}

void login_admin_menu()
{
    system("cls");
    int n;
    printf("-------LOGIN ADMIN MENU-------\n");
    printf("-----------1.登录-------------\n");
    printf("-----------2.注册-------------\n");
    printf("-----------3.修改密码---------\n");
    printf("-----------0.退出-------------\n");
    printf("--输入数字选择您要进行的操作--\n");
    scanf("%d", &n);
    while (n)
    {
        switch (n)
        {
        case 1:login_admin();
            break;
        case 2:add_admin();
            break;
        case 3:change_pwd_admin();
            break;
        case 0:welcome_menu();
            break;
        default:printf("-----无效的选项！-----\n");
            break;
        }
        _getch();
        login_admin_menu();
    }
    return;
}

void add_user()
{
    system("cls");
    user_info a, b;
    FILE* fp;
    char password_two[20];

    printf("----欢迎来到注册界面----\n");
    fp = fopen("user_info.txt", "r");
    fscanf(fp, "%d %s", &b.user_id, b.password);
    printf("请输入你的账号ID\n");
    scanf("%d", &a.user_id);
    while (1)
    {
        if (a.user_id != b.user_id) //如果两串不相等
        {
            if (!feof(fp))
            {
                fscanf(fp, "%d %s", &b.user_id, b.password);
            }
            else
            {
                break;
            }
        }
        else
        {
            printf("此用户名已存在！请重新注册！\n");
            fclose(fp);
            fp = NULL;
            return;
        }
    }
    printf("请输入密码\n");
    scanf("%s", &a.password);
    printf("请再次输入，确认密码\n");
    scanf("%s", &password_two);
    do
    {
        if (!strcmp(a.password, password_two))
        {
            fp = fopen("user_info.txt", "a+");
            fprintf(fp, "%d %s\n", a.user_id, &a.password);
            printf("账号注册成功，请登录！\n");
            fclose(fp);
            _getch();
            return;
        }
        else
        {
            printf("两次密码不匹配！请重新输入！\n");
            scanf("%s", &a.password);
            printf("请确认密码\n");
            scanf("%s", &password_two);
        }
    } while (1);
}

void add_admin()
{
    system("cls");
    admin_info a, b;
    FILE* fp;
    char password_two[20];

    printf("----欢迎来到注册界面----\n");
    fp = fopen("admin_info.txt", "r");
    fscanf(fp, "%d %s", &b.admin_id, b.password);
    printf("请输入你的账号ID\n");
    scanf("%d", &a.admin_id);
    while (1)
    {
        if (a.admin_id != b.admin_id) //如果两串不相等
        {
            if (!feof(fp))
            {
                fscanf(fp, "%d %s", &b.admin_id, b.password);
            }
            else
            {
                break;
            }
        }
        else
        {
            printf("此用户名已存在！请重新注册！\n");
            fclose(fp);
            fp = NULL;
            return;
        }
    }
    printf("请输入密码\n");
    scanf("%s", &a.password);
    printf("请再次输入，确认密码\n");
    scanf("%s", &password_two);
    do
    {
        if (!strcmp(a.password, password_two))
        {
            fp = fopen("admin_info.txt", "a+");
            fprintf(fp, "%d %s\n", a.admin_id, &a.password);
            printf("账号注册成功，请登录！\n");
            fclose(fp);
            _getch();
            return;
        }
        else
        {
            printf("两次密码不匹配！请重新输入！\n");
            scanf("%s", &a.password);
            printf("请确认密码\n");
            scanf("%s", &password_two);
        }
    } while (1);
}

void login_user()
{
    system("cls");
    user_info a, b[MAX_ADMIN];
    FILE* fp;
    int n;

    printf("-----欢迎来到用户登录界面!-----\n");
    printf("--------请输入账号:--------\n");
    scanf("%d", &a.user_id);
    printf("--------请输入密码:--------\n");

    int i = 0;
    do {                         //用*掩盖明文密码
        a.password[i] = _getch();
        if (a.password[i] == '\r')
            break;
        if (a.password[i] == '\b')
        {
            if (i == 0)
            {
                printf("\a");
                continue;
            }
            i = i - 1;
            printf("\b");
        }
        else
        {
            i = i + 1;
            printf("*");
        }
    } while (a.password[i] != '\n' && i < 20);

    a.password[i] = '\0';
    printf("\n");

    fp = fopen("user_info.txt", "r");

    int user_num = 0;
    int user_found = 0;
    while ((fscanf(fp, "%d %s", &b[user_num].user_id,&b[user_num].password)) == 2) user_num++;
    fclose(fp);
    
        for (int i = 0; i < user_num; ++i)
        {
            if (a.user_id == b[i].user_id)
            {
                if (strcmp(b[i].password, a.password) == 0)
                {
                    printf("登录成功！");
                    wait();
                    user_menu(a);
                }
            }
        }
        
            printf("未找到该用户，请重试！");
            wait();
            printf("------账号或密码错误！------\n");
            char temp;
            while ((temp = getchar()) != '\n');
            printf("-----1.重新输入密码-------\n");
            printf("-----2.注册新账号---------\n");
            printf("-----0.退出---------------\n");
            scanf("%d", &n);
            switch (n)
            {
                case 1:
                    login_user();//再次输入密码
                    break;
                case 2:
                    add_user();//注册新账号
                    break;
                case 0:
                    break;         //退出系统
                default:
                    printf("-----无效的选项！-----\n");
                    break;
                
            }
}

void login_admin()
{
    system("cls");
    admin_info a, b[MAX_ADMIN];
    FILE* fp;
    int n;

    printf("-----欢迎来到登录界面!-----\n");
    printf("--------请输入账号:--------\n");
    scanf("%d", &a.admin_id);
    printf("--------请输入密码:--------\n");

    int i = 0;
    do {                         //用*掩盖明文密码
        a.password[i] = _getch();
        if (a.password[i] == '\r')
            break;
        if (a.password[i] == '\b')
        {
            if (i == 0)
            {
                printf("\a");
                continue;
            }
            i = i - 1;
            printf("\b");
        }
        else
        {
            i = i + 1;
            printf("*");
        }
    } while (a.password[i] != '\n' && i < 20);

    a.password[i] = '\0';
    printf("\n");

    fp = fopen("admin_info.txt", "r");
    int user_num = 0;
    int user_found = 0;
    while ((fscanf(fp, "%d %s", &b[user_num].admin_id, &b[user_num].password)) == 2) user_num++;
    fclose(fp);

    for (int i = 0; i < user_num; ++i)
    {
        if (a.admin_id == b[i].admin_id)
        {
            if (strcmp(b[i].password, a.password) == 0)
            {
                printf("登录成功！");
                wait();
                admin_menu();
            }
        }
    }

    printf("未找到该用户，请重试！");
    wait();
    printf("------账号或密码错误！------\n");
    char temp;
    while ((temp = getchar()) != '\n');
    printf("-----1.重新输入密码-------\n");
    printf("-----2.注册新账号---------\n");
    printf("-----0.退出---------------\n");
    scanf("%d", &n);
    switch (n)
    {
    case 1:
        login_admin();
        break;
    case 2:
        add_admin();
        break;
    case 0:
        break;
    default:
        printf("-----输入内容无效-----\n");
        break;
    }
}

void change_pwd_user()
{
    system("cls");
    user_info a, b;
    int  n;
    FILE* fp;

    printf("----欢迎来到修改密码界面！------\n");
    printf("请输入账号:\n ");      // 获取要修改密码用户的信息
    scanf("%d", &a.user_id);

    printf("请输入原密码:\n ");
    int i = 0;
    do {                           //用*掩盖明文密码
        a.password[i] = _getch();
        if (a.password[i] == '\r')
            break;
        if (a.password[i] == '\b')
        {
            if (i == 0)
            {
                printf("\a");
                continue;
            }
            i = i - 1;
            printf("\b");
        }
        else
        {
            i = i + 1;
            printf("*");
        }
    } while (a.password[i] != '\n' && i < 20);

    a.password[i] = '\0';
    printf("\n");

    fp = fopen("user_info.txt", "r");                                      // 打开原始文件和临时文件
    FILE* temp_fp = fopen("temp_user_info.txt", "w");

    int found = 0;

    while (fscanf(fp, "%d %s", &b.user_id, b.password) == 2)
    {
        if (a.user_id == b.user_id && strcmp(a.password, b.password) == 0) // 找到要修改密码的用户，读取新密码
        {

            printf("请输入新密码: ");
            int i = 0;
            do
            {
                b.password[i] = _getch();
                if (b.password[i] == '\r')
                    break;
                if (b.password[i] == '\b')
                {
                    if (i == 0)
                    {
                        printf("\a");
                        continue;
                    }
                    i = i - 1;
                    printf("\b");
                }
                else
                {
                    i = i + 1;
                    printf("*");
                }
            } while (b.password[i] != '\n' && i < 20);

            b.password[i] = '\0';
            printf("\n");

            found = 1;
        }
        fprintf(temp_fp, "%d %s\n", b.user_id, b.password);   // 将用户信息写入临时文件
    }
    fclose(fp);// 关闭文件
    fclose(temp_fp);
    remove("admin_info.txt"); // 删除原始文件

    if (found)
    {
        rename("temp_user_info.txt", "user_info.txt");// 重命名临时文件为原始文件
        printf("密码修改成功！\n");
    }
    else
    {
        remove("temp_user_info.txt");           // 删除临时文件
        printf("-----用户名或原密码错误------\n");
        printf("------1.继续修改密码---------\n");
        printf("------2.登录-----------------\n");
        printf("------3.注册-----------------\n");
        printf("------0.退出-----------------\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:change_pwd_user();
            break;
        case 2:login_user();
            break;
        case 3:add_user();
            break;
        case 0:
            break;
        default:printf("-----输入内容无效-------\n");
            break;
        }
    }
    return;
}

void change_pwd_admin()
{
    system("cls");
    admin_info a, b;
    int  n;
    FILE* fp;

    printf("----欢迎来到修改密码界面！------\n");
    printf("请输入账号:\n ");      // 获取要修改密码用户的信息
    scanf("%d", &a.admin_id);

    printf("请输入原密码:\n ");
    int i = 0;
    do {                           //用*掩盖明文密码
        a.password[i] = _getch();
        if (a.password[i] == '\r')
            break;
        if (a.password[i] == '\b')
        {
            if (i == 0)
            {
                printf("\a");
                continue;
            }
            i = i - 1;
            printf("\b");
        }
        else
        {
            i = i + 1;
            printf("*");
        }
    } while (a.password[i] != '\n' && i < 20);

    a.password[i] = '\0';
    printf("\n");

    fp = fopen("admin_info.txt", "r");                                      // 打开原始文件和临时文件
    FILE* temp_fp = fopen("temp_admin_info.txt", "w");

    int found = 0;

    while (fscanf(fp, "%d %s", &b.admin_id, b.password) == 2)
    {
        if (a.admin_id == b.admin_id && strcmp(a.password, b.password) == 0) // 找到要修改密码的用户，读取新密码
        {

            printf("请输入新密码: ");
            int i = 0;
            do
            {
                b.password[i] = _getch();
                if (b.password[i] == '\r')
                    break;
                if (b.password[i] == '\b')
                {
                    if (i == 0)
                    {
                        printf("\a");
                        continue;
                    }
                    i = i - 1;
                    printf("\b");
                }
                else
                {
                    i = i + 1;
                    printf("*");
                }
            } while (b.password[i] != '\n' && i < 20);

            b.password[i] = '\0';
            printf("\n");

            found = 1;
        }
        fprintf(temp_fp, "%d %s\n", b.admin_id, b.password);   // 将用户信息写入临时文件
    }
    fclose(fp);// 关闭文件
    fclose(temp_fp);
    remove("admin_info.txt"); // 删除原始文件

    if (found)
    {
        rename("temp_admin_info.txt", "admin_info.txt");// 重命名临时文件为原始文件
        printf("密码修改成功！\n");
    }
    else
    {
        remove("temp_admin_info.txt");           // 删除临时文件
        printf("-----用户名或原密码错误------\n");
        printf("------1.继续修改密码---------\n");
        printf("------2.登录-----------------\n");
        printf("------3.注册-----------------\n");
        printf("------0.退出-----------------\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:change_pwd_admin();
            break;
        case 2:login_admin();
            break;
        case 3:add_admin();
            break;
        case 0:
            break;
        default:printf("-----输入内容无效-------\n");
            break;
        }
    }
    return;
}

void admin_menu()//管理员功能菜单
{
    system("cls");
    int n;
    printf("--------ADMIN MENU--------------\n");
    printf("--------1.增加影片---------------\n");
    printf("--------2.删除影片---------------\n");
    printf("--------3.影片排序---------------\n");
    printf("--------4.修改影片---------------\n");
    printf("--------5.电影票核销-------------\n");
    printf("--------6.显示排片---------------\n");
    printf("--------7.返回------------------\n");
    printf("-----输入数字选择您要进行的操作----\n");
    scanf("%d", &n);
    while (n)
    {
        switch (n)
        {
        case 1:add_movie();
            break;
        case 2:delete_movie();
            break;
        case 3:sort_movie();
            break;
        case 4:modify_movie();
            break;
        case 5:check_ticket();
            break;
        case 6:display_list();
            break;
        case 7:back();
            break;
        default:break;
        }
        _getch();
        printf("----------ADMIN MENU-------------\n");
        printf("--------1.增加影片---------------\n");
        printf("--------2.删除影片---------------\n");
        printf("--------3.影片排序---------------\n");
        printf("--------4.修改影片---------------\n");
        printf("--------5.电影票核销-------------\n");
        printf("--------6.显示排片---------------\n");
        printf("--------7.返回-------------------\n");
        printf("-----输入数字选择您要进行的操作--\n");
        scanf("%d", &n);
    }
    return;
}

void user_menu(user_info user)
{
    system("cls");
    int n;
    printf("--------USER MENU--------------\n");
    printf("--------1.查询电影信息---------------\n");
    printf("--------2.显示电影排片信息---------------\n");
    printf("--------3.预定电影票---------------\n");
    printf("--------4.退定电影票---------------\n");
    printf("--------5.返回------------------\n");
    printf("-----输入数字选择您要进行的操作----\n");
    scanf("%d", &n);
    while (n)
    {
        switch (n)
        {
        case 1:return;
            break;
        case 2:print_movies();
            break;
        case 3:buy_ticket(user);
            break;
        case 4:/*refund_movie()*/;
            break;
        case 5:welcome_menu();
            break;
        default:break;
        }
        _getch();
        printf("--------USER MENU--------------\n");
        printf("--------1.查询电影信息---------------\n");
        printf("--------2.显示电影拍片信息---------------\n");
        printf("--------3.预定电影票---------------\n");
        printf("--------4.退定电影票---------------\n");
        printf("--------5.返回------------------\n");
        printf("-----输入数字选择您要进行的操作----\n");
        scanf("%d", &n);
    }
    return;
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
        scanf("%s", movies[k].name);
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
    for (i = 0; i < num_movies - 1; i++) {
        for (j = 0; j < num_movies - 1 - i; j++) {
            if (movies[j].date > movies[j + 1].date) {
                temp = movies[j];
                movies[j] = movies[j + 1];
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
    p = fopen("movie_info.txt", "w");
    for (j = 0; j < num_movies; j++)
    {
        fprintf(p, "%d %s %lld %d 40\n", movies[j].id, &movies[j].name, movies[j].date, movies[j].price);

    }
    fclose(p);
    print_movies();
}

void modify_movie() {
    FILE* p;
    char movie_name[50];
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
    int label = 0;
    for (int i = 0; i < num_movies; i++) {
        printf("输入修改电影的名称：");
        scanf("%s", movie_name);
        if (strcmp(movie_name, movies[i].name) == 0) {
            printf("输入新的电影名称、放映时间、影片价格：");
            scanf("%s %d %d", movies[i].name, &movies[i].date, &movies[i].price);
            label = 1;
            break;
        }
    }
    if (label != 1) {
        printf("无该名称的电影！");
    }
}

void check_ticket() {
    FILE* order_info = fopen("order_info.txt", "r");
    FILE* p;
    int id;
    int found_num = 0;
    int order_num = 0;
    if (order_info == NULL) {
        printf("预定信息加载失败！请联系管理员。\n");
        wait();
        return;
    }
    
    while (fscanf(order_info, "%s %lld %d %d %d", orders[order_num].name, &orders[order_num].date, &orders[order_num].ordered_seat_x, &orders[order_num].ordered_seat_y, &orders[order_num].user_id) == 5)
        order_num++;
    fclose(order_info);
    
    if (order_num == 0) {
        printf("用户无电影预定信息！");
        wait();
        return;
    }
    int k = order_num;
    printf("请输入要核销的用户id: ");
    scanf("%d", &id);
    for (int m = 0; m < k; m++) {
        for (int i = 0; i < order_num; i++) {
            if (orders[i].user_id == id) {
                found_num++;
                printf("已找到%d用户的电影预定信息：\n电影名称：%s \n播放日期：%lld\n第%d排,第%d列", orders[i].user_id, &orders[i].name, orders[i].date, orders[i].ordered_seat_x, orders[i].ordered_seat_y);
                char ch;
                while ((ch = getchar()) != '\n');
                printf("是否确认核销？（Y确认）：");
                scanf("%c", &ch);
                if (ch == 'y' || ch == 'Y')
                {
                    for (int j = i; j < k; j++)
                    {                      
                            movies[j] = movies[j + 1];//将后一个记录前移
                    }
                    k--;
                    printf("\n电影核销成功！");
                }
                else
                {
                    printf("\n电影核销已取消！");
                    continue;
                }
            }
            if ((p = fopen("order_info.txt", "w")) == NULL)
            {
                printf("文件不存在！\n");
                return;
            }
            for (int j = 0; j < k; j++)
            {
                fprintf(p, "% s % lld % d % d % d\n", &orders[j].name, orders[j].date, orders[j].ordered_seat_x, orders[j].ordered_seat_y, orders[j].user_id);

            }
            fclose(p);
        }


    }
    if (!found_num)printf("未找到用户%d相关的订票信息！", id);
    char ch;
    printf("是否继续核销？（输入Y继续）：");
    while ((ch = getchar()) != '\n');
    scanf("%c", &ch);
    if (ch == 'y' || ch == 'Y')check_ticket();
}

void display_list() {

    print_movies();
    wait();
    system("cls");
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
                printf("您要预约 %lld时间段 ，名为《%s》的电影票，是否确认电影及时间段？（确认请输入Y）", movies[i].date, movies[i].name);
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
                    while (fscanf(order_info, "%s %lld %d %d %d", orders[order_num].name, &orders[order_num].date, &orders[order_num].ordered_seat_x, &orders[order_num].ordered_seat_y, &orders[order_num].user_id) == 5)
                        order_num++;
                    fclose(order_info);
                    int order[5][8] = { 0 };
                    printf("\n——————————————屏幕——————————————\n");
                    for (int k = 0; k < 5; k++)
                    {
                        for (int j = 0; j < 8; j++)
                        {
                            for (int n = 0; n < order_num; n++)//该循环用于检测是否存在信息重合的情况，可复用
                            {
                                if (strcmp(orders[n].name, movies[i].name) == 0 && orders[n].date == movies[i].date && orders[n].ordered_seat_x - 1 == k && orders[n].ordered_seat_y - 1 == j) order[k][j] = 1;
                            }

                        }
                    }
                    for (int k = 0; k < 5; k++)
                    {
                        printf("第%d排   ", k + 1);
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
            if (strcmp(orders[n].name, movies[i].name) == 0 && orders[n].date == movies[i].date) movies[i].remain_ticket--;
        }
        printf("%-7d %s %lld %d    剩余%d个\n", movies[i].id, movies[i].name, movies[i].date, movies[i].price, movies[i].remain_ticket);
    }
    return num_movies;
}

int main()
{
    welcome_menu();
}
