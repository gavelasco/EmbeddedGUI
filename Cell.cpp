#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

#include "Cell.h"

Cell::Cell()
{
   position_x = -1;
   position_y = -1;
}

Cell::Cell(int x, int y)
{
   position_x = x;
   position_y = y;
   player = NULL;
}

Cell::~Cell()
{
   delete player;
}

int Cell::getXCordinate(void)
{
   return position_x;
}

int Cell::getYCordinate(void)
{
   return position_y;
}

Player *Cell::getContent()
{
   return player;
}

void Cell::setContent( Player *newPlayer)
{
   player = newPlayer;
}

void Cell::deleteContent()
{
   // The player pointer must continue to exist but its contents must
   // be deleted.
   Player* temp = player;
   player = NULL;
   delete temp;
}
