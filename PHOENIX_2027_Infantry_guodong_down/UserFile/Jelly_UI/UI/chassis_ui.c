// 模块头文件声明对外接口，ui_g.h 提供网页导出的图元指针和分组函数。
#include "chassis_ui.h"
#include "ui_g.h"

#include <math.h>
#include <stdio.h>

// 导出代码将浮点读数存为有符号整数，1.25 对应 1250。
static int32_t encode_float(float value)
{
    // 先换算成千分之一单位，再限制在 int32_t 范围内并四舍五入。
    double scaled = (double)value * 1000.0;
    if (scaled >= INT32_MAX) return INT32_MAX;
    if (scaled <= INT32_MIN) return INT32_MIN;
    return (int32_t)round(scaled);
}

// 将调用方传入的在线状态换成选手端的颜色编号。
static unsigned status_color(ChassisUI_Status status)
{
    switch (status) {
    case CHASSIS_UI_ONLINE:  return 2; // 绿
    case CHASSIS_UI_OFFLINE: return 3; // 橙
    default:                 return 8; // 白，尚无反馈
    }
}

// 拼接标签和模式，例如 "CAP: ON"。没有模式时显示 "--"，写入长度受图元缓冲区限制。
static void set_mode(ui_interface_string_t *label, const char *prefix, const char *mode)
{
    snprintf(label->string, sizeof(label->string), "%s: %s",
             prefix, mode && mode[0] ? mode : "--");
}

// 建立整张界面。启动时先调用一次，后续用各组的更新函数刷新。
void ChassisUI_Init(void)
{
    // 先添加固定的标签、边框和方向环。
    ui_init_g_Ungroup();
    // 添加电容、速度、功率、俯仰角和车头方向点，初值取自网页设计。
    ui_init_g_cap_live();
    ui_init_g_speed_live();
    ui_init_g_power_live();
    ui_init_g_pitch_live();
    ui_init_g_heading_live();
    // 添加四个轮组圆圈和四个设备状态标签。
    ui_init_g_drive_live();
    ui_init_g_device_live();
    // 单独建立第二个俯仰电机的状态文字。
    ui_init_g_pitch2_live();
    // 添加底部三项模式文字。
    ui_init_g_chassis_live();
    ui_init_g_cap_mode_live();
    ui_init_g_mode_live();
}

// percent 是电容剩余百分比，同一个值同时决定绿条长度和下方数字。
void ChassisUI_SetCapPercent(uint8_t percent)
{
    // 超过 100 按满格处理，避免绿条越过边框。
    if (percent > 100) percent = 100;
    // 当前设计的满格跨度为 200 像素。
    ui_g_cap_live_cap_bar->end_x = ui_g_cap_live_cap_bar->start_x + 2 * percent;
    ui_g_cap_live_cap_value->number = percent;
    // 图元属性已写好，调用导出代码发送这一组的更新。
    ui_update_g_cap_live();
}

// vx 是底盘前进速度，更新左侧 VX 数字。
void ChassisUI_SetSpeed(float vx)
{
    // 速度无效就跳过刷新，保留上次读数。
    if (!isfinite(vx)) return;
    // 把速度换算为千分之一单位，写入 VX 图元。
    ui_g_speed_live_vx_value->number = encode_float(vx);
    // 图元属性已写好，调用导出代码发送这一组的更新。
    ui_update_g_speed_live();
}

// power_w 和 limit_w 是同一口径的实际功率和上限（W）。显示整数百分比，无有效输入时显示 -1。
void ChassisUI_SetPowerUsage(float power_w, float limit_w)
{
    // 无有效上限或读数时用白色 -1 表示未知。
    int32_t percent = -1;
    unsigned color = 8;
    if (isfinite(power_w) && isfinite(limit_w) && limit_w > 0.0f) {
        // 回馈时按零消耗显示，超限时保留超过 100% 的读数。
        double usage = 100.0 * fmax(0.0, (double)power_w) / limit_w;
        percent = usage >= INT32_MAX ? INT32_MAX : (int32_t)round(usage);

        // 按显示值变色：低于 90% 绿色，90% 起黄色，100% 起橙色。
        color = 2;
        if (percent >= 100) color = 3;
        else if (percent >= 90) color = 1;
    }
    ui_g_power_live_power_value->number = percent;
    ui_g_power_live_power_value->color = color;
    // 图元属性已写好，调用导出代码发送这一组的更新。
    ui_update_g_power_live();
}

// degrees 是俯仰角，正负值都可传入，显示在 PITCH 旁边。
void ChassisUI_SetPitch(float degrees)
{
    // 遇到 NaN 或无穷大就跳过本次更新。
    if (!isfinite(degrees)) return;
    ui_g_pitch_live_pitch_value->number = encode_float(degrees);
    // 图元属性已写好，调用导出代码发送这一组的更新。
    ui_update_g_pitch_live();
}

