#include "modules/dungeon_engine_dungeon_util_fragment_c05e4.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;


/* Advance the counter and mark completion at 16 ticks, decrementing the global count. */
void advance_timed_object_and_retire(void *counter) {
    u16 tick_count;

    tick_count = *(u16 *)counter + 1;
    *(u16 *)counter = tick_count;
    if ((s16)tick_count >= 0x10) {
        g_dungeon_status.unk_0A--;
        *(u16 *)((u8 *)counter - 2) |= 0x8000;
        object_flag_block.flags = object_flag_block.flags | 0x8000;
    }
}
