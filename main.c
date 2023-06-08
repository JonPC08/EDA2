#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
#define HASH_SIZE 100
//descargar el archivo users.csv y copiar aqui la ruta de acceso propio
char resourcesPath[256] = "C:\\Users\\guill\\Downloads\\EDAII BUENO (2)\\EDAII BUENO\\resources\\";
//añadimos usuarios en formato linked list
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
    usuario_nuevo->num_amigos=0;
    usuario_nuevo->num_soli = 0;
    usuario_nuevo->num_posts = 0;
}
//algoritmo de ordenacion para hacer una llamada en el metodo de ordenacion alfabetica
void bubble_sort(Usuario** arr, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j]->name, arr[j + 1]->name) > 0) {
                Usuario* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
//metodo de muestra de usuarios noraml
Usuario* print_users(Usuario* lista) {
    // Copiar la lista de usuarios en un nuevo arreglo
    int num_usuarios = 0;
    Usuario* current = lista;
    while (current != NULL) {
        num_usuarios++;
        current = current->siguiente;
    }

    Usuario** usuarios_arr = malloc(num_usuarios * sizeof(Usuario*));
    current = lista;
    int i = 0;
    while (current != NULL) {
        usuarios_arr[i] = current;
        current = current->siguiente;
        i++;
    }

    // Ordenar los usuarios por nombre
    bubble_sort(usuarios_arr, num_usuarios);

    // Imprimir los usuarios ordenados
    for (i = 0; i < num_usuarios; i++) {
        printf("------------------------------------------\n");
        printf("----------- Ficha del usuario %i ------------\n", usuarios_arr[i]->id);
        printf("Nombre de usuario: %s\n", usuarios_arr[i]->name);
        printf("Ano de nacimiento: %i\n", usuarios_arr[i]->year_nacimiento);
        printf("Correo: %s\n", usuarios_arr[i]->correo);
        printf("Localizacion: %s\n", usuarios_arr[i]->Localizacion);
        printf("Gustos: ");
        for (int j = 0; j < usuarios_arr[i]->cantidad_de_gustos; j++) {
            printf("%s ", usuarios_arr[i]->gustos[j]);
        }
        printf("\nID de usuario: %d\n", usuarios_arr[i]->id);
        printf("------------------------------------------\n");
    }

    // Liberar la memoria asignada al arreglo
    free(usuarios_arr);

    return lista;
}
//metodo de muestra de usuarios alfabetica
Usuario* print_users2(Usuario* lista) {
    Usuario* actual_Usuario = lista;
    while (actual_Usuario != NULL) {
        printf("------------------------------------------\n");
        printf("----------- Ficha del usuario %i ------------\n", actual_Usuario->id);
        printf("Nombre de usuario: %s\n", actual_Usuario->name);
        printf("Ano de nacimiento: %i\n", actual_Usuario->year_nacimiento);
        printf("Correo: %s\n", actual_Usuario->correo);
        printf("Localizacion: %s\n", actual_Usuario->Localizacion);
        printf("Gustos: ");
        for (int i = 0; i < actual_Usuario->cantidad_de_gustos; i++) {
            printf("%s ", actual_Usuario->gustos[i]);
        }
        printf("\nID de usuario: %d", actual_Usuario->id);
        printf("\n");
        actual_Usuario = actual_Usuario->siguiente;
        printf("------------------------------------------\n");
    }
    return lista;
}
//busqued de usuario por nombre
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
//implementacion de tabla hash
int hash_function(int id){
    return id % HASH_SIZE;
} //lectura del archivo de usuarios
int leerArchivo(const char* nombreArchivo, Usuario** lista, int id_count, Usuario** hash_table) {
    FILE* archivo = fopen(nombreArchivo, "r"); // Open the .csv file in read mode
    printf("%s", nombreArchivo);
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
    }
    char linea[256];
    while (fgets(linea, sizeof(linea), archivo)) {
        // Parse the line and extract user information
        char nombre[20];
        int year_nacimiento;
        char correo[30];
        char Localizacion[20];
        int cantidad_de_gustos;
        char gustos[5][30];

        sscanf(linea, "\"%[^\"]\", %d, \"%[^\"]\", \"%[^\"]\", %d, \"%[^\"]\", \"%[^\"]\", \"%[^\"]\", \"%[^\"]\", \"%[^\"]\"",
               nombre, &year_nacimiento, correo, Localizacion, &cantidad_de_gustos,
               gustos[0], gustos[1], gustos[2], gustos[3], gustos[4]);

        // Create a new user and populate the fields
        Usuario* usuario_nuevo = malloc(sizeof(Usuario));
        usuario_nuevo->num_amigos = 0;
        usuario_nuevo->siguiente = NULL;
        strcpy(usuario_nuevo->name, nombre);
        usuario_nuevo->year_nacimiento = year_nacimiento;
        id_count = id_count + 1;
        usuario_nuevo->id = id_count;
        strcpy(usuario_nuevo->correo, correo);
        strcpy(usuario_nuevo->Localizacion, Localizacion);
        usuario_nuevo->cantidad_de_gustos = cantidad_de_gustos;
        for (int i = 0; i < 5; i++) {
            if (i < cantidad_de_gustos) {
                strcpy(usuario_nuevo->gustos[i], gustos[i]);
            } else {
                strcpy(usuario_nuevo->gustos[i], "");
            }
        }
        // Add the user to the list
        add_user(lista, usuario_nuevo);

        int hash_index = hash_function(id_count);
        hash_table[hash_index] = usuario_nuevo;

    }

    fclose(archivo); // Close the file
    return id_count;
}
//añadimos publicaciones en formato stack
void add_post(Usuario* user, const char* message) {
    // Crear un nuevo post y asignar el mensaje
    post* newPost = (post*)malloc(sizeof(post));
    strcpy(newPost->publicacion, message);

    // Establecer el nuevo post como el primer elemento de la pila (nuevo Timeline)
    newPost->siguiente = user->Timeline;
    user->Timeline = newPost;
    user->num_posts++;
    printf("El post ha sido agregado con exito.\n");
}
//mostramos las publicaciones del usuario deseado
void print_posts(char nombre[20], Usuario* lista) {
    Usuario* user = search_user(lista,nombre);
    printf("Posts de %s:\n", user->name);
    printf("-----------------\n");

    post *currentPost = user->Timeline;
    int postCount = 1;

    for (int p = 0; p < user->num_posts; p++) {
        printf("Post %d:\n", postCount);
        printf("%s\n", currentPost->publicacion);
        printf("-----------------\n");

        currentPost = currentPost->siguiente;
        postCount++;
    }
}
//enviar solicitud de amisad
void add_friend_request(Usuario* usuarioEnvia, Usuario* usuarioRecibe) {
    if (usuarioEnvia == NULL || usuarioRecibe == NULL) {
        printf("Error: Usuario no valido\n");
        return;
    }

    // Verificar si ya son amigos
    for (int i = 0; i < usuarioEnvia->num_amigos; i++) {
        if (usuarioRecibe->amigos[i] == usuarioEnvia) {
            printf("%s y %s ya son amigos\n", usuarioEnvia->name, usuarioRecibe->name);
            return;
        }
    }

    // Verificar si ya hay una solicitud de amistad pendiente
    for (int i = 0; i < usuarioEnvia->num_soli; i++) {
        if (usuarioRecibe->soli[i] == usuarioEnvia) {
            printf("Ya existe una solicitud de amistad pendiente de %s a %s\n", usuarioEnvia->name, usuarioRecibe->name);
            return;
        }
    }

    // Agregar solicitud de amistad
    if (usuarioRecibe->num_soli < 20) {
        usuarioRecibe->soli[usuarioEnvia->num_soli] = usuarioEnvia;
        usuarioRecibe->num_soli++;
        printf("Solicitud de amistad enviada de %s a %s\n", usuarioEnvia->name, usuarioRecibe->name);
    } else {
        printf("Error: No se pueden enviar mas solicitudes de amistad\n");
    }
}
//gestion de solicitudes, se elimina la solicitud de la lista, en caso de ser aceptadas cada usuario saldrá en la lista de amigos del otro
void accept_friend_request(Usuario* user) {
    // Mostrar las solicitudes de amistad pendientes
    printf("Solicitudes de amistad pendientes:\n");
    for (int i = 0; i < user->num_soli; i++) {
        Usuario* amigo = user->soli[i];
        printf("%d. %s\n", i + 1, amigo->name);
    }

    // Solicitar al usuario que elija una solicitud para aceptar o rechazar
    printf("Ingrese el numero de la solicitud que desea gestionar (0 para cancelar): ");
    int opcion;
    scanf("%d", &opcion);

    if (opcion >= 1 && opcion <= user->num_soli) {
        Usuario* selectedUser = user->soli[opcion - 1];

        // Preguntar si desea aceptar o rechazar la solicitud
        printf("Desea aceptar la solicitud de amistad de %s? (1 para aceptar, 0 para rechazar): ", selectedUser->name);
        int decision;
        scanf("%d", &decision);

        if (decision == 1) {
            // Agregar al usuario seleccionado como amigo
            if (user->num_amigos >= MAX_AMIGOS) {
                printf("No se puede aceptar la solicitud. Se ha alcanzado el limite de amigos.\n");
                return;
            }

            user->amigos[user->num_amigos] = selectedUser;
            user->num_amigos++;
            //añadir en las dos listas de amigos
            selectedUser->amigos[selectedUser->num_amigos] = user;
            selectedUser->num_amigos++;

            printf("La solicitud de amistad de %s ha sido aceptada.\n", selectedUser->name);
            printf("Amigos de %s:\n",user->name);
            for(int j = 0; j<user->num_amigos;j++){
                printf("%s, ",user->amigos[j]);
            }
            printf("\n");
            printf("Amigos de %s:",selectedUser->name);
            for(int m = 0; m<selectedUser->num_amigos;m++){
                printf("%s, ",selectedUser->amigos[m]);
                printf("\n");
            }
        } else if (decision == 0) {
            // Eliminar la solicitud
            for (int i = opcion - 1; i < user->num_soli - 1; i++) {
                user->soli[i] = user->soli[i + 1];
            }
            user->num_soli--;

            printf("La solicitud de amistad de %s ha sido rechazada.\n", selectedUser->name);
        } else {
            printf("Opcion no valida.\n");
        }
    } else if (opcion != 0) {
        printf("Opcion no valida.\n");
    }
}
//eliminar amigos propios y te eliminas a ti de la lista del otro
void remove_friend(Usuario* usuario) {
    if (usuario->num_amigos == 0) {
        printf("No tienes amigos para eliminar.\n");
        return;
    }

    // Mostrar lista de amigos
    printf("Lista de amigos:\n");
    for (int i = 0; i < usuario->num_amigos; i++) {
        Usuario* friend = usuario->amigos[i];
        printf("%d. %s\n", i + 1, friend->name);
    }

    int opcion;
    printf("Ingrese el numero del amigo que desea eliminar (0 para salir): ");
    scanf("%d", &opcion);

    if (opcion >= 1 && opcion <= usuario->num_amigos) {
        Usuario* amigo = usuario->amigos[opcion - 1];

        if (amigo != NULL) {
            printf("Has eliminado a %s de tu lista de amigos.\n", amigo->name);

            // Mover los amigos restantes hacia adelante en el arreglo
            for (int i = opcion - 1; i < usuario->num_amigos - 1; i++) {
                usuario->amigos[i] = usuario->amigos[i + 1];
            }
            for(int j = 0; j<amigo->num_amigos;j++) {
                Usuario *auxiliar = amigo->amigos[j];
                if (strcmp(auxiliar->name, usuario->name) == 0);
                for (int n =j; j< amigo->num_amigos;n++){
                    amigo->amigos[j] = amigo->amigos[j+1];
                }
            }

            // Actualizar el número de amigos
            usuario->num_amigos--;
            amigo->num_amigos--;
        } else {
            printf("Amigo no valido.\n");
        }
    } else {
        printf("Opcion no valida.\n");
    }
}
//muestra otros usuarios con gustos coincidentes
void sugerencias(Usuario* usuario) {
    printf("Sugerencias de amistad para %s:\n", usuario->name);

    // Recorrer la lista de usuarios
    Usuario* actual = usuario->siguiente;
    while (actual != NULL) {
        // Verificar si ya son amigos
        int es_amigo = 0;
        for (int i = 0; i < usuario->num_amigos; i++) {
            if (usuario->amigos[i] == actual) {
                es_amigo = 1;
                break;
            }
        }

        // Verificar si ya hay una solicitud de amistad pendiente
        int solicitud_pendiente = 0;
        for (int i = 0; i < usuario->num_soli; i++) {
            if (usuario->soli[i] == actual) {
                solicitud_pendiente = 1;
                break;
            }
        }

        // Verificar si comparten al menos un gusto
        int gustos_comunes = 0;
        char gustos_en_comun[MAX_NUM_GUSTOS][MAX_GUSTO_LENGTH];
        for (int i = 0; i < usuario->cantidad_de_gustos; i++) {
            for (int j = 0; j < actual->cantidad_de_gustos; j++) {
                if (strcmp(usuario->gustos[i], actual->gustos[j]) == 0) {
                    strcpy(gustos_en_comun[gustos_comunes], usuario->gustos[i]);
                    gustos_comunes++;
                    break;
                }
            }
        }
    if (gustos_comunes==0){printf("No hay sugerencias");}
        // Si no son amigos, no hay solicitud pendiente y comparten al menos un gusto, mostrar el usuario y ofrecer enviar una solicitud de amistad
        if (!es_amigo && !solicitud_pendiente && gustos_comunes > 0) {
            printf("Usuario: %s\n", actual->name);
            printf("Gustos en comun (%d): ", gustos_comunes);
            for (int i = 0; i < gustos_comunes; i++) {
                printf("%s ", gustos_en_comun[i]);
            }
            printf("\n");
            printf("Enviar solicitud de amistad? (si/no): ");
            char respuesta[2];
            scanf("%s", respuesta);
            if (strcmp(respuesta, "si") == 0) {
                add_friend_request(usuario, actual);
                printf("Solicitud enviada.\n");
            }
        }

        actual = actual->siguiente;
    }

    printf("Fin de las sugerencias.\n");
}


