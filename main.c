#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"

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

Usuario *print_users(Usuario *lista) {
    Usuario *actual_Usuario = lista;
    while (actual_Usuario != NULL) {
        printf("Nombre de usuario: %s\n", actual_Usuario->name);
        printf("Año nacimiento %d", actual_Usuario->year_nacimiento);
        printf("Correo %s", actual_Usuario->correo);
        printf("Localización %s", actual_Usuario->Localizacion);
        printf("Gustos %s-%s-%s-%s-%s", actual_Usuario->gustos[0],actual_Usuario->gustos[1],actual_Usuario->gustos[2],actual_Usuario->gustos[3],actual_Usuario->gustos[4]);
        actual_Usuario = actual_Usuario->siguiente;
    }
    return actual_Usuario;
}
Usuario *search_user(Usuario *head, char *nombre) {
    Usuario *actual = head;
    while (actual != NULL) {
        if (strcmp(actual->name, nombre) == 0) {
            return actual; // si encuentra el usuario, devuelve el nodo
        }
        actual = actual->siguiente;
    }
    return NULL; // si no encuentra el usuario, devuelve NULL
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
        int numCampos = sscanf(linea, "%19[^,],%4[^,],%29[^,],%19[^,],%29[^,],%29[^,],%29[^,],%29[^,\n]",
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
void add_post(Usuario* usuario, char mensaje[120]) {
    post* nueva_publicacion = malloc(sizeof(post));
    strncpy(nueva_publicacion->publicacion, mensaje, 120);
    usuario->Timeline = nueva_publicacion;
}
int main() {
    int option = 0;
    Usuario *lista = NULL;
    while (option != 4) {
        printf("\n\n\n\nOpciones Menu Principal\n"
               "1. Insertar Nuevo usuario.\n"
               "2. Listar todos los usuarios.\n"
               "3. Encontrar y operar como un usuario en especifico.\n"
               "4. Salir\n");
        printf("Selecciona una de las opciones con un numero del 1 al 4:\n");
        scanf("%i", &option);

        if (option == 1) {
            // Añade un usuario y lo printea
            Usuario *usuario_nuevo = malloc(sizeof(Usuario));
            printf("Vamos a crear un ususario ");
            printf("Dime el nombre ");
            scanf("%19s", usuario_nuevo->name);
            printf("Dime el year de nacimiento ");
            scanf("%d", usuario_nuevo->year_nacimiento);
            printf("Dime el correo ");
            scanf("%29s", usuario_nuevo->correo);
            printf("Dime la Localizacion ");
            scanf("%19s", usuario_nuevo->Localizacion);
            char gustos[5][30];
            for (int i = 0; i < 5; i++) {
                printf("Dime tus gustos ");
                scanf("%c", usuario_nuevo->gustos[i]);
            }
            add_user(&lista, usuario_nuevo);
        }

        if (option == 2) {
            // Imprimir todos los usuarios existentes
            char respuesta[3];
            printf("Quieres Ver los Usuarios");
            scanf("%s", respuesta);
            if (strcmp(respuesta, "si") > 0) {
                print_users(lista);
            } else {
                printf("Volveras al menu");
            }
        }
        if (option == 3) {
            // Buscar un usuario en concreto en la lista
            char nombre[20];
            printf("Ingrese el nombre del usuario: ");
            scanf("%s", nombre);
            Usuario *encontrado = search_user(lista, nombre);
            if (encontrado != NULL) {
                // Si se encuentra el usuario, imprimimos sus características
                printf("Nombre: %s\n", encontrado->name);
                printf("Año de nacimiento: %d\n", encontrado->year_nacimiento);
                printf("Correo: %s\n", encontrado->correo);
                printf("Localización: %s\n", encontrado->Localizacion);
                printf("Gustos:\n");
                for (int i = 0; i < 5; i++) {
                    if (strcmp(encontrado->gustos[i], "") != 0) {
                        printf("- %s\n", encontrado->gustos[i]);
                    }
                }
            } else {
                printf("El usuario no fue encontrado.\n");
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
            if (sub_option == 5) {
                    break;
            }

        }

        if (option == 4) {
                break;
        }
    }
    return 0;

    }
    /* char respuesta2[3];
     printf("Quieres leer el  archivo de usuarios? (si/no)");
     scanf("%s", respuesta2);
     if(strcmp(respuesta2, "si") > 0){
         leerArchivo(usuarios, lista );
     }*/
