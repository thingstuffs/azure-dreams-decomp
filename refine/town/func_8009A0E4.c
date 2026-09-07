#include "common.h"

typedef struct {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    u16 field_A;
    s32 field_C;
    s32 field_10;
    u8 pad14[2];
    s16 field_16;
} UnkStack;

s32 func_800644B8(s32);
s32 func_80064584(s32);
s32 rand(void);
void func_800ABC00(UnkStack *, s16);

/* Spawns effects near the source with randomized positions and evenly spaced directions. */
void func_80097844(void *source, s32 effect_count)
{
    UnkStack effect;
    s32 angle;
    s32 spawned;
    s32 angle_step;
    register s32 full_turn ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */

    if (effect_count != 0) {
        full_turn = 0x1000;
        angle_step = full_turn / effect_count;
        spawned = 0;
        angle = rand();
        effect.field_16 = -4;
        effect.field_A = *(u16 *)((u8 *)source + 0xA);
        if (effect_count > 0) {
            do {
                spawned++;
                effect.x = (*(u16 *)((u8 *)source + 2) +
                          (rand() & 0x1F)) - 0x10;
                effect.y = (*(u16 *)((u8 *)source + 6) +
                          (rand() & 0x1F)) - 0x10;
                effect.field_C = func_80064584(angle) << 5;
                effect.field_10 = func_800644B8(angle) << 5;
                func_800ABC00(&effect, (s16)angle);
                angle += angle_step;
            } while (spawned < effect_count);
        }
    }
}

