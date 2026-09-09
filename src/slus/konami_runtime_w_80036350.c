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
extern void SD_Call(u32);
extern void func_80036434(CursorState *, s32, s32);

/* Wrap the cursor on directional input and dispatch the selected action. */
void func_80036350(CursorState *cursor, s32 action_arg1, s32 action_arg2)
{
    RuntimeState *runtime;
    u32 next_cursor;
    u32 flags_or_count;

    runtime = &D_80083160;
    flags_or_count = runtime->flags_10;
    if (flags_or_count & 0x4000) {
        SD_Call(0x502);
        next_cursor = cursor->cursor_4D + 1;
        flags_or_count = (u32)cursor->info_74;
        cursor->cursor_4D = next_cursor;
        next_cursor = cursor->cursor_4D;
        flags_or_count = *(u8 *)(flags_or_count + 0x26);
        flags_or_count = next_cursor % flags_or_count;
        cursor->cursor_4D = flags_or_count;
    } else if (flags_or_count & 0x1000) {
        SD_Call(0x502);
        flags_or_count = (u32)cursor->info_74;
        flags_or_count = *(u8 *)(flags_or_count + 0x26);
        next_cursor = cursor->cursor_4D + flags_or_count;
        next_cursor -= 1;
        cursor->cursor_4D = next_cursor;
        flags_or_count = (u32)cursor->info_74;
        next_cursor = cursor->cursor_4D;
        flags_or_count = *(u8 *)(flags_or_count + 0x26);
        flags_or_count = next_cursor % flags_or_count;
        cursor->cursor_4D = flags_or_count;
    }
    if (runtime->flags_10 & 0x40) {
        func_80036434(cursor, action_arg1, action_arg2);
    }
}
