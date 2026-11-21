//
// Created by 朱泽超 on 2026/11/8.
//

#include "GimbalTask.h"
#include "Gimbal_fun.h"

#include "dev_dr16.h"
#include "dev_et08a.h"
#include "dev_motor_dm.h"
#include "dev_motor_rs.h"

#include "cmsis_os.h"
#include "usb_device.h"

//*****云台电机config区*****//
//yaw轴config
static DmMotorInitConfig_s yaw_config = {
    .topic_name = "yaw",
    .type = J8006,
    .parameters = {
        .pos_max = 3.1415926f,
        .vel_max = 30.0f,       // 达妙 V_MAX，必须非 0：MIT 帧编码以它为分母
        .tor_max = 7.0f,
        .kp_max = 500.0f,       // 达妙 KP_MAX，必须非 0
        .kd_max = 5.0f,         // 达妙 KD_MAX，必须非 0
    },
    .can_config = {
        .can_number = 1,
        .rx_id = 0x01,
        .tx_id = 0x19
    },
    .control_mode = DM_POSITION,
    .velocity_pid_config = {
        .kp = 0.0f,
        .ki = 0.0f,
        .kd = 0.0f,
        .i_max = 0.0f,
        .out_max = 0.0f
    },
    .angle_pid_config = {
        .kp = 0.0f,
        .ki = 0.0f,
        .kd = 0.0f,
        .i_max = 0.0f,
        .out_max = 0.0f
    }
};
//大pitch轴config
static DmMotorInitConfig_s big_pitch_config = {
    .topic_name = "big_pitch",
    .type = J4340,
    .parameters = {
        .pos_max = 3.1415926f,
        .vel_max = 30.0f,       // 达妙 V_MAX，必须非 0：MIT 帧编码以它为分母
        .tor_max = 7.0f,
        .kp_max = 500.0f,       // 达妙 KP_MAX，必须非 0
        .kd_max = 5.0f,         // 达妙 KD_MAX，必须非 0
    },
    .can_config = {
        .can_number = 2,
        .rx_id = 0x01,
        .tx_id = 0x19
    },
    .control_mode = DM_POSITION,
    .velocity_pid_config = {
        .kp = 0.0f,
        .ki = 0.0f,
        .kd = 0.0f,
        .i_max = 0.0f,
        .out_max = 0.0f
    },
    .angle_pid_config = {
        .kp = 0.0f,
        .ki = 0.0f,
        .kd = 0.0f,
        .i_max = 0.0f,
        .out_max = 0.0f
    }
};
//小pitch轴config
static RsMotorInitConfig_s small_pitch_config = {
    .topic_name = "small_pitch",
    .type = EL_05,
    .can_config = {
        .can_number = 1,
        .rx_id = 0x001,
        .tx_id = 0x7FD
    },
    .control_mode = RS_POSITION,
    .velocity_pid_config = {
        .kp = 0.0f,
        .ki = 0.0f,
        .kd = 0.0f,
        .i_max = 0.0f,
        .out_max = 0.0f
    },
    .angle_pid_config = {
        .kp = 0.0f,
        .ki = 0.0f,
        .kd = 0.0f,
        .i_max = 0.0f,
        .out_max = 0.0f
    }
};

//*****变量instance声明区*****//
static DmMotorInstance_s *yaw_instance;
static DmMotorInstance_s *big_pitch_instance;
RsMotorInstance_s *small_pitch_instance;
#ifdef Dr16
Dr16Instance_s *dr16_instance;
#endif
#ifdef Et08a
Et08aInstance_s *et08a_instance;
#endif
gimbal_message_s *gimbal_message;
rm_massage_s *rm_massage;
extern quaternions_struct_t Quater;

void GimbalTask(void const * argument)
{
    /* init code for USB_DEVICE */
    MX_USB_DEVICE_Init();
    /* USER CODE BEGIN GimbalTask */
    Can_Init();
    /* 实例注册区 */
#ifdef Dr16
    dr16_instance = Dr16_Register(&huart6);
#endif
#ifdef Et08a
    et08a_instance = Et08a_Register(&huart3);
#endif
    //云台电机注册
    yaw_instance = Motor_DM_Register(&yaw_config);
    big_pitch_instance = Motor_DM_Register(&big_pitch_config);
    small_pitch_instance = Motor_RS_Register(&small_pitch_config);
    //云台电机注册
    gimbal_message = gimbal_register_fun(yaw_instance, big_pitch_instance, small_pitch_instance);
    //遥控器归一化注册
    rm_massage = rm_register_fun(et08a_instance);

    /* Infinite loop */
    for(;;)
    {

        gimbal_fun(gimbal_message, rm_massage, Quater); //得到目标值
        //*****电机控制*****//
        //yaw轴
        if (gimbal_message->yaw.gimbal_motor_state == 0)
        {
            Motor_Dm_Cmd(yaw_instance, DM_CMD_MOTOR_DISABLE);
        }
        if (gimbal_message->yaw.gimbal_motor_state == 1)
        {
            if (yaw_instance->motor_state == DM_DISABLE)
            {
                Motor_Dm_Cmd(yaw_instance, DM_CMD_MOTOR_ENABLE);
            }
            else
            {
                Motor_Dm_Control(yaw_instance, gimbal_message->yaw.target_position);
                Motor_Dm_Mit_Control(yaw_instance, 0.0f, 0.0f, yaw_instance->output);
            }

        }
        Motor_Dm_Transmit(yaw_instance);
        //大pitch轴
        if (gimbal_message->big_pitch.gimbal_motor_state == 0)
        {
            Motor_Dm_Cmd(big_pitch_instance, DM_CMD_MOTOR_DISABLE);
        }
        if (gimbal_message->big_pitch.gimbal_motor_state == 1)
        {
            if (big_pitch_instance->motor_state == DM_DISABLE)
            {
                Motor_Dm_Cmd(big_pitch_instance, DM_CMD_MOTOR_ENABLE);
            }
            else
            {
                Motor_Dm_Control(big_pitch_instance, gimbal_message->big_pitch.target_position);
                Motor_Dm_Mit_Control(big_pitch_instance, 0.0f, 0.0f, big_pitch_instance->output);
            }

        }
        Motor_Dm_Transmit(big_pitch_instance);
        //小pitch轴
        if (gimbal_message->small_pitch.gimbal_motor_state == 0)
        {
            Motor_RS_Disable(small_pitch_instance);
        }
        if (gimbal_message->small_pitch.gimbal_motor_state == 1)
        {
            if (small_pitch_instance->motor_state == RS_DISABLE)
            {
                Motor_RS_Enable(small_pitch_instance);
            }
            else
            {
                Motor_RS_Control(small_pitch_instance, gimbal_message->small_pitch.target_position);
                Motor_RS_Mit_Control(small_pitch_instance, 0.0f, 0.0f, 0.0f, 0.0f, small_pitch_instance->output);
            }
        }
        Motor_RS_Transmit(small_pitch_instance);

        osDelay(1);
    }
    /* USER CODE END GimbalTask */
}