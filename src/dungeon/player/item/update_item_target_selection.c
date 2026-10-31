#include "shared/dungeon_actor_callbacks.h"
#include "dungeon/player/input.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/tile_object.h"
#include "records/Rec_D_80082EB0.h"
#include "dungeon/effect/screen.h"
#include "dungeon/player/item.h"


enum ItemTargetPhase {
    ITEM_TARGET_OPEN = 0,
    ITEM_TARGET_WAIT = 1,
    ITEM_TARGET_RESTORE_INPUT = 2,
};

/* Starts an operation, waits for completion, then selects the next action from context flags. */
void update_item_target_selection(PlayerRecord *state, s32 unused_1, s32 unused_2, ActorRecord *context)
{
    void *operation;

    switch (state->actor.action_phase.u) {
    case ITEM_TARGET_OPEN:
        operation = create_item_target_selector(reference_tile_object.selected_item);
        state->unk_C8 = operation;
        if (operation == 0) {
            break;
        }
        state->actor.action_phase.u++;
    case ITEM_TARGET_WAIT:
        if (((ObjectNodeHeader *)state->unk_C8)->flags & 0x8000) {
            state->unk_C8 = 0;
            state->actor.action_phase.u++;
        }
        break;
    case ITEM_TARGET_RESTORE_INPUT:
        reference_tile_object.unk_038 = 0;
        if (context->flags1C & 0x100000) {
            state->actor.unk_8C.address = handle_carrying_player_input;
        } else {
            state->actor.unk_8C.address = handle_player_input;
        }
        break;
    }
}