// degrees 是车头相对当前画面的角度，正前方为 0°，向右为正。
void ChassisUI_SetHeading(float degrees)
{
    // 遇到 NaN 或无穷大就跳过本次更新。
    if (!isfinite(degrees)) return;
    // 从已初始化的白圈读取圆心和半径，布局调整后仍沿同一圆周移动。
    const ui_interface_round_t *ring = ui_g_Ungroup_heading_ring;
    ui_interface_round_t *dot = ui_g_heading_live_heading_dot;
    float radians = fmodf(degrees, 360.0f) * 0.01745329252f;

    // 画布 Y 轴向上。正前方在圆顶，顺时针转动时小点先向右移动。
    dot->start_x = ring->start_x + lroundf(ring->r * sinf(radians));
    dot->start_y = ring->start_y + lroundf(ring->r * cosf(radians));

    // 仅发送方向点所在组的更新。
    ui_update_g_heading_live();
}

// 更新底部 CHASSIS 文字，例如传入 "FOLLOW"。
void ChassisUI_SetChassisMode(const char *mode)
{
    set_mode(ui_g_chassis_live_chassis_mode, "CHASSIS", mode);
    // 图元属性已写好，调用导出代码发送这一组的更新。
    ui_update_g_chassis_live();
}

// 更新底部 CAP 开关状态，例如传入 "ON" 或 "OFF"。
void ChassisUI_SetCapMode(const char *mode)
{
    set_mode(ui_g_cap_mode_live_cap_mode, "CAP", mode);
    // 图元属性已写好，调用导出代码发送这一组的更新。
    ui_update_g_cap_mode_live();
}

// 更新底部 SHOOT 文字，传入要显示的模式名称。
void ChassisUI_SetShootMode(const char *mode)
{
    set_mode(ui_g_mode_live_shoot_mode, "SHOOT", mode);
    // 图元属性已写好，调用导出代码发送这一组的更新。
    ui_update_g_mode_live();
}

// wheel1 到 wheel4 依次控制底部 1～4 号全向轮圆圈的颜色。
void ChassisUI_SetDriveStatus(ChassisUI_Status wheel1, ChassisUI_Status wheel2,
                              ChassisUI_Status wheel3, ChassisUI_Status wheel4)
{
    ui_g_drive_live_drive_1->color = status_color(wheel1);
    ui_g_drive_live_drive_2->color = status_color(wheel2);
    ui_g_drive_live_drive_3->color = status_color(wheel3);
    ui_g_drive_live_drive_4->color = status_color(wheel4);
    // 图元属性已写好，调用导出代码发送这一组的更新。
    ui_update_g_drive_live();
}

// yaw、pitch、feed、fric 依次控制底部四个设备标签的颜色。
void ChassisUI_SetDeviceStatus(ChassisUI_Status yaw, ChassisUI_Status pitch,
                               ChassisUI_Status feed, ChassisUI_Status fric)
{
    ui_g_device_live_yaw_status->color = status_color(yaw);
    ui_g_device_live_pitch_status->color = status_color(pitch);
    ui_g_device_live_feed_status->color = status_color(feed);
    ui_g_device_live_fric_status->color = status_color(fric);
    // 图元属性已写好，调用导出代码发送这一组的更新。
    ui_update_g_device_live();
}

// 只提交第二个俯仰电机的状态文字。
void ChassisUI_SetPitch2Status(ChassisUI_Status status)
{
    ui_g_pitch2_live_pitch2_status->color = status_color(status);
    ui_update_g_pitch2_live();
}

/* 单任务使用。初始化成功后从第一组开始轮询。 */
static bool started;
static unsigned next_group;

bool ChassisUI_Start(uint8_t robot_id, ChassisUI_SendFrame send, void *context)
{
    started = false;
    if (robot_id == 0 || !send) return false;

    ui_self_id = robot_id;
    ui_bind_sender(send, context);
    ui_begin_batch();
    ChassisUI_Init();
    next_group = 0;
    started = ui_batch_ok();
    return started;
}

/* 每次处理一组；四个设备文字在设计器里各占一帧。 */
bool ChassisUI_RefreshNext(const ChassisUI_Data *data)
{
    if (!started || !data) return false;
    ui_begin_batch();
    switch (next_group) {
    case 0: ChassisUI_SetHeading(data->heading_deg); break;
    case 1: ChassisUI_SetPowerUsage(data->power_w, data->limit_w); break;
    case 2: ChassisUI_SetCapPercent(data->cap_percent); break;
    case 3: ChassisUI_SetSpeed(data->vx); break;
    case 4: ChassisUI_SetPitch(data->pitch_deg); break;
    case 5: ChassisUI_SetDriveStatus(data->wheels[0], data->wheels[1],
                                    data->wheels[2], data->wheels[3]); break;
    case 6: ChassisUI_SetDeviceStatus(data->yaw, data->pitch1, data->feed, data->fric); break;
    case 7: ChassisUI_SetPitch2Status(data->pitch2); break;
    case 8: ChassisUI_SetChassisMode(data->chassis_mode); break;
    case 9: ChassisUI_SetCapMode(data->cap_mode); break;
    case 10: ChassisUI_SetShootMode(data->shoot_mode); break;
    }
    if (!ui_batch_ok()) return false;
    next_group = (next_group + 1) % 11;
    return true;
}
