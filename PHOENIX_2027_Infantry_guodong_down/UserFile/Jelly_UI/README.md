# 新车接入选手端 UI

适用于使用战队裁判系统库、STM32 HAL 和 FreeRTOS 的底盘工程。界面布局已随 C 文件提供。应用层包含 `chassis_ui.h`，启动时传入本车 ID 和串口发送函数，运行中更新 `real_data`。

## 1. 把库加入新车工程

将本目录下 `UI/` 子目录的全部 `.c`、`.h` 复制到新车工程的 `UserFiles/Module/ui/`。把该目录加入头文件搜索路径，把 `chassis_ui.c`、`ui_g.c`、`ui_interface.c` 加入同一固件目标。项目已有相应目录的源文件收集规则时，重新配置 CMake 即可。

使用显式源文件列表的工程，可在创建固件目标后加入以下配置。将 `firmware` 换成项目实际的目标名。

```cmake
set(ui_dir "${CMAKE_CURRENT_SOURCE_DIR}/UserFiles/Module/ui")
target_sources(firmware PRIVATE
    "${ui_dir}/chassis_ui.c"
    "${ui_dir}/ui_g.c"
    "${ui_dir}/ui_interface.c")
target_include_directories(firmware PRIVATE "${ui_dir}")
# ARM GCC 工程若提示 sinf、round 等未定义，链接数学库
target_link_libraries(firmware PRIVATE m)
```

## 2. 让战队库接收裁判数据

确认新车接裁判系统的 UART 已初始化，RX、TX 都接好。应用启动时，用战队库的 `Referee_Register(&referee_config)` 注册这一路串口并保存返回的实例。已有裁判接收模块时直接复用实例。蛙头工程的实例是 `Referee`，配置用的是 `&huart6`，新车按接线选择。接收正常后，`Referee_Get_Robot_ID(Referee)` 会返回有效的本车 ID。UI 模块用它计算选手端地址并生成完整数据帧。

## 3. 在应用层新建 UI_Task.c

下面按蛙头的 CMSIS-RTOS v1 接口编写。假设整车已经定义并注册了全局裁判实例 `Referee`。如果你的工程用了别的实例名，替换声明和引用。把这个任务源文件也加入固件编译。示例还假设新车已启动共享 TX 服务。下面的 referee_tx.h 和 RefereeTx_Submit 是该服务的示例名称，需要对接整车实际接口。若只有裸 HAL，先按第 6 节实现发送服务。

```c
#include "cmsis_os.h"
#include "dev_referee.h"
#include "chassis_ui.h"
#include "referee_tx.h"  // 新车发送服务的头文件，按项目实际名称替换

extern RefereeInstance_s *Referee;

// 首次联调使用固定读数，先验证屏幕和数据通路。
static ChassisUI_Data real_data = {
    .cap_percent = 70, .power_w = 76.0f, .limit_w = 80.0f,
    .vx = 1.25f, .heading_deg = 90.0f,
    .pitch2 = CHASSIS_UI_ONLINE, .chassis_mode = "FOLLOW"
};

// 接到新车已有的共享 TX 服务。它在返回 true 前复制完整帧。
static bool SendUiFrame(void *context, const uint8_t *frame, uint16_t length)
{
    return RefereeTx_Submit((UART_HandleTypeDef *)context, frame, length);
}

void UI_Task(void const *argument)
{
    (void)argument;
    uint8_t robot_id = 0;

    // 等接收模块拿到有效 ID，再建图。
    while (robot_id == 0) {
        osDelay(100);
        if (Referee && Referee->uart_instance) {
            robot_id = Referee_Get_Robot_ID(Referee);
        }
    }

    // 注册回调，提交整张界面的创建帧。失败后延时重试。
    UART_HandleTypeDef *uart = Referee->uart_instance->uart_handle;
    while (!ChassisUI_Start(robot_id, SendUiFrame, uart)) {
        osDelay(500);
    }

    for (;;) {
        // 接实车时，在这里把最新采样值填入 real_data。
        // 例如已有电容百分比 cap_percent_now 时：
        // real_data.cap_percent = cap_percent_now;
        bool ok = ChassisUI_RefreshNext(&real_data);
        osDelay(ok ? 1 : 100);  // 失败后下次仍刷新当前组
    }
}
```

## 4. 创建任务，让它真正运行

在 FreeRTOS 初始化函数里创建一次 UI 任务。蛙头使用下面的写法。已有 CubeMX 生成的同名任务时，将上面的实现接到该任务入口即可。

```c
// 放在任务创建代码可见的位置
void UI_Task(void const *argument);

// 放在 MX_FREERTOS_Init() 函数体内
osThreadDef(UI, UI_Task, osPriorityNormal, 0, 512);
osThreadCreate(osThread(UI), NULL);
```

## 5. 看见模拟数据后，再接真实输入

首次联调预期看到电容 70、功率使用率 95%、方向点在圆环右侧、PITCH2 为绿色。调试时将 `real_data.cap_percent` 改为 45，轮到电容组后数字和条长应一起变化。接实车时，让同一个 UI 任务取整车最新数据并填入下表字段。如果多个任务共同维护原始数据，沿用整车已有的快照或互斥机制读取。

| 输入字段 | 填入的数据 |
| --- | --- |
| cap_percent | 电容剩余百分比，0～100 |
| power_w、limit_w | 实际底盘功率和同口径功率上限，单位 W。上限无效时显示 -1 |
| vx | 底盘前向速度，按整车约定的速度单位传入 |
| pitch_deg、heading_deg | 俯仰角、车头相对当前画面的角度，单位为度。车头向前为 0，向右为正 |
| wheels[0..3] | 对应屏幕 1～4 号轮子的反馈状态 |
| yaw、pitch1、pitch2、feed、fric | 对应设备的反馈状态，使用 CHASSIS_UI_UNKNOWN、CHASSIS_UI_ONLINE 或 CHASSIS_UI_OFFLINE |
| chassis_mode、cap_mode、shoot_mode | 当前模式的简短英文字符串，空指针显示占位符。字符串至少在本次调用期间有效 |

## 6. 串口与重绘

1. UI 和共用同一串口的其他业务都调用整车的提交接口。示例签名为 `bool RefereeTx_Submit(UART_HandleTypeDef *uart, const uint8_t *frame, uint16_t length)`。提交端复制长度和全部字节，队列满时可在任务上下文等待空位，超时返回 false。
2. 只有发送任务启动硬件。它取出一帧到专用缓冲区，按链路预算限速，再调用 `HAL_UART_Transmit_IT(uart, active_frame, length)`。HAL_OK 表示已启动，保持缓冲区有效。HAL_BUSY 时保留该帧，稍后重试；出错时按整车串口策略恢复。
3. 在该串口已有的 TX 完成回调里通知发送任务。确认上一帧结束后才能复用缓冲区。固定延时不能证明 IT 已结束。
4. 控制 UI 提交速率或限制待发 UI 数量，避免低频文字挤占其他业务。启动有 20 帧创建指令，全部需要送出；运行中保留最新 real_data，按组取值。初始化部分入队失败会导致 Start 返回 false，再调用会从头建图。

- 客户端重连、画面被清空后，可以从同一 UI 任务再次调用 ChassisUI_Start() 重建，然后继续刷新。
- 完全没有画面时，先看任务是否取得非零 robot_id，再看 SendUiFrame 是否被调用、HAL 是否返回 HAL_OK，最后核对实际 UART 的 TX 接线和客户端身份。若能看到初始值但一直不变，检查任务是否持续进入 ChassisUI_RefreshNext()，并观察 real_data 对应字段。
