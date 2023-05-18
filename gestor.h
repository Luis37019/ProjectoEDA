#ifndef GESTOR_H
#define GESTOR_H
#define GESTOR 0
typedef struct Gestor {
	unsigned int nif;
	char password[20];
	char name[50];
	char address[100];
	float balance;
	int type;
	struct Gestor* next;
} Gestor;

extern Gestor* gestorHead;

void addGestor(unsigned int nif, char password[], char name[], char address[]);
void registerGestor();
void loginGestor(Gestor* logged_account);
void showUsers();
void removeUsers(unsigned int nif);
void updateGestor(Gestor* logged_account);
void loadGestor();

#endif