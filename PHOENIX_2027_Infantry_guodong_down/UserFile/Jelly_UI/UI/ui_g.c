//
// Created by RM UI Designer
// Static Edition
//

#include <string.h>

#include "ui_interface.h"

ui_2_frame_t ui_g_Ungroup_0;

ui_interface_rect_t *ui_g_Ungroup_cap_frame = (ui_interface_rect_t*)&(ui_g_Ungroup_0.data[0]);
ui_interface_round_t *ui_g_Ungroup_heading_ring = (ui_interface_round_t*)&(ui_g_Ungroup_0.data[1]);

void _ui_init_g_Ungroup_0() {
    for (int i = 0; i < 2; i++) {
        ui_g_Ungroup_0.data[i].figure_name[0] = 0;
        ui_g_Ungroup_0.data[i].figure_name[1] = 0;
        ui_g_Ungroup_0.data[i].figure_name[2] = i + 0;
        ui_g_Ungroup_0.data[i].operate_type = 1;
    }
    for (int i = 2; i < 2; i++) {
        ui_g_Ungroup_0.data[i].operate_type = 0;
    }

    ui_g_Ungroup_cap_frame->figure_type = 1;
    ui_g_Ungroup_cap_frame->operate_type = 1;
    ui_g_Ungroup_cap_frame->layer = 0;
    ui_g_Ungroup_cap_frame->color = 8;
    ui_g_Ungroup_cap_frame->start_x = 84;
    ui_g_Ungroup_cap_frame->start_y = 281;
    ui_g_Ungroup_cap_frame->width = 2;
    ui_g_Ungroup_cap_frame->end_x = 292;
    ui_g_Ungroup_cap_frame->end_y = 301;

    ui_g_Ungroup_heading_ring->figure_type = 2;
    ui_g_Ungroup_heading_ring->operate_type = 1;
    ui_g_Ungroup_heading_ring->layer = 0;
    ui_g_Ungroup_heading_ring->color = 8;
    ui_g_Ungroup_heading_ring->start_x = 957;
    ui_g_Ungroup_heading_ring->start_y = 540;
    ui_g_Ungroup_heading_ring->width = 3;
    ui_g_Ungroup_heading_ring->r = 393;


    ui_proc_2_frame(&ui_g_Ungroup_0);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_0, sizeof(ui_g_Ungroup_0));
}

void _ui_update_g_Ungroup_0() {
    for (int i = 0; i < 2; i++) {
        ui_g_Ungroup_0.data[i].operate_type = 2;
    }

    ui_proc_2_frame(&ui_g_Ungroup_0);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_0, sizeof(ui_g_Ungroup_0));
}

void _ui_remove_g_Ungroup_0() {
    for (int i = 0; i < 2; i++) {
        ui_g_Ungroup_0.data[i].operate_type = 3;
    }

    ui_proc_2_frame(&ui_g_Ungroup_0);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_0, sizeof(ui_g_Ungroup_0));
}

ui_string_frame_t ui_g_Ungroup_1;
ui_interface_string_t* ui_g_Ungroup_pitch_label = &(ui_g_Ungroup_1.option);

void _ui_init_g_Ungroup_1() {
    ui_g_Ungroup_1.option.figure_name[0] = 0;
    ui_g_Ungroup_1.option.figure_name[1] = 0;
    ui_g_Ungroup_1.option.figure_name[2] = 2;
    ui_g_Ungroup_1.option.operate_type = 1;

    ui_g_Ungroup_pitch_label->figure_type = 7;
    ui_g_Ungroup_pitch_label->operate_type = 1;
    ui_g_Ungroup_pitch_label->layer = 0;
    ui_g_Ungroup_pitch_label->color = 8;
    ui_g_Ungroup_pitch_label->start_x = 28;
    ui_g_Ungroup_pitch_label->start_y = 478;
    ui_g_Ungroup_pitch_label->width = 2;
    ui_g_Ungroup_pitch_label->font_size = 20;
    ui_g_Ungroup_pitch_label->str_length = 5;
    strcpy(ui_g_Ungroup_pitch_label->string, "PITCH");


    ui_proc_string_frame(&ui_g_Ungroup_1);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_1, sizeof(ui_g_Ungroup_1));
}

void _ui_update_g_Ungroup_1() {
    ui_g_Ungroup_1.option.operate_type = 2;

    ui_proc_string_frame(&ui_g_Ungroup_1);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_1, sizeof(ui_g_Ungroup_1));
}

void _ui_remove_g_Ungroup_1() {
    ui_g_Ungroup_1.option.operate_type = 3;

    ui_proc_string_frame(&ui_g_Ungroup_1);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_1, sizeof(ui_g_Ungroup_1));
}
ui_string_frame_t ui_g_Ungroup_2;
ui_interface_string_t* ui_g_Ungroup_wheel_legend = &(ui_g_Ungroup_2.option);

void _ui_init_g_Ungroup_2() {
    ui_g_Ungroup_2.option.figure_name[0] = 0;
    ui_g_Ungroup_2.option.figure_name[1] = 0;
    ui_g_Ungroup_2.option.figure_name[2] = 3;
    ui_g_Ungroup_2.option.operate_type = 1;

    ui_g_Ungroup_wheel_legend->figure_type = 7;
    ui_g_Ungroup_wheel_legend->operate_type = 1;
    ui_g_Ungroup_wheel_legend->layer = 0;
    ui_g_Ungroup_wheel_legend->color = 8;
    ui_g_Ungroup_wheel_legend->start_x = 1410;
    ui_g_Ungroup_wheel_legend->start_y = 41;
    ui_g_Ungroup_wheel_legend->width = 1;
    ui_g_Ungroup_wheel_legend->font_size = 13;
    ui_g_Ungroup_wheel_legend->str_length = 13;
    strcpy(ui_g_Ungroup_wheel_legend->string, "1   2   3   4");


    ui_proc_string_frame(&ui_g_Ungroup_2);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_2, sizeof(ui_g_Ungroup_2));
}

