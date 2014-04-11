#include <cstdlib>
#include <ctime>

#include "PlayerRobot.h"

PlayerRobot::PlayerRobot()
{
}

PlayerRobot::PlayerRobot(int x, int y, string color, char type, int powerLevel, int feed, int mate,
      int life) :
      Player(x, y, color, type)
{
   power = powerLevel;
   timeToFeed = feed;
   timeToReproduce = mate;
   timeLifeRemaining = life;

   movePriority = movePriority_reproduce;
}

PlayerRobot::~PlayerRobot()
{
}

int PlayerRobot::getPower()
{
   return power;
}

int PlayerRobot::getTimeToFeed()
{
   return timeToFeed;
}

int PlayerRobot::getTimeToMate()
{
   return timeToReproduce;
}

int PlayerRobot::getTimeLifeRemaining()
{
   return timeLifeRemaining;
}

void PlayerRobot::decrementLife()
{
   timeLifeRemaining--;
}

int PlayerRobot::move(Arena* arena)
{
   // TODO - also decrement other times
   this->decrementLife();

   // TODO - figure out move logic.
   // This will try to reproduce first, then feed, then move
   int prev_x;
   int prev_y;
   int moveTo_x;
   int moveTo_y;

   moveTo_x = prev_x = this->getXCoord();
   moveTo_y = prev_y = this->getYCoord();


   // TODO - this will probably change into a switch statement so that each
   // priority of move can be tested.
//   if (movePriority_reproduce == movePriority)
   if(true)
   {
      srand((unsigned int)time(NULL));

      // TODO - for now, the robots will just move randomly
      int randNum = rand() % 4;

      //Move north
//      if (TEAM_1
//            & arena->getCell((this->getXCoord() + 1), this->getYCoord())->getContent()->getPlayerType())
      if(0 == randNum)
      {
         moveTo_x--;

         // Wrap around
         if(0 > moveTo_x)
         {
            moveTo_x = arena->getNumberOfRows() - 1;
         }
      }

      // move south
      if(1 == randNum)
      {
         moveTo_x++;

         // Wrap around
         if((arena->getNumberOfRows() - 1) < moveTo_x)
         {
            moveTo_x = 0;
         }
      }

      // move east
      if(2 == randNum)
      {
         moveTo_y++;

         if((arena->getNumberOfColumns() - 1) < moveTo_y)
         {
            moveTo_y = 0;
         }
      }

      // move west
      if(3 == randNum)
      {
         moveTo_y--;

         if(0 > moveTo_y)
         {
            moveTo_y = (arena->getNumberOfColumns() - 1);
         }
      }
   }

   arena->setCellContentToPlayer(moveTo_x, moveTo_y, this);
   arena->setCellContentToGround(prev_x, prev_y);

   this->setXCoord(moveTo_x);
   this->setYCoord(moveTo_y);

   return arena->getCellNumber(moveTo_x, moveTo_y);
}

