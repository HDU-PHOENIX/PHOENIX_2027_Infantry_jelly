//
// Created by 朱泽超 on 2026/11/16.
//

#include "ShootTask.h"
#include "Shoot_fun.h"
#include "dev_et08a.h"
#include "dev_motor_dji.h"
#include "cmsis_os.h"

DjiMotorInitConfig_s left_wheel_config = {
    .topic_name = "left_wheel",
    .type = M3508,
    .control_mode = DJI_VELOCITY,
    .id = 2,
    .can_config = {
        .can_number = 1,
        .rx_id = 0x202,
        .tx_id = 0x200
    },
    .reduction_ratio = 1.0f,
    .velocity_pid_config = {
        .kp = 1.0f,
        .ki = 0.001f,
        .kd = 0.0f,
        .i_max = 2000.0f,
        .out_max = 10000.0f
    }
};

DjiMotorInitConfig_s right_wheel_config = {
    .topic_name = "right_wheel",
    .type = M3508,
    .control_mode = DJI_VELOCITY,
    .id = 5,
    .can_config = {
        .can_number = 1,
        .rx_id = 0x205,
        .tx_id = 0x1FF
    },
    .reduction_ratio = 1.0f,
    .velocity_pid_config = {
        .kp = 1.0f,
        .ki = 0.001f,
        .kd = 0.0f,
        .i_max = 2000.0f,
        .out_max = 10000.0f
    }
};

DjiMotorInitConfig_s dial_config = {
    .topic_name = "dial",
    .type = M2006,
    .control_mode = DJI_POSITION,
    .reduction_ratio = 36.0f,
    .id = 3,
    .can_config = {
        .can_number = 1,
        .rx_id = 0x203,
        .tx_id = 0x200
    },
    .velocity_pid_config = {
        .i_max = 4000.0f,
        .out_max = 6000.0f,
        .kp = 450.0f,
        .ki = 0.01f,
        .kd = 0.0f,
    },
    .angle_pid_config = {
        .i_max = 0.0f,
        .out_max = 300.0f,
        .kp = 100.0f,
        .ki = 0.0f,
        .kd = 0.0f,
    }
};

DjiMotorInstance_s *dial_instance;
DjiMotorInstance_s *left_wheel_instance;
DjiMotorInstance_s *right_wheel_instance;
shoot_message_s *shoot_message;
extern rm_massage_s *rm_massage;
extern gimbal_message_s *gimbal_message;

void ShootTask(void const * argument)
{
    /* USER CODE BEGIN ShootTask */
    dial_instance = Motor_Dji_Register(&dial_config);
    left_wheel_instance = Motor_Dji_Register(&left_wheel_config);
    right_wheel_instance = Motor_Dji_Register(&right_wheel_config);
    shoot_message = shoot_register_fun(left_wheel_instance, right_wheel_instance, dial_instance);

    /* Infinite loop */
    for(;;)
    {
        shoot_mode_fun(shoot_message, gimbal_message, rm_massage);
        shoot_control_fun(shoot_message, rm_massage);
        if (shoot_message->shoot_mode != SHOOT_DISABLE)
        {
            Motor_Dji_Control(dial_instance, shoot_message->dial.target_position);
            Motor_Dji_Control(left_wheel_instance, shoot_message->left_motor.target_velocity);
            Motor_Dji_Control(right_wheel_instance, shoot_message->right_motor.target_velocity);
        }
        if (shoot_message->shoot_mode == SHOOT_DISABLE)
        {
            Motor_Dji_Control(dial_instance, shoot_message->dial.target_position);
            if (fabsf(left_wheel_instance->message.out_velocity) > 600.0f ||
                fabsf(right_wheel_instance->message.out_velocity) > 600.0f)
            {
                Motor_Dji_Control(left_wheel_instance, 0.0f);
                Motor_Dji_Control(right_wheel_instance, 0.0f);
            }
            else
            {
                Motor_Dji_SetCurrent(left_wheel_instance, 0.0f);
                Motor_Dji_SetCurrent(right_wheel_instance, 0.0f);
            }

        }
        if (dial_instance->output < -300.0f)
        {
            Motor_Dji_SetCurrent(dial_instance, 0.0f);
        }
        Motor_Dji_Transmit(dial_instance);
        Motor_Dji_Transmit(left_wheel_instance);
        Motor_Dji_Transmit(right_wheel_instance);
        osDelay(1);
    }
    /* USER CODE END ShootTask */
}


