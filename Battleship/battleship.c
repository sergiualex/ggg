/*==============================================================================
 | Filename: battleship.h
 | Programmer: Gabriel V. de a Cruz Jr.
 | Class: CptS 121, Fall 2012 ; Lab Section 7
 | Programming Assignment 4: Basic Game of Battleship
 | Date: October 17, 2012
 +------------------------------------------------------------------------------
 | Description: Thie file contains all the function definition of the prototypes
 |              listed in battleship.h These are the functions necessary to run
 |              the game of Battleship.
 ==============================================================================*/

#include "battleship.h"

/**
 * Function name : welcomeScreen ()
 * Date Created  : 17 October 2012
 * Usage         : welcomeScreen ();
 * Definition    : This function displays a welcome message along with the
 *                 Rules of Battleship.
 */
void welcomeScreen (void) {
    printf ("XXXXX   XXXX  XXXXXX XXXXXX XX     XXXXXX  XXXXX XX  XX XX XXXX\n");
    printf ("XX  XX XX  XX   XX     XX   XX     XX     XX     XX  XX XX XX  XX\n");
    printf ("XXXXX  XX  XX   XX     XX   XX     XXXX    XXXX  XXXXXX XX XXXX\n");
    printf ("XX  XX XXXXXX   XX     XX   XX     XX         XX XX  XX XX XX\n");
    printf ("XXXXX  XX  XX   XX     XX   XXXXXX XXXXXX XXXXX  XX  XX XX XX\n");
    printf ("\n\n");
    printf ("RULES OF THE GAME:\n");
    printf ("1. This is a two player game.\n");
    printf ("2. Player 1 is you and Player 2 is the computer.\n");
    printf ("3. Player 1 will be prompted if user wants to manually input coordinates\n");
    printf ("   for the game board or have the computer randomly generate a game board\n");
    printf ("4. There are five types of ships to be placed by longest length to the\n");
    printf ("   shortest; [c] Carrier has 5 cells, [b] Battleship has 4 cells, [r] Cruiser\n");
    printf ("   has 3 cells, [s] Submarine has 3 cells, [d] Destroyer has 2 cells\n");
    printf ("5. The computer randomly selects which player goes first\n");
    printf ("6. The game begins as each player tries to guess the location of the ships\n");
    printf ("   of the opposing player's game board; [*] hit and [m] miss\n");
    printf ("7. First player to guess the location of all ships wins\n\n");
}

/**
 * Function name : initializeGameBoard ()
 * Date Created  : 17 October 2012
 * Usage         : initializeGameBoard ();
 * Definition    : This function displays initializes values of the multi-
 *                 dimensional array called gameBoard.
 * Pre-condition : ROWS & COLS are defined as constant macros
 * Post-condition: Array initialize to (~) tilde representing water
 */
void initializeGameBoard (Cell gameBoard[][COLS]) {
    int i = 0, j = 0;

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++) {
            gameBoard[i][j].symbol          = AIR;
            gameBoard[i][j].position.row    = i;
            gameBoard[i][j].position.column = j;
        }
}

/**
 * Function name : printGameBoard ()
 * Date Created  : 17 October 2012
 * Usage         : printGameBoard (Cell [][], Boolean);
 * Definition    : This function prints the game board on the console
 *                 screen with an option of showing or not showing the pegs
 * Pre-condition : Game board is of Cell struct type and showPegs
                   if Boolean enum type
 * Post-condition: Game board printed on console screen
 */
void printGameBoard (Cell gameBoard [][COLS], Boolean showPegs) {
    int i = 0, j = 0;

    printf ("  0 1 2 3 4 5 6 7 8 9\n");

    for (i = 0; i < ROWS; i++) {
        printf ("%d ", i);

        for (j = 0; j < COLS; j++) {
            if (showPegs == TRUE)
                printf ("%c ", gameBoard [i][j].symbol);
            else {
                switch (gameBoard [i][j].symbol) {
                    case HIT:   printf ("%c ", HIT);   break;
                    case MISS:  printf ("%c ", MISS);  break;
                    case AIR:
                    default:    printf ("%c ", AIR); break;
                }
            }
        }

        putchar ('\n');
    }
}

