#include "common.h"

/* Shared gauge/timer struct layout also used by D_800848F8 / D_80084858
 * (see func_8005440C / func_800546B0 / func_800559B4 family notes):
 * field0 (fn ptr), field4 (s32 state), field8 (s16 current value),
 * fieldA (s16 target), field16 (u16 increment step), field18 (u16 decrement step). */
typedef struct S_800545F4 {
    /*0x00*/ void (*field0)(void);
    /*0x04*/ s32 field4;
    /*0x08*/ s16 field8;
    /*0x0A*/ s16 fieldA;
    /*0x0C*/ u8 pad0C[0xA];
    /*0x16*/ u16 field16;
    /*0x18*/ u16 field18;
} S_800545F4;

/* Raises or lowers the active gauge, calling its callback after an update or returning -1 on depletion. */
s32 func_800545F4(S_800545F4 *gauge)
{
    u16 next_value;

    switch (gauge->field4) {
    case 1:
        next_value = (u16)(gauge->field8 + gauge->field16);
        gauge->field8 = next_value;
        if (gauge->fieldA < (s16)next_value) {
            gauge->field8 = (s16)gauge->fieldA;
            gauge->field4 = 3;
        }
        break;
    case 2:
        next_value = (u16)(gauge->field8 - gauge->field18);
        gauge->field8 = next_value;
        if ((s16)next_value <= 0) {
            gauge->field8 = 0;
            return -1;
        }
        break;
    default:
        return 0;
    }

    if (gauge->field0 != 0) {
        gauge->field0();
    }
    return 0;
}
