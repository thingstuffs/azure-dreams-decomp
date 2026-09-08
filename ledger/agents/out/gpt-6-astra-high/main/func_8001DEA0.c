#include "common.h"
#include "m2c_compat.h"

typedef struct S_80404EA0_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80404EA0_3;   /* temp_s2 in func_80404EA0 */

typedef struct S_80404EA0_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    u32 unk_1C;
    u8 pad_20[0x4];
    s32 unk_24;
    u8 pad_28[0x4];
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
} S_80404EA0_4;   /* D_8009DDD8 + (((S_80404EA0_0 *)arg0)->unk_7C << 7) in func_80404EA0 */

typedef struct S_80404EA0_5 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80404EA0_5;   /* ((S_80404EA0_3 *)temp_s2)->unk_04 in func_80404EA0 */


typedef struct S_80404EA0_0 {
    u8 pad_00[0x7C];
    s32 unk_7C;
    u8 pad_80[0xA98];
    void * unk_B18;
    void * unk_B1C;
    void * unk_B20;
    void * unk_B24;
    void * unk_B28;
    void * unk_B2C;
    void * unk_B30;
} S_80404EA0_0;   /* arg0 in func_80404EA0 */

typedef struct S_80404EA0_1 {
    union { void * s; s32 u; } unk_00;   /* accessed as both */
} S_80404EA0_1;   /* temp_s2 in func_80404EA0 */

typedef struct S_80404EA0_2 {
    u8 pad_00[0xB34];
    void * unk_B34;
} S_80404EA0_2;   /* var_a1 in func_80404EA0 */

typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} Copy4;

M2C_UNK func_8003830C();                  /* extern */
M2C_UNK func_80051520();      /* extern */
M2C_UNK func_80051804();         /* extern */
M2C_UNK func_8005184C();         /* extern */
M2C_UNK func_80051898();                  /* extern */
M2C_UNK func_80051900();                       /* extern */
M2C_UNK func_80051B50(); /* extern */
M2C_UNK func_8007BF50();                /* extern */
M2C_UNK func_8007BF80();                  /* extern */
extern M2C_UNK D_8009DDE4[];
extern s16 D_80400660[];
extern s32 D_80400668[];
extern s16 D_804006AC[];
extern s16 D_804006BC[];
extern s16 D_804006C0[];
extern s32 D_80408CF4[];
extern s32 D_80408CFC[];
extern u8 D_8009DDD8[];
__asm__(".set D_8009DDD8, 0x8009DDD8");

