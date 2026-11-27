#include "common.h"
#include "dungeon/actor/state.h"

typedef struct Entry {
    u8 pad00[6];
    s16 depth_bias;
    void *position;
    struct Entry *sprite;
    u8 pad10[4];
    u16 flags;
} Entry;

extern void render_actor_sprite_parts(void *unused, void *position, Entry *sprite, s16 depth_bias);

/* Processes unflagged entries while following the state chain. */
s32 render_actor_part_chain(void *state_base, void *entry_data, Entry *entry)
{
    void *state = state_base;

    for (;;) {
        if (!(entry->flags & 0x80)) {
            render_actor_sprite_parts(state, entry_data, entry, entry->depth_bias);
        }
        entry = *(Entry **)((u8 *)state - 8);
        if (entry == 0) {
            break;
        }
        state = (u8 *)entry + 0x20;
        entry_data = entry->position;
        entry = entry->sprite;
    }
    return 0;
}
