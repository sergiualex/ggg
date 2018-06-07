/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> /* printf, sprintf */
#include <Winsock2.h> /* socket, connect */
//#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")

//#include "battleship.h"
#include "webservice.h"


#include <stdlib.h> /* exit */
#include <io.h> /* read, write, close */
#include <string.h> /* memcpy, memset */

//#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
//#include <netdb.h> /* struct hostent, gethostbyname */

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                TYPES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              PROTOTYPES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                           MEMORY CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              VARIABLES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/

#define CALL(x) if(!(x) && fprintf(stderr, "'%s' failed (error=%d)\n",#x,WSAGetLastError()))exit(1)

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/


/*********************************************************************
*
*   PROCEDURE NAME:
*       get_bot_ID
*
*   DESCRIPTION:
*       Makes a GET request at to_be_revealed_later.php
*
*********************************************************************/
void get_bot_ID
    (
    void
    )
{
char * message_fmt = "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n";

WSADATA wsa;
CALL( WSAStartup(MAKEWORD(2,2), &wsa) == 0 );

struct servent *sent;
CALL( (sent = getservbyname("http", "tcp")) != NULL );
int port = sent -> s_port;

struct protoent *pent;
CALL( (pent = getprotobyname("tcp")) != NULL );

struct hostent *hent;
char * host = "google.com";
CALL( (hent = gethostbyname(host)) != NULL);
printf("%s -> %s\n", hent->h_name, inet_ntoa(*((struct in_addr *)hent->h_addr)));

struct sockaddr_in addr;
addr.sin_family = AF_INET;
addr.sin_port = port;
addr.sin_addr = *((struct in_addr *) hent->h_addr);
memset(addr.sin_zero, 0, 8);

int sock;
CALL( (sock = socket(AF_INET, SOCK_STREAM, pent->p_proto)) > 0 );

CALL( (connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr))) == 0 );

char buff[1024+1];
sprintf(buff, message_fmt, host);
CALL ( send(sock, buff, strlen(buff), 0) == strlen(buff) );

int readin = recv(sock, buff, sizeof(buff) - 1, 0);
while(readin > 0) {
    buff[readin] = '\0';
    printf("%s", buff);
    readin = recv(sock, buff, sizeof(buff) - 1, 0);
    }

closesocket(sock);

}