#include "common.h"
#include "m2c_compat.h"

s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 rand();                                /* extern */
M2C_UNK func_800ABC00(void *, s16);              /* extern */

typedef struct {
    s16 unk0;
    s16 x;
    s16 unk4;
    s16 y;
    s16 unk8;
    u16 z;
    s32 a;
    s32 b;
    s16 unk14;
    s16 c;
} StackRecord;

typedef struct S_800ABD74_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800ABD74_0;   /* base in func_800ABD74 */

/* Spawns effects near the source position in evenly spaced directions. */
void func_800ABD74(void *source) {
    S_800ABD74_0 *origin;
    StackRecord effect;
    s32 angle;
    register s32 effect_count ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 angle_step;
    s32 effects_spawned;

    origin = source;
    effect_count = (rand() & 7) | 4;
    angle_step = 0x1000 / effect_count;
    effects_spawned = 0;
    angle = rand();
    ASM_KEEP(effect_count);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    effect.z = origin->unk_0A;
    effect.c = -4;
    if (effect_count != 0) {
        do {
            effects_spawned += 1;
            effect.x = (origin->unk_02 + (rand() & 0x1F)) - 0x10;
            effect.y = (origin->unk_06 + (rand() & 0x1F)) - 0x10;
            effect.a = func_80064584(angle) << 5;
            effect.b = func_800644B8(angle) << 5;
            func_800ABC00(&effect, angle);
            angle += angle_step;
        } while (effects_spawned < effect_count);
    }
}

