
#include <stdio.h>
#include <stdlib.h>
struct movie_info {

    char name[20];
    long long date;
    int price;
    int remain_ticket = 40;

};
struct admin_info {
    int admin_id;
    char password[20];
};
struct user_info{
    int user_id;
    char password[20];
    int ordered_seat[1][1] = { 0 };//座位位置，是一个（x，y）坐标，初始为（0，0）
};
struct order_info {
    char name[20];
    long long date;
    int user_id;
};
movie_info movies[50];
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

//admin部分功能
void add_movie();
void delete_movie();
void sort_movie();
void modify_movie();
void check_ticket();
void display_list();
void back();

//user部分功能
void buy_ticket();
int main()
{
    buy_ticket();
}
void buy_ticket()
{
    FILE* fp = fopen("movie_info.txt", "r");
    if (fp == NULL) {
        printf("电影信息加载失败！\n");
        char ch;
        while ((ch = getchar()) != '\n');
        getchar();
        return;
    }
    int num_movies = 0;
    while ((fscanf(fp, "%s %lld %d", &movies[num_movies].name, &movies[num_movies].date, &movies[num_movies].price))== 3) {  
        num_movies++;
    }
    fclose(fp);
    printf("片名\t时间\t票价\t剩余座位\n");
    for (int i = 0; i < num_movies; i++) {
        printf("%s %lld %d\n", movies[i].name, movies[i].date, movies[i].price);
    }
    char ch;
    while ((ch = getchar()) != '\n');
    getchar();
}
