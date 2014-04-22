// TODO - Add rest of players

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <algorithm>

#include "Arena.h"
#include "PlayerRobot.h"
#include "PlayerGround.h"
#include "PlayerObstacle.h"
//#include "PlayerBlackHole.h"
//#include "PlayerTransportHole.h"

enum
{
    unavailable,
    available,
    canMove,
    hasMoved
};

// Helper function declarations
//static void buildArenaWith(Cell** group, bool* availablePositions, int* size, int row, int column);

static void calculateNumberOfAllPlayers(short int* size, short int* numberOfRobots, short int* numberOfObsticles,
      short int* numberOfBlackHoles, short int* numberOfTransportHoles, short int* percentRobot,
      short int* percentObstacle, short int* percentBlackHole, short int* percentTransportHole);

//static void populateArena(Cell** group, bool* availablePositions, int* size, int* numberOfRobots,
//      int* numberOfObsticles, int* numberOfBlackHoles, int* numberOfTransportHoles);

Arena::Arena(short int row, short int column, short int percentRobot, short int percentObstacle,
      short int percentBlackHole, short int percentTransportHole)
{
   size = row * column;
   group = new Cell*[size];

// FIXME --------------------------------
   // Create all the Cell objects and have them point to a Ground object
//   buildArenaWith(group, availablePositions, &size, row, column);
   // Build the arena with cells
   short int iterator = 0;
   for (short int _row = 0; _row < row; _row++)
   {
      for (short int _col = 0; _col < column; _col++)
      {
         group[iterator] = new Cell(_row, _col);
         iterator++;
         content[_row][_col] = player_ground;
      }
   }

   // Initialize each cell to point to ground. Empty arena.
   for (iterator = 0; iterator < size; iterator++)
   {
      availablePositions[iterator] = available;
      moveOrder[iterator] = iterator;
      group[iterator]->setContent(
            new PlayerGround(group[iterator]->getXCordinate(), group[iterator]->getYCordinate(), player_ground));
   }
//-----------------------------------------

   // Calculate the number of all players with the percentages given
   calculateNumberOfAllPlayers(&size, &numberOfRobots, &numberOfObsticles, &numberOfBlackHoles,
         &numberOfTransportHoles, &percentRobot, &percentObstacle, &percentBlackHole,
         &percentTransportHole);

// FIXME --------------------
   // Populate arena with the number of each Player child object
//   populateArena(group, availablePositions, &size, &numberOfRobots, &numberOfObsticles,
//         &numberOfBlackHoles, &numberOfTransportHoles);
   srand((unsigned int) time(NULL));

   std::random_shuffle(&moveOrder[0], &moveOrder[size]);

   short int robots = numberOfRobots;
   numberOfRobots_blue = 0;
   numberOfRobots_red = 0;
   numberOfRobots_yellow = 0;
   numberOfRobots_green = 0;
   short int obstacles = numberOfObsticles;
//   int blackHoles = (*numberOfBlackHoles);
//   int transportHoles = (*numberOfTransportHoles);

    robots = 150;
    obstacles = 0;

    iterator = 0;
   while (robots || obstacles)
   {
      if (robots && (available == availablePositions[moveOrder[iterator]]))
      {
         // TODO - This is where the logic goes to figure out the different teams and stuff.
         // Right now it is only one type of robot
         group[moveOrder[iterator]]->deleteContent();
//         unsigned short int robotTeam = (unsigned int) (rand() % 4);
//         robotTeam *= 4;

         char team[] = {player_robot_blue_1,
                         player_robot_green_1,
                         player_robot_red_1,
                         player_robot_yellow_1};
         std::random_shuffle(&team[0], &team[4]);

         switch (team[0])
         {
             case player_robot_blue_1:
                group[moveOrder[iterator]]->setContent(new PlayerRobot(group[moveOrder[iterator]]->getXCordinate(),
                    group[moveOrder[iterator]]->getYCordinate(), player_robot_blue_1, 1, 1, 1, 10));
                content[group[moveOrder[iterator]]->getXCordinate()][group[moveOrder[iterator]]->getYCordinate()] = player_robot_blue_1;
                numberOfRobots_blue++;
                break;

            case player_robot_green_1:
                group[moveOrder[iterator]]->setContent(new PlayerRobot(group[moveOrder[iterator]]->getXCordinate(),
                    group[moveOrder[iterator]]->getYCordinate(), player_robot_green_1, 1, 1, 1, 10));
                content[group[moveOrder[iterator]]->getXCordinate()][group[moveOrder[iterator]]->getYCordinate()] = player_robot_green_1;
                numberOfRobots_green++;
                break;

            case player_robot_red_1:
                group[moveOrder[iterator]]->setContent(new PlayerRobot(group[moveOrder[iterator]]->getXCordinate(),
                    group[moveOrder[iterator]]->getYCordinate(), player_robot_red_1, 1, 1, 1, 10));
                content[group[moveOrder[iterator]]->getXCordinate()][group[moveOrder[iterator]]->getYCordinate()] = player_robot_red_1;
                numberOfRobots_red++;
                break;

            case player_robot_yellow_1:
                group[moveOrder[iterator]]->setContent(new PlayerRobot(group[moveOrder[iterator]]->getXCordinate(),
                    group[moveOrder[iterator]]->getYCordinate(), player_robot_yellow_1, 1, 1, 1, 10));
                content[group[moveOrder[iterator]]->getXCordinate()][group[moveOrder[iterator]]->getYCordinate()] = player_robot_yellow_1;
                numberOfRobots_yellow++;
                break;
         }

         robots--;
         availablePositions[moveOrder[iterator]] = canMove;
      }

      if (obstacles && (available == availablePositions[moveOrder[iterator]]))
      {
          group[moveOrder[iterator]]->deleteContent();
          group[moveOrder[iterator]]->setContent(new PlayerObstacle(group[moveOrder[iterator]]->getXCordinate(),
              group[moveOrder[iterator]]->getYCordinate(), player_obstacle));
          content[group[moveOrder[iterator]]->getXCordinate()][group[moveOrder[iterator]]->getYCordinate()] = player_obstacle;

          obstacles--;
          availablePositions[moveOrder[iterator]] = unavailable;
      }

      iterator++;
   }
//-----------------------------------------------


}

