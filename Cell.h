#ifndef CELL_H_
#define CELL_H_

#include "Player.h"

class Cell
{
   public:
      Cell();
      Cell(int x, int y);
      virtual ~Cell();

      Player *getContent();
      void setContent(Player *newPlayer);
      void deleteContent();

      int getXCordinate(void);
      int getYCordinate(void);


   private:
      Player * player;
      int position_x;
      int position_y;
};

#endif /* CELL_H_ */
