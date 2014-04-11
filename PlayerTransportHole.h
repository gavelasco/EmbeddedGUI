// TODO - What if all the spaces around the transport hole are occupied

#ifndef PLAYERTRANSPORTHOLE_H_
#define PLAYERTRANSPORTHOLE_H_

#include "Cell.h"

typedef short int SiblingID;

class PlayerTransportHole
{
   public:
      PlayerTransportHole();
      PlayerTransportHole(SiblingID brotherID, Cell* northCell, Cell* southCell, Cell* eastCell, Cell* westCell);

      virtual ~PlayerTransportHole();

   private:
      SiblingID id;

      Cell* north;
      Cell* south;
      Cell* east;
      Cell* west;
};

#endif /* PLAYERTRANSPORTHOLE_H_ */
