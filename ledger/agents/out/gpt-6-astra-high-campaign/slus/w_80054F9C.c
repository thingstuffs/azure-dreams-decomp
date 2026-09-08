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

/* Activates the task, snapshots its timer on entry, and assigns the pad event priority. */
void func_80054F9C(s32 pad_event, S_80084858 *task) {
    u32 event_index;
    s32 priority;
    static void *const keepalive[3] = { &&L_B1, &&L_C1, &&L_D1 };

    if (task->field4 != 2) {
        task->fieldA = task->field8;
        task->field4 = 2;
    }

    event_index = (pad_event & 0xFF) - 0xB1;
    if (event_index >= 0x24) {
        goto L_default;
    }
    goto *jtbl_80032E14[event_index];

L_B1:
    priority = 0xF;
    goto L_end;
L_C1:
    priority = 4;
    goto L_end;
L_D1:
    priority = 2;
    goto L_end;
L_default:
    priority = 0xA;
L_end:
    task->field18 = priority;
}
