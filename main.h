
#ifndef EDA2_MAIN_H
#define EDA2_MAIN_H

#endif //EDA2_MAIN_H
     typedef struct{
        char name[20];
        int year_nacimiento[1];
        char correo[30];
        char Localizacion[20];
        char gustos[5][30];
        struct post *Timeline;
        struct Usuario* soli[20];
        struct Usuario* head;
        struct Usuario* actual;
        struct Usuario* siguiente;
    }Usuario;

typedef struct{
    char publicacion[120];
}post;
Usuario *print_users(Usuario *lista);

Usuario *search_user(Usuario *node, char *nombre);

int leerArchivo(const char* nombreArchivo, Usuario* lista);