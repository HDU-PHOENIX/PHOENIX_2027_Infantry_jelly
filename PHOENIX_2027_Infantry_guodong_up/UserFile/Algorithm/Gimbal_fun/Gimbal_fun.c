//
// Created by 朱泽超 on 2026/11/8.
//

#include "Gimbal_fun.h"
#include "robot_config.h"

/**
 * @brief 最短路径规划
 * @note target 会被遥控器持续累加，与 now 的差值可能远大于一圈，
 *       这里用 fmodf 一次折算到位，避免 while 空转（数值很大时会卡住控制周期）
 */
static void shortest_way_find(float *now_position, float *target_position)
{
    float delta = *target_position - *now_position;
    if (delta > M_PI || delta < -M_PI)
    {
        delta = fmodf(delta, 2.0f * (float)M_PI);
        if (delta > M_PI)
        {
            delta -= 2.0f * (float)M_PI;
        }
        else if (delta < -M_PI)
        {
            delta += 2.0f * (float)M_PI;
        }
    }
    *target_position = *now_position + delta;
}

/**
 * @brief 云台状态函数
 * @return 云台状态枚举
 */

static gimbal_mode_e gimbal_mode_fun(rm_massage_s *rm_massage)
{
    if (rm_massage == NULL)
    {
        return GIMBAL_DISABLE;
    }

    switch (*rm_massage->sb)
    {
    case 3:                                 //拨杆中
        return GIMBAL_NORMAL;
    case 2:                                 //拨杆下
        return GIMBAL_FOLD;
    case 1:                                 //拨杆上
        if (*rm_massage->sc != 2)
        {
            return GIMBAL_DISABLE;
        }
        else
        {
            return GIMBAL_NORMAL;
        }
    default:                                //遥控器掉线/数据异常
        return GIMBAL_DISABLE;
    }
}




/**
 * @brief 折叠函数
 * @note 折叠过程未完成返回0，已完成返回1
 */
static bool gimbal_pitch_fold_fun(gimbal_message_s *gimbal_message, quaternions_struct_t Quater)
{
    static float delta = 0.0f; //大pitch现在角度与垂直角度差值

    gimbal_message->big_pitch.target_position = BIG_PITCH_FOLD_POSITION;
    shortest_way_find(gimbal_message->big_pitch.now_position, &gimbal_message->big_pitch.target_position);

    delta = *gimbal_message->small_pitch.now_position - BIG_PITCH_NORMAL_POSITION;
    gimbal_message->small_pitch.target_position = SMALL_PITCH_NORMAL_POSITION - delta;
    shortest_way_find(gimbal_message->small_pitch.now_position, &gimbal_message->small_pitch.target_position);

    if ((fabsf(*gimbal_message->small_pitch.now_position - SMALL_PITCH_FOLD_POSITION) <= 0.001f) &&
        (fabsf(*gimbal_message->big_pitch.now_position - BIG_PITCH_FOLD_POSITION) <= 0.001f))
    {
        return true;
    }
    return false;
}

/**
 * @brief 折叠时yaw轴死区限制函数
 * @return 限制后的yaw轴目标值
 */
