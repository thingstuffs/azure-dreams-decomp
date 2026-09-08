#include "common.h"

#define F8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define F16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define FU16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define F32(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern s32 D_800814A0;
extern void func_80173CFC(void *, s32 *, s32, s32);

/* Update an effect's color phases, burst, movement, and remaining lifetime. */
void func_80174374(u8 *effect, s32 *position, s32 effect_param)
{
    s16 state;
    s16 life_left;
    s16 red;
    s16 burst_index;
    s32 division_magic;
    u16 age;
    u8 green;
    u8 blue;

    state = F16(effect, 0x1C);
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto finish;
    }
    if (state == 2) {
        goto state_two;
    }
    goto finish;

state_zero:
    age = FU16(effect, 0x26) + 1;
    FU16(effect, 0x26) = age;
    if ((s16)age >= F16(effect, 0x2C)) {
        division_magic = 0x2AAA0000;
        if ((s16)age - F16(effect, 0x2C) < 7) {
            division_magic = 0x2AAAAAAB;
            red = (F8(effect, 0) * ((s16)age - F16(effect, 0x2C))) / 6;
            F8(effect, 0x10) = red;
            F8(effect, 0x0C) = red;
            F8(effect, 0x08) = red;
            F8(effect, 0x04) = red;
            green = (F8(effect, 1) * (F16(effect, 0x26) - F16(effect, 0x2C))) / 6;
            F8(effect, 0x11) = green;
            F8(effect, 0x0D) = green;
            F8(effect, 0x09) = green;
            F8(effect, 0x05) = green;
            blue = (F8(effect, 2) * (F16(effect, 0x26) - F16(effect, 0x2C))) / 6;
            F8(effect, 0x12) = blue;
            F8(effect, 0x0E) = blue;
            F8(effect, 0x0A) = blue;
            F8(effect, 0x06) = blue;
        }
    }
    if (F16(effect, 0x26) >= 0x22) {
        FU16(effect, 0x1C) = FU16(effect, 0x1C) + 1;
    }
    goto finish;

state_one:
    if (F16(effect, 0x2A) < 4) {
        age = FU16(effect, 0x26) + 1;
        FU16(effect, 0x26) = age;
        if ((s16)age + F16(effect, 0x2A) == 0x2D) {
            F8(effect, 0x12) = 0x80;
            F8(effect, 0x0E) = 0x80;
            F8(effect, 0x0A) = 0x80;
            F8(effect, 0x06) = 0x80;
            F8(effect, 0x11) = 0x80;
            F8(effect, 0x0D) = 0x80;
            F8(effect, 0x09) = 0x80;
            F8(effect, 0x05) = 0x80;
            F8(effect, 0x10) = 0x80;
            F8(effect, 0x0C) = 0x80;
            F8(effect, 0x08) = 0x80;
            F8(effect, 0x04) = 0x80;
        } else {
            u8 base_red = F8(effect, 0);
            u8 base_green = F8(effect, 1);
            u8 base_blue = F8(effect, 2);
            F8(effect, 0x10) = base_red;
            F8(effect, 0x0C) = base_red;
            F8(effect, 0x08) = base_red;
            F8(effect, 0x04) = base_red;
            F8(effect, 0x11) = base_green;
            F8(effect, 0x0D) = base_green;
            F8(effect, 0x09) = base_green;
            F8(effect, 0x05) = base_green;
            F8(effect, 0x12) = base_blue;
            F8(effect, 0x0E) = base_blue;
            F8(effect, 0x0A) = base_blue;
            F8(effect, 0x06) = base_blue;
        }
    }

state_one_common:
    if (F16(effect, 0x24) < 0x0C) {
        FU16(effect, 0x1C) = FU16(effect, 0x1C) + 1;
        F32(effect, 0x94) = (F16(effect, 0x44) + F16(effect, 0x56)) << 15;
        F32(effect, 0x98) = (F16(effect, 0x46) + F16(effect, 0x58)) << 15;
        F32(effect, 0x9C) = (F16(effect, 0x48) + F16(effect, 0x5A) + 0x40) << 15;
        if (F16(effect, 0x2A) == 0) {
            burst_index = 1;
            do {
                func_80173CFC(effect, position, effect_param, (burst_index << 26) >> 16);
                burst_index++;
            } while (burst_index < 8);
        }
    }
    goto finish;

state_two:
    blue = (F8(effect, 0) * F16(effect, 0x24)) / 10;
    F8(effect, 0x12) = blue;
    F8(effect, 0x0E) = blue;
    F8(effect, 0x0A) = blue;
    F8(effect, 0x06) = blue;
    F8(effect, 0x11) = blue;
    F8(effect, 0x0D) = blue;
    F8(effect, 0x09) = blue;
    F8(effect, 0x05) = blue;
    F8(effect, 0x10) = blue;
    F8(effect, 0x0C) = blue;
    F8(effect, 0x08) = blue;
    F8(effect, 0x04) = blue;
    position[0] += F32(effect, 0x94);
    position[1] += F32(effect, 0x98);
    position[2] += F32(effect, 0x9C);

finish:
    life_left = FU16(effect, 0x24) - 1;
    F16(effect, 0x24) = life_left;
    if ((life_left << 16) <= 0) {
        FU16(effect, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