void _ui_update_g_Ungroup_2() {
    ui_g_Ungroup_2.option.operate_type = 2;

    ui_proc_string_frame(&ui_g_Ungroup_2);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_2, sizeof(ui_g_Ungroup_2));
}

void _ui_remove_g_Ungroup_2() {
    ui_g_Ungroup_2.option.operate_type = 3;

    ui_proc_string_frame(&ui_g_Ungroup_2);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_2, sizeof(ui_g_Ungroup_2));
}
ui_string_frame_t ui_g_Ungroup_3;
ui_interface_string_t* ui_g_Ungroup_vx_label = &(ui_g_Ungroup_3.option);

void _ui_init_g_Ungroup_3() {
    ui_g_Ungroup_3.option.figure_name[0] = 0;
    ui_g_Ungroup_3.option.figure_name[1] = 0;
    ui_g_Ungroup_3.option.figure_name[2] = 4;
    ui_g_Ungroup_3.option.operate_type = 1;

    ui_g_Ungroup_vx_label->figure_type = 7;
    ui_g_Ungroup_vx_label->operate_type = 1;
    ui_g_Ungroup_vx_label->layer = 0;
    ui_g_Ungroup_vx_label->color = 8;
    ui_g_Ungroup_vx_label->start_x = 28;
    ui_g_Ungroup_vx_label->start_y = 430;
    ui_g_Ungroup_vx_label->width = 2;
    ui_g_Ungroup_vx_label->font_size = 20;
    ui_g_Ungroup_vx_label->str_length = 2;
    strcpy(ui_g_Ungroup_vx_label->string, "VX");


    ui_proc_string_frame(&ui_g_Ungroup_3);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_3, sizeof(ui_g_Ungroup_3));
}

void _ui_update_g_Ungroup_3() {
    ui_g_Ungroup_3.option.operate_type = 2;

    ui_proc_string_frame(&ui_g_Ungroup_3);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_3, sizeof(ui_g_Ungroup_3));
}

void _ui_remove_g_Ungroup_3() {
    ui_g_Ungroup_3.option.operate_type = 3;

    ui_proc_string_frame(&ui_g_Ungroup_3);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_3, sizeof(ui_g_Ungroup_3));
}
ui_string_frame_t ui_g_pitch2_live_0;
ui_interface_string_t* ui_g_pitch2_live_pitch2_status = &(ui_g_pitch2_live_0.option);

void ui_init_g_pitch2_live(void) {
    ui_g_pitch2_live_0.option.figure_name[0] = 0;
    ui_g_pitch2_live_0.option.figure_name[1] = 0;
    ui_g_pitch2_live_0.option.figure_name[2] = 5;
    ui_g_pitch2_live_0.option.operate_type = 1;

    ui_g_pitch2_live_pitch2_status->figure_type = 7;
    ui_g_pitch2_live_pitch2_status->operate_type = 1;
    ui_g_pitch2_live_pitch2_status->layer = 0;
    ui_g_pitch2_live_pitch2_status->color = 8;
    ui_g_pitch2_live_pitch2_status->start_x = 1034;
    ui_g_pitch2_live_pitch2_status->start_y = 44;
    ui_g_pitch2_live_pitch2_status->width = 2;
    ui_g_pitch2_live_pitch2_status->font_size = 15;
    ui_g_pitch2_live_pitch2_status->str_length = 6;
    strcpy(ui_g_pitch2_live_pitch2_status->string, "PITCH2");


    ui_proc_string_frame(&ui_g_pitch2_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_pitch2_live_0, sizeof(ui_g_pitch2_live_0));
}

void ui_update_g_pitch2_live(void) {
    ui_g_pitch2_live_0.option.operate_type = 2;

    ui_proc_string_frame(&ui_g_pitch2_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_pitch2_live_0, sizeof(ui_g_pitch2_live_0));
}

void ui_remove_g_pitch2_live(void) {
    ui_g_pitch2_live_0.option.operate_type = 3;

    ui_proc_string_frame(&ui_g_pitch2_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_pitch2_live_0, sizeof(ui_g_pitch2_live_0));
}
ui_string_frame_t ui_g_Ungroup_5;
ui_interface_string_t* ui_g_Ungroup_percent = &(ui_g_Ungroup_5.option);

void _ui_init_g_Ungroup_5() {
    ui_g_Ungroup_5.option.figure_name[0] = 0;
    ui_g_Ungroup_5.option.figure_name[1] = 0;
    ui_g_Ungroup_5.option.figure_name[2] = 6;
    ui_g_Ungroup_5.option.operate_type = 1;

    ui_g_Ungroup_percent->figure_type = 7;
    ui_g_Ungroup_percent->operate_type = 1;
    ui_g_Ungroup_percent->layer = 0;
    ui_g_Ungroup_percent->color = 8;
    ui_g_Ungroup_percent->start_x = 254;
    ui_g_Ungroup_percent->start_y = 527;
    ui_g_Ungroup_percent->width = 2;
    ui_g_Ungroup_percent->font_size = 20;
    ui_g_Ungroup_percent->str_length = 1;
    strcpy(ui_g_Ungroup_percent->string, "%");


    ui_proc_string_frame(&ui_g_Ungroup_5);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_5, sizeof(ui_g_Ungroup_5));
}

