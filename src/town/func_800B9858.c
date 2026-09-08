#include "common.h"

typedef struct S_800B6FB8_0 {
    u8 pad_00[0x14];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_800B6FB8_0;   /* draw in func_800B6FB8 */

typedef struct S_800B6FB8_1 {
    u8 pad_00[0x16];
    u16 unk_16;
} S_800B6FB8_1;   /* status in func_800B6FB8 */

typedef struct S_800B6FB8_2 {
    u8 pad_00[0x1DC];
    void * unk_1DC;
} S_800B6FB8_2;   /* base in func_800B6FB8 */

extern void func_80046E38(); extern void func_80067014(); extern void func_8006733C(); extern void func_800B73D0();
extern u8 D_80082E60[], D_80083160[], D_80110EC8[], D_801116C8[], D_80111EC8[], D_8012F004[], D_80162004[]; extern u16 D_80111FA8[];
/* Initialize drawing state and upload image and palette data. */
void func_800B6FB8(void)
{
    u8 *base, *status;
    u16 *image_rect, *first_rect, *palette_rect;
    u8 *image_data;
    void *draw;
    s32 width, color, draw_setting;
    u16 image_width;
    void *draw_buffer;

    image_rect = D_80111FA8;
    first_rect = image_rect;
    image_data = D_80110EC8;
    base = D_80083160;
    draw = base + 0x1DC;
    color = 0x7F;
    width = 0x2000;
    ((S_800B6FB8_0 *)draw)->unk_14 = 7;
    ((S_800B6FB8_0 *)draw)->unk_18 = color;
    ((S_800B6FB8_0 *)draw)->unk_1C = width;
    draw_setting = 7;
    ((S_800B6FB8_0 *)draw)->unk_16 = draw_setting;
    ((S_800B6FB8_0 *)draw)->unk_1A = color;
    ((S_800B6FB8_0 *)draw)->unk_1E = width;
    status = D_80082E60;

    D_80111FA8[0] = 0x328;
    image_rect[1] = 0x80;
    image_width = 8;
    image_rect[2] = image_width;
    image_rect[3] = 0x80;
    ((S_800B6FB8_1 *)status)->unk_16 &= 0xFFFE;
    func_8006733C(first_rect, image_data);

    D_80111FA8[0] = 0x330;
    image_rect[1] = 0x80;
    image_rect[2] = image_width;
    image_rect[3] = 0x80;
    func_8006733C(image_rect, D_801116C8);

    palette_rect = D_80111FA8;
    D_80111FA8[0] = 0;
    palette_rect[1] = 0x1FB;
    palette_rect[2] = 0x40;
    palette_rect[3] = 1;
    func_8006733C(palette_rect, D_80111EC8);
    func_80067014(0);

    draw_buffer = D_80162004;
    ((S_800B6FB8_2 *)base)->unk_1DC = draw_buffer;
    func_800B73D0();
    func_80046E38(0, D_8012F004);
}
