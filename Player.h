#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

#include "CustomTypes.h"

using std::string;

class Player
{
   public:
      Player();
      Player(int x, int y, string path, Player_Type type);
      virtual ~Player();

      int getXCoord();
      int getYCoord();
      void setXCoord(int x);
      void setYCoord(int y);

      string getPathToImage();
      Player_Type getPlayerType();

   private:
      string pathToImage;

      /* This is going to define each player by bit.
       * MS bits
       * Obstacle
       * Transport Hole
       * Black Hole
       * Ground
       *
       * LS bits
       * team 4
       * team 3
       * team 2
       * team 1
       */
      Player_Type playerType;

      int x_coord;
      int y_coord;
};

#endif /* PLAYER_H_ */