static float gimbal_yaw_limit_fun(gimbal_message_s *gimbal_message)
{
    if ((YAW_FOLD_LIMIT_UP * YAW_FOLD_LIMIT_DOWN) < -3.0f)     //分类，若灯条位置恰在PI~-PI处...不在...
    {
        if ((YAW_FOLD_LIMIT_UP + YAW_FOLD_LIMIT_DOWN) >= 0.0f)
        {
            if (gimbal_message->yaw.target_position < (YAW_FOLD_LIMIT_UP + (2.0f * M_PI + YAW_FOLD_LIMIT_DOWN - YAW_FOLD_LIMIT_UP)/2.0f) &&
                gimbal_message->yaw.target_position > YAW_FOLD_LIMIT_UP)
                gimbal_message->yaw.target_position = YAW_FOLD_LIMIT_UP;
            else
                gimbal_message->yaw.target_position = YAW_FOLD_LIMIT_DOWN;
        }
        if ((YAW_FOLD_LIMIT_UP + YAW_FOLD_LIMIT_DOWN) < 0.0f)
        {
            if (gimbal_message->yaw.target_position > (YAW_FOLD_LIMIT_DOWN - (2.0f * M_PI + YAW_FOLD_LIMIT_DOWN - YAW_FOLD_LIMIT_UP)/2.0f) &&
                gimbal_message->yaw.target_position < YAW_FOLD_LIMIT_DOWN)
                gimbal_message->yaw.target_position = YAW_FOLD_LIMIT_UP;
            else
                gimbal_message->yaw.target_position = YAW_FOLD_LIMIT_DOWN;
        }
    }
    else
    {
        if (gimbal_message->yaw.target_position > ((YAW_FOLD_LIMIT_UP + YAW_FOLD_LIMIT_DOWN)/2.0f) &&
            gimbal_message->yaw.target_position < YAW_FOLD_LIMIT_DOWN)
        {
            gimbal_message->yaw.target_position = YAW_FOLD_LIMIT_UP;
        }
        if (gimbal_message->yaw.target_position < ((YAW_FOLD_LIMIT_UP + YAW_FOLD_LIMIT_DOWN)/2.0f) &&
            gimbal_message->yaw.target_position > YAW_FOLD_LIMIT_DOWN)
        {
            gimbal_message->yaw.target_position = YAW_FOLD_LIMIT_DOWN;
        }
    }
    shortest_way_find(gimbal_message->yaw.now_position, &gimbal_message->yaw.target_position);
    return gimbal_message->yaw.target_position;
}

/**
 * @brief 云台控制计算函数
 * @return
 */
static bool gimbal_control_fun(gimbal_message_s * gimbal_message, rm_massage_s *rm_massage, quaternions_struct_t Quater)
{
    if (gimbal_message->gimbal_mode == GIMBAL_DISABLE)  //电机全设失能
    {
        gimbal_message->yaw.gimbal_motor_state = 0U;
        gimbal_message->big_pitch.gimbal_motor_state = 0U;
        gimbal_message->small_pitch.gimbal_motor_state = 0U;
    }
    if (gimbal_message->gimbal_mode == GIMBAL_NORMAL)   //电机全设使能
    {
        gimbal_message->yaw.gimbal_motor_state = 1U;
        gimbal_message->big_pitch.gimbal_motor_state = 1U;
        gimbal_message->small_pitch.gimbal_motor_state = 1U;

        gimbal_message->big_pitch.target_position = BIG_PITCH_NORMAL_POSITION;
        shortest_way_find(gimbal_message->big_pitch.now_position, &gimbal_message->big_pitch.target_position);
        gimbal_message->yaw.target_position += *rm_massage->rx * SENSITIVITY;
        gimbal_message->small_pitch.target_position += *rm_massage->ry * SENSITIVITY;

        if (gimbal_message->small_pitch.target_position > SMALL_PITCH_LIMIT_UP)
            gimbal_message->small_pitch.target_position = SMALL_PITCH_LIMIT_UP;
        if (gimbal_message->small_pitch.target_position < SMALL_PITCH_LIMIT_DOWN)
            gimbal_message->small_pitch.target_position = SMALL_PITCH_LIMIT_DOWN;

        shortest_way_find(gimbal_message->yaw.now_position, &gimbal_message->yaw.target_position);
        shortest_way_find(gimbal_message->small_pitch.now_position, &gimbal_message->small_pitch.target_position);
    }
    if (gimbal_message->gimbal_mode == GIMBAL_FOLD)     //折叠时yaw轴设置死区
    {
        gimbal_message->yaw.gimbal_motor_state = 1U;
        gimbal_message->big_pitch.gimbal_motor_state = 1U;
        gimbal_message->small_pitch.gimbal_motor_state = 1U;

        gimbal_message->yaw.target_position += *rm_massage->rx * SENSITIVITY;
        gimbal_yaw_limit_fun(gimbal_message);
        gimbal_pitch_fold_fun(gimbal_message, Quater);
    }

    return true;
}

