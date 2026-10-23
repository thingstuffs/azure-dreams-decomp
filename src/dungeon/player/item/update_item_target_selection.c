#include "shared/dungeon_actor_callbacks.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/tile_object.h"
#include "records/Rec_D_80082EB0.h"

typedef struct S_80091958_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x2C];
    void * unk_C8;
} S_80091958_0;   /* arg0 in update_item_target_selection */

extern u8 player_action_tag[];

void *create_item_target_selector(u8 *selection_data);

/* Starts an operation, waits for completion, then selects the next action from context flags. */
void update_item_target_selection(S_80091958_0 *state, s32 unused_1, s32 unused_2, ActorRecord *context)
{
    void *operation;

    switch (state->unk_9B) {
    case 0:
        operation = create_item_target_selector(reference_tile_object.selected_item);
        state->unk_C8 = operation;
        if (operation == 0) {
            break;
        }
        state->unk_9B++;
    case 1:
        if (((ObjectNodeHeader *)state->unk_C8)->flags & 0x8000) {
            state->unk_C8 = 0;
            state->unk_9B++;
        }
        break;
    case 2:
        reference_tile_object.unk_038 = 0;
        if (context->flags1C & 0x100000) {
            state->unk_8C = player_action_tag;
        } else {
            state->unk_8C = handle_player_input;
        }
        break;
    }
}
