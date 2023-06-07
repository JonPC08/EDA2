#ifndef EDA2_MAIN_H
#define EDA2_MAIN_H

#define MAX_AMIGOS 100
#define MAX_NAME_LENGTH 20
#define MAX_EMAIL_LENGTH 30
#define MAX_LOCATION_LENGTH 20
#define MAX_NUM_GUSTOS 5
#define MAX_GUSTO_LENGTH 30
#define MAX_PASSWORD_LENGTH 20
#define MAX_POST_LENGTH 121

typedef struct Usuario Usuario;
typedef struct Post Post;

struct Usuario {
    char name[MAX_NAME_LENGTH];
    int year_nacimiento;
    char correo[MAX_EMAIL_LENGTH];
    char Localizacion[MAX_LOCATION_LENGTH];
    int cantidad_de_gustos;
    char gustos[MAX_NUM_GUSTOS][MAX_GUSTO_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int id;
    struct Post* Timeline;
    struct Usuario* soli[20];
    struct Usuario* head;
    struct Usuario* siguiente;
    struct Usuario* amigos[MAX_AMIGOS]; // Array to store friends
    int num_amigos; // Number of friends
    int num_soli;
    int num_posts;
};

typedef struct{
    char publicacion[121];
    struct post* siguiente;
}post;

void add_user(Usuario** lista, Usuario* usuario_nuevo);
Usuario* print_users(Usuario* lista);
Usuario* search_user(Usuario* node, char* nombre);
int hash_function(int id);
void add_post(Usuario* usuario, const char* message);
void print_posts(char nombre[20], Usuario* lista);
void add_friend_request(Usuario* usuario, Usuario* amigo);
void accept_friend_request(Usuario* usuario);
void remove_friend(Usuario* usuario);
int leerArchivo(const char* nombreArchivo, Usuario** lista, int id_count, Usuario** hash_table);

#endif // EDA2_MAIN_H
