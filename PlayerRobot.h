#ifndef PLAYERROBOT_H_
#define PLAYERROBOT_H_

#include "Player.h"
#include "Arena.h"

class PlayerRobot: public Player
{
   public:
      PlayerRobot();
      PlayerRobot(short int x, short int y, Player_Type type, short int powerLevel,
                  short int feed, short int mate, short int life);

      int getPower();
      int getTimeToFeed();
      int getTimeToMate();
      int getTimeLifeRemaining();

      void decrementLife();
      void decrementMate();
      int move(Arena* arena);

      virtual ~PlayerRobot();

   private:
      short int power;
      short int timeToFeed;
      short int timeToReproduce;
      short int timeLifeRemaining;

      // In increasing numerical order of priority
      typedef enum
      {
         movePriority_move = 0,
         movePriority_feed,
         movePriority_reproduce
      } MovePriority;

      MovePriority movePriority;
};

#endif /* PLAYERROBOT_H_ */
