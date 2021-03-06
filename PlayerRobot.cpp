#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "PlayerRobot.h"

PlayerRobot::PlayerRobot()
{
}

PlayerRobot::PlayerRobot(short int x, short int y, Player_Type type, short int powerLevel,
                  short int feed, short int mate, short int life) : Player(x, y, type)
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

void PlayerRobot::decrementMate()
{
   timeToReproduce--;
}

int PlayerRobot::move(Arena* arena)
{
   // TODO - also decrement other times
   this->decrementLife();
   this->decrementMate();

   short int current_x;
   short int current_y;
   short int next_x;
   short int next_y;

   next_x = current_x = this->getXCoord();
   next_y = current_y = this->getYCoord();

   enum
   {
       stay = 0x00,
       north = 0x01,
       south = 0x02,
       east = 0x04,
       west = 0x08,
       doNothing = 0x10, // Lowest priority
       move = 0x20,
       attack = 0x40,
       reproduce = 0x80 // Highest priority
   };

   char moveDirection[] = {north, south, east, west};
   std::random_shuffle(&moveDirection[0], &moveDirection[4]);
   char moveTo = stay | doNothing; // least sig nibble = direction, most sig nibble = action

   // Priority filter for the move. Looks at all the NSEW cells anc choses where it will
   // move based on priority
   for (char look = 0; look < 4; look++)
   {
        Player_Type peekType;

        if (moveDirection[look] == north)
        {
            next_x--;
            if (0 > next_x)
                next_x = arena->getNumberOfRows() - 1;
            peekType = arena->getCell(next_x, next_y)->getContent()->getPlayerType();

            // comparison is done only on level 1 of each color
            // Each if increases in priority
            // move
            if ((peekType == player_ground) && (moveTo < move))
                moveTo = moveDirection[look] | move;

            // Attack regarless of level
            // Logic is wrong in the second condition, it should be  peekType < player_robot_max, but it
            // ain't working for some reason
            if ((peekType != this->getPlayerType()) && (peekType != player_obstacle) && (peekType != player_ground) && (moveTo < attack))
                moveTo = moveDirection[look] | move;

            // reproduce
            if ((peekType == this->getPlayerType()) && (timeToReproduce <= 0) && (moveTo < reproduce) && (peekType != player_obstacle) && (peekType != player_ground))
               moveTo = stay | reproduce;
        }

        if (moveDirection[look] == south)
        {
            next_x++;
            if((arena->getNumberOfRows() - 1) < next_x)
                next_x = 0;
            peekType = arena->getCell(next_x, next_y)->getContent()->getPlayerType();

            // comparison is done only on level 1 of each color
            // Each if increases in priority
            // move
            if ((peekType == player_ground) && (moveTo < move))
                moveTo = moveDirection[look] | move;

            // Attack regarless of level
            if ((peekType != this->getPlayerType()) && (peekType != player_obstacle) && (peekType != player_ground) && (moveTo < attack))
                moveTo = moveDirection[look] | move;

            // reproduce
            if ((peekType == this->getPlayerType()) && (timeToReproduce <= 0) && (moveTo < reproduce) && (peekType != player_obstacle) && (peekType != player_ground))
               moveTo = stay | reproduce;
        }

        if (moveDirection[look] == east)
        {
            next_y++;
            if((arena->getNumberOfColumns() - 1) < next_y)
                next_y = 0;
            peekType = arena->getCell(next_x, next_y)->getContent()->getPlayerType();

            // comparison is done only on level 1 of each color
            // Each if increases in priority
            // move
            if ((peekType == player_ground) && (moveTo < move))
                moveTo = moveDirection[look] | move;

            // Attack regarless of level
            // todo - implement attack and reproduce
            if ((peekType != this->getPlayerType()) && (peekType != player_obstacle) && (peekType != player_ground) && (moveTo < attack))
                moveTo = moveDirection[look] | move;

            // reproduce
            if ((peekType == this->getPlayerType()) && (timeToReproduce <= 0) && (moveTo < reproduce) && (peekType != player_obstacle) && (peekType != player_ground))
               moveTo = stay | reproduce;
        }

        if (moveDirection[look] == west)
        {
            next_y--;
            if(0 > next_y)
                next_y = (arena->getNumberOfColumns() - 1);
            peekType = arena->getCell(next_x, next_y)->getContent()->getPlayerType();

            // comparison is done only on level 1 of each color
            // Each if increases in priority
            // move
            if ((peekType == player_ground) && (moveTo < move))
                moveTo = moveDirection[look] | move;

            // Attack regarless of level
            // todo - implement attack and reproduce
            if ((peekType != this->getPlayerType()) && (peekType != player_obstacle) && (peekType != player_ground) && (moveTo < attack))
                moveTo = moveDirection[look] | move;

            // reproduce
            if ((peekType == this->getPlayerType()) && (timeToReproduce <= 0) && (moveTo < reproduce) && (peekType != player_obstacle) && (peekType != player_ground))
               moveTo = stay | reproduce;
        }
        next_x = current_x;
        next_y = current_y;
   }

    if ((moveTo & move) == move)
    {
        if ((moveTo & north) == north)
        {
            next_x--;
            if (0 > next_x) next_x = arena->getNumberOfRows() - 1;
        }

        if ((moveTo & south) == south)
        {
            next_x++;
            if((arena->getNumberOfRows() - 1) < next_x) next_x = 0;
        }

        if ((moveTo & east) == east)
        {
            next_y++;
            if((arena->getNumberOfColumns() - 1) < next_y) next_y = 0;
        }

        if ((moveTo & west) == west)
        {
            next_y--;
            if(0 > next_y) next_y = (arena->getNumberOfColumns() - 1);
        }
    }

    if ((moveTo & reproduce) == reproduce)
    {// Look for first available ground
      for (char look = 0; look < 4; look++)
      {
         Player_Type peekType;

         srand((unsigned int) time(NULL));
         short int lifetime = rand() % 21 + 10;
         short int reproducetime = rand() % 4 + 1;

         if (moveDirection[look] == north)
         {
            next_x--;
            if (0 > next_x)
               next_x = arena->getNumberOfRows() - 1;

            peekType = arena->getCell(next_x, next_y)->getContent()->getPlayerType();

            if (peekType == player_ground)
            {
               arena->setCellContentToPlayer(next_x, next_y, new PlayerRobot(next_x, next_y, this->getPlayerType(),
                                             1, 1, reproducetime, lifetime));
               return arena->getCellNumber(next_x, next_y);
            }
         }

         if (moveDirection[look] == south)
         {
            next_x++;
            if((arena->getNumberOfRows() - 1) < next_x)
               next_x = 0;

            peekType = arena->getCell(next_x, next_y)->getContent()->getPlayerType();

            if (peekType == player_ground)
            {
               arena->setCellContentToPlayer(next_x, next_y, new PlayerRobot(next_x, next_y, this->getPlayerType(),
                                             1, 1, reproducetime, lifetime));
               return arena->getCellNumber(next_x, next_y);
            }
         }

         if (moveDirection[look] == east)
         {
            next_y++;
            if((arena->getNumberOfColumns() - 1) < next_y)
               next_y = 0;

            peekType = arena->getCell(next_x, next_y)->getContent()->getPlayerType();

            if (peekType == player_ground)
            {
               arena->setCellContentToPlayer(next_x, next_y, new PlayerRobot(next_x, next_y, this->getPlayerType(),
                                             1, 1, reproducetime, lifetime));
               return arena->getCellNumber(next_x, next_y);
            }
         }

         if (moveDirection[look] == west)
         {
            next_y--;
            if(0 > next_y)
               next_y = (arena->getNumberOfColumns() - 1);

            peekType = arena->getCell(next_x, next_y)->getContent()->getPlayerType();

            if (peekType == player_ground)
            {
               arena->setCellContentToPlayer(next_x, next_y, new PlayerRobot(next_x, next_y, this->getPlayerType(),
                                             1, 1, reproducetime, lifetime));
               return arena->getCellNumber(next_x, next_y);
            }
         }
         next_x = current_x;
         next_y = current_y;
      }
    }

   if ((moveTo & reproduce) == reproduce) return arena->getCellNumber(current_x, current_y);

   arena->setCellContentToPlayer(next_x, next_y, this);
   arena->setCellContentToGround(current_x, current_y);

   this->setXCoord(next_x);
   this->setYCoord(next_y);

   return arena->getCellNumber(next_x, next_y);
}

