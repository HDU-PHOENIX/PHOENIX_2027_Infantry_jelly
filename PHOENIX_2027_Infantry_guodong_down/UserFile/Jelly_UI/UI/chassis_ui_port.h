#ifndef CHASSIS_UI_PORT_H
#define CHASSIS_UI_PORT_H
#include <stdbool.h>
#include <stdint.h>

// 每次收到一个完整裁判帧。返回前须完成发送或复制入队；成功返回 true。
// 串口适配器负责所有帧的发送间隔，共享串口时还需统一排队。
typedef bool (*ChassisUI_SendFrame)(void *context, const uint8_t *frame, uint16_t length);

#endif
