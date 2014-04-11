#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

#define OBSTACLE 0x80
#define TRANSPORT_HOLE 0x40
#define BLACK_HOLE 0x20
#define GROUND 0x10

#define TEAM_4 0x08
#define TEAM_3 0x04
#define TEAM_2 0x02
#define TEAM_1 0x01

using std::string;

class Player
{
   public:
      Player();
      Player(int x, int y, string path, char type);
      virtual ~Player();

      int getXCoord();
      int getYCoord();
      void setXCoord(int x);
      void setYCoord(int y);

      string getPathToImage();
      char getPlayerType();

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
      char playerType;

      int x_coord;
      int y_coord;
};

#endif /* PLAYER_H_ */
