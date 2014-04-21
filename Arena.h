// FIXME - Arena currently has a max size of 255

#ifndef ARENA_H_
#define ARENA_H_

#include <vector>

#include "Cell.h"

using std::vector;

class Arena
{
   public:
      Arena(short int rows, short int columns, short int percentRobot,
             short int percentObstacle, short int percentBlackHole,
             short int percentTransportHole);
      virtual ~Arena();

      int getNumberOfRows(void);
      int getNumberOfColumns(void);
      int getSize(void);
      int getCellNumber(int row, int column);
      int getNumberOfRobots(void);
      int getNumberOfObsticles(void);
      int getNumberOfBlackHoles(void);
      int getNumberOfTransportHoles(void);
      Cell* getCell(int row, int column);

      void setCellContentToPlayer(int row, int column, Player* player);
      void setCellContentToGround(int row, int column);

      void animate(void);

      Player_Type content[TOTAL_ROWS][TOTAL_COLUMNS];

   private:
      Cell** group;

      short int size;

      short int numberOfRobots;
      short int numberOfObsticles;
      short int numberOfBlackHoles;
      short int numberOfTransportHoles;

      char availablePositions[MAX_AVAILABLE_SIZE];
      short int moveOrder[MAX_AVAILABLE_SIZE];
};

#endif /* ARENA_H_ */
