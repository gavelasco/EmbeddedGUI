#include "PlayerTransportHole.h"

PlayerTransportHole::PlayerTransportHole()
{
   id = -1;
   north = NULL;
   south = NULL;
   east =  NULL;
   west =  NULL;
}

PlayerTransportHole::PlayerTransportHole(SiblingID sibling_id, Cell* northCell, Cell* southCell, Cell* eastCell, Cell* westCell)
{
   id = sibling_id;
   north = northCell;
   south = southCell;
   east = eastCell;
   west = westCell;
}

PlayerTransportHole::~PlayerTransportHole()
{
   delete north;
   delete south;
   delete east ;
   delete west ;
}

