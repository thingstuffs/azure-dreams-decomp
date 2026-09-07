#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct DungeonGlobal {
    s32 pad_00[4];
    s32 field_10;
} DungeonGlobal;

extern void func_800A2B04(void *, s32, s32);
extern void func_800AAA54(void *, void *, void *, s32);
extern void func_800AD4D0(void *);
extern DungeonGlobal D_80083460;
extern s32 D_80171CE8;

void func_80173D34(void *arg0, void *arg1, void *arg2, void *arg3)
{
    DungeonGlobal *global;
    s32 state;
    s32 timer_signed;
    s32 timer_unsigned;
    s32 timer_next;
    s32 timer_init;

    state = FIELD(arg0, u8, 0x9B);
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
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    FIELD(arg0, u8, 0x9B)++;

    if (FIELD(arg3, u8, 0x28) == 0) {
        goto call_update;
    }
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg0, u8, 0x9B) = 2;
        goto epilogue;
    }

    timer_init = -1;
    if (FIELD(arg3, s32, 0x1C) & 0x228) {
        timer_init = 8;
    }
    FIELD(arg0, u16, 0x96) = timer_init;

state_one:
    timer_signed = FIELD(arg0, s16, 0x96);
    timer_unsigned = FIELD(arg0, u16, 0x96);
    if (timer_signed > 0) {
        FIELD(arg0, u16, 0x96) = timer_unsigned - 1;
        goto check_timer;
    }
    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        FIELD(arg0, u16, 0x96) = 0;
    }

check_timer:
    if (FIELD(arg0, s16, 0x96) != 0) {
        goto epilogue;
    }
    if (FIELD(arg3, u8, 0x28) == 0) {
call_update:
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800AAA54(arg0, arg1, arg2, 0);
        goto epilogue;
    }
    FIELD(arg0, u16, 0x96) = 1;
    FIELD(arg0, u8, 0x9B)++;
    goto epilogue;

state_two:
    timer_next = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = timer_next;
    if ((timer_next << 16) > 0) {
        goto epilogue;
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));

    global = &D_80083460;
    if (global->field_10 == (s32)((u8 *)arg3 - 0x20)) {
        global->field_10 &= 0x7FFFFFFF;
    }
    FIELD(arg0, void *, 0x8C) = &D_80171CE8;

epilogue:
    return;
}
