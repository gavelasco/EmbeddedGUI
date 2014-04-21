#ifndef PLAYEROBSTACLE_H_
#define PLAYEROBSTACLE_H_

#include "Player.h"

class PlayerObstacle: public Player
{
   public:
      PlayerObstacle(int x, int y, Player_Type type);
      virtual ~PlayerObstacle();
};

#endif /* PLAYEROBSTACLE_H_ */