void _ui_update_g_Ungroup_5() {
    ui_g_Ungroup_5.option.operate_type = 2;

    ui_proc_string_frame(&ui_g_Ungroup_5);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_5, sizeof(ui_g_Ungroup_5));
}

void _ui_remove_g_Ungroup_5() {
    ui_g_Ungroup_5.option.operate_type = 3;

    ui_proc_string_frame(&ui_g_Ungroup_5);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_5, sizeof(ui_g_Ungroup_5));
}
ui_string_frame_t ui_g_Ungroup_6;
ui_interface_string_t* ui_g_Ungroup_power_label = &(ui_g_Ungroup_6.option);

void _ui_init_g_Ungroup_6() {
    ui_g_Ungroup_6.option.figure_name[0] = 0;
    ui_g_Ungroup_6.option.figure_name[1] = 0;
    ui_g_Ungroup_6.option.figure_name[2] = 7;
    ui_g_Ungroup_6.option.operate_type = 1;

    ui_g_Ungroup_power_label->figure_type = 7;
    ui_g_Ungroup_power_label->operate_type = 1;
    ui_g_Ungroup_power_label->layer = 0;
    ui_g_Ungroup_power_label->color = 8;
    ui_g_Ungroup_power_label->start_x = 28;
    ui_g_Ungroup_power_label->start_y = 524;
    ui_g_Ungroup_power_label->width = 2;
    ui_g_Ungroup_power_label->font_size = 20;
    ui_g_Ungroup_power_label->str_length = 1;
    strcpy(ui_g_Ungroup_power_label->string, "W");


    ui_proc_string_frame(&ui_g_Ungroup_6);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_6, sizeof(ui_g_Ungroup_6));
}

void _ui_update_g_Ungroup_6() {
    ui_g_Ungroup_6.option.operate_type = 2;

    ui_proc_string_frame(&ui_g_Ungroup_6);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_6, sizeof(ui_g_Ungroup_6));
}

void _ui_remove_g_Ungroup_6() {
    ui_g_Ungroup_6.option.operate_type = 3;

    ui_proc_string_frame(&ui_g_Ungroup_6);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_6, sizeof(ui_g_Ungroup_6));
}

void ui_init_g_Ungroup() {
    _ui_init_g_Ungroup_0();
    _ui_init_g_Ungroup_1();
    _ui_init_g_Ungroup_2();
    _ui_init_g_Ungroup_3();
    _ui_init_g_Ungroup_5();
    _ui_init_g_Ungroup_6();
}

void ui_update_g_Ungroup() {
    _ui_update_g_Ungroup_0();
    _ui_update_g_Ungroup_1();
    _ui_update_g_Ungroup_2();
    _ui_update_g_Ungroup_3();
    _ui_update_g_Ungroup_5();
    _ui_update_g_Ungroup_6();
}

void ui_remove_g_Ungroup() {
    _ui_remove_g_Ungroup_0();
    _ui_remove_g_Ungroup_1();
    _ui_remove_g_Ungroup_2();
    _ui_remove_g_Ungroup_3();
    _ui_remove_g_Ungroup_5();
    _ui_remove_g_Ungroup_6();
}

ui_2_frame_t ui_g_cap_live_0;

ui_interface_line_t *ui_g_cap_live_cap_bar = (ui_interface_line_t*)&(ui_g_cap_live_0.data[0]);
ui_interface_number_t *ui_g_cap_live_cap_value = (ui_interface_number_t*)&(ui_g_cap_live_0.data[1]);

void _ui_init_g_cap_live_0() {
    for (int i = 0; i < 2; i++) {
        ui_g_cap_live_0.data[i].figure_name[0] = 0;
        ui_g_cap_live_0.data[i].figure_name[1] = 1;
        ui_g_cap_live_0.data[i].figure_name[2] = i + 0;
        ui_g_cap_live_0.data[i].operate_type = 1;
    }
    for (int i = 2; i < 2; i++) {
        ui_g_cap_live_0.data[i].operate_type = 0;
    }

    ui_g_cap_live_cap_bar->figure_type = 0;
    ui_g_cap_live_cap_bar->operate_type = 1;
    ui_g_cap_live_cap_bar->layer = 0;
    ui_g_cap_live_cap_bar->color = 2;
    ui_g_cap_live_cap_bar->start_x = 88;
    ui_g_cap_live_cap_bar->start_y = 289;
    ui_g_cap_live_cap_bar->width = 8;
    ui_g_cap_live_cap_bar->end_x = 228;
    ui_g_cap_live_cap_bar->end_y = 289;

    ui_g_cap_live_cap_value->figure_type = 6;
    ui_g_cap_live_cap_value->operate_type = 1;
    ui_g_cap_live_cap_value->layer = 0;
    ui_g_cap_live_cap_value->color = 8;
    ui_g_cap_live_cap_value->start_x = 165;
    ui_g_cap_live_cap_value->start_y = 262;
    ui_g_cap_live_cap_value->width = 2;
    ui_g_cap_live_cap_value->font_size = 20;
    ui_g_cap_live_cap_value->number = 70;


    ui_proc_2_frame(&ui_g_cap_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_cap_live_0, sizeof(ui_g_cap_live_0));
}

