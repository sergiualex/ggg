#include "battleship.h"
#include "webservice.h"

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