/* Build the selected slot's text fields and position its status icons. */
void func_80404EA0(void *panel) {
    s16 text_buf[32];
    s16 number_buf[8];
    s16 time_buf[4];
    s16 icon_x;
    s32 *icon_cursor;
    s32 *inactive_icon;
    s32 icon_index;
    s32 icon_data;
    s32 bit_one;
    s16 icon_y;
    u32 hours;
    u32 mins;
    u32 minute_quotient;
    u32 secs;
    u32 second_quotient;
    void *slot_text;
    void *detail_text;
    void *value_text;
    void *time_text;
    void *count_text;
    void *footer_text;
    S_80404EA0_1 *widget;
    void *widget_cursor;
    void *footer_buf;
    s32 *icon_table;

    widget = ((S_80404EA0_0 *)panel)->unk_B18;
    func_8003830C(((S_80404EA0_0 *)panel)->unk_7C + 1, text_buf);
    func_8007BF50(text_buf, D_80400660);
    func_8007BF50(text_buf, (s16 *)((((S_80404EA0_0 *)panel)->unk_7C << 7) + (s32)&D_8009DDE4));
    slot_text = panel + 0x80;
    func_80051B50(slot_text, text_buf, 1);
    widget->unk_00.s = slot_text;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->unk_08 = 0xA9;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->unk_0A = 0x110;
    widget = ((S_80404EA0_0 *)panel)->unk_B1C;
    memcpy(text_buf, D_80400668, 0x2A);
    func_80051B50(panel + 0x188, text_buf, 1);
    widget->unk_00.s = panel + 0x188;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->unk_08 = 0xBC;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->unk_0A = 0x110;
    if (((S_80404EA0_4 *)(D_8009DDD8 + (((S_80404EA0_0 *)panel)->unk_7C << 7)))->unk_08 != 0) {
        widget = ((S_80404EA0_0 *)panel)->unk_B20;
        func_8007BF80(text_buf, D_80408CF4[0]);
        func_8003830C(((S_80404EA0_4 *)(D_8009DDD8 + (((S_80404EA0_0 *)panel)->unk_7C << 7)))->unk_34, number_buf);
        func_8007BF50(text_buf, number_buf);
        func_8007BF50(text_buf, D_804006AC);
        detail_text = panel + 0x290;
        func_80051B50(detail_text, text_buf, 1);
        widget->unk_00.s = detail_text;
        ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->unk_08 = 0xBC;
        ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->unk_0A = 0x140;
    }
    widget = ((S_80404EA0_0 *)panel)->unk_B24;
    func_80051804(((S_80404EA0_4 *)(D_8009DDD8 + (((S_80404EA0_0 *)panel)->unk_7C << 7)))->unk_24, 0xA, text_buf);
    func_80051900(text_buf);
    value_text = panel + 0x398;
    func_80051520(value_text, text_buf, 1);
    widget->unk_00.s = value_text;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->unk_08 = 0x140;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->unk_0A = 0x110;
    widget = ((S_80404EA0_0 *)panel)->unk_B28;
    func_80051898(((S_80404EA0_4 *)(D_8009DDD8 + (((S_80404EA0_0 *)panel)->unk_7C << 7)))->unk_1C, text_buf);
    hours = ((S_80404EA0_4 *)(D_8009DDD8 + (((S_80404EA0_0 *)panel)->unk_7C << 7)))->unk_1C / 216000;
    func_80051804(hours, 3, text_buf);
    func_8007BF50(text_buf, D_804006BC);
    mins = ((S_80404EA0_4 *)(D_8009DDD8 + (((S_80404EA0_0 *)panel)->unk_7C << 7)))->unk_1C / 3600;
    minute_quotient = mins / 3600;
    func_8005184C(mins - minute_quotient * 3600, 2, time_buf);
    func_8007BF50(text_buf, time_buf);
    func_8007BF50(text_buf, D_804006BC);
    secs = ((S_80404EA0_4 *)(D_8009DDD8 + (((S_80404EA0_0 *)panel)->unk_7C << 7)))->unk_1C / 60;
    second_quotient = secs / 60;
    func_8005184C(secs - second_quotient * 60, 2, time_buf);
    func_8007BF50(text_buf, time_buf);
    func_80051900(text_buf);
    time_text = panel + 0x4A0;
    func_80051520(time_text, text_buf, 1);
    widget->unk_00.s = time_text;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->unk_08 = 0x147;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->unk_0A = 0x120;
    widget = ((S_80404EA0_0 *)panel)->unk_B2C;
    func_80051804(((S_80404EA0_4 *)(D_8009DDD8 + (((S_80404EA0_0 *)panel)->unk_7C << 7)))->unk_2C, 4, text_buf);
    func_80051900(text_buf);
    count_text = panel + 0x5A8;
    func_80051520(count_text, text_buf, 1);
    widget->unk_00.s = count_text;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->unk_08 = 0xF2;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->unk_0A = 0x120;
    widget = ((S_80404EA0_0 *)panel)->unk_B30;
    memcpy(text_buf, D_804006C0, 3);
    footer_buf = text_buf;
    func_80051900(footer_buf);
    footer_text = panel + 0x6B0;
    func_80051520(footer_text, footer_buf, 1);
    icon_index = 0;
    bit_one = 1;
    icon_table = D_80408CFC;
    inactive_icon = icon_table + 10;
    icon_y = 0xB0;
    icon_x = 0x38;
    icon_cursor = icon_table;
    widget_cursor = panel;
    widget->unk_00.s = footer_text;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->unk_08 = 0x180;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->unk_0A = 0x130;
    do {
        widget = ((S_80404EA0_2 *)widget_cursor)->unk_B34;
        if ((bit_one << icon_index) & ((S_80404EA0_4 *)(D_8009DDD8 + (((S_80404EA0_0 *)panel)->unk_7C << 7)))->unk_30) {
            icon_data = *icon_cursor;
        } else {
            icon_data = *inactive_icon;
        }
        icon_cursor += 1;
        widget_cursor += 4;
        widget->unk_00.u = icon_data;
        icon_index += 1;
        ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->unk_08 = icon_x;
        ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->unk_0A = icon_y;
        icon_x += 0x10;
    } while (icon_index < 0xA);
}
