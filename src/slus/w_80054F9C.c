#include "common.h"

/* Task/timer object struct, shared with w_800559B4.c's S_80084858 (field0 is a
 * callback function pointer; field8/fieldA/field18 are s16). */
typedef struct S_80084858 {
    void (*field0)(void); /* 0x00 */
    s32 field4;            /* 0x04 */
    s16 field8;              /* 0x08 */
    s16 fieldA;                /* 0x0A */
    s32 fieldC;                /* 0x0C */
    s16 field10;                /* 0x10 */
    s16 field12;                  /* 0x12 */
    s16 field14;                    /* 0x14 */
    s16 field16;                      /* 0x16 */
    s16 field18;                        /* 0x18 */
} S_80084858;

/* Pre-existing rodata jump table (part of the retail binary blob, already
 * placed at this fixed address) used by the dispatch below. */
extern void *jtbl_80032E14[0x24];

/* Event handler: on first entry into "active" state (field4 != 2), snapshots
 * field8 into fieldA and marks field4 as active (2). Then classifies the pad
 * event byte a0 into a priority code stored into field18. */
void func_80054F9C(s32 a0, S_80084858 *a1) {
    u32 idx;
    s32 result;
    static void *const keepalive[3] = { &&L_B1, &&L_C1, &&L_D1 };

    if (a1->field4 != 2) {
        a1->fieldA = a1->field8;
        a1->field4 = 2;
    }

    idx = (a0 & 0xFF) - 0xB1;
    if (idx >= 0x24) {
        goto L_default;
    }
    goto *jtbl_80032E14[idx];

L_B1:
    result = 0xF;
    goto L_end;
L_C1:
    result = 4;
    goto L_end;
L_D1:
    result = 2;
    goto L_end;
L_default:
    result = 0xA;
L_end:
    a1->field18 = result;
}