/**
 * Function name : putShipOnGameBoard ()
 * Date Created  : 17 October 2012
 * Usage         : putShipOnGameBoard (Cell [][], WaterCraft, Coordinate, int)
 * Definition    : This function allows you to put the 5 types of ship in the
 *                 the game board specified in the formal argument
 * Pre-condition : n/a
 * Post-condition: Specific type of ship place on specificied target cell
 */
void putShipOnGameBoard (Cell gameBoard[][COLS], Coordinate position, int direction_of_flight)
{
    int j;
    switch (direction_of_flight)
        {
        case NORTH:
            /* Add the body */
            for (j = 0; j < PLANE_LENGTH; j++)
                {
                gameBoard[position.row + j][position.column].symbol = PLANE;
                }
            /* Add the wings */
            for (j = 1; j < WING_LENGTH + 1; j++)
                {
                gameBoard[position.row + 1][position.column - j].symbol = PLANE;
                gameBoard[position.row + 1][position.column + j].symbol = PLANE;
                }
            /* Add the tail */
            gameBoard[position.row + PLANE_LENGTH - 1][position.column + 1].symbol = PLANE;
            gameBoard[position.row + PLANE_LENGTH - 1][position.column - 1].symbol = PLANE;
            break;
        case SOUTH:
            /* Add the body */
            for (j = 0; j < PLANE_LENGTH; j++)
                {
                gameBoard[position.row - j][position.column].symbol = PLANE;
                }
            /* Add the wings */
            for (j = 1; j < WING_LENGTH + 1; j++)
                {
                gameBoard[position.row - 1][position.column - j].symbol = PLANE;
                gameBoard[position.row - 1][position.column + j].symbol = PLANE;
                }
            /* Add the tail */
            gameBoard[position.row - PLANE_LENGTH + 1][position.column + 1].symbol = PLANE;
            gameBoard[position.row - PLANE_LENGTH + 1][position.column - 1].symbol = PLANE;
            break;
        case WEST:
            /* Add the body */
            for (j = 0; j < PLANE_LENGTH; j++)
                {
                gameBoard[position.row][position.column + j].symbol = PLANE;
                }
            /* Add the wings */
            for (j = 1; j < WING_LENGTH + 1; j++)
                {
                gameBoard[position.row - j][position.column + 1].symbol = PLANE;
                gameBoard[position.row + j][position.column + 1].symbol = PLANE;
                }
            /* Add the tail */
            gameBoard[position.row - 1][position.column + PLANE_LENGTH - 1].symbol = PLANE;
            gameBoard[position.row + 1][position.column + PLANE_LENGTH - 1].symbol = PLANE;
            break;
        case EAST:
            /* Add the body */
            for (j = 0; j < PLANE_LENGTH; j++)
                {
                gameBoard[position.row][position.column - j].symbol = PLANE;
                }
            /* Add the wings */
            for (j = 1; j < WING_LENGTH + 1; j++)
                {
                gameBoard[position.row - j][position.column - 1].symbol = PLANE;
                gameBoard[position.row + j][position.column - 1].symbol = PLANE;
                }
            /* Add the tail */
            gameBoard[position.row - 1][position.column - PLANE_LENGTH + 1].symbol = PLANE;
            gameBoard[position.row + 1][position.column - PLANE_LENGTH + 1].symbol = PLANE;
            break;
        }
}

/**
 * Function name : manuallyPlaceShipsOnGameBoard ()
 * Date Created  : 17 October 2012
 * Usage         : manuallyPlaceShipsOnGameBoard (Cell [][], WaterCraft []);
 * Definition    : This function allows user to manually place ship on the specified
 *                 gameboard with specific ship
 * Pre-condition : Assuming user inputs correct coordinates as it does not check
 *                 if input is correctly inputted
 * Post-condition: Ships placed on game board
 */
