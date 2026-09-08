#include "common.h"

#define U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define S8(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8;
extern u8 D_80170E68;
extern u8 D_80173894[];

/* Advances an actor action through animation setup, a delay, and completion. */
void func_80172698(void *action, void *motion, void *sprite, void *actor)
{
    s32 phase;
    s32 loaded_phase;
    u16 delay_ticks;

    phase = U8(action, 0x9B);
    if (phase == 1) {
        goto wait_delay;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto begin_action;
        }
        goto done;
    }
    if (phase == 2) {
        goto finish_action;
    }
    goto done;

begin_action:
    if (U16(sprite, 0x14) & 0x8000) {
        U8(action, 0x9B) = 2;
        U16(sprite, 0x14) |= 0x6000;
        func_8009C12C(actor, sprite, S16(actor, 0x2A), 1);
        goto done;
    }

    S32(motion, 0x14) = 0;
    S32(motion, 0x10) = 0;
    S32(motion, 0x0C) = 0;
    PTR(sprite, 0x2C) = D_80173894;
    func_80047784(sprite,
        D_80173894[((D_80083228 + S16(actor, 0x2A) + 0x100) >> 9) & 7],
        0);
    loaded_phase = U8(action, 0x9B);
    U16(action, 0x96) = 0;
    goto advance_phase;

wait_delay:
    delay_ticks = U16(action, 0x96) + 1;
    U16(action, 0x96) = delay_ticks;
    if ((s16)delay_ticks != 10) {
        goto done;
    }
    func_800A56E0(0x808);
    func_8009C12C(actor, sprite, S16(actor, 0x2A), 1);
    loaded_phase = U8(action, 0x9B);

advance_phase:
    U8(action, 0x9B) = loaded_phase + 1;
    goto done;

finish_action:
    if (!(U16(sprite, 0x14) & 0xE000)) {
        goto done;
    }
    func_800A2B04(motion, U8(sprite, 0x24), U8(sprite, 0x25));
    func_800AD594(actor, 0x100);
    PTR(action, 0x8C) = &D_80170E68;
    D_8008346C = 0;
    func_800A4ACC(actor);
    if (S8(actor, 0x6D) == 0) {
        U16(actor, 0x46) &= 0x7FFF;
    } else {
        D_800E3DE8 = (u8 *)actor - 0x20;
    }

done:
    return;
}

