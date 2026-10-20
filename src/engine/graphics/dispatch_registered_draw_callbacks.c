#include "common.h"
#include "shared/game_work.h"

typedef s32 (*Callback)(void *, s32, s32);

typedef struct Entry {
    u8 pad0[8];
    s32 callback_arg1;
    s32 callback_arg2;
    u8 pad10[0xE];
    u16 flags;
    u8 data[1];
} Entry;

extern s32 is_frame_packet_arena_overflowed(s32);
extern Callback registered_draw_callbacks[0x20];
extern Entry *registered_draw_objects[0x20];

void dispatch_registered_draw_callbacks(void)
{
    s32 i;

    for (i = 0; i < 32; i++) {
        Callback callback = registered_draw_callbacks[i];
        if (callback != 0) {
            Entry *entry = registered_draw_objects[i];
            if (entry != 0) {
                if (!(entry->flags & 0x800)) {
                    callback(entry->data, entry->callback_arg1, entry->callback_arg2);
                    if (is_frame_packet_arena_overflowed(*(s32 *)((u8 *)g_game_work.draw_buffer + 0x8D0))) {
                        break;
                    }
                }
            } else {
                registered_draw_callbacks[i] = 0;
            }
        }
    }
}
