#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define MY_PORT 8080

int main(void){

//SERVIDOR

struct sockaddr_in direccionServidor;
direccionServidor.sin_family = AF_INET;
direccionServidor.sin_addr.s_addr = INADDR_ANY;
direccionServidor.sin_port = htons(MY_PORT);

int servidor = socket(AF_INET, SOCK_STREAM,0);

if(bind(servidor , (void* ) &direccionServidor, sizeof(direccionServidor))!=0){
	perror("Fallo el bind");
	return 1;
}

printf("Estoy escuchando\n");
listen(servidor,100);


////////////////////////////////////////////////

//CLIENTE

struct sockaddr_in direccionCliente;
unsigned int tamanioDireccion;
int cliente = accept(servidor,(void*) direccionCliente, &tamanioDireccion);

printf("Recibi una conexion en %d \n", cliente);

send(cliente, "Hola",13,0);

////////////////////////////////////////////////


//RECIBO MENSAJES

char* buffer = malloc(5);

int bytesRecibidos = recv(cliente, buffer ,4,0);
if(bytesRecibidos < 0){
	perror("Se desconecto el otro");
	return 1;
}

buffer[bytesRecibidos] = "\0";

printf("Llegaron %d bytes con %s", bytesRecibidos, buffer);

free(buffer);

////////////////////////////////////////////////////////////


// HAGO LO MISMO PERO MAS VECES


char* buffer = malloc(1000);

while(1){
	int bytesRecibidos = recv(cliente, buffer, 1000,0);
	if(bytesRecibidos <= 0 ){
	perror("El otro se desconecto");
	return 1;
}
	buffer[bytesRecibidos] = "\0";
	printf("Llegaron %d bytes con %s", bytesRecibidos, buffer);
}

	free(buffer);



return 0;
}
