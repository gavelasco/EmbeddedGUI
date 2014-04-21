#include "Player.h"

Player::Player()
{
}

Player::Player(int x, int y, Player_Type type)
{
   x_coord = x;
   y_coord = y;
   playerType = type;
}

Player::~Player()
{
}

int Player::getXCoord()
{
   return x_coord;
}

int Player::getYCoord()
{
   return y_coord;
}

Player_Type Player::getPlayerType()
{
   return playerType;
}

void Player::setXCoord(int x)
{
   x_coord = x;
}
void Player::setYCoord(int y)
{
   y_coord = y;
}
