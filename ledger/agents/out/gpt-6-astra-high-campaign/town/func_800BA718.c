#include "common.h"

extern u16 D_80111FA8[];
extern u8 D_80110EC8[];
extern u8 D_801110C8[];
extern u8 D_801112C8[];
extern u8 D_801114C8[];
extern void *D_800893A0[];

extern void LoadImage(void *, void *);

/* Advance the animation tick and upload the selected frame to VRAM. */
void func_800B7E78(u16 *frame_tick) {
    u16 next_tick;
    s32 tick_index;
    s32 rect_page;
    void *rect;
    register void *pixels ASM_REG("$5");
    static void *const frame_labels[] = { &&L0, &&L4, &&L8, &&L12 };

    next_tick = *frame_tick + 1;
    *frame_tick = next_tick;
    if ((s16)next_tick >= 24) {
        *frame_tick = 0;
    }

    tick_index = (s16)*frame_tick % 24;
    if ((u32)tick_index >= 21) {
        return;
    }
    goto *D_800893A0[tick_index];

L0:
    rect_page = (s32)0x80110000;
    ASM_KEEP(rect_page);
    rect = (void *)(rect_page + 0x1FA8);
    pixels = D_80110EC8;
    goto tail;

L4:
    rect_page = (s32)0x80110000;
    ASM_KEEP(rect_page);
    rect = (void *)(rect_page + 0x1FA8);
    pixels = D_801110C8;
    goto tail;

L8:
    rect_page = (s32)0x80110000;
    ASM_KEEP(rect_page);
    rect = (void *)(rect_page + 0x1FA8);
    pixels = D_801112C8;
    goto tail;

L12:
    rect_page = (s32)0x80110000;
    ASM_KEEP(rect_page);
    rect = (void *)(rect_page + 0x1FA8);
    pixels = D_801114C8;

tail:
    (*(u16 *)(rect_page + 0x1FA8)) = 808;
    ((u16 *)rect)[1] = 128;
    ((u16 *)rect)[2] = 8;
    ((u16 *)rect)[3] = 32;
    LoadImage(rect, pixels);
}
