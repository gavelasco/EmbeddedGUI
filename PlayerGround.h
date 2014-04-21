#ifndef PLAYERGROUND_H_
#define PLAYERGROUND_H_

#include "Player.h"

class PlayerGround: public Player
{
   public:
      PlayerGround();
      PlayerGround(int x, int y, Player_Type type);
      virtual ~PlayerGround();
};

#endif /* PLAYERGROUND_H_ */
