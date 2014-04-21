#ifndef CUSTOMTYPES_H_INCLUDED
#define CUSTOMTYPES_H_INCLUDED

#define TOTAL_ROWS 14
#define TOTAL_COLUMNS 20
#define BITMAP_DIMENSIONS 45

typedef enum
{
    player_robot_blue_1 = 0x00,
    player_robot_blue_2,
    player_robot_blue_3,
    player_robot_blue_4,
    player_robot_green_1 = 0x04,
    player_robot_green_2,
    player_robot_green_3,
    player_robot_green_4,
    player_robot_red_1 = 0x08,
    player_robot_red_2,
    player_robot_red_3,
    player_robot_red_4,
    player_robot_yellow_1 = 0x10,
    player_robot_yellow_2,
    player_robot_yellow_3,
    player_robot_yellow_4,
    player_robot_max,
    player_ground = 0x20,
    player_obstacle = 0x40,
    player_max
} Player_Type;

#endif // CUSTOMTYPES_H_INCLUDED