void manuallyPlaceShipsOnGameBoard (Cell gameBoard[ROWS][COLS], AirCraft ship[])
{
    char        stringPosition[10] = "";
    int         i = 0, j = 0;
    int         direction_of_flight;
    Coordinate  position;
    Boolean     isValid = FALSE;

    fflush (stdin);

    for (i = 0; i < NUM_OF_PLANES; i++)
        {
        while (TRUE)
            {
            system ("cls");
            printGameBoard (gameBoard, TRUE);
            printf ("> Please enter the x-y coordinates of the head of the plane and direction of flight(1-south, 2-west, 3-north, 4-east):\n" );
            printf ("> ");
            scanf_s ("%s", stringPosition, (unsigned)_countof(stringPosition));

            /* Check if valid string and position */
            isValid = ( convertStringtoPosition (&position, stringPosition, &direction_of_flight)
                     && isValidLocation(gameBoard, position, direction_of_flight) );
            if (isValid)
                {
                switch (direction_of_flight)
                    {
                    case NORTH:
                        /* Add the body */
                        for (j = 0; j < PLANE_LENGTH; j++)
                            {
                            gameBoard[position.row + j][position.column].symbol = PLANE;
                            }
                        /* Add the wings */
                        for (j = 1; j < WING_LENGTH + 1; j++)
                            {
                            gameBoard[position.row + 1][position.column - j].symbol = PLANE;
                            gameBoard[position.row + 1][position.column + j].symbol = PLANE;
                            }
                        /* Add the tail */
                        gameBoard[position.row + PLANE_LENGTH - 1][position.column + 1].symbol = PLANE;
                        gameBoard[position.row + PLANE_LENGTH - 1][position.column - 1].symbol = PLANE;
                        break;
                    case SOUTH:
                        /* Add the body */
                        for (j = 0; j < PLANE_LENGTH; j++)
                            {
                            gameBoard[position.row - j][position.column].symbol = PLANE;
                            }
                        /* Add the wings */
                        for (j = 1; j < WING_LENGTH + 1; j++)
                            {
                            gameBoard[position.row - 1][position.column - j].symbol = PLANE;
                            gameBoard[position.row - 1][position.column + j].symbol = PLANE;
                            }
                        /* Add the tail */
                        gameBoard[position.row - PLANE_LENGTH + 1][position.column + 1].symbol = PLANE;
                        gameBoard[position.row - PLANE_LENGTH + 1][position.column - 1].symbol = PLANE;
                        break;
                    case WEST:
                        /* Add the body */
                        for (j = 0; j < PLANE_LENGTH; j++)
                            {
                            gameBoard[position.row][position.column + j].symbol = PLANE;
                            }
                        /* Add the wings */
                        for (j = 1; j < WING_LENGTH + 1; j++)
                            {
                            gameBoard[position.row - j][position.column + 1].symbol = PLANE;
                            gameBoard[position.row + j][position.column + 1].symbol = PLANE;
                            }
                        /* Add the tail */
                        gameBoard[position.row - 1][position.column + PLANE_LENGTH - 1].symbol = PLANE;
                        gameBoard[position.row + 1][position.column + PLANE_LENGTH - 1].symbol = PLANE;
                        break;
                    case EAST:
                        /* Add the body */
                        for (j = 0; j < PLANE_LENGTH; j++)
                            {
                            gameBoard[position.row][position.column - j].symbol = PLANE;
                            }
                        /* Add the wings */
                        for (j = 1; j < WING_LENGTH + 1; j++)
                            {
                            gameBoard[position.row - j][position.column - 1].symbol = PLANE;
                            gameBoard[position.row + j][position.column - 1].symbol = PLANE;
                            }
                        /* Add the tail */
                        gameBoard[position.row - 1][position.column - PLANE_LENGTH + 1].symbol = PLANE;
                        gameBoard[position.row + 1][position.column - PLANE_LENGTH + 1].symbol = PLANE;
                        break;
                    }
                }
            if (isValid == TRUE)
                break;
            }
        }
}

/**
 * Function name : randomlyPlaceShipsOnGameBoard ()
 * Date Created  : 17 October 2012
 * Usage         : randomlyPlaceShipsOnGameBoard (Cell [][], WaterCraft []);
 * Definition    : This function lets the computer randomly place ship on the
 *                 game board
 * Pre-condition : n/a
 * Post-condition: Ships placed on game board
 */
void randomlyPlaceShipsOnGameBoard (Cell gameBoard[][COLS], AirCraft ship[]) {
    Coordinate position;
    int direction_of_flight = -1;
    int i = 0;

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
        putShipOnGameBoard (gameBoard, position, direction_of_flight);
        }
}

