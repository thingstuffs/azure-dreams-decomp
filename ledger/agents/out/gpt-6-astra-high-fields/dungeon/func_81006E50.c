#include "common.h"

typedef struct S_func_81006E50_0 {
    u8 pad_00[0x8C];
    void *unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_func_81006E50_0;

typedef struct S_func_81006E50_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_func_81006E50_1;

typedef struct S_func_81006E50_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void *unk_2C;
} S_func_81006E50_2;

typedef struct S_func_81006E50_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} S_func_81006E50_3;

extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8;
extern u8 D_80171058[];
extern u8 D_801748B8[];

void func_80047784(void *, u8, s32);
void func_8009C12C(void *, void *, s16, s32);
void func_800A2B04(void *, u8, u8);
void func_800A4ACC(void *);
void func_800A56E0(s32);
void func_800AD594(void *, s32);

/* Advances the actor animation sequence and resets its action state on completion. */
void func_80172650(S_func_81006E50_0 *action, S_func_81006E50_1 *motion, S_func_81006E50_2 *animation, void *actor_data) {
    register S_func_81006E50_3 *actor ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    u16 delay_ticks;
    u8 next_state;
    s32 state;

    actor = actor_data;
    state = action->unk_9B;
    switch (state) {
        case 0:
            action->unk_9B = 1;
        case 1:
            goto state_1;
        case 2:
            goto state_2;
        case 3:
            goto state_3;
        default:
            return;
    }

state_1:
    if (animation->unk_14 & 0x8000) {
        action->unk_9B = 3;
        animation->unk_14 |= 0x6000;
        func_8009C12C(actor, animation, actor->unk_2A, 1);
        goto end;
    }
    motion->unk_14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    *(void **)((u8 *)animation + 0x2C) = D_801748B8;
    func_80047784(animation,
        D_801748B8[((D_80083228 + actor->unk_2A + 0x100) >> 9) & 7],
        0);
    next_state = action->unk_9B;
    action->unk_96 = 0;
    goto increment_state;

state_2:
    delay_ticks = action->unk_96 + 1;
    action->unk_96 = delay_ticks;
    if ((s16)delay_ticks != 2) {
        goto end;
    }
    func_800A56E0(0x808);
    func_8009C12C(actor, animation, actor->unk_2A, 1);
    next_state = action->unk_9B;

increment_state:
    next_state++;
    action->unk_9B = next_state;
    goto end;

state_3:
    if (!(animation->unk_14 & 0xE000)) {
        goto end;
    }
    func_800A2B04(motion, animation->unk_24, animation->unk_25);
    func_800AD594(actor, 0x100);
    action->unk_8C = D_80171058;
    D_8008346C = 0;
    func_800A4ACC(actor);
    if (actor->unk_6D == 0) {
        actor->unk_46 &= 0x7FFF;
        goto end;
    }
    D_800E3DE8 = (u8 *)actor - 0x20;
    ASM_USE(actor);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

end:
    return;
}
