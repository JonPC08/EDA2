
#ifndef EDA2_MAIN_H
#define EDA2_MAIN_H

#endif //EDA2_MAIN_H
 typedef struct{
    char name[20];
    int año_nacimiento[4];
    char correo[30];
    char Localizacion[20];
    char gustos[5][30];
}Usuario;
typedef struct node{
    Usuario usuario;
    struct node *siguiente;
} Node;
Node *print_users(Node *lista);

Node *search_user(Node *node, char *nombre);