Arena::~Arena()
{
   for (int iterator = 0; iterator < size; iterator++)
   {
      delete group[iterator];
   }

   delete[] group;
}

int Arena::getNumberOfRows()
{
   return group[(size - 1)]->getXCordinate() + 1;
}

int Arena::getNumberOfColumns()
{
   return group[(size - 1)]->getYCordinate() + 1;
}

int Arena::getSize()
{
   return Arena::getNumberOfRows() * Arena::getNumberOfColumns();
}

int Arena::getCellNumber(int row, int column)
{
   return row * Arena::getNumberOfColumns() + column;
}

Cell* Arena::getCell(int row, int column)
{
   if (column > Arena::getNumberOfColumns() || row > Arena::getNumberOfRows())
   {
      return NULL;
   }
   else
   {
      return group[Arena::getCellNumber(row, column)];
   }
}

int Arena::getNumberOfRobots(void)
{
   return numberOfRobots;
}

int Arena::getNumberOfObsticles(void)
{
   return numberOfObsticles;
}

int Arena::getNumberOfBlackHoles(void)
{
   return numberOfBlackHoles;
}

int Arena::getNumberOfTransportHoles(void)
{
   return numberOfTransportHoles;
}

void Arena::setCellContentToPlayer(int row, int column, Player* player)
{
   group[Arena::getCellNumber(row, column)]->deleteContent();
   group[Arena::getCellNumber(row, column)]->setContent(player);
}

void Arena::setCellContentToGround(int row, int column)
{
   group[Arena::getCellNumber(row, column)]->setContent(new PlayerGround(row, column, player_ground));
}

Player_Type Arena::getWinningTeam()
{
   // blue wins
   if ((0 == numberOfRobots_red) &&
       (0 == numberOfRobots_green) &&
       (0 == numberOfRobots_yellow))
         return player_robot_blue_1;
   // red wins
   else if ((0 == numberOfRobots_blue) &&
             (0 == numberOfRobots_green) &&
             (0 == numberOfRobots_yellow))
         return player_robot_red_1;
   // green wins
   else if ((0 == numberOfRobots_blue) &&
             (0 == numberOfRobots_red) &&
             (0 == numberOfRobots_yellow))
         return  player_robot_green_1;
   // yellow wins
   else if ((0 == numberOfRobots_blue) &&
             (0 == numberOfRobots_red) &&
             (0 == numberOfRobots_green))
         return player_robot_yellow_1;
   // game goes on
   else
      return player_max;

}

