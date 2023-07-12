
#include <stdio.h>
#include <stdlib.h>
struct movie_info {
    int id;
    char name[20];
    long long date;
    int price;
    int seat[5][8] = {0};
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

int main()
{
   
}

