#include "shared/dungeon_actor_callbacks.h"
#include "dungeon/player/input.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "dungeon/level.h"

/* Updates global flags and stores the pointer selected by the source flags. */
void *refresh_actor_lists_and_select_controller(ActorRecord *body, void *unused_1, void *unused_2, ActorRecord *actor) {
    void *next_ptr;

    process_unflagged_linked_entries_alt(actor->next_actor_header);
    process_unflagged_linked_entries(actor->next_actor_header);
    g_dungeon_status.flags |= 0x812;
    if (actor->flags1C & 0x100000) {
        next_ptr = handle_carrying_player_input;
    } else {
        next_ptr = handle_player_input;
    }
    body->unk_8C.address = next_ptr;
    return next_ptr;
}
