#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
#define HASH_SIZE 100

void add_user(Usuario** lista, Usuario* usuario_nuevo) {
    if (*lista == NULL) {
        *lista = usuario_nuevo;
    } else {
        Usuario* nodo_actual = *lista;
        while (nodo_actual->siguiente != NULL) {
            nodo_actual = nodo_actual->siguiente;
        }
        nodo_actual->siguiente = usuario_nuevo;
    }
}

Usuario* print_users(Usuario* lista) {
    Usuario* actual_Usuario = lista;
    while (actual_Usuario != NULL) {
        printf("Nombre de usuario: %s\n", actual_Usuario->name);
        printf("Año de nacimiento: %d\n", actual_Usuario->year_nacimiento);
        printf("Correo: %s\n", actual_Usuario->correo);
        printf("Localizacion: %s\n", actual_Usuario->Localizacion);
        printf("Gustos: ");
        for (int i = 0; i < 5; i++) {
            printf("%s ", actual_Usuario->gustos[i]);
        }
        printf("\nID de usuario %d", actual_Usuario->id);
        printf("\n");
        actual_Usuario = actual_Usuario->siguiente;
    }
    return actual_Usuario;
}

Usuario* search_user(Usuario* head, char* nombre) {
    Usuario* actual = head;
    while (actual != NULL) {
        if (strcmp(actual->name, nombre) == 0) {
            return actual; // if the user is found, return the node
        }
        actual = actual->siguiente;
    }
    return NULL; // if the user is not found, return NULL
}
int hash_function(int id){
    return id % HASH_SIZE;
}
void add_post(Usuario* usuario, char mensaje[120]) {
    post* nueva_publicacion = malloc(sizeof(post));
    strncpy(nueva_publicacion->publicacion, mensaje, 120);
    usuario->Timeline = nueva_publicacion;
}
void add_friend_request(Usuario* usuario, Usuario* amigo) {
    int i = 0;
    while (usuario->soli[i] != NULL && i < 20) {
        i++;
    }
    if (i < 20) {
        usuario->soli[i] = amigo;
    } else {
        printf("No se pueden agregar más solicitudes de amistad.\n");
    }
}
int leerArchivo(const char* nombreArchivo, Usuario* lista) {
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
            add_user(lista, &usuario);
        } else {
            printf("Error al leer los campos del usuario.\n");
        }
    }

    fclose(archivo);
    return 1;
}

int main() {
    int option = 0;
    static int userCount = 0;
    Usuario* lista = NULL;
    Usuario* hash_table[HASH_SIZE]; // Tabla hash
    for (int i = 0; i < HASH_SIZE; i++) {
        hash_table[i] = NULL; // Inicializar la tabla hash
    }
    while (option != 4) {
        printf("\n\n\n\nOpciones del Menu Principal\n"
               "1. Insertar nuevo usuario.\n"
               "2. Listar todos los usuarios.\n"
               "3. Encontrar y operar como un usuario en especifico.\n"
               "4. Salir\n");
        printf("Selecciona una de las opciones con un numero del 1 al 4:\n");
        scanf("%i", &option);

        if (option == 1) {
            // Add a user and print it
            Usuario* usuario_nuevo = malloc(sizeof(Usuario));
            printf("Vamos a crear un usuario.\n");
            printf("Dime el nombre: ");
            scanf("%19s", usuario_nuevo->name);
            printf("Dime el año de nacimiento: ");
            scanf("%d", &usuario_nuevo->year_nacimiento);
            printf("Dime el correo: ");
            scanf("%29s", usuario_nuevo->correo);
            printf("Dime la localizacion: ");
            scanf("%19s", usuario_nuevo->Localizacion);
            printf("Dime tus gustos (separados por espacios): ");
            for (int i = 0; i < 5; i++) {
                scanf("%29s", usuario_nuevo->gustos[i]);
            }
            printf("Ingrese una contraseña:");
            scanf("%19s",usuario_nuevo->password);
            usuario_nuevo->siguiente = NULL;
            int id = userCount+1;
            usuario_nuevo->id = id;
            add_user(&lista, usuario_nuevo);
            int hash_index = hash_function(id);
            hash_table[hash_index] = usuario_nuevo;
        }

        if (option == 2) {
            // Print all existing users
            char respuesta[3];
            printf("¿Quieres ver los usuarios? (si/no): ");
            scanf("%s", respuesta);
            if (strcmp(respuesta, "si") == 0) {
                print_users(lista);
            } else {
                printf("Volveras al menu.\n");
            }
        }
        if (option == 3) {
            // Search for a specific user in the list
            int id;
            printf("Ingrese el ID del usuario: ");
            scanf("%d", &id);
            int hash_index = hash_function(id);
            char nombre[20];
            printf("Ingrese el nombre del usuario: ");
            scanf("%19s", nombre);
            Usuario* encontrado = search_user(lista, nombre);
            Usuario* encontradO = hash_table[hash_index];
            if (encontrado != NULL) {
                // If the user is found, print their details
                printf("Nombre: %s\n", encontrado->name);
                printf("Año de nacimiento: %d\n", encontrado->year_nacimiento);
                printf("Correo: %s\n", encontrado->correo);
                printf("Localizacion: %s\n", encontrado->Localizacion);
                printf("Gustos: ");
                for (int i = 0; i < 5; i++) {
                    if (strcmp(encontrado->gustos[i], "") != 0) {
                        printf("%s ", encontrado->gustos[i]);
                    }
                }
                printf("\n");
            } else {
                printf("El usuario no fue encontrado.\n");
            }
            printf("\n\nSubmenu:\n"
                   "1. Enviar solicitud de amistad.\n"
                   "2. Gestionar solicitudes pendientes.\n"
                   "3. Realizar una publicacion.\n"
                   "4. Listar las publicaciones de un usuario.\n"
                   "5. Salir al menu\n");
            int sub_option;
            printf("Selecciona una de las opciones con un numero del 1 al 5:\n");
            scanf("%i", &sub_option);
            if (sub_option == 5) {
            }
        }

        if (option == 4) {
            break;
        }
    }
    return 0;
}