#include "common.h"

typedef struct S_80173D34_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173D34_0;   /* arg0 in func_80173D34 */

typedef struct S_80173D34_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80173D34_1;   /* arg1 in func_80173D34 */

typedef struct S_80173D34_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x8];
    u8 unk_28;
} S_80173D34_2;   /* arg3 in func_80173D34 */

typedef struct S_80173D34_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80173D34_3;   /* arg2 in func_80173D34 */



typedef struct DungeonGlobal {
    s32 pad_00[4];
    s32 field_10;
} DungeonGlobal;

extern void func_800A2B04(void *, s32, s32);
extern void func_800AAA54(void *, void *, void *, s32);
extern void func_800AD4D0(void *);
extern DungeonGlobal D_80083460;
extern s32 D_80171CE8;

/* Advance a timed entity state transition, clearing motion and updating its handler. */
void func_80173D34(S_80173D34_0 *controller, S_80173D34_1 *motion, S_80173D34_3 *actor, void *entity_data)
{
    DungeonGlobal *global;
    s32 state;
    s32 timer_signed;
    s32 timer_unsigned;
    s32 timer_next;
    s32 timer_init;

    state = controller->unk_9B;
    switch (state) {
    case 0:
        break;
    case 1:
        goto state_one;
    case 2:
        goto state_two;
    default:
        goto epilogue;
    }

    func_800AD4D0(entity_data);
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    controller->unk_9B++;

    if (((S_80173D34_2 *)entity_data)->unk_28 == 0) {
        goto call_update;
    }
    if (actor->unk_14 & 0x8000) {
        controller->unk_96.s = 0;
        controller->unk_9B = 2;
        goto epilogue;
    }

    timer_init = -1;
    if (((S_80173D34_2 *)entity_data)->unk_1C & 0x228) {
        timer_init = 8;
    }
    controller->unk_96.s = timer_init;

state_one:
    timer_signed = controller->unk_96.u;
    timer_unsigned = controller->unk_96.s;
    if (timer_signed > 0) {
        controller->unk_96.s = timer_unsigned - 1;
        goto check_timer;
    }
    if (actor->unk_14 & 0x6000) {
        controller->unk_96.s = 0;
    }

check_timer:
    if (controller->unk_96.u != 0) {
        goto epilogue;
    }
    if (((S_80173D34_2 *)entity_data)->unk_28 == 0) {
call_update:
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800AAA54(controller, motion, actor, 0);
        goto epilogue;
    }
    controller->unk_96.s = 1;
    controller->unk_9B++;
    goto epilogue;

state_two:
    timer_next = controller->unk_96.s - 1;
    controller->unk_96.s = timer_next;
    if ((timer_next << 16) > 0) {
        goto epilogue;
    }

    motion->unk_14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    func_800A2B04(motion, actor->unk_24, actor->unk_25);

    global = &D_80083460;
    if (global->field_10 == (s32)((u8 *)entity_data - 0x20)) {
        global->field_10 &= 0x7FFFFFFF;
    }
    controller->unk_8C = &D_80171CE8;

epilogue:
    return;
}