int main() {
    int option = 0;
    static int id_count = 0;
    Usuario* lista = NULL;
    Usuario* hash_table[HASH_SIZE]; // Tabla hash
    for (int i = 0; i < HASH_SIZE; i++) {
        hash_table[i] = NULL; // Inicializar la tabla hash
    }

    while (option != 4) {
        printf("\n\nOpciones del Menu Principal\n"
               "1. Insertar nuevo usuario.\n"
               "2. Listar todos los usuarios.\n"
               "3. Encontrar y operar como un usuario en especifico.\n"
               "4. Salir\n");
        printf("Selecciona una de las opciones con un numero del 1 al 4:\n");
        scanf("%i", &option);
        if(option>4 || option<1({)
            printf("Opcion invalida");
            break;
        }
        /// 1. Opcion para añadir usuarios. 1.1. Añadir usuario manualmente, 1.2. Añadir usuarios con .csv
        if (option == 1) {
            // Upload a user
            int read_csv;
            printf("Que deseas hacer ?\n");
            printf("1. Anadir a un usuario manualmente\n");
            printf("2. Importar con un archivo (.csv)\n");
            scanf("%i", &read_csv);
            if (read_csv == 1) {
                Usuario *usuario_nuevo = malloc(sizeof(Usuario));
                usuario_nuevo->num_amigos = 0;
                printf("---------------------------\n");
                printf("Vamos a crear un usuario.\n");
                printf("Dime el nombre: \n");
                scanf("%19s", usuario_nuevo->name);
                printf("Dime el ano de nacimiento: \n");
                scanf("%d", &usuario_nuevo->year_nacimiento);
                printf("Dime el correo: \n");
                scanf("%29s", usuario_nuevo->correo);
                printf("Dime la localizacion: \n");
                scanf("%19s", usuario_nuevo->Localizacion);
                printf("A continuacion introduciras tus gustos,\n");
                printf("Cuantos gustos quieres introducir ? (Selecciona un numero del 1 al 5) \n");
                scanf("%i", &usuario_nuevo->cantidad_de_gustos);
                printf("Dime tus gustos (separados por espacios): \n");
                for (int i = 0; i < usuario_nuevo->cantidad_de_gustos; i++) {
                    scanf("%29s", usuario_nuevo->gustos[i]);
                }
                for (int i = 0; i < 20; i++) {
                    usuario_nuevo->soli[i] = NULL;
                }
                printf("Ingrese una contrasena: \n");
                scanf("%19s", usuario_nuevo->password);
                printf("---------------------------\n");
                usuario_nuevo->siguiente = NULL;
                id_count = id_count + 1;
                usuario_nuevo->id = id_count;
                add_user(&lista, usuario_nuevo);
                int hash_index = hash_function(id_count);
                hash_table[hash_index] = usuario_nuevo;
            }
            else if (read_csv == 2) {
                char archivo_csv[100];
                printf("Ingrese el nombre del archivo CSV: \n");
                scanf("%s", archivo_csv);
                char csvPath[256];
                strcpy(csvPath, resourcesPath);
                strcat(csvPath, archivo_csv);
                id_count = leerArchivo(csvPath, &lista, id_count, hash_table);
            }else if (read_csv !=1 && read_csv!=2){
                break;
            }
        }
            /// 2. Imprimir todos los usuario guardados en la base de datos.
        else if (option == 2) {
            // Print all existing users
            char respuesta[2];
            printf("Quieres ver los usuarios? (si/no): \n");
            scanf("%s", respuesta);
            if (strcmp(respuesta, "si") == 0) {
                printf("Deseas ver los usuarios en orden alfabetico? (si/no): \n");
                scanf("%s", respuesta);
                if (strcmp(respuesta, "si") == 0) {
                    print_users(lista);
                } else {
                    print_users2(lista);
                }
            } else {
                printf("Volveras al menu.\n");
            }
        }

            /// 3. Buscar un usuario entre todos y iniciar sesion como él.
        else if (option == 3) {
            // Search for a specific user in the list
            // declaramos antes la variable +encontrado para que no haya un problema de memoria al inicalizar en los bloques if, else if
            Usuario* encontrado = NULL;
            int id_;
            printf("Iniciar sesion con id o con nombre?");
            char respuesta[10];
            scanf("%s",respuesta);
            if(strcmp(respuesta, "id") == 0){
                printf("Ingrese el ID del usuario: \n");
                scanf("%d", &id_);
                int hash_index = hash_function(id_);
                encontrado = hash_table[hash_index];
            }
            else if(strcmp(respuesta,"nombre") == 0){
                char nombre[20];
                printf("Ingrese el nombre del usuario: \n");
                scanf("%19s", nombre);
                encontrado = search_user(lista, nombre);
            }
            if (encontrado != NULL) {
                printf("------------------------------------------\n");
                printf("----------- Ficha del usuario %i ------------\n", encontrado->id);
                printf("Nombre de usuario: %s\n", encontrado->name);
                printf("Ano de nacimiento: %i\n", encontrado->year_nacimiento);
                printf("Correo: %s\n", encontrado->correo);
                printf("Localizacion: %s\n", encontrado->Localizacion);
                printf("Gustos: ");
                for (int i = 0; i < encontrado->cantidad_de_gustos; i++) {
                    printf("%s ", encontrado->gustos[i]);
                }
                printf("\nID de usuario %d", encontrado->id);
                printf("\n");
                while (1) {
                    printf("------------------------------------------\n");
                    printf("\n\nSubmenu:\n"
                           "1. Enviar solicitud de amistad.\n"
                           "2. Gestionar solicitudes pendientes.\n"
                           "3. Realizar una publicacion.\n"
                           "4. Listar las publicaciones de un usuario.\n"
                           "5. Mostrar las sugerencias\n"
                           "6. Salir al menu\n");
                    int sub_option;
                    printf("Selecciona una de las opciones con un numero del 1 al 5:\n");
                    scanf("%i", &sub_option);

                    /// 3.1. Enviar solicitud de amistad a otro usuario
                    if (sub_option == 1) {
                        // Send a friend request
                        char friend_name[20];
                        printf("Ingrese el nombre del amigo al que desea enviar la solicitud: ");
                        scanf("%19s", friend_name);
                        Usuario* amigo = search_user(lista, friend_name);
                        if (amigo != NULL) {
                            add_friend_request(encontrado, amigo);
                            for (int i =0; i<encontrado->num_amigos;i++){
                                Usuario* Auxiliar = encontrado->amigos[i];
                                printf("Tus amigos %s", Auxiliar->name);
                            }
                        }
                        else {
                            printf("El amigo no fue encontrado.\n");
                        }
                    }
                        /// 3.2. Gestionar las solicitudes pendientes.
                    else if (sub_option == 2) {
                        accept_friend_request(encontrado);
                        printf("Deseas eliminar algun amigo? (si/no) ");
                        char eliminar[4];
                        scanf("%s",eliminar);
                        if (strcmp(eliminar, "si")== 0){
                            remove_friend(encontrado);
                        }
                    }
                        /// 3.3. Realizar una publicación.
                    else if (sub_option ==3){
                        printf("Introduce aqui tu post (maximo 120 caracteres): ");
                        char publicacion[121]; // 120 caracteres + 1 para el carácter nulo
                        getchar(); // Consumir el carácter de nueva línea anterior
                        fgets(publicacion, sizeof(publicacion), stdin);
                        add_post(encontrado, publicacion);
                    }
                    else if (sub_option == 4) {
                        printf("De quien quieres ver los posts? ");
                        getchar();
                        char nombreaver[20];
                        fgets(nombreaver, sizeof(nombreaver), stdin);
                        nombreaver[strcspn(nombreaver, "\n")] = '\0';
                        print_posts(nombreaver,lista);
                    }
                    else if (sub_option == 5){
                        printf("Quieres ver las sugerencias? (si/no) ");
                        char mostrar[4];
                        scanf("%s",mostrar);
                        if (strcmp(mostrar,"si")==0){
                            sugerencias(encontrado);
                        }
                    }
                    else if (sub_option == 6) {
                        break;
                    }
                }
            } else {
                printf("El usuario no fue encontrado.\n");
            }
        }
        else if (option == 4) {
            printf("Hasta la proxima");
            break;
        }

        else {
            printf("\n\nLa opcion que has seleccionado no esta disponible.\n");
            printf("Por favor, selecciona una opcion con un numero del 1-5.\n\n");
        }
    }
    return 0;
}
