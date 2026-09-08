#include "common.h"

extern u16 D_80111FA8[];
extern u8 D_80110EC8[];
extern u8 D_801110C8[];
extern u8 D_801112C8[];
extern u8 D_801114C8[];
extern u8 D_801116C8[];
extern u8 D_801118C8[];
extern u8 D_80111AC8[];
extern u8 D_80111CC8[];
extern u8 D_80111EC8[];
extern u8 D_80111EE8[];
extern u8 D_80111F08[];
extern u8 D_80111F28[];
extern void *D_80089348[];

extern void func_800672D8();

/* Advance the animation tick and upload the current texture and palette frames. */
void func_800B7B8C(u16 *anim_tick, s32 unused, s32 upload_arg) {
    u16 next_tick;
    s16 phase;
    s32 dispatch_index;
    s32 palette_rect_base;
    s32 texture_rect_base;
    s16 *rect;
    register u8 *pixels ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s32 tile_width;
    static void *const keepalive[] = { &&L0, &&L4, &&L8, &&L12 };

    next_tick = *anim_tick + 1;
    *anim_tick = next_tick;
    if ((s16)next_tick >= 48) {
        *anim_tick = 0;
    }

    phase = *(s16 *)anim_tick % 24;
    dispatch_index = phase;
    if ((u32)dispatch_index >= 21) {
        goto Lafter_first;
    }
    goto *D_80089348[dispatch_index];

L0:
    texture_rect_base = 0x80110000;
    ASM_KEEP(texture_rect_base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    rect = (s16 *)(texture_rect_base + 0x1FA8);
    pixels = D_80110EC8;
    goto Lfirst_common;

L4:
    texture_rect_base = 0x80110000;
    ASM_KEEP(texture_rect_base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    rect = (s16 *)(texture_rect_base + 0x1FA8);
    pixels = D_801110C8;
    goto Lfirst_common;

L8:
    texture_rect_base = 0x80110000;
    ASM_KEEP(texture_rect_base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    rect = (s16 *)(texture_rect_base + 0x1FA8);
    pixels = D_801112C8;
    goto Lfirst_common;

L12:
    texture_rect_base = 0x80110000;
    ASM_KEEP(texture_rect_base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    rect = (s16 *)(texture_rect_base + 0x1FA8);
    pixels = D_801114C8;

Lfirst_common:
    *(s16 *)(texture_rect_base + 0x1FA8) = 0x328;
    rect[1] = 0x80;
    rect[2] = 8;
    rect[3] = 0x20;
    func_800672D8(rect, pixels, upload_arg);

Lafter_first:
    phase = *(s16 *)anim_tick % 16;
    if (phase == 4) {
        goto Lsecond_4;
    }
    if (phase < 5) {
        if (phase == 0) {
            goto Lsecond_0;
        }
        goto Lafter_second;
    }
    tile_width = 8;
    if (phase == tile_width) {
        goto Lsecond_8;
    }
    if (phase == 12) {
        goto Lsecond_12;
    }
    goto Lafter_second;

Lsecond_0:
    texture_rect_base = 0x80110000;
    ASM_KEEP(texture_rect_base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    rect = (s16 *)(texture_rect_base + 0x1FA8);
    pixels = D_801116C8;
    *(volatile s16 *)(texture_rect_base + 0x1FA8) = 0x330;
    ((volatile s16 *)rect)[1] = 0x80;
    ((volatile s16 *)rect)[2] = 8;
    goto Lsecond_tail;

Lsecond_4:
    pixels = (u8 *)0x80110000;
    ASM_KEEP(pixels);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    texture_rect_base = 0x80110000;
    ASM_KEEP(texture_rect_base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    rect = (s16 *)(texture_rect_base + 0x1FA8);
    pixels += 0x18C8;
    *(s16 *)(texture_rect_base + 0x1FA8) = 0x330;
    rect[1] = 0x80;
    rect[2] = 8;
    ASM_KEEP(rect);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    goto Lsecond_tail;

Lsecond_8:
    pixels = (u8 *)0x80110000;
    ASM_KEEP(pixels);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    texture_rect_base = 0x80110000;
    ASM_KEEP(texture_rect_base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    rect = (s16 *)(texture_rect_base + 0x1FA8);
    pixels += 0x1AC8;
    goto Lsecond_common;

Lsecond_12:
    texture_rect_base = 0x80110000;
    ASM_KEEP(texture_rect_base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    rect = (s16 *)(texture_rect_base + 0x1FA8);
    pixels = D_80111CC8;

Lsecond_common:
    *(s16 *)(texture_rect_base + 0x1FA8) = 0x330;
    rect[1] = 0x80;
    {
        s32 tile_height;
        tile_height = 0x20;
        rect[2] = tile_width;
        rect[3] = tile_height;
        func_800672D8(rect, pixels);
    }
    goto Lafter_second;

Lsecond_tail:
    rect[3] = 0x20;
    func_800672D8(rect, pixels);

Lafter_second:
    phase = *(s16 *)anim_tick % 8;
    if (phase == 2) {
        goto Lthird_2;
    }
    if (phase < 3) {
        if (phase == 0) {
            goto Lthird_0;
        }
        return;
    }
    if (phase == 4) {
        goto Lthird_4;
    }
    if (phase == 6) {
        goto Lthird_6;
    }
    return;

Lthird_0:
    palette_rect_base = 0x80110000;
    ASM_KEEP(palette_rect_base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    rect = (s16 *)(palette_rect_base + 0x1FA8);
    pixels = D_80111EC8;
    goto Lthird_common;

Lthird_2:
    palette_rect_base = 0x80110000;
    ASM_KEEP(palette_rect_base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    rect = (s16 *)(palette_rect_base + 0x1FA8);
    pixels = D_80111EE8;
    goto Lthird_common;

Lthird_4:
    palette_rect_base = 0x80110000;
    ASM_KEEP(palette_rect_base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    rect = (s16 *)(palette_rect_base + 0x1FA8);
    pixels = D_80111F08;
    goto Lthird_common;

Lthird_6:
    palette_rect_base = 0x80110000;
    ASM_KEEP(palette_rect_base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    rect = (s16 *)(palette_rect_base + 0x1FA8);
    pixels = D_80111F28;

Lthird_common:
    *(s16 *)(palette_rect_base + 0x1FA8) = 0;
    rect[1] = 0x1FB;
    rect[2] = 0x10;
    rect[3] = 1;
    func_800672D8(rect, pixels);
}
