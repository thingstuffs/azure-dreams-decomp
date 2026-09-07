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

/* Advance the entity timers and dispatch its movement and state updates. */
void func_81978140(S_81978140 *entity)
{
    S_81978140_inner *inner;
    u16 timer;
    s32 state;
    s32 timer_under_four;
    static void *const retained_labels[] = {
        &&L0, &&L1, &&L2, &&L3, &&L4,
        &&L5, &&L6, &&L7, &&L8,
    };

    inner = entity->inner;
    inner->value++;
    timer = (u16)entity->timer;
    state = (s16)entity->state;
    timer++;
    entity->timer = timer;
    if ((u32)state >= 5) {
        goto epilogue;
    }
    {
        void * volatile *state_table = jtbl_80024020;
        goto *state_table[state];
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
    entity->x += entity->dx;
    entity->y += entity->dy;
    entity->z += entity->dz;
    if ((s16)entity->timer < 12) {
        goto epilogue;
    }
    func_80025A54();

L5:
    func_800257B8();
    func_800257B8();
L6:
    timer_under_four = (s16)entity->timer < 4;
    ASM_TAILSLOT_PIN_TIED(timer_under_four);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    func_80025A4C();

L7:
    if (entity->timer < 8) {
        goto epilogue;
    }
    {
        u16 next_state = entity->state;
        entity->timer = 0;
        next_state++;
        entity->state = next_state;
    }
    func_80025A88();

L8:
    entity[-1].timer |= 0x8000;
    D_800814A0[0] |= 0x8000;

epilogue:
    (void)retained_labels;
}