void _ui_update_g_cap_live_0() {
    for (int i = 0; i < 2; i++) {
        ui_g_cap_live_0.data[i].operate_type = 2;
    }

    ui_proc_2_frame(&ui_g_cap_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_cap_live_0, sizeof(ui_g_cap_live_0));
}

void _ui_remove_g_cap_live_0() {
    for (int i = 0; i < 2; i++) {
        ui_g_cap_live_0.data[i].operate_type = 3;
    }

    ui_proc_2_frame(&ui_g_cap_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_cap_live_0, sizeof(ui_g_cap_live_0));
}


void ui_init_g_cap_live() {
    _ui_init_g_cap_live_0();
}

void ui_update_g_cap_live() {
    _ui_update_g_cap_live_0();
}

void ui_remove_g_cap_live() {
    _ui_remove_g_cap_live_0();
}


ui_string_frame_t ui_g_cap_mode_live_0;
ui_interface_string_t* ui_g_cap_mode_live_cap_mode = &(ui_g_cap_mode_live_0.option);

void _ui_init_g_cap_mode_live_0() {
    ui_g_cap_mode_live_0.option.figure_name[0] = 0;
    ui_g_cap_mode_live_0.option.figure_name[1] = 2;
    ui_g_cap_mode_live_0.option.figure_name[2] = 0;
    ui_g_cap_mode_live_0.option.operate_type = 1;

    ui_g_cap_mode_live_cap_mode->figure_type = 7;
    ui_g_cap_mode_live_cap_mode->operate_type = 1;
    ui_g_cap_mode_live_cap_mode->layer = 0;
    ui_g_cap_mode_live_cap_mode->color = 8;
    ui_g_cap_mode_live_cap_mode->start_x = 121;
    ui_g_cap_mode_live_cap_mode->start_y = 341;
    ui_g_cap_mode_live_cap_mode->width = 2;
    ui_g_cap_mode_live_cap_mode->font_size = 20;
    ui_g_cap_mode_live_cap_mode->str_length = 7;
    strcpy(ui_g_cap_mode_live_cap_mode->string, "CAP: --");


    ui_proc_string_frame(&ui_g_cap_mode_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_cap_mode_live_0, sizeof(ui_g_cap_mode_live_0));
}

void _ui_update_g_cap_mode_live_0() {
    ui_g_cap_mode_live_0.option.operate_type = 2;

    ui_proc_string_frame(&ui_g_cap_mode_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_cap_mode_live_0, sizeof(ui_g_cap_mode_live_0));
}

void _ui_remove_g_cap_mode_live_0() {
    ui_g_cap_mode_live_0.option.operate_type = 3;

    ui_proc_string_frame(&ui_g_cap_mode_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_cap_mode_live_0, sizeof(ui_g_cap_mode_live_0));
}

void ui_init_g_cap_mode_live() {
    _ui_init_g_cap_mode_live_0();
}

void ui_update_g_cap_mode_live() {
    _ui_update_g_cap_mode_live_0();
}

void ui_remove_g_cap_mode_live() {
    _ui_remove_g_cap_mode_live_0();
}


ui_string_frame_t ui_g_chassis_live_0;
ui_interface_string_t* ui_g_chassis_live_chassis_mode = &(ui_g_chassis_live_0.option);

void _ui_init_g_chassis_live_0() {
    ui_g_chassis_live_0.option.figure_name[0] = 0;
    ui_g_chassis_live_0.option.figure_name[1] = 3;
    ui_g_chassis_live_0.option.figure_name[2] = 0;
    ui_g_chassis_live_0.option.operate_type = 1;

    ui_g_chassis_live_chassis_mode->figure_type = 7;
    ui_g_chassis_live_chassis_mode->operate_type = 1;
    ui_g_chassis_live_chassis_mode->layer = 0;
    ui_g_chassis_live_chassis_mode->color = 8;
    ui_g_chassis_live_chassis_mode->start_x = 570;
    ui_g_chassis_live_chassis_mode->start_y = 88;
    ui_g_chassis_live_chassis_mode->width = 2;
    ui_g_chassis_live_chassis_mode->font_size = 20;
    ui_g_chassis_live_chassis_mode->str_length = 11;
    strcpy(ui_g_chassis_live_chassis_mode->string, "CHASSIS: --");


    ui_proc_string_frame(&ui_g_chassis_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_chassis_live_0, sizeof(ui_g_chassis_live_0));
}

void _ui_update_g_chassis_live_0() {
    ui_g_chassis_live_0.option.operate_type = 2;

    ui_proc_string_frame(&ui_g_chassis_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_chassis_live_0, sizeof(ui_g_chassis_live_0));
}

void _ui_remove_g_chassis_live_0() {
    ui_g_chassis_live_0.option.operate_type = 3;

    ui_proc_string_frame(&ui_g_chassis_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_chassis_live_0, sizeof(ui_g_chassis_live_0));
}

void ui_init_g_chassis_live() {
    _ui_init_g_chassis_live_0();
}

void ui_update_g_chassis_live() {
    _ui_update_g_chassis_live_0();
}

void ui_remove_g_chassis_live() {
    _ui_remove_g_chassis_live_0();
}


ui_string_frame_t ui_g_device_live_0;
ui_interface_string_t* ui_g_device_live_yaw_status = &(ui_g_device_live_0.option);