/**
 * @云台函数（包含初始化缓慢抬升至正常态）
 * @param 云台数据
 * @param 遥控器数据
 * @return 云台接收数据是否正常
 */
bool gimbal_fun(gimbal_message_s *gimbal_message, rm_massage_s *rm_massage, quaternions_struct_t Quater)
{
    if (gimbal_message == NULL || rm_massage == NULL)
    {
        return false;
    }

    gimbal_message->gimbal_mode = gimbal_mode_fun(rm_massage);

    if (gimbal_message->gimbal_mode == GIMBAL_DISABLE) //失能后重设初始化标志
    {
        gimbal_message->yaw.gimbal_motor_state = 0U;
        gimbal_message->big_pitch.gimbal_motor_state = 0U;
        gimbal_message->small_pitch.gimbal_motor_state = 0U;
        gimbal_message->gimbal_init_state = false;
    }
    
    if (gimbal_message->gimbal_mode != GIMBAL_DISABLE)
    {
        gimbal_message->yaw.gimbal_motor_state = 1U;
        gimbal_message->big_pitch.gimbal_motor_state = 1U;
        gimbal_message->small_pitch.gimbal_motor_state = 1U;

        if (gimbal_message->gimbal_init_state) //正常情况下
        {
            gimbal_control_fun(gimbal_message, rm_massage, Quater);
        }
        else                                   //当云台已使能但未初始化时：进行初始化，并在初始化完成后置初始化标志为ture
        {
            /*
            gimbal_message->yaw.target_position = *gimbal_message->yaw.now_position;
            gimbal_message->big_pitch.target_position = *gimbal_message->big_pitch.now_position;
            gimbal_message->small_pitch.target_position = *gimbal_message->small_pitch.now_position;
            if (fabsf(Quater.pitch) > 0.005f)
            {
                gimbal_message->small_pitch.target_position += 0.005f;
                shortest_way_find(gimbal_message->small_pitch.now_position, &gimbal_message->small_pitch.target_position);
            }
            else
            {
                gimbal_message->gimbal_init_state = true;
            }
            */
            gimbal_message->gimbal_init_state = true;
        }
    }
    //上时刻位置记录
    gimbal_message->yaw.last_position = *gimbal_message->yaw.now_position;
    gimbal_message->big_pitch.last_position = *gimbal_message->big_pitch.now_position;
    gimbal_message->small_pitch.last_position = *gimbal_message->small_pitch.now_position;

    return true;
}

/**
 * @brief 遥控器归一化注册函数
 *
 */
rm_massage_s *rm_register_fun(Et08aInstance_s *et08a_instance)
{
    static rm_massage_s rm_massage;

    rm_massage.sa = &et08a_instance->sa;
    rm_massage.sb = &et08a_instance->sb;
    rm_massage.sc = &et08a_instance->sc;
    rm_massage.sd = &et08a_instance->sd;

    rm_massage.lx = &et08a_instance->lx;
    rm_massage.ly = &et08a_instance->ly;
    rm_massage.rx = &et08a_instance->rx;
    rm_massage.ry = &et08a_instance->ry;

    rm_massage.ld = &et08a_instance->ld;
    rm_massage.rd = &et08a_instance->rd;

    return &rm_massage;
}

/**
 * @brief 云台电机注册函数
 * @note 为了给文件提供统一化数据接口。若后续修改电机在此处修改结构体类型
 */
gimbal_message_s *gimbal_register_fun(DmMotorInstance_s *yaw,
                                      DmMotorInstance_s *big_pitch,
                                      RsMotorInstance_s *small_pitch)
{
    /* 用静态对象代替堆分配：不会失败、不占 FreeRTOS 堆，且 BSS 零初始化即 GIMBAL_DISABLE */
    static gimbal_message_s gimbal_message;
    (void)yaw;
    (void)big_pitch;
    (void)small_pitch;

    gimbal_message.yaw.now_position = &yaw->message.out_position;
    gimbal_message.big_pitch.now_position = &big_pitch->message.out_position;
    gimbal_message.small_pitch.now_position = &small_pitch->message.position;

    return &gimbal_message;
}