// FIXME - The everything to do with the robot (like life and move) should have been done within the robot
// the arena should not tell the robot to move, it should tell the robot to take action and the robot
// decides what to do with itself.
void Arena::animate(void)
{
   numberOfRobots_blue = 0;
   numberOfRobots_red = 0;
   numberOfRobots_yellow = 0;
   numberOfRobots_green = 0;

   // fixme - movement isn't random
   for (short int iterator = 0; iterator < size; iterator++)
   {
      PlayerRobot* moveBot = (PlayerRobot*) group[iterator]->getContent();
      // check life remaining
      // FIXME - nasty hack to not kill obstacles
      if ((0 == moveBot->getTimeLifeRemaining()) && (moveBot->getPlayerType() != player_obstacle) &&
          (moveBot->getPlayerType() != player_ground))
      {
         availablePositions[iterator] = available;
//         content[moveBot->getXCoord()][moveBot->getYCoord()] = player_ground;
         Arena::setCellContentToPlayer(moveBot->getXCoord(), moveBot->getYCoord(),
                                       new PlayerGround(moveBot->getXCoord(), moveBot->getYCoord(), player_ground));
         continue;
      }

      if (canMove == availablePositions[iterator])
      {
         availablePositions[moveBot->move(this)] = hasMoved;
         if(group[iterator]->getContent()->getPlayerType() == moveBot->getPlayerType())
         {
            availablePositions[iterator] = hasMoved;
         }
         else
         {
            availablePositions[iterator] = available;
         }
      }
   }

   for (short int iterator = 0; iterator < size; iterator++)
   {
       if (availablePositions[iterator] == hasMoved)
       {
           availablePositions[iterator] = canMove;
       }
       content[group[iterator]->getXCordinate()][group[iterator]->getYCordinate()] = group[iterator]->getContent()->getPlayerType();

       if(content[group[iterator]->getXCordinate()][group[iterator]->getYCordinate()] == player_robot_blue_1) numberOfRobots_blue++;
       if(content[group[iterator]->getXCordinate()][group[iterator]->getYCordinate()] == player_robot_red_1) numberOfRobots_red++;
       if(content[group[iterator]->getXCordinate()][group[iterator]->getYCordinate()] == player_robot_green_1) numberOfRobots_green++;
       if(content[group[iterator]->getXCordinate()][group[iterator]->getYCordinate()] == player_robot_yellow_1) numberOfRobots_yellow++;
   }
}

//static void buildArenaWith(Cell** group, bool* availablePositions, int* size, int row, int column)
//{
//   // Build the arena with cells
//   unsigned int iterator = 0;
//   for (int _row = 0; _row < row; _row++)
//   {
//      for (int _col = 0; _col < column; _col++)
//      {
//         group[iterator] = new Cell(_row, _col);
//         iterator++;
//      }
//   }
//
//   // Initialize each cell to point to ground. Empty arena.
//   for (iterator = 0; iterator < (unsigned int) *size; iterator++)
//   {
//      availablePositions[iterator] = true;
//      group[iterator]->setContent(
//            new PlayerGround(group[iterator]->getXCordinate(), group[iterator]->getYCordinate(), player_ground));
//   }
//}

static void calculateNumberOfAllPlayers(short int* size, short int* numberOfRobots, short int* numberOfObsticles,
      short int* numberOfBlackHoles, short int* numberOfTransportHoles, short int* percentRobot,
      short int* percentObstacle, short int* percentBlackHole, short int* percentTransportHole)
{
   int sumOfPercentPlayers = (*percentRobot) + (*percentObstacle) + (*percentBlackHole)
         + (*percentTransportHole);
   int totalNumberOfPlayers = ((sumOfPercentPlayers * (*size)) / 100);

   *numberOfRobots = ((totalNumberOfPlayers * (*percentRobot)) / 100);
   *numberOfObsticles = ((totalNumberOfPlayers * (*percentObstacle)) / 100);
   *numberOfBlackHoles = ((totalNumberOfPlayers * (*percentBlackHole)) / 100);
   *numberOfTransportHoles = ((totalNumberOfPlayers * (*percentTransportHole)) / 100);
}

//static void populateArena(Cell** group, bool* availablePositions, int* size, int* numberOfRobots,
//      int* numberOfObsticles, int* numberOfBlackHoles, int* numberOfTransportHoles)
//{
//   srand((unsigned int) time(NULL));
//
//   int robots = (*numberOfRobots);
//   int obsticles = (*numberOfObsticles);
//   int blackHoles = (*numberOfBlackHoles);
//   int transportHoles = (*numberOfTransportHoles);
//
//   (void) obsticles;
//   (void) blackHoles;
//   (void) transportHoles;
//
//// TODO - This while is supposed to be for all the players but for now, its only robots
////   while(sumOfPercentPlayers)
//   while (robots)
//   {
//      unsigned int cellNumber = (unsigned int) (rand() % (*size));
//      if (robots && (true == availablePositions[cellNumber]))
//      {
//         // TODO - This is where the logic goes to figure out the different teams and stuff.
//         // Right now it is only one type of robot
//         group[cellNumber]->deleteContent();
//         group[cellNumber]->setContent(
//               new PlayerRobot(group[cellNumber]->getXCordinate(),
//                     group[cellNumber]->getYCordinate(), player_robot_blue_1, 1, 1, 1, 1));
//         robots--;
//         availablePositions[cellNumber] = false;
//      }
//   }
//}

