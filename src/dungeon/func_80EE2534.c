#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80173D34_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173D34_0;   /* arg0 in func_80173D34 */






typedef struct DungeonGlobal {
    s32 pad_00[4];
    s32 field_10;
} DungeonGlobal;

extern void func_800A2B04(void *, s32, s32);
extern void func_800AAA54(void *, void *, void *, s32);
extern void func_800AD4D0(void *);
extern DungeonGlobal D_80083460;
extern s32 D_80171CE8;

void func_80173D34(S_80173D34_0 *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2, void *arg3)
{
    DungeonGlobal *global;
    s32 state;
    s32 timer_signed;
    s32 timer_unsigned;
    s32 timer_next;
    s32 timer_init;

    state = arg0->unk_9B;
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

    func_800AD4D0(arg3);
    arg1->unk_10.at00_s32.v = 0;
    arg1->unk_0C.as_s32 = 0;
    arg0->unk_9B++;

    if (((Rec_D_800E3D7C *)arg3)->unk_28 == 0) {
        goto call_update;
    }
    if (arg2->unk_14.at00_u16.v & 0x8000) {
        arg0->unk_96.s = 0;
        arg0->unk_9B = 2;
        goto epilogue;
    }

    timer_init = -1;
    if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x228) {
        timer_init = 8;
    }
    arg0->unk_96.s = timer_init;

state_one:
    timer_signed = arg0->unk_96.u;
    timer_unsigned = arg0->unk_96.s;
    if (timer_signed > 0) {
        arg0->unk_96.s = timer_unsigned - 1;
        goto check_timer;
    }
    if (arg2->unk_14.at00_u16.v & 0x6000) {
        arg0->unk_96.s = 0;
    }

check_timer:
    if (arg0->unk_96.u != 0) {
        goto epilogue;
    }
    if (((Rec_D_800E3D7C *)arg3)->unk_28 == 0) {
call_update:
        arg1->unk_14.as_s32 = 0;
        arg1->unk_10.at00_s32.v = 0;
        arg1->unk_0C.as_s32 = 0;
        func_800AAA54(arg0, arg1, arg2, 0);
        goto epilogue;
    }
    arg0->unk_96.s = 1;
    arg0->unk_9B++;
    goto epilogue;

state_two:
    timer_next = arg0->unk_96.s - 1;
    arg0->unk_96.s = timer_next;
    if ((timer_next << 16) > 0) {
        goto epilogue;
    }

    arg1->unk_14.as_s32 = 0;
    arg1->unk_10.at00_s32.v = 0;
    arg1->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);

    global = &D_80083460;
    if (global->field_10 == (s32)((u8 *)arg3 - 0x20)) {
        global->field_10 &= 0x7FFFFFFF;
    }
    arg0->unk_8C = &D_80171CE8;

epilogue:
    return;
}
