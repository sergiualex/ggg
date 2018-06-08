/*==============================================================================
 | Filename: battleship.h
 | Programmer: Gabriel V. de a Cruz Jr.
 | Class: CptS 121, Fall 2012 ; Lab Section 7
 | Programming Assignment 4: Basic Game of Battleship
 | Date: October 17, 2012
 +------------------------------------------------------------------------------
 | Description: The file contains all of the function prototypee, structs,
 |              enumerated types, constanct macros and standard libraries,
 |              required to run the game of Battleship.
 ==============================================================================*/

#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

/* CONSTANT MACROS */

#define ROWS 10
#define COLS 10

#define NUM_OF_PLANES   3

#define AIR            '?'
#define HIT            'x'
#define MISS           '1'

#define PLANE          'p'

#define SOUTH           1
#define WEST            2
#define NORTH           3
#define EAST            4

#define PLANE_LENGTH    4
#define WING_LENGTH     2

/* ENUMERATED TYPES */

typedef enum {
    FALSE, TRUE
} Boolean;

/* STRUCT TYPES */

typedef struct aircraft {
    char   symbol;
    short  length;
    char   *name;
} AirCraft;

typedef struct stats {
    int        numHits;
    int        numMisses;
    int        totalShots;
    double     hitMissRatio;
} Stats;

typedef struct coordinate {
    int        row;
    int        column;
} Coordinate;

typedef struct cell {
    char       symbol;
    Coordinate position;
} Cell;

/* FUNCTION PROTOTYPES */

void         welcomeScreen                  (void);
void         initializeGameBoard            (Cell gameBoard[][COLS]);
void         printGameBoard                 (Cell gameBoard[][COLS], Boolean showPegs);
void         putShipOnGameBoard             (Cell gameBoard[][COLS], Coordinate position, int direction_of_flight);
void         manuallyPlaceShipsOnGameBoard  (Cell gameBoard[][COLS], AirCraft ship[]);
void         randomlyPlaceShipsOnGameBoard  (Cell gameBoard[][COLS], AirCraft ship[]);
void         updateGameBoard                (Cell gameBoard[][COLS], Coordinate target);
void         checkBoundsOfCardinal          (Boolean cardinals[], int bound, int direction);
void         systemMessage                  (char *message);
void         huntCoordinates                (Coordinate *target);
void         calculateNextShot(Cell gameBoard[][COLS], Coordinate *nextTarget, Coordinate originalTarget);

Boolean      checkIfShotDown                (void);
Boolean      checkSunkShip                  (short sunkShip[][NUM_OF_PLANES], short player, char shipSymbol, FILE *stream);
Boolean      isValidLocation                (Cell gameBoard[][COLS], Coordinate position, int direction);
Boolean      convertStringtoPosition        (Coordinate *position, char *stringPosition, int *direction_of_flight);
Boolean      isWinner                       (Stats players[], int player);
Coordinate   generatePosition               (int direction);
Coordinate   getTarget                      (void);

short        checkShot                      (Cell gameBoard[][COLS], Coordinate target);
int          getRandomNumber                (int lowest, int highest);

#endif