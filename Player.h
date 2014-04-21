#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

#include "CustomTypes.h"

using std::string;

class Player
{
   public:
      Player();
      Player(int x, int y, Player_Type type);
      virtual ~Player();

      int getXCoord();
      int getYCoord();
      void setXCoord(int x);
      void setYCoord(int y);

      Player_Type getPlayerType();

   private:
      Player_Type playerType;

      int x_coord;
      int y_coord;
};

#endif /* PLAYER_H_ */
