/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> /* printf, sprintf */
#include <Winsock2.h> /* socket, connect */

#pragma comment(lib, "ws2_32.lib")

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
*       get_input
*
*   DESCRIPTION:
*       Get input from server
*
*********************************************************************/
int get_input
    (
    int *yourTurn
    )
{
int state = 5;
char * message_fmt = "GET / HTTP/1.1\r\nHost: %s\r\nbot: Mutant Sock.5b16ecc18a30f4397e0f5\r\n\r\n";

WSADATA wsa;
CALL( WSAStartup(MAKEWORD(2,2), &wsa) == 0 );

struct servent *sent;
CALL( (sent = getservbyname("http", "tcp")) != NULL );
int port = 63330;

struct protoent *pent;
CALL( (pent = getprotobyname("tcp")) != NULL );

struct hostent *hent;
char * host = "172.17.53.251";
CALL( (hent = gethostbyname(host)) != NULL);
//printf("%s -> %s\n", hent->h_name, inet_ntoa(*((struct in_addr *)hent->h_addr)));

struct sockaddr_in addr;
addr.sin_family = AF_INET;
addr.sin_port = port;
addr.sin_addr.S_un.S_un_b.s_b1 = 172;
addr.sin_addr.S_un.S_un_b.s_b2 = 17;
addr.sin_addr.S_un.S_un_b.s_b3 = 53;
addr.sin_addr.S_un.S_un_b.s_b4 = 251;
memset(addr.sin_zero, 0, 8);

int sock;
CALL( (sock = socket(AF_INET, SOCK_STREAM, pent->p_proto)) > 0 );

CALL( (connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr))) == 0 );

char buff[2048 * 10];
sprintf(buff, message_fmt, host);
CALL ( send(sock, buff, strlen(buff), 0) == strlen(buff) );

int foundStatus = 0;
int foundyourTurn = 0;
int readin = recv(sock, buff, sizeof(buff) - 1, 0);

char *state_0_exists = strstr(buff, "\"state\":0");
if (state_0_exists)
{
    state = 0;
}
char *state_1_exists = strstr(buff, "\"state\":1");
if (state_1_exists)
{
    state = 1;
}
char *state_2_exists = strstr(buff, "\"state\":2");
if (state_2_exists)
{
    state = 2;
}
char *state_3_exists = strstr(buff, "\"state\":3");
if (state_3_exists)
{
    state = 3;
}
char *state_4_exists = strstr(buff, "\"state\":4");
if (state_4_exists)
{
    state = 4;
}
if (state != 5)
    foundStatus = 1;

char *yourTurn_true = strstr(buff, "\"yourTurn\":true");
if (yourTurn_true)
    {
    *yourTurn = TRUE;
    foundyourTurn = 1;
    }
char *yourTurn_false = strstr(buff, "\"yourTurn\":false");
if (yourTurn_false)
    {
    *yourTurn = FALSE;
    foundyourTurn = 1;
    }

while (readin > 0 && (foundStatus == 0 || foundyourTurn == 0)) {
    buff[readin] = '\0';
    //printf("%s", buff);
    readin = recv(sock, buff, sizeof(buff) - 1, 0);

    if (foundStatus == 0)
    {
        char *state_0_exists = strstr(buff, "\"state\":0");
        if (state_0_exists)
        {
            state = 0;
        }
        char *state_1_exists = strstr(buff, "\"state\":1");
        if (state_1_exists)
        {
            state = 1;
        }
        char *state_2_exists = strstr(buff, "\"state\":2");
        if (state_2_exists)
        {
            state = 2;
        }
        char *state_3_exists = strstr(buff, "\"state\":3");
        if (state_3_exists)
        {
            state = 3;
        }
        char *state_4_exists = strstr(buff, "\"state\":4");
        if (state_4_exists)
        {
            state = 4;
        }
        if (state != 5)
            foundStatus = 1;
    }

    if (foundyourTurn == 0)
    {
        char *yourTurn_true = strstr(buff, "\"yourTurn\":true");
        if (yourTurn_true)
        {
            *yourTurn = TRUE;
            foundyourTurn = 1;
        }
        char *yourTurn_false = strstr(buff, "\"yourTurn\":true");
        if (yourTurn_false)
        {
            *yourTurn = FALSE;
            foundyourTurn = 1;
        }
    }
}