void _ui_init_g_device_live_0() {
    ui_g_device_live_0.option.figure_name[0] = 0;
    ui_g_device_live_0.option.figure_name[1] = 4;
    ui_g_device_live_0.option.figure_name[2] = 0;
    ui_g_device_live_0.option.operate_type = 1;

    ui_g_device_live_yaw_status->figure_type = 7;
    ui_g_device_live_yaw_status->operate_type = 1;
    ui_g_device_live_yaw_status->layer = 0;
    ui_g_device_live_yaw_status->color = 8;
    ui_g_device_live_yaw_status->start_x = 833;
    ui_g_device_live_yaw_status->start_y = 44;
    ui_g_device_live_yaw_status->width = 2;
    ui_g_device_live_yaw_status->font_size = 15;
    ui_g_device_live_yaw_status->str_length = 3;
    strcpy(ui_g_device_live_yaw_status->string, "YAW");


    ui_proc_string_frame(&ui_g_device_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_device_live_0, sizeof(ui_g_device_live_0));
}

void _ui_update_g_device_live_0() {
    ui_g_device_live_0.option.operate_type = 2;

    ui_proc_string_frame(&ui_g_device_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_device_live_0, sizeof(ui_g_device_live_0));
}

void _ui_remove_g_device_live_0() {
    ui_g_device_live_0.option.operate_type = 3;

    ui_proc_string_frame(&ui_g_device_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_device_live_0, sizeof(ui_g_device_live_0));
}
ui_string_frame_t ui_g_device_live_1;
ui_interface_string_t* ui_g_device_live_pitch_status = &(ui_g_device_live_1.option);

void _ui_init_g_device_live_1() {
    ui_g_device_live_1.option.figure_name[0] = 0;
    ui_g_device_live_1.option.figure_name[1] = 4;
    ui_g_device_live_1.option.figure_name[2] = 1;
    ui_g_device_live_1.option.operate_type = 1;

    ui_g_device_live_pitch_status->figure_type = 7;
    ui_g_device_live_pitch_status->operate_type = 1;
    ui_g_device_live_pitch_status->layer = 0;
    ui_g_device_live_pitch_status->color = 8;
    ui_g_device_live_pitch_status->start_x = 915;
    ui_g_device_live_pitch_status->start_y = 44;
    ui_g_device_live_pitch_status->width = 2;
    ui_g_device_live_pitch_status->font_size = 15;
    ui_g_device_live_pitch_status->str_length = 6;
    strcpy(ui_g_device_live_pitch_status->string, "PITCH1");


    ui_proc_string_frame(&ui_g_device_live_1);
    SEND_MESSAGE((uint8_t *) &ui_g_device_live_1, sizeof(ui_g_device_live_1));
}

void _ui_update_g_device_live_1() {
    ui_g_device_live_1.option.operate_type = 2;

    ui_proc_string_frame(&ui_g_device_live_1);
    SEND_MESSAGE((uint8_t *) &ui_g_device_live_1, sizeof(ui_g_device_live_1));
}

void _ui_remove_g_device_live_1() {
    ui_g_device_live_1.option.operate_type = 3;

    ui_proc_string_frame(&ui_g_device_live_1);
    SEND_MESSAGE((uint8_t *) &ui_g_device_live_1, sizeof(ui_g_device_live_1));
}
ui_string_frame_t ui_g_device_live_2;
ui_interface_string_t* ui_g_device_live_feed_status = &(ui_g_device_live_2.option);

void _ui_init_g_device_live_2() {
    ui_g_device_live_2.option.figure_name[0] = 0;
    ui_g_device_live_2.option.figure_name[1] = 4;
    ui_g_device_live_2.option.figure_name[2] = 2;
    ui_g_device_live_2.option.operate_type = 1;

    ui_g_device_live_feed_status->figure_type = 7;
    ui_g_device_live_feed_status->operate_type = 1;
    ui_g_device_live_feed_status->layer = 0;
    ui_g_device_live_feed_status->color = 8;
    ui_g_device_live_feed_status->start_x = 1186;
    ui_g_device_live_feed_status->start_y = 43;
    ui_g_device_live_feed_status->width = 2;
    ui_g_device_live_feed_status->font_size = 15;
    ui_g_device_live_feed_status->str_length = 4;
    strcpy(ui_g_device_live_feed_status->string, "FEED");


    ui_proc_string_frame(&ui_g_device_live_2);
    SEND_MESSAGE((uint8_t *) &ui_g_device_live_2, sizeof(ui_g_device_live_2));
}

void _ui_update_g_device_live_2() {
    ui_g_device_live_2.option.operate_type = 2;

    ui_proc_string_frame(&ui_g_device_live_2);
    SEND_MESSAGE((uint8_t *) &ui_g_device_live_2, sizeof(ui_g_device_live_2));
}

void _ui_remove_g_device_live_2() {
    ui_g_device_live_2.option.operate_type = 3;

    ui_proc_string_frame(&ui_g_device_live_2);
    SEND_MESSAGE((uint8_t *) &ui_g_device_live_2, sizeof(ui_g_device_live_2));
}
ui_string_frame_t ui_g_device_live_3;
ui_interface_string_t* ui_g_device_live_fric_status = &(ui_g_device_live_3.option);

void _ui_init_g_device_live_3() {
    ui_g_device_live_3.option.figure_name[0] = 0;
    ui_g_device_live_3.option.figure_name[1] = 4;
    ui_g_device_live_3.option.figure_name[2] = 3;
    ui_g_device_live_3.option.operate_type = 1;

    ui_g_device_live_fric_status->figure_type = 7;
    ui_g_device_live_fric_status->operate_type = 1;
    ui_g_device_live_fric_status->layer = 0;
    ui_g_device_live_fric_status->color = 8;
    ui_g_device_live_fric_status->start_x = 1287;
    ui_g_device_live_fric_status->start_y = 43;
    ui_g_device_live_fric_status->width = 2;
    ui_g_device_live_fric_status->font_size = 15;
    ui_g_device_live_fric_status->str_length = 4;
    strcpy(ui_g_device_live_fric_status->string, "FRIC");


    ui_proc_string_frame(&ui_g_device_live_3);
    SEND_MESSAGE((uint8_t *) &ui_g_device_live_3, sizeof(ui_g_device_live_3));
}

