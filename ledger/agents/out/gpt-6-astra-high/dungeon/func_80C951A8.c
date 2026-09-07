#include "common.h"

typedef struct S_801729A8_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801729A8_0;   /* arg0 in func_801729A8 */

typedef struct S_801729A8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_801729A8_1;   /* arg2 in func_801729A8 */

typedef struct S_801729A8_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801729A8_2;   /* arg3 in func_801729A8 */

typedef struct S_801729A8_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801729A8_3;   /* arg1 in func_801729A8 */



extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_8017102C[];
extern u8 D_801752DC[];

/* Advances a timed actor animation and performs its completion cleanup. */
void func_801729A8(void *action, void *motion, void *sprite, void *actor)
{
    s32 state;
    s32 next_state;
    s32 start_state;
    u16 timer;

    state = ((S_801729A8_0 *)action)->unk_9B;
    start_state = 1;
    if (state == start_state) {
        goto state_1;
    }
    if (!(state < 2)) {
        goto state_ge_2;
    }
    if (state == 0) {
        goto state_0;
    }
    goto end;

state_ge_2:
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto end;

state_0:
    ((S_801729A8_0 *)action)->unk_9B = start_state;

state_1:
    if (((S_801729A8_1 *)sprite)->unk_14 & 0x8000) {
        ((S_801729A8_0 *)action)->unk_9B = 3;
        ((S_801729A8_1 *)sprite)->unk_14 |= 0x6000;
        func_8009C12C(actor, sprite, ((S_801729A8_2 *)actor)->unk_2A, 1);
        goto end;
    }

    ((S_801729A8_3 *)motion)->unk_14 = 0;
    ((S_801729A8_3 *)motion)->unk_10 = 0;
    ((S_801729A8_3 *)motion)->unk_0C = 0;
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801752DC;
    func_80047784(sprite,
        D_801752DC[((D_80083228 + ((S_801729A8_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    next_state = ((S_801729A8_0 *)action)->unk_9B;
    ((S_801729A8_0 *)action)->unk_96.s = 0;
    goto bump_state;

state_2:
    timer = ((S_801729A8_0 *)action)->unk_96.s + 1;
    ((S_801729A8_0 *)action)->unk_96.s = timer;
    if ((s16)timer == 7 || (((S_801729A8_1 *)sprite)->unk_14 & 0x8000)) {
        func_8009C12C(actor, sprite, ((S_801729A8_2 *)actor)->unk_2A, 1);
    }
    if (((S_801729A8_0 *)action)->unk_96.u == 6) {
        func_800A56E0(0x808);
    }
    if (((S_801729A8_0 *)action)->unk_96.u == 8) {
        ((S_801729A8_1 *)sprite)->unk_14 |= 0x0800;
    }
    if (((S_801729A8_0 *)action)->unk_96.u == 15 ||
        (((S_801729A8_1 *)sprite)->unk_14 & 0x8000)) {
        ((S_801729A8_1 *)sprite)->unk_14 &= 0xF7FF;
        next_state = ((S_801729A8_0 *)action)->unk_9B;
        goto bump_state;
    }
    goto end;

bump_state:
    next_state++;
    ((S_801729A8_0 *)action)->unk_9B = next_state;
    goto end;

state_3:
    if (((S_801729A8_1 *)sprite)->unk_14 & 0xE000) {
        func_800AD594(actor, 0x100);
        ((S_801729A8_0 *)action)->unk_8C = D_8017102C;
        D_8008346C = 0;
        func_800A4ACC(actor);
        ((S_801729A8_2 *)actor)->unk_46 &= 0x7FFF;
    }

end:
    return;
}