/**
 * Function name : updateGameBoard ()
 * Date Created  : 17 October 2012
 * Usage         : updateGameBoard (Cell [][], Coordinate);
 * Definition    : This function updates the game board whether
 *                 its a hit or miss
 * Pre-condition : n/a
 * Post-condition: Game board updated with proper symbol
 */
void updateGameBoard (Cell gameBoard[][COLS], Coordinate target) {
    switch (gameBoard[target.row][target.column].symbol) {
        /* miss */
        case AIR:
            gameBoard[target.row][target.column].symbol = MISS;
            break;

        /* hit */
        case PLANE:
            gameBoard[target.row][target.column].symbol = HIT;
            break;

        case HIT:
        case MISS:
        default:
            break;
    }
}

/**
 * Function name : checkBoundsOfCardinal ()
 * Date Created  : 17 October 2012
 * Usage         : checkBoundsOfCardinal (Boolean [], int, int);
 * Definition    : This function checks if the specified direction is
 *                 not over the bounds and sets the cardinals with TRUE
 *                 if its within bounds, otherwise FALSE
 * Pre-condition : n/a
 * Post-condition: Updates the cardinals array
 */
void checkBoundsOfCardinal (Boolean cardinals[], int bound, int direction) {
    switch (direction) {
        case NORTH:
            if (bound < 0)
                cardinals[0] = FALSE;
            else
                cardinals[0] = TRUE;
            break;

        case SOUTH:
            if (bound > 9)
                cardinals[1] = FALSE;
            else
                cardinals[1] = TRUE;
            break;

        case WEST:
            if (bound < 0)
                cardinals[2] = FALSE;
            else
                cardinals[2] = TRUE;
            break;

        case EAST:
            if (bound > 9)
                cardinals[3] = FALSE;
            else
                cardinals[3] = TRUE;
            break;
    }
}

/**
 * Function name : systemMessage ()
 * Date Created  : 17 October 2012
 * Usage         : systemMessage (char *);
 * Definition    : This function prints a message on the console and awaits
 *                 for user to press the enter key
 * Pre-condition : n/a
 * Post-condition: n/a
 */
void systemMessage (char *message) {
    char ch = '\0';

    do {
        printf ("%s", message);
    } while ((ch = _getch()) != '\r');
}

/**
 * Function name : checkSunkShip ()
 * Date Created  : 17 October 2012
 * Usage         : checkSunkShip (shor [][], short, char, FILE *);
 * Definition    : This function check if a ship has sunk based on the
 *                 how of the length of ship is left. If a ship was sunk
 *                 it is logged on an output file
 * Pre-condition : stream to output file was created
 * Post-condition: n/a
 */
Boolean checkSunkShip (short sunkPlane[][NUM_OF_PLANES], short player, char shipSymbol, FILE *stream) {
    Boolean shot_down = FALSE;

    switch (shipSymbol) {
        case PLANE:
            if (--sunkPlane[player][0] == 0) {
                printf ("> Player %d's Plane shot down!\n", player + 1);

                /* Write to battleship.log */
                fprintf (stream, "Player %d's Plane shot down!\n", player + 1);

                shot_down = TRUE;
            }
            break;
        default:
                break;
    }

    return shot_down;
}

/**
 * Function name : isValidLocation ()
 * Usage         : isValidLocation (Cell [][], Coordinate, int);
 * Definition    : This function checks if specified position, direction and
 *                 length is valid on location specified on the game board
 * Pre-condition : n/a
 * Post-condition: n/a
 */
