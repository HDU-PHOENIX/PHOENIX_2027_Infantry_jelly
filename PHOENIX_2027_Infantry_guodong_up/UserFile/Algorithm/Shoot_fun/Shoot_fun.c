//
// Created by 朱泽超 on 2026/11/16.
//

#include "Shoot_fun.h"
#include "robot_config.h"

/**
 *
 * @param shoot_message
 * @param gimbal_message
 * @param rm_massage
 * @return
 */
shoot_mode_e shoot_mode_fun(shoot_message_s *shoot_message,
                            gimbal_message_s *gimbal_message,
                            rm_massage_s *rm_massage)
{
    if (rm_massage == NULL)
    {
        shoot_message->shoot_mode = SHOOT_DISABLE;
        return SHOOT_DISABLE;
    }
/*
    if (gimbal_message->gimbal_mode == GIMBAL_FOLD)
    {
        shoot_message->shoot_mode = SHOOT_DISABLE;
        return SHOOT_DISABLE;
    }
*/
    if (*rm_massage->sc == 3)
    {
        if (*rm_massage->sb == 1)
        {
            shoot_message->shoot_mode = SHOOT_AUTOAIM;
            return SHOOT_AUTOAIM;
        }
    }
    if (*rm_massage->sc == 2)
    {
        switch (*rm_massage->sb)
        {
            case 1:
                shoot_message->shoot_mode = SHOOT_SINGLE;
                return SHOOT_SINGLE;
            case 3:
                shoot_message->shoot_mode = SHOOT_CONTINUOUS;
                return SHOOT_CONTINUOUS;
            default:
                shoot_message->shoot_mode = SHOOT_DISABLE;
                return SHOOT_DISABLE;
        }
    }
    shoot_message->shoot_mode = SHOOT_DISABLE;
    return SHOOT_DISABLE;
}

/**
 *
 * @param shoot_message
 * @param rm_massage
 * @return
 */
bool shoot_control_fun(shoot_message_s *shoot_message, rm_massage_s *rm_massage)
{
    static uint16_t count = 0; //频率计数
    static uint8_t check = 1;  //单发检查
    switch (shoot_message->shoot_mode)
    {
        case SHOOT_DISABLE:
            shoot_message->dial.target_position = *shoot_message->dial.now_position;
            shoot_message->left_motor.target_velocity = 0.0f;
            shoot_message->right_motor.target_velocity = 0.0f;
            return true;
        case SHOOT_SINGLE:
            if (check == 0 && *rm_massage->sa == 2)
            {
                shoot_message->dial.target_position += 44.98f/180.0f*M_PI;
                check = 1;
            }
            else if (check == 1 && *rm_massage->sa == 1)
            {
                check = 0;
            }
            if ((shoot_message->dial.target_position - *shoot_message->dial.now_position) < -M_PI)
                shoot_message->dial.target_position += 2*M_PI;
            else if ((shoot_message->dial.target_position - *shoot_message->dial.now_position) > M_PI)
                shoot_message->dial.target_position -= 2*M_PI;
            shoot_message->left_motor.target_velocity = WHEEL_VELOCITY;
            shoot_message->right_motor.target_velocity = -WHEEL_VELOCITY;
            return true;
        case SHOOT_CONTINUOUS:
            count++;
            if (count >= (1000/DIAL_FREQUENCY - 1)){
                shoot_message->dial.target_position += 44.98f/180.0f*M_PI;
                count=0;
            }
            if ((shoot_message->dial.target_position - *shoot_message->dial.now_position) < -M_PI)
                shoot_message->dial.target_position += 2*M_PI;
            else if ((shoot_message->dial.target_position - *shoot_message->dial.now_position) > M_PI)
                shoot_message->dial.target_position -= 2*M_PI;
            shoot_message->left_motor.target_velocity = WHEEL_VELOCITY;
            shoot_message->right_motor.target_velocity = -WHEEL_VELOCITY;
            return true;
        case SHOOT_AUTOAIM:
            shoot_message->left_motor.target_velocity = WHEEL_VELOCITY;
            shoot_message->right_motor.target_velocity = -WHEEL_VELOCITY;
            return true;
        default:
            return false;
    }
    return false;
}

/**
 *
 * @param left_motor
 * @param right_motor
 * @param dial
 * @return
 */
shoot_message_s *shoot_register_fun(DjiMotorInstance_s *left_motor,
                                    DjiMotorInstance_s *right_motor,
                                    DjiMotorInstance_s *dial)
{
    /* 用静态对象代替堆分配：不会失败、不占 FreeRTOS 堆，且 BSS 零初始化即 SHOOT_DISABLE */
    static shoot_message_s shoot_message;
    (void)left_motor;
    (void)right_motor;
    (void)dial;

    shoot_message.dial.now_velocity = &dial->message.out_velocity;
    shoot_message.dial.now_position = &dial->message.out_position;
    shoot_message.left_motor.now_velocity = &left_motor->message.out_velocity;
    shoot_message.left_motor.now_position = &left_motor->message.out_position;
    shoot_message.right_motor.now_velocity = &right_motor->message.out_velocity;
    shoot_message.right_motor.now_position = &right_motor->message.out_position;

    return &shoot_message;
}