void _ui_update_g_device_live_3() {
    ui_g_device_live_3.option.operate_type = 2;

    ui_proc_string_frame(&ui_g_device_live_3);
    SEND_MESSAGE((uint8_t *) &ui_g_device_live_3, sizeof(ui_g_device_live_3));
}

void _ui_remove_g_device_live_3() {
    ui_g_device_live_3.option.operate_type = 3;

    ui_proc_string_frame(&ui_g_device_live_3);
    SEND_MESSAGE((uint8_t *) &ui_g_device_live_3, sizeof(ui_g_device_live_3));
}

void ui_init_g_device_live() {
    _ui_init_g_device_live_0();
    _ui_init_g_device_live_1();
    _ui_init_g_device_live_2();
    _ui_init_g_device_live_3();
}

void ui_update_g_device_live() {
    _ui_update_g_device_live_0();
    _ui_update_g_device_live_1();
    _ui_update_g_device_live_2();
    _ui_update_g_device_live_3();
}

void ui_remove_g_device_live() {
    _ui_remove_g_device_live_0();
    _ui_remove_g_device_live_1();
    _ui_remove_g_device_live_2();
    _ui_remove_g_device_live_3();
}

ui_5_frame_t ui_g_drive_live_0;

ui_interface_round_t *ui_g_drive_live_drive_1 = (ui_interface_round_t*)&(ui_g_drive_live_0.data[0]);
ui_interface_round_t *ui_g_drive_live_drive_2 = (ui_interface_round_t*)&(ui_g_drive_live_0.data[1]);
ui_interface_round_t *ui_g_drive_live_drive_3 = (ui_interface_round_t*)&(ui_g_drive_live_0.data[2]);
ui_interface_round_t *ui_g_drive_live_drive_4 = (ui_interface_round_t*)&(ui_g_drive_live_0.data[3]);

void _ui_init_g_drive_live_0() {
    for (int i = 0; i < 4; i++) {
        ui_g_drive_live_0.data[i].figure_name[0] = 0;
        ui_g_drive_live_0.data[i].figure_name[1] = 5;
        ui_g_drive_live_0.data[i].figure_name[2] = i + 0;
        ui_g_drive_live_0.data[i].operate_type = 1;
    }
    for (int i = 4; i < 5; i++) {
        ui_g_drive_live_0.data[i].operate_type = 0;
    }

    ui_g_drive_live_drive_1->figure_type = 2;
    ui_g_drive_live_drive_1->operate_type = 1;
    ui_g_drive_live_drive_1->layer = 0;
    ui_g_drive_live_drive_1->color = 8;
    ui_g_drive_live_drive_1->start_x = 1436;
    ui_g_drive_live_drive_1->start_y = 35;
    ui_g_drive_live_drive_1->width = 3;
    ui_g_drive_live_drive_1->r = 10;

    ui_g_drive_live_drive_2->figure_type = 2;
    ui_g_drive_live_drive_2->operate_type = 1;
    ui_g_drive_live_drive_2->layer = 0;
    ui_g_drive_live_drive_2->color = 8;
    ui_g_drive_live_drive_2->start_x = 1489;
    ui_g_drive_live_drive_2->start_y = 35;
    ui_g_drive_live_drive_2->width = 3;
    ui_g_drive_live_drive_2->r = 10;

    ui_g_drive_live_drive_3->figure_type = 2;
    ui_g_drive_live_drive_3->operate_type = 1;
    ui_g_drive_live_drive_3->layer = 0;
    ui_g_drive_live_drive_3->color = 8;
    ui_g_drive_live_drive_3->start_x = 1542;
    ui_g_drive_live_drive_3->start_y = 35;
    ui_g_drive_live_drive_3->width = 3;
    ui_g_drive_live_drive_3->r = 10;

    ui_g_drive_live_drive_4->figure_type = 2;
    ui_g_drive_live_drive_4->operate_type = 1;
    ui_g_drive_live_drive_4->layer = 0;
    ui_g_drive_live_drive_4->color = 8;
    ui_g_drive_live_drive_4->start_x = 1595;
    ui_g_drive_live_drive_4->start_y = 35;
    ui_g_drive_live_drive_4->width = 3;
    ui_g_drive_live_drive_4->r = 10;


    ui_proc_5_frame(&ui_g_drive_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_drive_live_0, sizeof(ui_g_drive_live_0));
}

void _ui_update_g_drive_live_0() {
    for (int i = 0; i < 4; i++) {
        ui_g_drive_live_0.data[i].operate_type = 2;
    }

    ui_proc_5_frame(&ui_g_drive_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_drive_live_0, sizeof(ui_g_drive_live_0));
}

void _ui_remove_g_drive_live_0() {
    for (int i = 0; i < 4; i++) {
        ui_g_drive_live_0.data[i].operate_type = 3;
    }

    ui_proc_5_frame(&ui_g_drive_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_drive_live_0, sizeof(ui_g_drive_live_0));
}


void ui_init_g_drive_live() {
    _ui_init_g_drive_live_0();
}

