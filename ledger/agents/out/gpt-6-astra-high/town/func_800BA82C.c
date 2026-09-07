#include "common.h"

extern void func_800672D8(void *, void *);
extern void *D_800893F8[];
extern u8 D_80110EC8[];
extern u8 D_801110C8[];
extern u8 D_801112C8[];
extern u8 D_801114C8[];
extern u16 D_80111F48[];
extern u16 D_80111F68[];
extern u16 D_80111F88[];

/* Advance the animation tick and upload the selected texture and palette frames. */
void func_800B7F8C(u16 *anim_tick)
{
    static void *const keepalive[] = {
        &&L0, &&after_first, &&after_first, &&after_first,
        &&L4, &&after_first, &&after_first, &&after_first,
        &&L8, &&after_first, &&after_first, &&after_first,
        &&L12, &&after_first, &&after_first, &&after_first,
        &&L8, &&after_first, &&after_first, &&after_first,
        &&L4
    };
    s32 texture_base;
    register s32 palette_base ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    void *rect;
    register void *upload_data ASM_REG("$5");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 palette_phase;
    s32 next_tick;
    s32 texture_phase;

    next_tick = *anim_tick + 1;
    *anim_tick = next_tick;
    if ((s16)next_tick >= 24) {
        *anim_tick = 0;
    }

    texture_phase = (s16)*anim_tick % 24;
    if ((u32)texture_phase >= 21) {
        goto after_first;
    }
    (void)keepalive;
    goto *D_800893F8[texture_phase];

L0:
        texture_base = (s32)0x80110000;
        ASM_KEEP(texture_base);   /* MATCH pin: keeps a statement from moving across a call/branch */
        rect = (void *)(texture_base + 0x1FA8);
        upload_data = D_80110EC8;
        goto first_common;
L4:
        texture_base = (s32)0x80110000;
        ASM_KEEP(texture_base);   /* MATCH pin: keeps a statement from moving across a call/branch */
        rect = (void *)(texture_base + 0x1FA8);
        upload_data = D_801110C8;
        goto first_common;
L8:
        texture_base = (s32)0x80110000;
        ASM_KEEP(texture_base);   /* MATCH pin: keeps a statement from moving across a call/branch */
        rect = (void *)(texture_base + 0x1FA8);
        upload_data = D_801112C8;
        goto first_common;
L12:
        texture_base = (s32)0x80110000;
        ASM_KEEP(texture_base);   /* MATCH pin: keeps a statement from moving across a call/branch */
        rect = (void *)(texture_base + 0x1FA8);
        upload_data = D_801114C8;
        goto first_common;

first_common:
    *(u16 *)(texture_base + 0x1FA8) = 808;
    ((u16 *)rect)[1] = 128;
    ((u16 *)rect)[2] = 8;
    ((u16 *)rect)[3] = 32;
    func_800672D8(rect, upload_data);

after_first:
    palette_phase = (s16)*anim_tick % 6;
    switch (palette_phase) {
    case 0:
        palette_base = (s32)0x80110000;
        ASM_KEEP(palette_base);   /* MATCH pin: keeps a statement from moving across a call/branch */
        rect = (void *)(palette_base + 0x1FA8);
        upload_data = D_80111F48;
        goto second_common;
    case 2:
        palette_base = (s32)0x80110000;
        ASM_KEEP(palette_base);   /* MATCH pin: keeps a statement from moving across a call/branch */
        rect = (void *)(palette_base + 0x1FA8);
        upload_data = D_80111F68;
        goto second_common;
    case 4:
        palette_base = (s32)0x80110000;
        ASM_KEEP(palette_base);   /* MATCH pin: keeps a statement from moving across a call/branch */
        rect = (void *)(palette_base + 0x1FA8);
        upload_data = D_80111F88;
        goto second_common;
    default:
        return;
    }

second_common:
    *(u16 *)(palette_base + 0x1FA8) = 16;
    ((u16 *)rect)[1] = 449;
    ((u16 *)rect)[2] = 16;
    ((u16 *)rect)[3] = 1;
    func_800672D8(rect, upload_data);
}
