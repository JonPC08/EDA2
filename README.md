# ESTRUCTURAS DE DATOS Y ALGORITMOS II, 2022-2023
## Red Social en C
### Jon Parra (268826), Sergi Rivet (268433) y Guillem Vizcarro (268252)
---
### Notas Importantes !!!

## Link del video demostración:

https://drive.google.com/file/d/1fmeed_3VrJxnnQM4IegHca1lkcAm1n9v/view?usp=sharing


## Importante: Configuración de path.

Al ejecutar nuestro programa, debes introducir la ruta propia de tu ordenador hacia la carpeta resources. Sustituirla en la variable resourcesPath en la linea 7.

---

## INTRODUCCIÓN

· El contexto es el siguiente: tenemos que crear una red social funcional en lenguaje C, para la cual tenemos que hacer uso de los conocimientos de programación que hemos obtenido en EDA I y en EDA II, cómo puede ser por ejemplo la implementación de una pila, una cola, un algoritmo de ordenación, un diccionario, una tabla de hash, etc.

· La idea principal de nuestra red social es que fuera una red en la cual puedas, al registrarte, introducir tus gustos, localización, etc. y que puedas interactuar con otros usuarios y ver si compartís esos mismos gustos, si vivís en la misma zona, ver sus publicaciones, etc. 

· Para ello, decidimos implementar un menú el cual imprimiera diferentes opciones: una de ellas era crear un nuevo usuario, para el cual te pedía nombre, correo, localización y gustos. Otra funcionalidad que queríamos implementar era que se pudiesen enviar solicitudes de amistad a otros usuarios registrados, y mediante una opción del menú cada usuario podría ver sus solicitudes de amistad y aceptarlas y rechazarlas. 

· Por último, otra funcionalidad extra que se nos ocurrió y nos pareció bastante interesante y original es que cada usuario tuviera “sugerencias”. Esto funciona de la siguiente manera: Se comparan los gustos de cada usuario y si comparten alguno, se añaden a sugerencias (especificando cuál es el gusto compartido).

· También tuvimos en cuenta un objetivo deseable que nos pareció interesante que era el de que el programa pudiera leer datos de usuarios de un archivo .csv y que de esta manera se añadiesen solos y no los tuviéramos que cargar nosotros manualmente que es bastante lento y aburrido.

---

## OBJETIVOS DEL PROYECTO

### Objetivos obligatorios alcanzados:

1. La lista está implementada en el almacenamiento de usuarios. El Stack lo hemos usado para las publicaciones. La cola está implementada también en los usuarios y hay una opción de quitar de la cola cualquier usuario (no solo el primero). 

La función add_user añade usuarios a una lista enlazada de usuarios, guarda sus características e inicializa sus contadores en 0.

La función remove_friend quita de la cola de amigos al usuario escogido utilizando un linear search.

La función add_post gestiona en formato pila las publicaciones guardando espacio a un puntero post cada vez que queremos añadir un post.


2. La búsqueda de LinearSearch está implementada en un algoritmo de búsqueda de usuario.

La función que implementa la búsqueda es search_user que busca comparando string.


3. El algoritmo de BubbleSort lo hemos implementado para ordenar alfabéticamente la lista de usuarios (a petición del usuario).

Función bubble_sort que luego implementa la función print_users para ordenar los usuarios alfabéticamente.


4. Hemos implementado una tabla hash para proporcionar un ID único a cada usuario que se organice y distinga cada usuario.

Función hash_table que usa el algoritmo de las tablas hash para proporcionar un valor a cada llave que en este caso es un usuario, y así se establecen como estructuras de datos manejables por nosotros.


5. Comentarios básicos antes de cada grupo de código para explicar la funcionalidad.


6. Uso de github con algún problema para subir y descargar el proyecto ya que es la primera vez que lo usamos.



### Objetivos deseables alcanzados:

1. Leer datos de un archivo csv (para cargar los usuarios). La función leerArchivo lee un archivo externo de usuarios con cada formato de la información de un usuario.


2. Red Social temática, sugerencias de usuarios con gustos coincidentes al tuyo, sistema de amistad mutuo, sistema de posts públicos. Podemos enviar solicitudes de amistad a usuarios que conocemos, subir posts públicos para los usuarios que nos conozcan (aunque no seamos amigos) y tenemos un sistema de sugerencias que funciona por comparación de gustos de los usuarios.



### Objetivos exploratorios adquiridos

1. Funcionalidad de lectura y guardado de datos de los usuarios. Misma función leerArchivo que después de leer guarda los usuarios en la lista y hace uso de la tabla hash para poder darles uso, sino serían como información estática solo para ver.


2. Funcionalidades extra como subir posts y ver los posts de cualquiera y agregar amigos.
La función add_friend_request recibe un usuario y envía una variable tipo usuario como petición a su lista de solicitudes. add_friend_request nos permite gestionar nuestras solicitudes podemos rechazar o aceptar, si aceptamos la amistad es mutua. 


3. Print_posts recibe un usuario e imprime los posts del usuario que introducimos en formato pila. Sugerencias revisa entre los usuarios de la red social si el usuario que ha iniciado sesión tiene gustos en común, en ese caso te ofrece enviar una solicitud de amistad.

