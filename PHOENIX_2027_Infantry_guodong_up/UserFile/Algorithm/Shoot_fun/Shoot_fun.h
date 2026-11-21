//
// Created by 朱泽超 on 2026/11/16.
//

#ifndef PHOENIX_2027_INFANTRY_GUODONG_UP_SHOOT_FUN_H
#define PHOENIX_2027_INFANTRY_GUODONG_UP_SHOOT_FUN_H


#include <stdbool.h>

#include "dev_et08a.h"
#include "dev_motor_dji.h"
#include "Gimbal_fun.h"

//摩擦轮速度（rpm）
#define WHEEL_VELOCITY 3600
//拨弹盘频率
#define DIAL_FREQUENCY 8.0f

//云台状态枚举
typedef enum
{
    SHOOT_DISABLE = 0U,  //失能
    SHOOT_SINGLE = 1U,   //单发
    SHOOT_CONTINUOUS = 2U,//连发
    SHOOT_AUTOAIM = 3U   //自瞄
}shoot_mode_e;

//发射机构电机信息
typedef struct
{
    bool  shoot_motor_state;   //0失能，1使能

    float *now_velocity;        //电机当前编码器值
    float target_velocity;     //电机目标编码器值

    float *now_position;        //电机当前编码器值
    float last_position;       //电机上时刻编码器值
    float target_position;     //电机目标编码器值
}shoot_motor_message_s;

//
typedef struct
{
    shoot_mode_e shoot_mode;

    shoot_motor_message_s left_motor;
    shoot_motor_message_s right_motor;
    shoot_motor_message_s dial;
}shoot_message_s;

shoot_mode_e shoot_mode_fun(shoot_message_s *shoot_message,
                            gimbal_message_s *gimbal_message,
                            rm_massage_s *rm_massage);

bool shoot_control_fun(shoot_message_s *shoot_message, rm_massage_s *rm_massage);

shoot_message_s *shoot_register_fun(DjiMotorInstance_s *left_motor,
                                    DjiMotorInstance_s *right_motor,
                                    DjiMotorInstance_s *dial);
#endif //PHOENIX_2027_INFANTRY_GUODONG_UP_SHOOT_FUN_H
