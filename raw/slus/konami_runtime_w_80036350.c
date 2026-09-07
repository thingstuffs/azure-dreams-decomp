#include "common.h"

#include "common.h"

typedef struct RuntimeState {
    u8 pad_00[0x10];
    u32 flags_10;
} RuntimeState;

typedef struct CursorInfo {
    u8 pad_00[0x26];
    u8 count_26;
} CursorInfo;

typedef struct CursorState {
    u8 pad_00[0x4D];
    u8 cursor_4D;
    u8 pad_4E[0x26];
    CursorInfo *info_74;
} CursorState;

extern RuntimeState D_80083160;
extern void func_80053DA8(u32);
extern void func_80036434(CursorState *, s32, s32);

void func_80036350(CursorState *arg0, s32 arg1, s32 arg2)
{
    RuntimeState *runtime;
    u32 value;
    u32 flags;

    runtime = &D_80083160;
    flags = runtime->flags_10;
    if (flags & 0x4000) {
        func_80053DA8(0x502);
        value = arg0->cursor_4D + 1;
        flags = (u32)arg0->info_74;
        arg0->cursor_4D = value;
        value = arg0->cursor_4D;
        flags = *(u8 *)(flags + 0x26);
        flags = value % flags;
        arg0->cursor_4D = flags;
    } else if (flags & 0x1000) {
        func_80053DA8(0x502);
        flags = (u32)arg0->info_74;
        flags = *(u8 *)(flags + 0x26);
        value = arg0->cursor_4D + flags;
        value -= 1;
        arg0->cursor_4D = value;
        flags = (u32)arg0->info_74;
        value = arg0->cursor_4D;
        flags = *(u8 *)(flags + 0x26);
        flags = value % flags;
        arg0->cursor_4D = flags;
    }
    if (runtime->flags_10 & 0x40) {
        func_80036434(arg0, arg1, arg2);
    }
}