Boolean isValidLocation (Cell gameBoard[ROWS][COLS], Coordinate position,
                         int direction_of_flight) {
    int i;
    Boolean lengthOK = TRUE;
    Boolean wingsOK  = TRUE;
    Boolean tailOK   = TRUE;

    switch (direction_of_flight)
        {
        case NORTH:
            for (i = 0; lengthOK && i < PLANE_LENGTH; i++)
                {
                if ((position.row + i) >= ROWS
                 || gameBoard[position.row + i][position.column].symbol != AIR)
                    {
                    lengthOK = FALSE;
                    }
                }

            for (i = 1; wingsOK && i < WING_LENGTH + 1; i++)
                {
                if (((position.column - i < 0) || (position.column + i >= COLS))
                 || gameBoard[position.row + 1][position.column - i].symbol != AIR
                 || gameBoard[position.row + 1][position.column + i].symbol != AIR)
                    {
                    wingsOK = FALSE;
                    }
                }
            if (gameBoard[position.row + PLANE_LENGTH - 1][position.column - 1].symbol != AIR
             || gameBoard[position.row + PLANE_LENGTH - 1][position.column + 1].symbol != AIR)
                {
                tailOK = FALSE;
                }
            break;
        case SOUTH:
            for (i = 0; lengthOK && i < PLANE_LENGTH; i++)
                {
                if ((position.row - i) < 0
                || gameBoard[position.row - i][position.column].symbol != AIR )
                    {
                    lengthOK = FALSE;
                    }
                }
            for (i = 1; wingsOK && i < WING_LENGTH + 1; i++)
                {
                if (((position.column - i < 0) || (position.column + i >= COLS))
                 || gameBoard[position.row - 1][position.column - i].symbol != AIR
                 || gameBoard[position.row - 1][position.column + i].symbol != AIR)
                    {
                    wingsOK = FALSE;
                    }
                }
            if (gameBoard[position.row - PLANE_LENGTH + 1][position.column - 1].symbol != AIR
             || gameBoard[position.row - PLANE_LENGTH + 1][position.column + 1].symbol != AIR)
                {
                tailOK = FALSE;
                }
            break;
        case WEST:
            for (i = 0; lengthOK && i < PLANE_LENGTH; i++)
                {
                if ((position.column + i) >= COLS
                 || gameBoard[position.row][position.column + i].symbol != AIR )
                    {
                    lengthOK = FALSE;
                    }
                }
            for (i = 1; wingsOK && i < WING_LENGTH + 1; i++)
                {
                if (((position.row - i < 0) || (position.row + i >= ROWS))
                 || gameBoard[position.row - i][position.column + 1].symbol != AIR
                 || gameBoard[position.row + i][position.column + 1].symbol != AIR)
                    {
                    wingsOK = FALSE;
                    }
                }
            if (gameBoard[position.row - 1][position.column + PLANE_LENGTH - 1].symbol != AIR
             || gameBoard[position.row + 1][position.column + PLANE_LENGTH - 1].symbol != AIR)
                {
                tailOK = FALSE;
                }
            break;
        case EAST:
            for (i = 0; lengthOK && i < PLANE_LENGTH; i++)
                {
                if ((position.column - i) < 0
                 || gameBoard[position.row][position.column - i].symbol != AIR )
                    {
                    lengthOK = FALSE;
                    }
                }
            for (i = 1; wingsOK && i < WING_LENGTH + 1; i++)
                {
                if (((position.row - i < 0) || (position.row + i >= ROWS))
                 || gameBoard[position.row - i][position.column - 1].symbol != AIR
                 || gameBoard[position.row + i][position.column - 1].symbol != AIR )
                    {
                    wingsOK = FALSE;
                    }
                }
            if (gameBoard[position.row - 1][position.column - PLANE_LENGTH + 1].symbol != AIR
             || gameBoard[position.row + 1][position.column - PLANE_LENGTH + 1].symbol != AIR)
                {
                tailOK = FALSE;
                }
            break;
        default:
            lengthOK = FALSE;
            wingsOK = FALSE;
            tailOK = FALSE;
        }

    return (lengthOK && wingsOK && tailOK);
}

/**
 * Function name : convertStringtoPosition ()
 * Date Created  : 17 October 2012
 * Usage         : convertStringtoPosition (Cell [], char *, int);
 * Definition    : This function converts string coordinates into individual
 *                 integer coordinates
 * Pre-condition : Assuming that user inputs correct coordinates since program
 *                 does not check for inccorrect coordinates
 * Post-condition: n/a
 */