void ui_update_g_drive_live() {
    _ui_update_g_drive_live_0();
}

void ui_remove_g_drive_live() {
    _ui_remove_g_drive_live_0();
}

ui_1_frame_t ui_g_heading_live_0;

ui_interface_round_t *ui_g_heading_live_heading_dot = (ui_interface_round_t*)&(ui_g_heading_live_0.data[0]);

void _ui_init_g_heading_live_0() {
    for (int i = 0; i < 1; i++) {
        ui_g_heading_live_0.data[i].figure_name[0] = 0;
        ui_g_heading_live_0.data[i].figure_name[1] = 6;
        ui_g_heading_live_0.data[i].figure_name[2] = i + 0;
        ui_g_heading_live_0.data[i].operate_type = 1;
    }
    for (int i = 1; i < 1; i++) {
        ui_g_heading_live_0.data[i].operate_type = 0;
    }

    ui_g_heading_live_heading_dot->figure_type = 2;
    ui_g_heading_live_heading_dot->operate_type = 1;
    ui_g_heading_live_heading_dot->layer = 0;
    ui_g_heading_live_heading_dot->color = 0;
    ui_g_heading_live_heading_dot->start_x = 957;
    ui_g_heading_live_heading_dot->start_y = 933;
    ui_g_heading_live_heading_dot->width = 8;
    ui_g_heading_live_heading_dot->r = 4;


    ui_proc_1_frame(&ui_g_heading_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_heading_live_0, sizeof(ui_g_heading_live_0));
}

void _ui_update_g_heading_live_0() {
    for (int i = 0; i < 1; i++) {
        ui_g_heading_live_0.data[i].operate_type = 2;
    }

    ui_proc_1_frame(&ui_g_heading_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_heading_live_0, sizeof(ui_g_heading_live_0));
}

void _ui_remove_g_heading_live_0() {
    for (int i = 0; i < 1; i++) {
        ui_g_heading_live_0.data[i].operate_type = 3;
    }

    ui_proc_1_frame(&ui_g_heading_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_heading_live_0, sizeof(ui_g_heading_live_0));
}


void ui_init_g_heading_live() {
    _ui_init_g_heading_live_0();
}

void ui_update_g_heading_live() {
    _ui_update_g_heading_live_0();
}

void ui_remove_g_heading_live() {
    _ui_remove_g_heading_live_0();
}


ui_string_frame_t ui_g_mode_live_0;
ui_interface_string_t* ui_g_mode_live_shoot_mode = &(ui_g_mode_live_0.option);

void _ui_init_g_mode_live_0() {
    ui_g_mode_live_0.option.figure_name[0] = 0;
    ui_g_mode_live_0.option.figure_name[1] = 7;
    ui_g_mode_live_0.option.figure_name[2] = 0;
    ui_g_mode_live_0.option.operate_type = 1;

    ui_g_mode_live_shoot_mode->figure_type = 7;
    ui_g_mode_live_shoot_mode->operate_type = 1;
    ui_g_mode_live_shoot_mode->layer = 0;
    ui_g_mode_live_shoot_mode->color = 8;
    ui_g_mode_live_shoot_mode->start_x = 1190;
    ui_g_mode_live_shoot_mode->start_y = 88;
    ui_g_mode_live_shoot_mode->width = 2;
    ui_g_mode_live_shoot_mode->font_size = 20;
    ui_g_mode_live_shoot_mode->str_length = 9;
    strcpy(ui_g_mode_live_shoot_mode->string, "SHOOT: --");


    ui_proc_string_frame(&ui_g_mode_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_mode_live_0, sizeof(ui_g_mode_live_0));
}

void _ui_update_g_mode_live_0() {
    ui_g_mode_live_0.option.operate_type = 2;

    ui_proc_string_frame(&ui_g_mode_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_mode_live_0, sizeof(ui_g_mode_live_0));
}

void _ui_remove_g_mode_live_0() {
    ui_g_mode_live_0.option.operate_type = 3;

    ui_proc_string_frame(&ui_g_mode_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_mode_live_0, sizeof(ui_g_mode_live_0));
}

void ui_init_g_mode_live() {
    _ui_init_g_mode_live_0();
}

void ui_update_g_mode_live() {
    _ui_update_g_mode_live_0();
}

void ui_remove_g_mode_live() {
    _ui_remove_g_mode_live_0();
}

ui_1_frame_t ui_g_pitch_live_0;

ui_interface_number_t *ui_g_pitch_live_pitch_value = (ui_interface_number_t*)&(ui_g_pitch_live_0.data[0]);

void _ui_init_g_pitch_live_0() {
    for (int i = 0; i < 1; i++) {
        ui_g_pitch_live_0.data[i].figure_name[0] = 0;
        ui_g_pitch_live_0.data[i].figure_name[1] = 8;
        ui_g_pitch_live_0.data[i].figure_name[2] = i + 0;
        ui_g_pitch_live_0.data[i].operate_type = 1;
    }
    for (int i = 1; i < 1; i++) {
        ui_g_pitch_live_0.data[i].operate_type = 0;
    }

    ui_g_pitch_live_pitch_value->figure_type = 5;
    ui_g_pitch_live_pitch_value->operate_type = 1;
    ui_g_pitch_live_pitch_value->layer = 0;
    ui_g_pitch_live_pitch_value->color = 8;
    ui_g_pitch_live_pitch_value->start_x = 178;
    ui_g_pitch_live_pitch_value->start_y = 481;
    ui_g_pitch_live_pitch_value->width = 2;
    ui_g_pitch_live_pitch_value->font_size = 20;
    ui_g_pitch_live_pitch_value->number = 0;


    ui_proc_1_frame(&ui_g_pitch_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_pitch_live_0, sizeof(ui_g_pitch_live_0));
}

