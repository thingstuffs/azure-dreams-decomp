#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;


/* Advance the counter and mark completion at 16 ticks, decrementing the global count. */
void func_800A5D5C(void *counter) {
    u16 tick_count;
    u16 *state;

    tick_count = *(u16 *)counter + 1;
    *(u16 *)counter = tick_count;
    if ((s16)tick_count >= 0x10) {
        state = (u16 *)((D_80083460_t *)&dungeonStatus);
        state[5]--;
        *(u16 *)((u8 *)counter - 2) |= 0x8000;
        objectFlagBlock.flags = objectFlagBlock.flags | 0x8000;
    }
}
