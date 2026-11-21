该热量控制包括发弹判断还有热量控制共3个函数，针对小弹丸
#### 1. 发弹检测（摩擦轮）
```
uint16_t ShotDetect_Update(ShotDetect_t *detector, bool friction_on,float target_speed,float left_speed, float right_speed,uint16_t update_hz)
```
需定义结构体ShotDetect_t，输入是否开启摩擦轮，左右轮目标/实际速度，该函数的调用频率。
输出发弹数增加量，通常0/1

摩擦轮检测：传入的左右轮速度要先统一方向，如蛙头是左轮取反。`200–500` 的掉速窗口沿用蛙头的 rpm 反馈，换电机或轮组后要重新确认调试。`update_hz` 填函数实际被调用的频率。

#### 2. 发弹检测（波弹盘，波弹盘在云台使用）
`uint16_t FeedAngle_Update(FeedAngle_t *state, float angle, uint8_t number_round)`
需定义结构体FeedAngle_t，波弹盘角度，一圈波弹盘弹个数

拨弹盘检测：传有效的输出轴实际角度（弧度，`[-π, π]`）和每圈格数。返回值是**新增拨过的格数，空拨也可能计数**。两种检测可以并行对照，给热量模块时只选一路，避免一发加两次热量。

#### 3. 热量控制（输出弹频）
```
float ShootHeat_Frequency(ShootHeat_t *heat,uint16_t new_shots,float referee_heat,float cooling_rate, float heat_limit,float cla_frequency)
```
需定义结构体shootheat，输入`new_shots` （是自上次更新以来的新增发数），裁判系统读取的热量、冷却速率、热量上限、还有该函数的调用频率
输出发弹频率，如15.5发/秒
当前频率上限  记得在.c开头修改
```
#define  max_shot_hz 20.0
```

热量控制：状态结构体要零初始化，裁判数据是否有效由任务层判断。当前按裁判热量数值变化校正。