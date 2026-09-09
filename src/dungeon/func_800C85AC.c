#include "common.h"

typedef struct {
    u8 pad0[0x14];
    u16 flags;
    u8 pad16[0xE];
    u8 x;
    u8 y;
} Entry;

extern u8 D_800E3D40[];
extern u8 D_800DF870[];

extern s32 func_800A6D30(void *, s32, s32, s32);
extern void func_800A6508(void);
extern void func_800A56E0(s32);
extern void func_800C8DB0(void *, s32, s32);
extern void func_800C5E5C(s32, s32, s32, void *, s32);

/* Applies a chance-based effect, with visual and sound feedback for unflagged entries. */
s32 func_800CDD0C(void *state, s32 rng_arg1, s32 rng_arg2, s32 rng_arg3)
{
    register s32 roll ASM_REG("$2");
    register s32 remainder ASM_REG("$3");
    register s32 random_value ASM_REG("$4");
    s32 roll_range;
    s32 effect_amount;
    Entry *entry;

    if (D_800E3D40[0] != 0) {
        goto zero_roll;
    }
    random_value = func_800A6D30(state, rng_arg1, rng_arg2, rng_arg3) & 0xFFFF;
    roll_range = *(u8 *)((u8 *)state + 3);
    if (roll_range == 0) {
        goto zero_roll;
    }
    roll = roll_range;
    ASM_USE(roll_range);
    remainder = random_value % roll;
    roll = remainder;
    goto check_roll;

zero_roll:
    roll = 0;

check_roll:
    if (roll < 0x30) {
        effect_amount = 0x20;
        if (D_800E3D40[0] != 0) {
            effect_amount = 0x400;
        }
        func_800C8DB0(state, effect_amount, 0x10);

        entry = *(Entry **)((u8 *)state - 0x14);
        if (!(entry->flags & 0x8000)) {
            func_800C5E5C((entry->x << 6) | 0x20,
                          (entry->y << 6) | 0x20,
                          *(s16 *)((u8 *)state + 0x88), D_800DF870, 0);
            func_800A56E0(0x70A);
            return 1;
        }
        return 1;
    }

    if (*(u8 *)((u8 *)state + 0x13) == 0) {
        func_800A6508();
    }
    return 1;
}
