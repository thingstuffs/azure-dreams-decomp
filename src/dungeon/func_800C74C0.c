#include "common.h"

typedef struct {
    u8 pad[3];
    u8 flags;
} Entry4;

extern u8 D_800E3648[];
extern u8 D_800E39C8[];
extern u8 D_800E3D40;
extern u8 D_800E5908;
extern s32 D_800DCF78;

void func_800A56E0(s32);
void func_800A6508(void);
s32 func_800A6D30(void);
void func_800B835C(void *, void *, s32, s32);
void func_800CCA14(u8, u8, s16);

s32 func_800CCC20(void *arg0, s16 arg1)
{
    s32 stack_args[2];
    register s32 value ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    register s32 remainder ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 random ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    s32 range;
    s32 index;
    s32 scaled_index;   /* MATCH pin: keeps a constant in a register as retail does */
    s32 field;
    register s32 count ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    s32 flags;
    u8 *map_base;   /* MATCH pin: keeps a statement from moving across a call/branch */
    u8 *item_base;
    u8 *entry;
    register u8 *item ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    u8 *countp;
    s32 tail_index;
    register u8 *tail_base ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

    if (arg0 == 0) {
        map_base = D_800E3648;
        index = arg1;
        scaled_index = index * 4;
        entry = scaled_index + map_base;
        flags = entry[3];
        if (flags & 0x80) {
            value = flags & 0x7F;
            item_base = D_800E39C8;
            entry[3] = value;
            item = item_base + index * 24;
            countp = &D_800E5908;
            field = *(u16 *)(item + 0x14);
            count = *countp;
            field &= 0xF7FF;
            count++;
            *(u16 *)(item + 0x14) = field;
            *countp = count;
            goto update_item;
        }
        goto return_one;
    }

    if (D_800E3D40 != 0) {
        value = 0;
    } else {
        random = func_800A6D30() & 0xFFFF;
        range = *((u8 *)arg0 + 3);
        if (range != 0) {
            value = range;
            ASM_USE(range);   /* MATCH pin: retail delay-slot fill depends on it */
            remainder = random % value;
            value = remainder;
        } else {
            value = 0;
        }
    }

    if (value >= 0x40) {
        func_800A6508();
        value = 1;
        goto epilogue;
    }

    D_800DCF78 = 0x00202080;
    stack_args[0] = 0x01000340;
    stack_args[1] = 0x00200020;
    func_800B835C((u8 *)&D_800DCF78 - 0x10, stack_args, 1, 0);
    D_800E5908 = 0;

update_item:
    tail_base = D_800E39C8;
    tail_index = arg1;
    item = tail_base + tail_index * 24;
    func_800CCA14(item[6], item[7], *(s16 *)(item + 0x12));
    func_800A56E0(0x817);

return_one:
    value = 1;
epilogue:
    return value;
}

/* MECHANISM: Recover true-space joins locally and model the call workspace as an
   escaping 8-byte stack record.  Hold arg0/arg1 in s0/s1 and use guarded a0/v1
   RNG/remainder roles so the explicit result merge survives before the threshold. */
