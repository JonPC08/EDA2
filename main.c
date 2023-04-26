#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"

void add_user(Node **lista, Usuario *usuario_nuevo){
    Node *new_node=malloc(sizeof(Node));
    new_node->usuario=*usuario_nuevo;
    new_node->siguiente=*lista;
    *lista=new_node;
}
Node *print_users(Node *lista) {
    Node *actual_node = lista;
    while (actual_node != NULL) {
        printf("Nombre de usuario: %s\n", actual_node->usuario.name);
        printf("Año nacimiento %d", actual_node->usuario.año_nacimiento);
        printf("Correo %s", actual_node->usuario.correo);
        printf("Localización %s", actual_node->usuario.Localizacion);
        printf("Gustos %s", actual_node->usuario.gustos);;
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
int main() {
    Node *lista = NULL;
    for (int i = 0; i < 100; i++) {
        Usuario usuario_nuevo;
        sprintf(usuario_nuevo.name, "usuario%d", i);
        add_user(&lista, &usuario_nuevo);
    }
    char respuesta[3];
    printf("Quieres Ver los Usuarios");
    scanf("%s", respuesta);
    if(respuesta == "si"){
        print_users(lista);
    }
    char nombre[20];
    printf("Ingrese el nombre del usuario: ");
    scanf("%s", nombre);
    Node *encontrado = search_user(lista, nombre);
    if (encontrado != NULL) {
        // Si se encuentra el usuario, imprimimos sus características
        printf("Nombre: %s\n", encontrado->usuario.name);
        printf("Año de nacimiento: %d/%d/%d\n", encontrado->usuario.año_nacimiento);
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
    return 0;
}