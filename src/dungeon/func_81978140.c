#include "common.h"

typedef struct {
    u8 pad[0x1A];
    u16 value;
} S_81978140_inner;

typedef struct {
    u8 pad0[0x2A];
    u16 value;
} S_81978140_global;

typedef struct {
    S_81978140_inner *inner;
    u8 pad04[0x30];
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
    u16 state;
    s16 timer;
} S_81978140;

extern void *jtbl_80024020[5];
__asm__(".set jtbl_80024020, 0x80024020");
extern S_81978140_global *D_800814A8;
extern s32 D_800814A0[3];

extern void func_800257B8(void);
extern void func_80025A40(void) __attribute__((noreturn));
extern void func_80025A4C(void) __attribute__((noreturn));
extern void func_80025A54(void) __attribute__((noreturn));
extern void func_80025A88(void) __attribute__((noreturn));

void func_81978140(S_81978140 *arg0)
{
    S_81978140_inner *inner;
    u16 timer;
    s32 state;
    s32 dead;
    static void *const keepalive[] = {
        &&L0, &&L1, &&L2, &&L3, &&L4,
        &&L5, &&L6, &&L7, &&L8,
    };

    inner = arg0->inner;
    inner->value++;
    timer = (u16)arg0->timer;
    state = (s16)arg0->state;
    timer++;
    arg0->timer = timer;
    if ((u32)state >= 5) {
        goto epilogue;
    }
    {
        void * volatile *table = jtbl_80024020;
        goto *table[state];
    }

L0:
    func_800257B8();
L1:
    func_800257B8();
L2:
    D_800814A8->value -= 0x200;
    func_80025A40();

L3:
    func_800257B8();
    func_800257B8();
L4:
    arg0->x += arg0->dx;
    arg0->y += arg0->dy;
    arg0->z += arg0->dz;
    if ((s16)arg0->timer < 12) {
        goto epilogue;
    }
    func_80025A54();

L5:
    func_800257B8();
    func_800257B8();
L6:
    dead = (s16)arg0->timer < 4;
    ASM_TAILSLOT_PIN_TIED(dead);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    func_80025A4C();

L7:
    if (arg0->timer < 8) {
        goto epilogue;
    }
    {
        u16 next_state = arg0->state;
    arg0->timer = 0;
        next_state++;
        arg0->state = next_state;
    }
    func_80025A88();

L8:
    arg0[-1].timer |= 0x8000;
    D_800814A0[0] |= 0x8000;

epilogue:
    (void)keepalive;
}
