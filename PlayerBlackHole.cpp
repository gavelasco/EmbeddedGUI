#include <cstdlib>
#include <ctime>

#include "PlayerBlackHole.h"

PlayerBlackHole::PlayerBlackHole()
{
   _north = NULL;
   _south = NULL;
   _east = NULL;
   _west = NULL;
}

PlayerBlackHole::PlayerBlackHole(Cell* northCell, Cell* southCell, Cell* eastCell, Cell* westCell)
{
   _north = northCell;
   _south = southCell;
   _east = eastCell;
   _west = westCell;
}

PlayerBlackHole::~PlayerBlackHole()
{
   delete _north;
   delete _south;
   delete _east;
   delete _west;
}

Cell* getCellInCardinal(Cardinal cardinal, Cell* north, Cell* south, Cell* east, Cell* west)
{
   switch(cardinal)
   {
      case card_North:
         return north;

      case card_South:
         return south;

      case card_East:
         return east;

      case card_West:
         return west;

      // Intentional fall through
      case card_Max:
      default:
         break;
   }

   return NULL;
}

void PlayerBlackHole::consume(void)
{
   srand((unsigned int)time(NULL));

   getCellInCardinal(static_cast<Cardinal>(rand() % 4), _north, _south, _east, _west)->deleteContent();
}