void _ui_update_g_pitch_live_0() {
    for (int i = 0; i < 1; i++) {
        ui_g_pitch_live_0.data[i].operate_type = 2;
    }

    ui_proc_1_frame(&ui_g_pitch_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_pitch_live_0, sizeof(ui_g_pitch_live_0));
}

void _ui_remove_g_pitch_live_0() {
    for (int i = 0; i < 1; i++) {
        ui_g_pitch_live_0.data[i].operate_type = 3;
    }

    ui_proc_1_frame(&ui_g_pitch_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_pitch_live_0, sizeof(ui_g_pitch_live_0));
}


void ui_init_g_pitch_live() {
    _ui_init_g_pitch_live_0();
}

void ui_update_g_pitch_live() {
    _ui_update_g_pitch_live_0();
}

void ui_remove_g_pitch_live() {
    _ui_remove_g_pitch_live_0();
}

ui_1_frame_t ui_g_power_live_0;

ui_interface_number_t *ui_g_power_live_power_value = (ui_interface_number_t*)&(ui_g_power_live_0.data[0]);

void _ui_init_g_power_live_0() {
    for (int i = 0; i < 1; i++) {
        ui_g_power_live_0.data[i].figure_name[0] = 0;
        ui_g_power_live_0.data[i].figure_name[1] = 9;
        ui_g_power_live_0.data[i].figure_name[2] = i + 0;
        ui_g_power_live_0.data[i].operate_type = 1;
    }
    for (int i = 1; i < 1; i++) {
        ui_g_power_live_0.data[i].operate_type = 0;
    }

    ui_g_power_live_power_value->figure_type = 6;
    ui_g_power_live_power_value->operate_type = 1;
    ui_g_power_live_power_value->layer = 0;
    ui_g_power_live_power_value->color = 8;
    ui_g_power_live_power_value->start_x = 178;
    ui_g_power_live_power_value->start_y = 527;
    ui_g_power_live_power_value->width = 2;
    ui_g_power_live_power_value->font_size = 20;
    ui_g_power_live_power_value->number = 0;


    ui_proc_1_frame(&ui_g_power_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_power_live_0, sizeof(ui_g_power_live_0));
}

void _ui_update_g_power_live_0() {
    for (int i = 0; i < 1; i++) {
        ui_g_power_live_0.data[i].operate_type = 2;
    }

    ui_proc_1_frame(&ui_g_power_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_power_live_0, sizeof(ui_g_power_live_0));
}

void _ui_remove_g_power_live_0() {
    for (int i = 0; i < 1; i++) {
        ui_g_power_live_0.data[i].operate_type = 3;
    }

    ui_proc_1_frame(&ui_g_power_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_power_live_0, sizeof(ui_g_power_live_0));
}


void ui_init_g_power_live() {
    _ui_init_g_power_live_0();
}

void ui_update_g_power_live() {
    _ui_update_g_power_live_0();
}

void ui_remove_g_power_live() {
    _ui_remove_g_power_live_0();
}

ui_1_frame_t ui_g_speed_live_0;

ui_interface_number_t *ui_g_speed_live_vx_value = (ui_interface_number_t*)&(ui_g_speed_live_0.data[0]);

void _ui_init_g_speed_live_0() {
    for (int i = 0; i < 1; i++) {
        ui_g_speed_live_0.data[i].figure_name[0] = 0;
        ui_g_speed_live_0.data[i].figure_name[1] = 10;
        ui_g_speed_live_0.data[i].figure_name[2] = i + 0;
        ui_g_speed_live_0.data[i].operate_type = 1;
    }
    for (int i = 1; i < 1; i++) {
        ui_g_speed_live_0.data[i].operate_type = 0;
    }

    ui_g_speed_live_vx_value->figure_type = 5;
    ui_g_speed_live_vx_value->operate_type = 1;
    ui_g_speed_live_vx_value->layer = 0;
    ui_g_speed_live_vx_value->color = 8;
    ui_g_speed_live_vx_value->start_x = 176;
    ui_g_speed_live_vx_value->start_y = 436;
    ui_g_speed_live_vx_value->width = 2;
    ui_g_speed_live_vx_value->font_size = 20;
    ui_g_speed_live_vx_value->number = 1250;


    ui_proc_1_frame(&ui_g_speed_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_speed_live_0, sizeof(ui_g_speed_live_0));
}

void _ui_update_g_speed_live_0() {
    for (int i = 0; i < 1; i++) {
        ui_g_speed_live_0.data[i].operate_type = 2;
    }

    ui_proc_1_frame(&ui_g_speed_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_speed_live_0, sizeof(ui_g_speed_live_0));
}

void _ui_remove_g_speed_live_0() {
    for (int i = 0; i < 1; i++) {
        ui_g_speed_live_0.data[i].operate_type = 3;
    }

    ui_proc_1_frame(&ui_g_speed_live_0);
    SEND_MESSAGE((uint8_t *) &ui_g_speed_live_0, sizeof(ui_g_speed_live_0));
}


void ui_init_g_speed_live() {
    _ui_init_g_speed_live_0();
}

void ui_update_g_speed_live() {
    _ui_update_g_speed_live_0();
}

void ui_remove_g_speed_live() {
    _ui_remove_g_speed_live_0();
}

