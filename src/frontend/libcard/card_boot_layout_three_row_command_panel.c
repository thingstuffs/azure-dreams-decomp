#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800233D0_arg0.h"


typedef struct S_80023600_2 {
    u8 pad_00[0x1A8];
    void * unk_1A8;
    u8 pad_1AC[0xC];
    void * unk_1B8;
    u8 pad_1BC[0xC];
    void * unk_1C8;
    u8 pad_1CC[0xC];
    void * unk_1D8;
} S_80023600_2;

typedef struct S_80023600_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023600_3;   /* ((Rec_func_800233D0_arg0 *)arg0)->unk_1A0 in card_boot_layout_three_row_command_panel */

typedef struct S_80023600_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023600_4;

typedef struct S_80023600_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023600_5;

typedef struct S_80023600_6 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023600_6;

typedef struct S_80023600_7 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023600_7;

typedef struct S_80023600_8 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80023600_8;   /* ((S_80023600_3 *)(((Rec_func_800233D0_arg0 *)arg0)->unk_1A0))->unk_04 in card_boot_layout_three_row_command_panel */

typedef struct S_80023600_9 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80023600_9;

typedef struct S_80023600_10 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80023600_10;

typedef struct S_80023600_11 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80023600_11;

typedef struct S_80023600_12 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80023600_12;


#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"

/* Initialize the panel and position its elements in three rows. */
void card_boot_layout_three_row_command_panel(void *panel) {
    s32 lower_x;
    s32 left_x;
    s32 right_x;
    s32 middle_x;
    s32 row_y;
    s32 lower_y;
    s32 row_index;

    ((Rec_func_800233D0_arg0 *)panel)->unk_80 = 1;
    ((Rec_func_800233D0_arg0 *)panel)->unk_84 = 1;
    card_boot_format_command_panel_labels(panel);
    card_boot_set_centered_rectangle((s32)(panel + 4), 0x36, 0x10);
    card_boot_bind_command_panel_resources(panel);
    row_index = 0;
    lower_x = 0x8E;
    left_x = 9;
    right_x = 0x42;
    middle_x = 0x24;
    row_y = 0xA;
    lower_y = 0x82;
    ((S_80023600_8 *)(((S_80023600_3 *)(((Rec_func_800233D0_arg0 *)panel)->unk_1A0))->unk_04))->unk_0A = 0x1A;
    do {
        ((S_80023600_9 *)(((S_80023600_4 *)(((S_80023600_2 *)((u8 *)panel + row_index * 4))->unk_1D8))->unk_04))->unk_08 = lower_x;
        ((S_80023600_9 *)(((S_80023600_4 *)(((S_80023600_2 *)((u8 *)panel + row_index * 4))->unk_1D8))->unk_04))->unk_0A = lower_y;
        ((S_80023600_10 *)(((S_80023600_5 *)(((S_80023600_2 *)((u8 *)panel + row_index * 4))->unk_1A8))->unk_04))->unk_08 = left_x;
        ((S_80023600_10 *)(((S_80023600_5 *)(((S_80023600_2 *)((u8 *)panel + row_index * 4))->unk_1A8))->unk_04))->unk_0A = row_y;
        ((S_80023600_11 *)(((S_80023600_6 *)(((S_80023600_2 *)((u8 *)panel + row_index * 4))->unk_1B8))->unk_04))->unk_08 = right_x;
        ((S_80023600_11 *)(((S_80023600_6 *)(((S_80023600_2 *)((u8 *)panel + row_index * 4))->unk_1B8))->unk_04))->unk_0A = row_y;
        ((S_80023600_12 *)(((S_80023600_7 *)(((S_80023600_2 *)((u8 *)panel + row_index * 4))->unk_1C8))->unk_04))->unk_08 = middle_x;
        lower_y += 0x10;
        ((S_80023600_12 *)(((S_80023600_7 *)(((S_80023600_2 *)((u8 *)panel + row_index * 4))->unk_1C8))->unk_04))->unk_0A = row_y;
        row_y += 0x10;
        row_index += 1;
    } while (row_index < 3);
    card_boot_reset_three_row_highlight(panel);
}
