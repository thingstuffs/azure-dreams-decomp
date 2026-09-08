#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80067014();                     /* extern */
M2C_UNK func_800672D8();                  /* extern */
extern s16 D_80083D78[];


typedef struct S_800B5B20_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
} S_800B5B20_0;   /* temp_s0 in func_800B5B20 */

/* Transfer pending texture and palette data, then clear the transfer state. */
void func_800B5B20(void *texture_state) {
    s32 table_index;
    volatile s16 rect_x;
    volatile s16 rect_y;
    volatile s16 rect_width;
    volatile s16 rect_height;
    void *state = texture_state;
    void *texture;
    s16 *slot_table;

    if ((*(s32 *)((u8 *)state + 0xD4)) != 0) {
        func_80067014(0);
        slot_table = D_80083D78;
        table_index = (*(s16 *)((u8 *)state + 8));
        texture = (*(void * volatile *)((u8 *)state + 0x14));
        (*(s32 *)((u8 *)state + 0xD0)) = 0;
        (*(s32 *)((u8 *)state + 0xD4)) = 0;
        slot_table[table_index * 2] = (*(u16 *)((u8 *)state + 0xA));
        slot_table[((*(s16 *)((u8 *)state + 8)) * 2) + 1] = (*(u16 *)((u8 *)state + 0x10));

        rect_x = ((u8) ((S_800B5B20_0 *)texture)->unk_08 >> 2) + ((((S_800B5B20_0 *)texture)->unk_04 << 6) & 0x3C0);
        rect_y = ((S_800B5B20_0 *)texture)->unk_09 + (((*(u16 *)((u8 *)texture + 4)) * 0x10) & 0x100);
        rect_width = (s16) ((u8) ((S_800B5B20_0 *)texture)->unk_0A >> 2);
        rect_height = (s16) ((S_800B5B20_0 *)texture)->unk_0B;
        func_800672D8(&rect_x, (*(s32 *)((u8 *)state + 0xE0)));
        if ((*(s16 *)((u8 *)state + 8)) != 0) {
            volatile s16 *palette_rect = &rect_x;
            u16 palette_y;
            s32 palette_offset;
            s32 data_base;

            rect_x = (((S_800B5B20_0 *)texture)->unk_06 & 0x3F) * 0x10;
            palette_y = (*(u16 *)((u8 *)texture + 6));
            rect_width = 0x10;
            rect_height = 1;
            palette_y >>= 6;
            rect_y = (s16) palette_y;

            palette_offset = (*(s32 *)((u8 *)state + 0x10));
            data_base = (*(s32 *)((u8 *)state + 0xE0));
            palette_offset <<= 5;
            palette_offset += 0x200;

            func_800672D8(palette_rect, data_base + palette_offset);
        }
        func_80067014(0);
    }
    (*(s32 *)((u8 *)state + 0xE0)) = 0;
}
