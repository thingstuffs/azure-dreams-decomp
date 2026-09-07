#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_800537D0(s32, s32, void *);
extern s32 D_800814A0;

void func_800232F4(void *arg0)
{
    u8 *obj;
    void *owner;
    s16 state;
    register u16 step ASM_REG("$4");
    u16 value;
    register s32 correction ASM_REG("$3");
    volatile u16 *position;

    obj = arg0;
    state = FIELD(obj, s16, 0);
    owner = FIELD(obj, void *, 0xC);

    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    func_800537D0(*FIELD(obj, u16 *, 8) * 100, 5,
                  FIELD(obj, void *, 4) + 4);
    if (FIELD(owner, s16, 0x5C) != 3) {
        goto done;
    }

    if (FIELD(obj, s16, 0x16) < 120) {
        FIELD(obj, s16, 2) = -8;
    } else {
        FIELD(obj, s16, 2) = 8;
    }
    FIELD(obj, u16, 0)++;
    goto done;

state_one:
    step = FIELD(obj, u16, 2);
    position = (volatile u16 *)(obj + 0x16);
    value = *position;
    correction = step;
    ASM_KEEP(correction);
    value += step;
    ASM_KEEP(value);
    *position = value;
    correction = (s32)(correction << 16) >> 18;
    value += correction;
    *position = value;
    ASM_KEEP(step);
    if ((u16)(value + 8) >= 249) {
        FIELD(obj, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

done:
    return;
}

/* MECHANISM: True-space labels plus held obj/owner produce the 0x20 s0/s1/ra frame
   and exact zero/default/one CFG. Volatile stores preserve the two-stage position RMW;
   pinned a0/v1 roles and the value fence select retail's copy/add/shift schedule. */
