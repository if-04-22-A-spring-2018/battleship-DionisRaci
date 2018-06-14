
/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>
#include "battleship.h"

static CellContent user_player_field[FIELDSIZE][FIELDSIZE];
static CellContent opponent_player_field[FIELDSIZE][FIELDSIZE];
static CellContent guess[FIELDSIZE][FIELDSIZE];

void load_game(){
  FILE* user_file = fopen("battleship.my","r");
  FILE* opponent_file = fopen("battleship.op","r");
  for(int i = 0; i < FIELDSIZE; i++)
  {
    for (int j = 0; j < FIELDSIZE; j++)
    {
        fread(&user_player_field[j][i],4,1,user_file);
        fread(&opponent_player_field[j][i],4,1,opponent_file);
        guess[j][i] = Unknown;
    }
  }
  fclose(user_file);
  fclose(opponent_file);
}

CellContent get_shot(int row, int col){
  if(row < 0 || row >= FIELDSIZE || col < 0 || col >= FIELDSIZE)
  {
    return OutOfRange;
  }
  else
  {
    return user_player_field[col][row];
  }
}


bool shoot(int row, int col){
 CellContent check = get_my_guess(row,col);
 if(check == OutOfRange)
 {
   return false;
 }
 if(opponent_player_field[col][row] == Boat || opponent_player_field[col][row] == Water)
 {
   guess[col][row] = opponent_player_field[col][row];

   if(guess[col][row] == Boat)
   {
     for (int i = -1; i < 2; i++)
     {
       for (int j = -1; j < 2; j++)
        {
         check = get_my_guess(row+j,col+i);
         if (check == Unknown)
         {
           guess[col+i][row+j] = Water;
         }
       }
     }
   }
 }
 return true;
}

CellContent get_my_guess(int row, int col){
  if(row < 0 || row >= FIELDSIZE || col < 0 || col >= FIELDSIZE)
  {
    return OutOfRange;
  }
  else{
    return guess[col][row];
  }
}
