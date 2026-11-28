// 头文件保护，避免在同一次编译中重复声明。
#ifndef CHASSIS_UI_H
#define CHASSIS_UI_H

// 提供百分比和功率参数所用的定宽整数类型。
#include <stdint.h>
#include "chassis_ui_port.h"

#ifdef __cplusplus
// 供 C++ 工程调用时，沿用 C 的函数链接方式。
extern "C" {
#endif

// 轮组圆圈和设备文字共用这三种状态：未知为白，在线为绿，离线为橙。
typedef enum {
    CHASSIS_UI_UNKNOWN = 0,
    CHASSIS_UI_ONLINE,
    CHASSIS_UI_OFFLINE
} ChassisUI_Status;

// 任务把最新读数放进这里。模式字符串在本次函数调用期间有效即可。
typedef struct {
    uint8_t cap_percent;
    float vx, power_w, limit_w, pitch_deg, heading_deg;
    ChassisUI_Status wheels[4];  // 顺序对应界面 1～4
    ChassisUI_Status yaw, pitch1, pitch2, feed, fric;
    const char *chassis_mode, *cap_mode, *shoot_mode;
} ChassisUI_Data;

// 收到有效本车 ID 后调用。context 由串口适配器解释，可传串口句柄。
bool ChassisUI_Start(uint8_t robot_id, ChassisUI_SendFrame send, void *context);
// 每次轮流更新一组，提交失败返回 false，下次仍刷新该组。
bool ChassisUI_RefreshNext(const ChassisUI_Data *data);

// 在同一个 UI 任务中，先初始化，再按需调用对应组的更新函数。
// 建立整张界面。启动时先调用一次，后续用各组的更新函数刷新。
void ChassisUI_Init(void);
// percent 是电容剩余百分比，同一个值同时决定绿条长度和下方数字。
void ChassisUI_SetCapPercent(uint8_t percent);
// vx 是底盘前进速度，更新左侧 VX 数字。
void ChassisUI_SetSpeed(float vx);
// power_w 和 limit_w 是同一口径的实际功率和上限（W）。显示整数百分比，无有效输入时显示 -1。
void ChassisUI_SetPowerUsage(float power_w, float limit_w);
// degrees 是俯仰角，正负值都可传入，显示在 PITCH 旁边。
void ChassisUI_SetPitch(float degrees);
// 第二个俯仰电机的反馈状态决定 PITCH2 文字颜色。
void ChassisUI_SetPitch2Status(ChassisUI_Status status);
// degrees 是车头相对当前画面的角度，正前方为 0°，向右为正。
void ChassisUI_SetHeading(float degrees);  // 正上方为 0，顺时针为正

// mode 传简短英文，如 "FOLLOW"。空指针或空串显示 "--"。
// 更新底部 CHASSIS 文字，例如传入 "FOLLOW"。
void ChassisUI_SetChassisMode(const char *mode);
// 更新底部 CAP 开关状态，例如传入 "ON" 或 "OFF"。
void ChassisUI_SetCapMode(const char *mode);
// 更新底部 SHOOT 文字，传入要显示的模式名称。
void ChassisUI_SetShootMode(const char *mode);

// 轮组参数按编号排序；设备参数按函数声明排序。
// wheel1 到 wheel4 依次控制底部 1～4 号全向轮圆圈的颜色。
void ChassisUI_SetDriveStatus(ChassisUI_Status wheel1, ChassisUI_Status wheel2,
                              ChassisUI_Status wheel3, ChassisUI_Status wheel4);
// yaw、pitch、feed、fric 依次控制底部四个设备标签的颜色。
void ChassisUI_SetDeviceStatus(ChassisUI_Status yaw, ChassisUI_Status pitch,
                               ChassisUI_Status feed, ChassisUI_Status fric);

#ifdef __cplusplus
}
#endif
#endif
