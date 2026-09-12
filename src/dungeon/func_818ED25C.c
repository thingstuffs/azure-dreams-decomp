#include "common.h"

typedef struct S_80024A5C_0 {
    u8 pad_00[0x8B0];
    u32 unk_8B0;
    u8 pad_8B4[0x1C];
    u8 * unk_8D0;
} S_80024A5C_0;   /* ctx in func_80024A5C */

typedef struct S_80024A5C_1 {
    u32 unk_00;
} S_80024A5C_1;   /* packet in func_80024A5C */

typedef struct S_80024A5C_2 {
    u16 unk_00;
    s16 unk_02;
} S_80024A5C_2;   /* work in func_80024A5C */

typedef struct S_80024A5C_3 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_80024A5C_3;   /* ctx2 in func_80024A5C */

typedef struct S_80024A5C_4 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   /* overlapping accesses */
    u32 unk_04;
    u16 unk_08;
    s16 unk_0A;
    s32 unk_0C;
} S_80024A5C_4;   /* packet2 in func_80024A5C */

typedef struct S_80024A5C_5 {
    u16 unk_00;
    s16 unk_02;
    s32 unk_04;
} S_80024A5C_5;   /* arg1 in func_80024A5C */

typedef struct S_80024A5C_6 {
    u32 unk_00;
} S_80024A5C_6;   /* ot in func_80024A5C */

typedef struct S_80024A5C_7 {
    void * unk_00;
} S_80024A5C_7;   /* pbase in func_80024A5C */


typedef struct { void *p; } PagePtr;
extern PagePtr D_80083160;
extern u8 D_801C9E40[16];

extern void func_80024094(void *, s32, void *, s32);
extern void func_80067E2C(void *, void *);


/* Draws at a page-adjusted position with clipping commands and an optional black rectangle. */
void func_80024A5C(volatile s32 draw_data, S_80024A5C_5 *clip_rect, void *screen_pos, u16 clear_rect, s32 draw_param)
{
    u16 draw_pos[2];
    u16 clear_enabled;
    s32 draw_y;
    s32 rect_y;
    u8 *clip_packet;
    register u8 *page_ptr ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 saved_param ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    u32 tag_mask;
    u8 *pos_or_ot;
    u8 *order_table;
    void *draw_page;
    S_80024A5C_3 *packet_page;
    s16 offset_y;
    void *call_pos;
    s32 call_data;
    void *call_order_table;
    s32 call_param;

    draw_page = D_80083160.p;
    pos_or_ot = screen_pos;
    clip_packet = ((S_80024A5C_0 *)draw_page)->unk_8D0;
    offset_y = draw_page != (void *)D_801C9E40;
    ((S_80024A5C_0 *)draw_page)->unk_8D0 = clip_packet + 0xC;
    saved_param = draw_param;
    clear_enabled = clear_rect;
    func_80067E2C(clip_packet, D_80083160.p);
    tag_mask = 0xFF000000U;

    ((S_80024A5C_1 *)clip_packet)->unk_00 = (((S_80024A5C_1 *)clip_packet)->unk_00 & tag_mask) |
                            (((S_80024A5C_0 *)draw_page)->unk_8B0 & 0x00FFFFFFU);
    ((S_80024A5C_0 *)draw_page)->unk_8B0 = (((S_80024A5C_0 *)draw_page)->unk_8B0 & tag_mask) |
                             ((u32)clip_packet & 0x00FFFFFFU);

    draw_pos[0] = ((S_80024A5C_2 *)pos_or_ot)->unk_00;
    page_ptr = (u8 *)&D_80083160;
    draw_y = ((S_80024A5C_2 *)pos_or_ot)->unk_02;
    pos_or_ot = (u8 *)draw_page + 0x8B0;
    order_table = pos_or_ot;
    if (offset_y != 0) {
        draw_y -= 0xE0;
    }
    call_pos = draw_pos;
    call_param = (s32)((u32)saved_param << 16);
    call_order_table = order_table;
    ASM_KEEP_NV(call_pos);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    call_data = draw_data;
    call_param >>= 16;
    draw_pos[1] = draw_y;
    func_80024094(call_pos, call_data, call_order_table, call_param);

    if (clear_enabled != 0) {
        u8 *fill_packet;

        packet_page = D_80083160.p;
        fill_packet = packet_page->unk_8D0;
        packet_page->unk_8D0 = fill_packet + 0x10;
        ((S_80024A5C_4 *)fill_packet)->unk_04 = 0x60000000;
        ((S_80024A5C_4 *)fill_packet)->unk_00.at03.v = 3;
        ((S_80024A5C_4 *)fill_packet)->unk_08 = clip_rect->unk_00;
        rect_y = clip_rect->unk_02;
        if (offset_y != 0) {
            rect_y -= 0xE0;
        }
        ((S_80024A5C_4 *)fill_packet)->unk_0A = rect_y;
        ((S_80024A5C_4 *)fill_packet)->unk_0C = clip_rect->unk_04;
        ((S_80024A5C_4 *)fill_packet)->unk_00.at00.v = (((S_80024A5C_4 *)fill_packet)->unk_00.at00.v & tag_mask) |
                                 (((S_80024A5C_6 *)order_table)->unk_00 & 0x00FFFFFFU);
        ((S_80024A5C_6 *)order_table)->unk_00 = (((S_80024A5C_6 *)order_table)->unk_00 & tag_mask) |
                            ((u32)fill_packet & 0x00FFFFFFU);
    }

    packet_page = ((S_80024A5C_7 *)page_ptr)->unk_00;
    clip_packet = packet_page->unk_8D0;
    packet_page->unk_8D0 = clip_packet + 0xC;
    func_80067E2C(clip_packet, clip_rect);
    ((S_80024A5C_1 *)clip_packet)->unk_00 = (((S_80024A5C_1 *)clip_packet)->unk_00 & 0xFF000000U) |
                            (((S_80024A5C_6 *)order_table)->unk_00 & 0x00FFFFFFU);
    ((S_80024A5C_6 *)order_table)->unk_00 = (((S_80024A5C_6 *)order_table)->unk_00 & 0xFF000000U) |
                        ((u32)clip_packet & 0x00FFFFFFU);
}
