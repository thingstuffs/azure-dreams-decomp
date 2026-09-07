#include "common.h"

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 state;
    u16 counter;
    s16 x;
    s16 y;
    s16 step;
    s16 angle;
} TownAnimState;

extern void *jtbl_8052674C[];
extern void func_8052D62C(s32 x, s32 y, s32 angle);
extern void func_8052D618(void) __attribute__((noreturn));
extern void func_8052D558(void) __attribute__((noreturn));
extern void func_8052D604(void) __attribute__((noreturn));
__asm__(".set jtbl_8052674C, 0x8052674C");

void func_808128B8(TownAnimState *anim)
{
    s32 state = anim->state;
    static void *const keepalive[] = {
        &&state_0, &&state_1, &&state_2, &&state_3, &&state_4,
    };

    if ((u32)state >= 5) {
        return;
    }
    goto *jtbl_8052674C[state];

state_0:
    anim->step = anim->angle = 0;
    func_8052D62C(anim->x, anim->y, anim->angle);
    anim->state = 1;
    func_8052D618();

state_2:
    if (anim->counter++ & 1) {
        if (anim->step < 12) {
            anim->step++;
            func_8052D558();
        }
        ASM_SCHED_BARRIER();
        anim->state = 3;
    }

state_3:
    anim->angle -= anim->step;
    if (anim->angle < 0) {
        do {
            anim->angle += 32;
            anim->y = (anim->y + 1) % 12;
        } while (anim->angle < 0);
        func_8052D604();
    }
    goto update;

state_4:
    anim->angle -= anim->angle >> 2;
    if (anim->angle < 4) {
        anim->angle = 0;
        anim->state = 0;
    }

update:
    func_8052D62C(anim->x, anim->y, anim->angle);

state_1:
    (void)keepalive;
}
