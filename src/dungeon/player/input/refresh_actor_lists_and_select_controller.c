#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/dungeon_status.h"

extern void process_unflagged_linked_entries(s32);
extern void process_unflagged_linked_entries_alt(s32);
extern u8 player_action_tag[];

/* Updates global flags and stores the pointer selected by the source flags. */
void *refresh_actor_lists_and_select_controller(void *state, void *unused_1, void *unused_2, void *source) {
    void *next_ptr;

    process_unflagged_linked_entries_alt(*(s32 *)((u8 *)source + 0x5C));
    process_unflagged_linked_entries(*(s32 *)((u8 *)source + 0x5C));
    g_dungeon_status.flags |= 0x812;
    if (*(s32 *)((u8 *)source + 0x1C) & 0x100000) {
        next_ptr = player_action_tag;
    } else {
        next_ptr = handle_player_input;
    }
    *(void **)((u8 *)state + 0x8C) = next_ptr;
    return next_ptr;
}