Boolean convertStringtoPosition (Coordinate *position, char *stringPosition, int *direction_of_flight)
{
    Boolean flag = TRUE;

    /* checks if length of input is good */
    if( strlen (stringPosition) == 3 )
        {
        /* checks if each cell is a digit for each plane */
        if( isdigit(stringPosition[0])
         && isdigit(stringPosition[1])
         && isdigit(stringPosition[2]) )
            {
            position->row        = stringPosition[0] - '0';
            position->column     = stringPosition[1] - '0';
            *direction_of_flight = stringPosition[2] - '0';
            }
        else
            {
            flag = FALSE;
            }
        }
    else
        {
        flag = FALSE;
        }

    return flag;
}

/**
 * Function name : isWinner ()
 * Date Created  : 17 October 2012
 * Usage         : isWinner (Stats [], int);
 * Definition    : This function determines if there is a winner based
 *                 on the 17 total pegs for each player
 * Pre-condition : n/a
 * Post-condition: n/a
 */
Boolean isWinner (Stats players[], int player) {
    Boolean isWin = FALSE;

    if (players[player].numHits == 17)
        isWin = TRUE;

    return isWin;
}

/**
 * Function name : generatePosition ()
 * Usage         : generatePosition (int);
 * Definition    : This function generates position based on the
 *                 direction of flight and it can't be more than
 *                 the game board size
 * Pre-condition : n/a
 * Post-condition: n/a
 */
Coordinate generatePosition (int direction_of_flight)
{
    Coordinate position;

    switch (direction_of_flight)
        {
        case NORTH:
            position.row    = getRandomNumber( 0, ROWS - PLANE_LENGTH );
            position.column = getRandomNumber( WING_LENGTH, COLS - WING_LENGTH - 1 );
            break;
        case SOUTH:
            position.row    = getRandomNumber( PLANE_LENGTH - 1, ROWS - 1 );
            position.column = getRandomNumber( WING_LENGTH, COLS - WING_LENGTH - 1 );
            break;
        case WEST:
            position.row    = getRandomNumber( WING_LENGTH, ROWS - WING_LENGTH - 1 );
            position.column = getRandomNumber( 0, COLS - PLANE_LENGTH );
            break;
        case EAST:
            position.row    = getRandomNumber( WING_LENGTH, ROWS - WING_LENGTH - 1 );
            position.column = getRandomNumber( PLANE_LENGTH - 1, COLS - 1 );
            break;
        default:
            position.row    = 0;
            position.column = 0;
            break;
        }

    return position;
}

/**
 * Function name : getTarget ()
 * Date Created  : 17 October 2012
 * Usage         : getTarget ();
 * Definition    : This function reads a row and column values from
 *                 the user
 * Pre-condition : n/a
 * Post-condition: n/a
 */
Coordinate getTarget (void) {
    Coordinate target;

    fflush (stdin);

    printf ("> Enter Target (ex. > 3 4):\n");
    printf ("> ");
    scanf_s ("%d %d", &target.row, &target.column);

    return target;
}

/**
 * Function name : checkShot ()
 * Date Created  : 17 October 2012
 * Usage         : checkShot (Cell [][], Coordinate);
 * Definition    : This function checks if the coordinates on the
 *                 game board is a miss, hit, water or water craft
 * Pre-condition : n/a
 * Post-condition: n/a
 */
short checkShot (Cell gameBoard[][COLS], Coordinate target) {
    int hit = -2;

    switch (gameBoard[target.row][target.column].symbol) {
        /* miss */
        case AIR:
            hit = 0;
            break;

        /* hit */
        case PLANE:
            hit = 1;
            break;

        case HIT:
        case MISS:
        default:
            hit = -1;
            break;
    }

    return hit;
}

/**
 * Function name : getRandomNumber ()
 * Date Created  : 17 October 2012
 * Usage         : getRandomNumber (int, int);
 * Definition    : This function returns a random number between and
 *                 including the lowest to the highest number
 * Pre-condition : n/a
 * Post-condition: n/a
 */
int getRandomNumber (int lowest, int highest) {
    if (lowest == 0)
        return rand () % ++highest;

    if (lowest > 0)
        return rand () % highest + lowest;
}

void huntCoordinates(Coordinate *target)
{
    do
        {
        target->row = getRandomNumber(1, ROWS - 1);
        target->column = getRandomNumber(1, COLS - 1);
        } while ( (target->row + target->column) % 2 == 0 );
}

void calculateNextShot(Coordinate *target)
{

}