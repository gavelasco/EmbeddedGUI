#ifndef PLAYERROBOT_H_
#define PLAYERROBOT_H_

#include "Player.h"
#include "Arena.h"

class PlayerRobot: public Player
{
   public:
      PlayerRobot();
      PlayerRobot(int x, int y, string color, Player_Type type, int powerLevel, int feed, int mate, int life);

      int getPower();
      int getTimeToFeed();
      int getTimeToMate();
      int getTimeLifeRemaining();

      void decrementLife();
      int move(Arena* arena);

      virtual ~PlayerRobot();

   private:
      int power;
      int timeToFeed;
      int timeToReproduce;
      int timeLifeRemaining;

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
