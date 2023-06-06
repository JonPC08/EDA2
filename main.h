#ifndef EDA2_MAIN_H
#define EDA2_MAIN_H
#define MAX_AMIGOS 100

#endif //EDA2_MAIN_H//
typedef struct {
    char name[20];
    int year_nacimiento;
    char correo[30];
    char Localizacion[20];
    int cantidad_de_gustos;
    char gustos[5][30];
    char password[20];
    int id;
    struct post* Timeline;
    struct Usuario* soli[20];
    struct Usuario* head;
    struct Usuario* siguiente;
    struct Usuario* amigos[MAX_AMIGOS]; // Array to store friends
    int num_amigos; // Number of friends
    int num_soli;
    int num_posts;
} Usuario;


typedef struct{
    char publicacion[121];
    struct post* siguiente;
}post;
/*
void add_user(Usuario** lista, Usuario* usuario_nuevo);
Usuario* print_users(Usuario *lista);
Usuario *search_user(Usuario *node, char *nombre);
int hash_function(int id);
void add_post(Usuario* usuario, const char* message);
void add_friend_request(Usuario* usuario, Usuario* amigo);
void accept_friend_request(Usuario* usuario);
void remove(Usuario* usuario);
void leerArchivo(const char* nombreArchivo, Usuario** lista);*/