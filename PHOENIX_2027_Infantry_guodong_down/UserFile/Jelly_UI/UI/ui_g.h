//
// Created by RM UI Designer
// Static Edition
//

#ifndef UI_g_H
#define UI_g_H

#include "ui_interface.h"

extern ui_interface_rect_t *ui_g_Ungroup_cap_frame;
extern ui_interface_round_t *ui_g_Ungroup_heading_ring;
extern ui_interface_string_t *ui_g_Ungroup_pitch_label;
extern ui_interface_string_t *ui_g_Ungroup_wheel_legend;
extern ui_interface_string_t *ui_g_Ungroup_vx_label;
extern ui_interface_string_t *ui_g_pitch2_live_pitch2_status;
extern ui_interface_string_t *ui_g_Ungroup_percent;
extern ui_interface_string_t *ui_g_Ungroup_power_label;

void ui_init_g_pitch2_live(void);
void ui_update_g_pitch2_live(void);
void ui_remove_g_pitch2_live(void);

void ui_init_g_Ungroup();
void ui_update_g_Ungroup();
void ui_remove_g_Ungroup();

extern ui_interface_line_t *ui_g_cap_live_cap_bar;
extern ui_interface_number_t *ui_g_cap_live_cap_value;

void ui_init_g_cap_live();
void ui_update_g_cap_live();
void ui_remove_g_cap_live();

extern ui_interface_string_t *ui_g_cap_mode_live_cap_mode;

void ui_init_g_cap_mode_live();
void ui_update_g_cap_mode_live();
void ui_remove_g_cap_mode_live();

extern ui_interface_string_t *ui_g_chassis_live_chassis_mode;

void ui_init_g_chassis_live();
void ui_update_g_chassis_live();
void ui_remove_g_chassis_live();

extern ui_interface_string_t *ui_g_device_live_yaw_status;
extern ui_interface_string_t *ui_g_device_live_pitch_status;
extern ui_interface_string_t *ui_g_device_live_feed_status;
extern ui_interface_string_t *ui_g_device_live_fric_status;

void ui_init_g_device_live();
void ui_update_g_device_live();
void ui_remove_g_device_live();

extern ui_interface_round_t *ui_g_drive_live_drive_1;
extern ui_interface_round_t *ui_g_drive_live_drive_2;
extern ui_interface_round_t *ui_g_drive_live_drive_3;
extern ui_interface_round_t *ui_g_drive_live_drive_4;

void ui_init_g_drive_live();
void ui_update_g_drive_live();
void ui_remove_g_drive_live();

extern ui_interface_round_t *ui_g_heading_live_heading_dot;

void ui_init_g_heading_live();
void ui_update_g_heading_live();
void ui_remove_g_heading_live();

extern ui_interface_string_t *ui_g_mode_live_shoot_mode;

void ui_init_g_mode_live();
void ui_update_g_mode_live();
void ui_remove_g_mode_live();

extern ui_interface_number_t *ui_g_pitch_live_pitch_value;

void ui_init_g_pitch_live();
void ui_update_g_pitch_live();
void ui_remove_g_pitch_live();

extern ui_interface_number_t *ui_g_power_live_power_value;

void ui_init_g_power_live();
void ui_update_g_power_live();
void ui_remove_g_power_live();

extern ui_interface_number_t *ui_g_speed_live_vx_value;

void ui_init_g_speed_live();
void ui_update_g_speed_live();
void ui_remove_g_speed_live();


#endif // UI_g_H
