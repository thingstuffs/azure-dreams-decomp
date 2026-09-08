#include "common.h"

typedef struct S_800232F4_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    void * unk_04;
    u16 * unk_08;
    void * unk_0C;
    u8 pad_10[0x6];
    s16 unk_16;
} S_800232F4_0;   /* obj in func_800232F4 */

typedef struct S_800232F4_1 {
    u8 pad_00[0x5C];
    s16 unk_5C;
} S_800232F4_1;   /* owner in func_800232F4 */



extern void func_800537D0(s32, s32, void *);
extern s32 D_800814A0;

/* Updates the display value, then moves the object outward and flags it when out of bounds. */
void func_800232F4(void *object)
{
    u8 *obj;
    void *owner;
    s16 state;
    register u16 step ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u16 position_value;
    register s32 quarter_step ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    volatile u16 *position;

    obj = object;
    state = ((S_800232F4_0 *)obj)->unk_00.s;
    owner = ((S_800232F4_0 *)obj)->unk_0C;

    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    func_800537D0(*((S_800232F4_0 *)obj)->unk_08 * 100, 5,
                  ((S_800232F4_0 *)obj)->unk_04 + 4);
    if (((S_800232F4_1 *)owner)->unk_5C != 3) {
        goto done;
    }

    if (((S_800232F4_0 *)obj)->unk_16 < 120) {
        ((S_800232F4_0 *)obj)->unk_02.s = -8;
    } else {
        ((S_800232F4_0 *)obj)->unk_02.s = 8;
    }
    ((S_800232F4_0 *)obj)->unk_00.u++;
    goto done;

state_one:
    step = ((S_800232F4_0 *)obj)->unk_02.u;
    position = (volatile u16 *)(obj + 0x16);
    position_value = *position;
    quarter_step = step;
    position_value += step;
    ASM_KEEP(position_value);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    *position = position_value;
    quarter_step = (s32)(quarter_step << 16) >> 18;
    position_value += quarter_step;
    *position = position_value;
    if ((u16)(position_value + 8) >= 249) {
        (*(u16 *)((u8 *)obj + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

done:
    return;
}

/* MECHANISM: True-space labels plus held obj/owner produce the 0x20 s0/s1/ra frame
   and exact zero/default/one CFG. Volatile stores preserve the two-stage position RMW;
   pinned a0/v1 roles and the value fence select retail's copy/add/shift schedule. */
