/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> /* printf, sprintf */
#include <Winsock2.h> /* socket, connect */

#pragma comment(lib, "ws2_32.lib")

#include "battleship.h"
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
*       Makes a GET request to the server to get the bot ID
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
//int port = sent -> s_port;
int port = 25335;

struct protoent *pent;
CALL( (pent = getprotobyname("tcp")) != NULL );

struct hostent *hent;
char * host = "172.17.53.251";
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

}  /* get_bot_ID */


/*********************************************************************
*
*   PROCEDURE NAME:
*       take_shot
*
*   DESCRIPTION:
*       Makes a POST request to the server to take a shot
*
*********************************************************************/
void take_shot
    (
    int x,
    int y
    )
{
char * message_fmt = "POST /{%d: int, %d: int} HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n";

WSADATA wsa;
CALL( WSAStartup(MAKEWORD(2,2), &wsa) == 0 );

struct servent *sent;
CALL( (sent = getservbyname("http", "tcp")) != NULL );
//int port = sent -> s_port;
int port = 25335;

struct protoent *pent;
CALL( (pent = getprotobyname("tcp")) != NULL );

struct hostent *hent;
char * host = "172.17.53.251";
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
sprintf(buff, message_fmt, x, y, host);
CALL ( send(sock, buff, strlen(buff), 0) == strlen(buff) );

int readin = recv(sock, buff, sizeof(buff) - 1, 0);
while(readin > 0) {
    buff[readin] = '\0';
    printf("%s", buff);
    readin = recv(sock, buff, sizeof(buff) - 1, 0);
    }

closesocket(sock);

} /* take_shot */

/*********************************************************************
*
*   PROCEDURE NAME:
*       set_board
*
*   DESCRIPTION:
*       Sends the our board info to server
*
*********************************************************************/
void set_board
    (
    void
    )
{
    Cell gameBoard[ROWS][COLS];
    Coordinate position;
    int direction_of_flight = -1;
    int i = 0;
    int battlePlan[3][3];

    for (i = 0; i < NUM_OF_PLANES; i++)
        {
        while (TRUE)
            {
            direction_of_flight = getRandomNumber (1, 3); /*  1 -> SOUTH
                                                              2 -> WEST
                                                              3 -> NORTH
                                                              4 -> EAST */
            position = generatePosition (direction_of_flight);

            if (isValidLocation (gameBoard, position, direction_of_flight)) break;
            }
        battlePlan[i][0] = position.row;
        battlePlan[i][1] = position.column;
        battlePlan[i][2] = direction_of_flight;
        }

    /* TODO: send battle plan */
}

/*********************************************************************
*
*   PROCEDURE NAME:
*       get_input
*
*   DESCRIPTION:
*       Obtains input from server
*
*********************************************************************/
void get_input
    (
    void
    )
{
    /* TODO: get input from server*/
}
