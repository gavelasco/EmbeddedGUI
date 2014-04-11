// TODO - Does a black hole consume obstacles and transport holese?

#ifndef PLAYERBLACKHOLE_H_
#define PLAYERBLACKHOLE_H_

#include "Cell.h"

typedef enum
{
   card_North,
   card_South,
   card_East,
   card_West,
   card_Max
} Cardinal;

class PlayerBlackHole
{
   public:
      PlayerBlackHole();
      PlayerBlackHole(Cell* northCell, Cell* southCell, Cell* eastCell, Cell* westCell);

      virtual ~PlayerBlackHole();

      void consume(void);

   private:
      Cell* _north;
      Cell* _south;
      Cell* _east;
      Cell* _west;
};

#endif /* PLAYERBLACKHOLE_H_ */
