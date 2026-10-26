#include "common.h"

typedef struct Entry {
    u8 pad00[6];
    s16 unk06;
    void *unk08;
    struct Entry *unk0C;
    u8 pad10[4];
    u16 unk14;
} Entry;

extern void render_actor_sprite_parts(void *unused, void *position, Entry *sprite, s16 depth_bias);

/* Processes unflagged entries while following the state chain. */
s32 process_actor_state_chain(void *state_base, void *entry_data, Entry *entry)
{
    void *state = state_base;

    for (;;) {
        if (!(entry->unk14 & 0x80)) {
            render_actor_sprite_parts(state, entry_data, entry, entry->unk06);
        }
        entry = *(Entry **)((u8 *)state - 8);
        if (entry == 0) {
            break;
        }
        state = (u8 *)entry + 0x20;
        entry_data = entry->unk08;
        entry = entry->unk0C;
    }
    return 0;
}