closesocket(sock);
printf("State: %d, yourTurn: %d\n", state, *yourTurn);
return state;

}  /* get_input */


/*********************************************************************
*
*   PROCEDURE NAME:
*       take_shot
*
*   DESCRIPTION:
*       Makes a POST request to the server to take a shot
*
*********************************************************************/
int take_shot
    (
    int x,
    int y
    )
{
char * message_fmt = "POST / HTTP/1.1\r\nHost: %s\r\nContent-Length: 16\r\nbot: Mutant Sock.5b16ecc18a30f4397e0f5\r\n\r\n{\"x\": %d, \"y\": %d}\r\n\r\n";

WSADATA wsa;
CALL(WSAStartup(MAKEWORD(2, 2), &wsa) == 0);

struct servent *sent;
CALL((sent = getservbyname("http", "tcp")) != NULL);
int port = 63330;

struct protoent *pent;
CALL((pent = getprotobyname("tcp")) != NULL);

struct hostent *hent;
char * host = "172.17.53.251";
CALL((hent = gethostbyname(host)) != NULL);
//printf("%s -> %s\n", hent->h_name, inet_ntoa(*((struct in_addr *)hent->h_addr)));

struct sockaddr_in addr;
addr.sin_family = AF_INET;
addr.sin_port = port;
addr.sin_addr.S_un.S_un_b.s_b1 = 172;
addr.sin_addr.S_un.S_un_b.s_b2 = 17;
addr.sin_addr.S_un.S_un_b.s_b3 = 53;
addr.sin_addr.S_un.S_un_b.s_b4 = 251;
memset(addr.sin_zero, 0, 8);

int sock;
CALL((sock = socket(AF_INET, SOCK_STREAM, pent->p_proto)) > 0);

CALL((connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr))) == 0);

char buff[1024+1];
sprintf(buff, message_fmt, host, x, y);
CALL ( send(sock, buff, strlen(buff), 0) == strlen(buff) );

int readin = recv(sock, buff, sizeof(buff) - 1, 0);
while(readin > 0) {
    buff[readin] = '\0';
    //printf("%s", buff);
    readin = recv(sock, buff, sizeof(buff) - 1, 0);
    }

int hit;
char *hit_exists = strstr(buff, "\"status\":true");
if (hit_exists)
{
    hit = 1;
}
else
{
    hit = 0;
}

closesocket(sock);

return hit;

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
    int battlePlan[3][3]
    )
{
    char * message_fmt = "POST / HTTP/1.1\r\nHost: %s\r\nContent-Length: 43\r\nbot: Mutant Sock.5b16ecc18a30f4397e0f5\r\n\r\n{ \"battlePlan\": [[%d,%d,%d],[%d,%d,%d],[%d,%d,%d]] }\r\n\r\n";

    WSADATA wsa;
    CALL(WSAStartup(MAKEWORD(2, 2), &wsa) == 0);

    struct servent *sent;
    CALL((sent = getservbyname("http", "tcp")) != NULL);
    int port = 63330;

    struct protoent *pent;
    CALL((pent = getprotobyname("tcp")) != NULL);

    struct hostent *hent;
    char * host = "172.17.53.251";
    CALL((hent = gethostbyname(host)) != NULL);
    //printf("%s -> %s\n", hent->h_name, inet_ntoa(*((struct in_addr *)hent->h_addr)));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr = *((struct in_addr *) hent->h_addr);
    memset(addr.sin_zero, 0, 8);

    int sock;
    CALL((sock = socket(AF_INET, SOCK_STREAM, pent->p_proto)) > 0);

    CALL((connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr))) == 0);

    char buff[1024 + 1];
    sprintf(buff, message_fmt, host, battlePlan[0][0], battlePlan[0][1], battlePlan[0][2], battlePlan[1][0], battlePlan[1][1], battlePlan[1][2], battlePlan[2][0], battlePlan[2][1], battlePlan[2][2] );
    //printf("Request:\n%s\n", buff);
    CALL(send(sock, buff, strlen(buff), 0) == strlen(buff));

    /*int readin = recv(sock, buff, sizeof(buff) - 1, 0);
    while (readin > 0) {
        buff[readin] = '\0';
        printf("%s", buff);
        readin = recv(sock, buff, sizeof(buff) - 1, 0);
    }*/

    closesocket(sock);
}