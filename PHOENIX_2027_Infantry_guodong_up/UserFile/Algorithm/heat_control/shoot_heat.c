#include "shoot_heat.h"
#include <math.h>

#define  max_shot_hz 20.0

uint16_t ShotDetect_Update(ShotDetect_t *detector, bool friction_on,float target_speed,
    float left_speed, float right_speed,uint16_t update_hz)
{
    if (!friction_on || update_hz == 0) {
        detector->armed = false;
        detector->consecutive_count = 0;
        return 0;
    }

    if (!detector->armed) {
        if (!(fabsf(left_speed) >= fabsf(target_speed) &&fabsf(right_speed) >= fabsf(target_speed))) {
            return 0;
        }
        detector->armed = true;
        detector->consecutive_count = 0;
    }

    //暂时还是使用摩擦轮速度与目标速度的差判断
    // 输入时记得处理正负，比如蛙头的左右轮转向相反
    const float left_drop = target_speed-left_speed;
    const float right_drop = target_speed -right_speed;
    if (left_drop > 200.0f && left_drop < 500.0f &&right_drop > 200.0f && right_drop < 500.0f) {
        detector->consecutive_count++;

        //含义是满足区间10 ms返回1
        if ((uint32_t)detector->consecutive_count * 1000U >= (uint32_t)update_hz * 10U) {
            detector->consecutive_count = 0;
            return 1;
        }
    } else {
        detector->consecutive_count = 0;
    }

    return 0;
}

float ShootHeat_Frequency(ShootHeat_t *heat,uint16_t new_shots,float referee_heat,float cooling_rate,
    float heat_limit,float cla_frequency)
{
    //周期处理，根据填入的实际计算周期，满100ms计算一次冷却值
    heat->cooling_count++;
    if (heat->cooling_count >= cla_frequency/10) {
        heat->cooling_count = 0;
        heat->estimated_heat -= cooling_rate/10;
        if (heat->estimated_heat < 0.0f) {
            heat->estimated_heat = 0.0f;
        }
    }
//裁判系统更新判断方式--热量值变化，如果板间通讯运行，建议新增数据更新标志而不是用相等判断
    if (referee_heat != heat->last_referee_heat) {
        heat->last_referee_heat = referee_heat;
        heat->estimated_heat = referee_heat;
    }
    heat->estimated_heat += new_shots * 10.0f;

    //下面是射频计算。
    float shot_hz = 0.0f;
    if (heat->estimated_heat <= heat_limit - 16.0f) {
        if (heat->estimated_heat > heat_limit * 0.5f) {
            shot_hz = (heat_limit - heat->estimated_heat) / 30.0f + cooling_rate / 10.0f;
        }
        else {
            shot_hz = (heat_limit - heat->estimated_heat) / 15.0f + cooling_rate / 10.0f;
        }
    }
//工程上处理，降频。除以15代表1.5秒打完剩余热量的弹频

    if (shot_hz <= 0.0f || max_shot_hz <= 0.0f) {
        return 0.0f;
    }
    return shot_hz > max_shot_hz ? max_shot_hz : shot_hz;
}

uint16_t FeedAngle_Update(FeedAngle_t *state, float angle, uint8_t number_round)
{
    const float pi = 3.14159265f;
    const float two_pi = 2.0f * pi;

    if (number_round == 0 || !(angle >= -pi && angle <= pi)) {
        return 0;
    }

    if (!state->initialized) {
        state->initialized = true;
        state->last_angle = angle;
        return 0;
    }

    float delta = angle - state->last_angle;
    state->last_angle = angle;

    // 相邻采样转角小于半圈时，还原跨 ±pi 的角度差
    if (delta > pi) {
        delta -= two_pi;
    } else if (delta < -pi) {
        delta += two_pi;
    }

    // 反转产生负转角，回到已计数的位置时不重复计数
    state->progress += delta;
    const float solo_angle = two_pi / number_round;
    if (state->progress < solo_angle) {
        return 0;
    }

    const uint16_t new_slots = (uint16_t)(state->progress / solo_angle);
    state->progress -= new_slots * solo_angle;
    return new_slots;
}
