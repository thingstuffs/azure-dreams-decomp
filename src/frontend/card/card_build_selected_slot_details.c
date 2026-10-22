#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "main/data.h"

typedef struct S_80404EA0_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80404EA0_3;

typedef struct S_80404EA0_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    u32 play_frames; /* 0x1C */
    u8 pad_20[0x4];
    s32 unk_24;
    u8 pad_28[0x4];
    s32 unk_2C;
    s32 icon_flags; /* 0x30 */
    s32 unk_34;
} S_80404EA0_4;   /* D_8009DDD8 + (((S_80404EA0_0 *)arg0)->slot_index << 7) in card_build_selected_slot_details */

typedef struct S_80404EA0_5 {
    u8 pad_00[0x8];
    s16 x; /* 0x08 */
    s16 y; /* 0x0A */
} S_80404EA0_5;


typedef struct S_80404EA0_0 {
    u8 pad_00[0x7C];
    s32 slot_index; /* 0x7C */
    u8 pad_80[0xA98];
    void * slot_widget; /* 0xB18 */
    void * label_widget; /* 0xB1C */
    void * detail_widget; /* 0xB20 */
    void * value_widget; /* 0xB24 */
    void * time_widget; /* 0xB28 */
    void * count_widget; /* 0xB2C */
    void * footer_widget; /* 0xB30 */
} S_80404EA0_0;   /* arg0 in card_build_selected_slot_details */

typedef struct S_80404EA0_1 {
    union { void * s; s32 u; } unk_00;   /* accessed as both */
} S_80404EA0_1;

typedef struct S_80404EA0_2 {
    u8 pad_00[0xB34];
    void * icon_widget; /* 0xB34 */
} S_80404EA0_2;

typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} Copy4;
void func_8003830C(s32 value, void *text);                  /* extern */
void func_80051520(void *, void *, s32);      /* extern */
void func_80051804(u32 value, s32 digits, void *text);         /* extern */
void func_8005184C(s32, s32, void *);         /* extern */
void func_80051898(u32, void *);                  /* extern */
void func_80051900(void *);                       /* extern */
void func_80051B50(void *, void *, s32); /* extern */
void func_8007BF50(void *, void *);                /* extern */
void func_8007BF80(void *, s32);                  /* extern */
extern M2C_UNK D_8009DDE4[];
extern u8 card_slot_header_cache[];

/* Build the selected slot's text fields and position its status icons. */
void card_build_selected_slot_details(void *panel) {
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

    widget = ((S_80404EA0_0 *)panel)->slot_widget;
    func_8003830C(((S_80404EA0_0 *)panel)->slot_index + 1, text_buf);
    func_8007BF50(text_buf, D_80400660);
    func_8007BF50(text_buf, (s16 *)((((S_80404EA0_0 *)panel)->slot_index << 7) + (s32)&D_8009DDE4));
    slot_text = panel + 0x80;
    func_80051B50(slot_text, text_buf, 1);
    widget->unk_00.s = slot_text;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->x = 0xA9;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->y = 0x110;
    widget = ((S_80404EA0_0 *)panel)->label_widget;
    memcpy(text_buf, D_80400668, 0x2A);
    func_80051B50(panel + 0x188, text_buf, 1);
    widget->unk_00.s = panel + 0x188;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->x = 0xBC;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->y = 0x110;
    if (((S_80404EA0_4 *)(card_slot_header_cache + (((S_80404EA0_0 *)panel)->slot_index << 7)))->unk_08 != 0) {
        widget = ((S_80404EA0_0 *)panel)->detail_widget;
        func_8007BF80(text_buf, D_80408CF4[0]);
        func_8003830C(((S_80404EA0_4 *)(card_slot_header_cache + (((S_80404EA0_0 *)panel)->slot_index << 7)))->unk_34, number_buf);
        func_8007BF50(text_buf, number_buf);
        func_8007BF50(text_buf, D_804006AC);
        detail_text = panel + 0x290;
        func_80051B50(detail_text, text_buf, 1);
        widget->unk_00.s = detail_text;
        ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->x = 0xBC;
        ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->y = 0x140;
    }
    widget = ((S_80404EA0_0 *)panel)->value_widget;
    func_80051804(((S_80404EA0_4 *)(card_slot_header_cache + (((S_80404EA0_0 *)panel)->slot_index << 7)))->unk_24, 0xA, text_buf);
    func_80051900(text_buf);
    value_text = panel + 0x398;
    func_80051520(value_text, text_buf, 1);
    widget->unk_00.s = value_text;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->x = 0x140;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->y = 0x110;
    widget = ((S_80404EA0_0 *)panel)->time_widget;
    func_80051898(((S_80404EA0_4 *)(card_slot_header_cache + (((S_80404EA0_0 *)panel)->slot_index << 7)))->play_frames, text_buf);
    hours = ((S_80404EA0_4 *)(card_slot_header_cache + (((S_80404EA0_0 *)panel)->slot_index << 7)))->play_frames / 216000;
    func_80051804(hours, 3, text_buf);
    func_8007BF50(text_buf, D_804006BC);
    mins = ((S_80404EA0_4 *)(card_slot_header_cache + (((S_80404EA0_0 *)panel)->slot_index << 7)))->play_frames / 3600;
    minute_quotient = mins / 3600;
    func_8005184C(mins - minute_quotient * 3600, 2, time_buf);
    func_8007BF50(text_buf, time_buf);
    func_8007BF50(text_buf, D_804006BC);
    secs = ((S_80404EA0_4 *)(card_slot_header_cache + (((S_80404EA0_0 *)panel)->slot_index << 7)))->play_frames / 60;
    second_quotient = secs / 60;
    func_8005184C(secs - second_quotient * 60, 2, time_buf);
    func_8007BF50(text_buf, time_buf);
    func_80051900(text_buf);
    time_text = panel + 0x4A0;
    func_80051520(time_text, text_buf, 1);
    widget->unk_00.s = time_text;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->x = 0x147;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->y = 0x120;
    widget = ((S_80404EA0_0 *)panel)->count_widget;
    func_80051804(((S_80404EA0_4 *)(card_slot_header_cache + (((S_80404EA0_0 *)panel)->slot_index << 7)))->unk_2C, 4, text_buf);
    func_80051900(text_buf);
    count_text = panel + 0x5A8;
    func_80051520(count_text, text_buf, 1);
    widget->unk_00.s = count_text;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->x = 0xF2;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->y = 0x120;
    widget = ((S_80404EA0_0 *)panel)->footer_widget;
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
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->x = 0x180;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->y = 0x130;
    do {
        widget = ((S_80404EA0_2 *)widget_cursor)->icon_widget;
        if ((bit_one << icon_index) & ((S_80404EA0_4 *)(card_slot_header_cache + (((S_80404EA0_0 *)panel)->slot_index << 7)))->icon_flags) {
            icon_data = *icon_cursor;
        } else {
            icon_data = *inactive_icon;
        }
        icon_cursor += 1;
        widget_cursor += 4;
        widget->unk_00.u = icon_data;
        icon_index += 1;
        ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->x = icon_x;
        ((S_80404EA0_5 *)(((S_80404EA0_3 *)widget)->unk_04))->y = icon_y;
        icon_x += 0x10;
    } while (icon_index < 0xA);
}
