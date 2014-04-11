// TODO - Add rest of players

#include <cstdlib>
#include <cstdio>
#include <ctime>

#include "Arena.h"
#include "PlayerRobot.h"
#include "PlayerGround.h"
//#include "PlayerObstacle.h"
//#include "PlayerBlackHole.h"
//#include "PlayerTransportHole.h"

// Helper function declarations
static void buildArenaWith(Cell** group, bool* availablePositions, int* size, int row, int column);
static void calculateNumberOfAllPlayers(int* size, int* numberOfRobots, int* numberOfObsticles,
      int* numberOfBlackHoles, int* numberOfTransportHoles, short int* percentRobot,
      short int* percentObstacle, short int* percentBlackHole, short int* percentTransportHole);
static void populateArena(Cell** group, bool* availablePositions, int* size, int* numberOfRobots,
      int* numberOfObsticles, int* numberOfBlackHoles, int* numberOfTransportHoles);

Arena::Arena(short int row, short int column, short int percentRobot, short int percentObstacle,
      short int percentBlackHole, short int percentTransportHole)
{
   size = row * column;
   group = new Cell*[size];

   // Create all the Cell objects and have them point to a Ground object
   buildArenaWith(group, availablePositions, &size, row, column);

   // Calculate the number of all players with the percentages given
   calculateNumberOfAllPlayers(&size, &numberOfRobots, &numberOfObsticles, &numberOfBlackHoles,
         &numberOfTransportHoles, &percentRobot, &percentObstacle, &percentBlackHole,
         &percentTransportHole);

   // Populate arena with the number of each Player child object
   populateArena(group, availablePositions, &size, &numberOfRobots, &numberOfObsticles,
         &numberOfBlackHoles, &numberOfTransportHoles);
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
   group[Arena::getCellNumber(row, column)]->setContent(new PlayerGround(row, column, ".", GROUND));
}

void Arena::animate(void)
{
   for (int iterator = 0; iterator < size; iterator++)
   {
      if (!availablePositions[iterator])
      {
         // FIXME - this is a bad idea, but I know that right now there are only robots
         // inside.
         PlayerRobot* moveBot = (PlayerRobot*) group[iterator]->getContent();
         availablePositions[iterator] = true;
         availablePositions[moveBot->move(this)] = false;
         break;  // FIXME - this is hella wrong.
      }
   }
}

static void buildArenaWith(Cell** group, bool* availablePositions, int* size, int row, int column)
{
   // Build the arena with cells
   unsigned int iterator = 0;
   for (int _row = 0; _row < row; _row++)
   {
      for (int _col = 0; _col < column; _col++)
      {
         group[iterator] = new Cell(_row, _col);
         iterator++;
      }
   }

   // Initialize each cell to point to ground. Empty arena.
   for (iterator = 0; iterator < (unsigned int) *size; iterator++)
   {
      availablePositions[iterator] = true;
      group[iterator]->setContent(
            new PlayerGround(group[iterator]->getXCordinate(), group[iterator]->getYCordinate(),
                  "Ground.bmp", GROUND));
   }
}

static void calculateNumberOfAllPlayers(int* size, int* numberOfRobots, int* numberOfObsticles,
      int* numberOfBlackHoles, int* numberOfTransportHoles, short int* percentRobot,
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

static void populateArena(Cell** group, bool* availablePositions, int* size, int* numberOfRobots,
      int* numberOfObsticles, int* numberOfBlackHoles, int* numberOfTransportHoles)
{
   srand((unsigned int) time(NULL));

   int robots = (*numberOfRobots);
   int obsticles = (*numberOfObsticles);
   int blackHoles = (*numberOfBlackHoles);
   int transportHoles = (*numberOfTransportHoles);

   (void) obsticles;
   (void) blackHoles;
   (void) transportHoles;

// TODO - This while is supposed to be for all the players but for now, its only robots
//   while(sumOfPercentPlayers)
   while (robots)
   {
      unsigned int cellNumber = (unsigned int) (rand() % (*size));
      if (robots && (true == availablePositions[cellNumber]))
      {
         // TODO - This is where the logic goes to figure out the different teams and stuff.
         // Right now it is only one type of robot
         group[cellNumber]->deleteContent();
         group[cellNumber]->setContent(
               new PlayerRobot(group[cellNumber]->getXCordinate(),
                     group[cellNumber]->getYCordinate(), "RL1Blue.bmp", TEAM_1, 1, 1, 1, 1));
         robots--;
         availablePositions[cellNumber] = false;
      }
   }
}
