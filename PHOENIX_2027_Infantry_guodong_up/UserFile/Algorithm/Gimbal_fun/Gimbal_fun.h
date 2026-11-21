//
// Created by 朱泽超 on 2026/11/8.
//

#ifndef PHOENIX_2027_INFANTRY_GUODONG_UP_GIMBAL_FUN_H
#define PHOENIX_2027_INFANTRY_GUODONG_UP_GIMBAL_FUN_H

#include "app_ins_task.h"
#include "dev_dr16.h"
#include "dev_et08a.h"
#include "dev_motor_dji.h"
#include "dev_motor_dm.h"
#include "dev_motor_rs.h"

#include <stdbool.h>
# define Et08a

#ifndef M_PI
#define M_PI 3.1415926f
#endif
//遥控器灵敏度
#define SENSITIVITY (0.001f/660.0f)
//小pitch限位
#define SMALL_PITCH_LIMIT_UP 0.0f           //小pitch上限
#define SMALL_PITCH_LIMIT_DOWN 0.0f         //小pitch下限
#define SMALL_PITCH_FOLD_POSITION 0.0f      //小pitch折叠位置
//大pitch位置
#define BIG_PITCH_NORMAL_POSITION 0.0f  //大pitch垂直位置
#define BIG_PITCH_FOLD_POSITION 1.0f    //大pitch折叠位置
//yaw轴折叠时限位
#define YAW_FOLD_LIMIT_UP 0.0f          //yaw灯条死区上限
#define YAW_FOLD_LIMIT_DOWN 0.0f        //yaw灯条死区下限，up>down

//云台状态枚举
typedef enum
{
    GIMBAL_DISABLE = 0U,  //失能
    GIMBAL_NORMAL = 1U,   //正常模式
    GIMBAL_FOLD = 2U      //折叠模式
}gimbal_mode_e;

//云台电机控制信息
typedef struct
{
    bool  gimbal_motor_state;  //0失能，1使能

    float *now_position;        //电机当前编码器值
    float last_position;       //电机上时刻编码器值
    float target_position;     //电机目标编码器值
}gimbal_motor_message_s;

//遥控器接收信息
typedef struct
{
    //开关
    int8_t *sa;
    int8_t *sb;
    int8_t *sc;
    int8_t *sd;
    //摇杆
    int16_t *lx;
    int16_t *ly;
    int16_t *rx;
    int16_t *ry;
    //拨轮
    int16_t *ld;
    int16_t *rd;
}rm_massage_s;

//云台控制信息汇总
typedef struct
{
    bool gimbal_init_state;           //云台初始化状态标志，0为未初始化，1为已初始化
    gimbal_mode_e gimbal_mode;         //云台状态

    gimbal_motor_message_s yaw;          //yaw轴控制信息
    gimbal_motor_message_s big_pitch;    //大pitch轴控制信息
    gimbal_motor_message_s small_pitch;  //小pitch轴控制信息
}gimbal_message_s;

/**
 * @云台函数（包含初始化缓慢抬升至正常态）
 * @param 云台数据；遥控器数据
 * @return 云台接收数据是否正常
 */
bool gimbal_fun(gimbal_message_s *gimbal_message, rm_massage_s *rm_massage, quaternions_struct_t Quater);

/**
 * @brief 云台电机迁移函数
 * @note 为了给文件提供统一化数据接口。若后续修改电机在此处修改结构体类型
 */
gimbal_message_s *gimbal_register_fun(DmMotorInstance_s *yaw, DmMotorInstance_s *big_pitch, RsMotorInstance_s *small_pitch);

/**
 * @brief 遥控器归一化注册函数
 *
 */
rm_massage_s *rm_register_fun(Et08aInstance_s *et08a_instance);

#endif //PHOENIX_2027_INFANTRY_GUODONG_UP_GIMBAL_FUN_H
