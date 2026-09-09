#include "common.h"
#define U8(p,o) (*(u8 *)((u8 *)(p)+(o)))
#define S16(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define U16(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define U32(p,o) (*(u32 *)((u8 *)(p)+(o)))
#define P32(p,o) (*(void **)((u8 *)(p)+(o)))
extern s32 func_800A6D30(void *, s32, s32, s32); extern s32 func_800A48F0(); extern void func_800C5BBC();
extern void func_800A56E0(s32); extern void func_80099844();
extern u8 D_800E3D40; extern u8 D_800E1BBC[];
/* Attempts a random status effect and plays its visual and sound effects on success. */
s32 func_800CC058(void *entity, s32 rng_input_a, s32 rng_input_b, s32 rng_input_c)
{
    s32 notify_failure = 0, random_value;
    register s32 roll_or_failure ASM_REG("$2");
    void *parent;

    if (!D_800E3D40 &&
        (random_value = func_800A6D30(entity, rng_input_a, rng_input_b, rng_input_c) & 0xffff,
         U8(entity, 3))) {
        register s32 remainder ASM_REG("$3");

        remainder = random_value % U8(entity, 3);
        roll_or_failure = remainder;
    } else {
        roll_or_failure = 0;
    }
    if (roll_or_failure < 0x30 && (func_800A48F0(entity, 7, -0x10) << 16) >= 0) {
        parent = P32(entity, -0x14);
        if (!(U16(parent, 0x14) & 0x8000)) {
            func_800C5BBC((U8(parent, 0x24) << 6) | 0x20,
                          (U8(parent, 0x25) << 6) | 0x20,
                          S16(entity, 0x88), 0x202020, 0x40, 0);
            func_800A56E0(0x615);
        }
        if (U32(entity, 0x14) & 0x4000) {
            func_80099844(entity, D_800E1BBC);
        }
    } else {
        roll_or_failure = U8(entity, 0x13) == 0;
        ASM_KEEP(roll_or_failure);
        notify_failure = roll_or_failure;
    }
    roll_or_failure = notify_failure;
    ASM_KEEP(roll_or_failure);
    if (roll_or_failure) {
        func_800A6508();
    }
    return 1;
}