---

## SOLUCIÓN

## Arquitectura del sistema

Hemos utilizado muchas variables para que este proyecto funcione correctamente. Esta es una lista con un resumen de la funcionalidad de cada una de ellas:

1. char resourcesPath[256]: Esta variable almacena la ruta al directorio de recursos, que se utiliza en las operaciones de archivo. Es fundamental que la persona que utilice el programa introduzca el suyo para el correcto funcionamiento del código.


2. Usuario** lista: Este es un puntero a un puntero de tipo Usuario. Se utiliza para mantener una lista enlazada de usuarios. Esta lista junto a la “Hash Table” son los elementos que nos permiten almacenar los usuarios.


3. Usuario* siguiente: Este es un puntero al próximo usuario en la lista enlazada. Se utiliza para vincular a los usuarios entre sí. 


4. int num_amigos: Esta variable almacena el número de amigos que tiene un usuario. Esto es necesario ya que una vez aceptada la solicitud de amistad, debemos contar el nuevo amigo que tiene tanto el usuario que acepta como el que ha enviado la solicitud.


5. int num_soli: Esta variable almacena el número de solicitudes de amistad que tiene un usuario. Se necesita por el mismo motivo que la variable num_amigos.


6. int num_posts: Esta variable almacena la cantidad de publicaciones que tiene un usuario.


7. char name[20]: Esta variable almacena el nombre de un usuario. 


8. int year_nacimiento: Esta variable almacena el año de nacimiento de un usuario. 


9. char correo[30]: Esta variable almacena la dirección de correo electrónico de un usuario. 


10. char Localizacion[20]: Esta variable almacena la ubicación de un usuario. 


11. int cantidad_de_gustos: Esta variable almacena el número de intereses (gustos) que tiene un usuario. Es necesaria ya que cuando introducimos los gustos, utilizamos un sistema que emplea un for loop. Pidiendo el número de gustos simplificamos ese mismo sistema.


12. char gustos[5][30]: Esta matriz bidimensional almacena los intereses (gustos) de un usuario. Es necesario que sea una matriz bidimensional, ya que cuando almacenamos los gustos lo hacemos solo separando con un espacio. De esta manera tenemos hasta 5 gustos de 30 caracteres cada uno.


13. int id: Esta variable almacena el identificador único (ID) de un usuario. 


14. FILE* archivo: Este es un puntero de archivo utilizado para operaciones con archivos. Lo utilizamos para importar usuarios con archivos csv como el que hemos dejado en la carpeta de recursos. 


15. char linea[256]: Esta variable almacena una línea leída de un archivo. Esto sirve para poder almacenar la información de cada una de las líneas que aparecen en el documento csv individualmente.


16. post* Timeline: Este es un puntero a la línea de tiempo del usuario, que es una lista enlazada de publicaciones. Gracias a esto es que podemos ver los posts que ha realizado un usuario.


17. char password[20]: Esta lista almacena la contraseña de el usuario. Finalmente hemos decidido no utilizar la contraseña, ya que implementar un sistema de login elevaría la complejidad de este proyecto, además de que C no sería el mejor lenguaje para esto, SQL o un lenguaje de database sería mucho mejor. Al seleccionar la opción de inicio de sesión, simplemente eliges la id del usuario que quieres e inicias sesión sin contraseña, aunque lógicamente si vendieras esta red social como producto habría que crear un sistema de login.


18. Usuario* amigos[MAX_AMIGOS]: Esta variable almacena los amigos (amigos) de un usuario. A diferencia de num_amigos, esta variable almacena quienes son esos amigos.


19. Usuario* soli[20]: Este arreglo almacena las solicitudes de amistad (solicitudes) enviadas por un usuario. Como en el ejemplo anterior, la diferencia es que aquí almacenamos de quienes son esas solicitudes.


20. int option: Esta variable se utiliza para almacenar la opción seleccionada del menú. Al iniciar el programa, el menú nos muestra estas opciones:

1. Insertar nuevo usuario.
2. Listar todos los usuarios.
3. Encontrar y operar como un usuario en específico.
4. Salir.


21. int sub_option: Esta variable se utiliza para almacenar la opción seleccionada del submenú. Al iniciar el programa, el menú nos muestra estas opciones:

1. Enviar solicitud de amistad.
2. Gestionar solicitudes pendientes.
3. Realizar una publicación.
4. Listar las publicaciones de un usuario.
5. Sugerir Usuarios
6. Salir


22. int id_count: Esta variable realiza un seguimiento del número total de usuarios creados y asigna ID únicos a cada usuario. Esta variable es necesaria, ya que sin ella cuando creamos todos los usuarios importados de un archivo csv creariamos 10 id. Si no las contamos al añadir una nueva id empezaremos a contar desde 1.


23. Usuario* hash_table[HASH_SIZE]: Esta es una matriz de punteros a los objetos Usuario utilizados como una tabla hash para una recuperación eficiente del usuario. La base de datos se basa en esta tabla, que almacena los usuarios usando las estructuras de datos que discutiremos en el siguiente punto.



