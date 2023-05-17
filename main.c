#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"

void add_user(Node **lista, Usuario usuario_nuevo) {
    Node *new_node = malloc(sizeof(Node));
    new_node->usuario = usuario_nuevo;
    new_node->siguiente = NULL;
    // Si la lista está vacía, el nuevo nodo se convierte en el primer nodo
    if (*lista == NULL) {
        *lista = new_node;
    }
        // Si la lista no está vacía, se enlaza el nuevo nodo al principio de la lista
    else {
        new_node->siguiente = *lista;
        *lista = new_node;
    }
}
Node *print_users(Node *lista) {
    Node *actual_node = lista;
    while (actual_node != NULL) {
        printf("Nombre de usuario: %s\n", actual_node->usuario.name);
        printf("Año nacimiento %d", actual_node->usuario.year_nacimiento);
        printf("Correo %s", actual_node->usuario.correo);
        printf("Localización %s", actual_node->usuario.Localizacion);
        printf("Gustos %s-%s-%s-%s-%s", actual_node->usuario.gustos[0],actual_node->usuario.gustos[1],actual_node->usuario.gustos[2],actual_node->usuario.gustos[3],actual_node->usuario.gustos[4]);
        actual_node = actual_node->siguiente;
    }
    return actual_node;
}
Node *search_user(Node *head, char *nombre) {
    Node *actual = head;
    while (actual != NULL) {
        if (strcmp(actual->usuario.name, nombre) == 0) {
            return actual; // si encuentra el usuario, devuelve el nodo
        }
        actual = actual->siguiente;
    }
    return NULL; // si no encuentra el usuario, devuelve NULL
}
int leerArchivo(const char* nombreArchivo, Node** lista) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return -1;
    }

    char linea[256];

    while (fgets(linea, sizeof(linea), archivo)) {
        Usuario usuario;
        int numCampos = sscanf(linea, "%19[^,],%4[^,],%29[^,],%19[^,],%29[^,],%29[^,],%29[^,],%29[^,],%29[^,\n]",
                               usuario.name, usuario.year_nacimiento, usuario.correo, usuario.Localizacion,
                               usuario.gustos[0], usuario.gustos[1], usuario.gustos[2], usuario.gustos[3], usuario.gustos[4]);

        if (numCampos == 8) {
            add_user(lista, usuario);
        } else {
            printf("Error al leer los campos del usuario.\n");
        }
    }

    fclose(archivo);
    return 1;
}
int main() {
    while (1){
        Node *lista = NULL;
        printf("\n\n\n\nOpciones Menu Principal\n"
               "1. Insertar Nuevo usuario.\n"
               "2. Listar todos los usuarios.\n"
               "3. Encontrar y operar como un usuario en especifico.\n"
               "4. Salir\n");
        int option;
        printf("Selecciona una de las opciones con un numero del 1 al 4:\n");
        scanf("%i",&option);

        if (option == 1){
            // Añade un usuario y lo printea
            for (int i = 0; i < 100; i++) {
                Usuario usuario_nuevo;
                sprintf(usuario_nuevo.name, "usuario%d", i);
                add_user(&lista, &usuario_nuevo);
            }
        }

        if (option == 2){
            // Imprimir todos los usuarios existentes
            char respuesta[3];
            printf("Quieres Ver los Usuarios");
            scanf("%s", respuesta);
            if(strcmp(respuesta,"si")>0){
                print_users(lista);
            }
        }


        if (option == 3) {
            // Buscar un usuario en concreto en la lista
            char nombre[20];
            printf("Ingrese el nombre del usuario: ");
            scanf("%s", nombre);
            Node *encontrado = search_user(lista, nombre);
            if (encontrado != NULL) {
                // Si se encuentra el usuario, imprimimos sus características
                printf("Nombre: %s\n", encontrado->usuario.name);
                printf("Año de nacimiento: %d\n", encontrado->usuario.year_nacimiento);
                printf("Correo: %s\n", encontrado->usuario.correo);
                printf("Localización: %s\n", encontrado->usuario.Localizacion);
                printf("Gustos:\n");
                for (int i = 0; i < 5; i++) {
                    if (strcmp(encontrado->usuario.gustos[i], "") != 0) {
                        printf("- %s\n", encontrado->usuario.gustos[i]);
                    }
                }
                printf("\n\nSubmenú:\n"
                       "1. Enviar solicitud de amistad.\n"
                       "2. Gestionar solicitudes pendientes.\n"
                       "3. Realizar una publicacion.\n"
                       "4. Listar las publicaciones de un usuario.\n"
                       "5. Salir\n");
                int sub_option;
                printf("Selecciona una de las opciones con un numero del 1 al 5:\n");
                scanf("%i", &sub_option);

                if (sub_option == 5){
                    break;
                }

            } else {
                printf("El usuario no fue encontrado.\n");
            }
        }
        if (option == 4){
            break;
        }
    }
    Node *lista = NULL;
    Usuario *usuario_nuevo;
    printf("Vamos a crear un ususario ");
    printf("Dime el nombre %s");
    char nombre[20];
    scanf("%s", nombre);
    strcpy(usuario_nuevo->name, nombre);
    printf("Dime el año de nacimiento %d");
    int año[4];
    scanf("%d",año);
    strcpy(usuario_nuevo->year_nacimiento, año);
    printf("Dime el correo %s");
    char correo[20];
    scanf("%s", correo);
    strcpy(usuario_nuevo->correo, correo);
    printf("Dime la Localización %s");
    char sitio[30];
    scanf("%s", sitio);
    strcpy(usuario_nuevo->Localizacion, sitio);
    char gustos[5][30];
    for(int i = 0; i<5;i++){
        printf("Dime tus gustos %c");
        scanf("%c",gustos[i]);
        strcpy(usuario_nuevo->gustos[i], gustos[i]);
    }
    add_user(&lista, *usuario_nuevo);

    char respuesta[3];
    printf("Quieres Ver los Usuarios? (si/no)");
    scanf("%s", respuesta);
    if(strcmp(respuesta,"si")>0){
        print_users(lista);
    }
    else {/*ir a menu*/}
    char nombre_2[20];
    printf("Ingrese el nombre del usuario: ");
    scanf("%s", nombre);
    Node *encontrado = search_user(lista, nombre);
    if (encontrado != NULL) {
        // Si se encuentra el usuario, imprimimos sus características
        printf("Nombre: %s\n", encontrado->usuario.name);
        printf("Año de nacimiento: %d\n", encontrado->usuario.year_nacimiento);
        printf("Correo: %s\n", encontrado->usuario.correo);
        printf("Localización: %s\n", encontrado->usuario.Localizacion);
        printf("Gustos:\n");
        for (int i = 0; i < 5; i++) {
            if (strcmp(encontrado->usuario.gustos[i], "") != 0) {
                printf("- %s\n", encontrado->usuario.gustos[i]);
            }
        }
    } else {
        printf("El usuario no fue encontrado.\n");
    }
   /* char respuesta2[3];
    printf("Quieres leer ela rchivo de usuarios? (si/no)");
    scanf("%s", respuesta2);
    if(strcmp(respuesta2, "si") > 0){
        leerArchivo(usuarios, lista );
    }*/
        return 0;
}