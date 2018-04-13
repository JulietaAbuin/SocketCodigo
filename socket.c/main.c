/*
 * main.c
 *
 *  Created on: 12 abr. 2018
 *      Author: utnso
 */


#include <stdio.h>
  //  int socket(int domain, int type, int protocol);
    // si solo se hace connect, el bind es innecesario
    //int bind(int sockfd, struct sockaddr *my_addr, int addrlen);
    //sockfd es el descriptor de fichero de
//socket que devolvió socket(). my_addr es un
//puntero a una estructura struct sockaddr que
//contiene información acerca de tu propia
//dirección, a saber, puerto y dirección IP.
//addrlen se puede asignar a sizeof(struct sockaddr)
//int connect(int sockfd, struct sockaddr *serv_addr, int addrlen);

 #include <string.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #define MYPORT 3490
    int main()
    {
        int sockfd;
        struct sockaddr_in my_addr;
        sockfd = socket(AF_INET, SOCK_STREAM, 0); // ¡Comprueba que no hay errores!
        my_addr.sin_family = AF_INET;         // Ordenación de máquina
        my_addr.sin_port = htons(MYPORT);     // short, Ordenación de la red
        my_addr.sin_addr.s_addr = inet_addr("10.12.110.57");
        memset(&(my_addr.sin_zero), '\0', 8); // Poner a cero el resto de la estructura
        // no olvides comprobar los errores de bind():
        bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));

        my_addr.sin_port = 0; // Elige, aletoriamente, un puerto que no se esté usando
        my_addr.sin_addr.s_addr = INADDR_ANY;  // usa mi dirección IP
        return 0; }

    // Olvidémonos del error "Address already in use" [La dirección ya se está usando]
        if (setsockopt(listener,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1){
            perror("setsockopt");
            exit(1);
        }