## Gestión de errores

Para la gestión de errores en nuestro proyecto hemos utilizado varios while loops. Entre otras razones, hemos utilizado while loops ya que con ellos podemos navegar a través de los menús de manera fluida. Esto se debe a que nuestro programa es una red social, y una red social solo se cierra cuando tú lo decides. 

Esto hace que el programa siempre te mantenga en un while loop que te devuelve al menú principal a menos de que elijas la opción 4, que te permite salir o, te metas en un SubMenú. En el caso de que entres a un SubMenú, entraras a un while loop secundario que te devuelve al SubMenú hasta que aprietes la opción de salir al menú principal. 

Juntando estos while loops con unos cuantos if else statements podemos navegar por el menú, y si el usuario hace algo que no debe podemos mostrar un mensaje de error indicando lo que debería hacer. En total hay 2 while loops que se encargan de manejar errores, pero hay al menos 10 else if que se encargan de avisarte de que tu input no es el correcto para devolverte hacia atrás gracias al while.

Otra de las opciones es simplemente limitar los inputs que introduce el usuario, haciendo que solo pueda acceder a el apartado siguiente si el input es correcto. Esta opción también sería válida, pero como ya hemos mencionado, al ser una red social con menús los cuales han de permitir volver hacia atrás, así que lo más eficiente era juntar el manejo de errores con el sistema de menús. 



## Diseño del modelo de datos

Esta es una explicación de las estructuras de datos que hemos utilizado para este proyecto:

· Linked List: La estructura “Usuario” es una linked list, la cual representa cada uno de los usuario en la red social con sus datos correspondientes (Nombre, fecha de nacimiento, Ubicación…). Hemos utilizado una linked list ya que tras probar con otros tipos de estructuras, el código y funcionamiento del mismo eran mas complejos asi que hemos decidido que esta era la forma más óptima de almacenar los usuarios.

· Hash Table: Esta estructura de datos la hemos usado en conjunto con la anterior, ya que era la mejor opción para recuperar los datos de uno de los usuarios de la linked list utilizando los ID. Gracias a esta hash table podemos recuperar los datos de uno de los usuarios, almacenando sus IDs dentro de la hash table, podemos referenciar estas IDs para poder conseguir la información.

· Stack: La estructura de datos que hemos escogido para almacenar los posts ha sido un Stack. En este caso, no la hemos escogido porque sea la más óptima, sino porque queriamos experimentar como funciona la implementación de un Stack en un caso real.

· En resumen, todos los datos y estructuras giran alrededor de la linked list “Usuario”, que es la que permite almacenar todos los datos de cada uno de los usuarios individuales. Esta estructura es la principal, pero las demás también son necesarias para el correcto funcionamiento del programa. 



## Descripción y procesamiento del conjunto de datos

Este programa es una red social, así que su objetivo es interconectar a los usuarios y compartir su información. Cada vez que se crea un nuevo usuario el programa requiere de los siguientes datos:

· Nombre del usuario.

· Fecha de nacimiento.

· Correo electrónico.

· Localización.

· Gustos (entre 1 y 5)

· Contraseña.

Todos estos datos son procesados por diferentes funciones y algoritmos, pero el objetivo final es acabar almacenados como los atributos de un elemento (Un usuario) en la linkedlist “Usuario”. El programa está diseñado para que todos estos atributos estén asociados a un número de ID, que se asigna correspondiendo al orden en el que se añadió el usuario a la base de datos (El primero es 1, el segundo es 2, el tercero es 3…). Esto permite que gracias a la hashtable, en la que este ID se almacena, podamos acceder a cada uno de los atributos de cada usuario, simplemente sabiendo su nombre o ID.

Hay una segunda situación donde se almacenan datos, al hacer una publicación/un post. Cuando inicias sesión y publicas contenido utilizamos otra estructura de datos, un Stack. El stack o pila, por definición, hace que cada una de las publicaciones se guarde una encima de otra. Esto significa que podemos navegar y mostrar los posts de un usuario de manera lineal, ya que siempre estarán apilados. 

---

### REFERENCIAS

Hemos usado Chat GPT para que nos ayude en la comprensión del uso de estructuras y gestión del espacio, como por ejemplo el uso del malloc punteros dobles, entradas de funciones en el main, etc. También aunque no ayuda a resolver errores directamente debido a la complejidad del conjunto del código, depende del prompt es capaz de separar partes del código y ayuda a focalizarse en esa parte en concreto y encontrar el error. Por ejemplo, si tienes localizado un error en una función y se lo envías es capaz de corregirlo de una manera más eficaz. Además debido a las discusiones con esta inteligencia artificial hemos aprendido a solucionar nosotros los problemas ya que además tiene la capacidad de decirte cuál es el error, porque daba error y la manera en la que lo ha solucionado. Un ejemplo de esto es la función de sugerencias, ya que nosotros teníamos una idea de cómo debería ser el código y de las funciones que tendríamos que usar pero no conseguimos hacerlo de manera correcta, y Chat GPT nos ayudó a completar esta función que creemos que es muy original.
