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

/* Activates the task, snapshots its timer on entry, and assigns the pad event priority. */
void func_80054F9C(s32 pad_event, S_80084858 *task) {
    u32 event_index;
    s32 priority;

    if (task->field4 != 2) {
        task->fieldA = task->field8;
        task->field4 = 2;
    }

    event_index = (pad_event & 0xFF) - 0xB1;
    switch (event_index) {
    case 0:
    case 3:
        priority = 0xF;
        break;
    case 16:
    case 19:
        priority = 4;
        break;
    case 32:
    case 35:
        priority = 2;
        break;
    default:
        priority = 0xA;
        break;
    }
    task->field18 = priority;
}
