#include "common.h"
#include "engine/graphics.h"

typedef struct Entry {
    u8 pad00[6];
    s16 unk06;
    void *unk08;
    struct Entry *unk0C;
    u8 pad10[4];
    u16 unk14;
} Entry;

typedef struct {
    u8 pad[0x13C];
    s32 flag;
} Scratchpad;

/* Walk linked entries, update the scratch flag, and process entries without bit 0x80 set. */
s32 render_actor_sprite_chain(void *initial_state, void *context, Entry *entry)
{
    void *state = initial_state;
    Scratchpad *scratch = (Scratchpad *)0x1F800000;

    for (;;) {
        scratch->flag = *(s16 *)((u8 *)state + 8);
        if (!(entry->unk14 & 0x80)) {
            project_sprite_commands(state, context, entry, entry->unk06);
        }

        entry = *(Entry **)((u8 *)state - 8);
        if (entry != 0) {
            state = (u8 *)entry + 0x20;
            context = entry->unk08;
            entry = entry->unk0C;
            continue;
        }
        return 0;
    }
}
