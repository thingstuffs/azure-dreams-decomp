#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct {
    u16 *random_data;
    s16 mode;
    u16 count;
    u8 unk8[0x22];
    s16 value2a;
} D_800DB420_Obj;

typedef struct {
    u8 unk0[2];
    s16 x;
    u8 unk4[2];
    s16 y;
    u8 unk8[2];
    s16 z;
} D_800DB420_RngOut;

typedef struct {
    u8 unk0[0xC];
    u32 wordC;
    s16 half10;
    u8 unk12[0x1A];
    u8 *data2c;
} D_800DB420_Effect;

extern s32 D_800814A0[3];
extern u8 D_80045340[];
extern s16 D_80083228[5];
extern void func_8004491C(void *, void *);
extern s32 rand(void);
extern void func_80047784(void *, s32, s32);
extern void func_800478B8(void *);

/* Jitter the position and advance the effect through its modes and countdown. */
void func_800DB420(D_800DB420_Obj *state, D_800DB420_RngOut *position, D_800DB420_Effect *effect) {
    position->x = state->random_data[1] + (rand() % 11) - 5;
    position->y = state->random_data[3] + (rand() % 11) - 5;
    position->z = state->random_data[5] + (rand() % 11) - 5;

    switch (state->mode) {
    case 0:
        effect->half10 = 0x60;
        effect->wordC = 0x00303030;
        goto common;
    case 1:
        func_8004491C((u8 *)state - 0x20, D_80045340);
        func_80047784(effect, effect->data2c[((*D_80083228 + state->value2a + 0x100) >> 9) & 7], 0);
    common:
        *(u16 *)((u8 *)state + 4) += 1;
        goto done;
    case 2:
        func_800478B8(effect);
        {
            u16 remaining = *(u16 *)((u8 *)state + 6) - 1;
            *(u16 *)((u8 *)state + 6) = remaining;
            if ((remaining << 0x10) <= 0) {
                *(u16 *)((u8 *)state - 2) |= 0x8000;
                D_800814A0[0] = D_800814A0[0] | 0x8000;
            }
        }
    default:
        goto done;
    }

done:
    return;
}
