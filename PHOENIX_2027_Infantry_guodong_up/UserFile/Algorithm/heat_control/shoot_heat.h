#ifndef SHOOT_HEAT_H
#define SHOOT_HEAT_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    bool armed;                 // 双轮达到目标转速后开始检测
    uint16_t consecutive_count;  // 连续满足掉速条件的次数
} ShotDetect_t;


// update_hz 是检测函数每秒实际调用次数。
uint16_t ShotDetect_Update(ShotDetect_t *detector, bool friction_on,
                           float target_speed, float left_speed, float right_speed,
                           uint16_t update_hz);

typedef struct {
    float estimated_heat;      // 本地估算热量
    float last_referee_heat;   // 上次用于校正的裁判热量
    uint16_t cooling_count;    // 冷却更新计数
} ShootHeat_t;

float ShootHeat_Frequency(ShootHeat_t *heat,uint16_t new_shots,float referee_heat,float cooling_rate,
    float heat_limit,float cla_frequency);

typedef struct {
    bool initialized;
    float last_angle;  // 上一次实际角度
    float progress;    // 尚未计为整格的净转角
} FeedAngle_t;

// 收到有效电机反馈后调用，angle 为 [-pi, pi] 内的输出轴角度，单位 rad。
// number_round 为拨弹盘一圈的格数。
uint16_t FeedAngle_Update(FeedAngle_t *state, float angle, uint8_t number_round);

#endif
