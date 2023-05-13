#ifndef CLIENTE_H
#define CLIENTE_H
#define CLIENT 0
typedef struct User User;

struct User {
    unsigned int nif;
    char password[20];
    char name[50];
    char address[100];
    float balance;
    int type;
    struct User* next;
};

extern User* userHead;

void addUser(unsigned int nif, char password[], char name[], char address[], float balance);
void registerUser();

void loginUser(User* logged_account);
void removeData(unsigned int nif, char password[]);
void updateData(User* logged_account);
void cpyUserData(User* user1, User* user2);
void addBalance(unsigned int nif, float value);
void viewBalance(User* user);

#endif