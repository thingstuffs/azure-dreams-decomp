#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "dungeon/player.h"

typedef struct S_80094E34_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80094E34_1;   /* object in clear_player_linked_action_flags */


extern s32 held_item_record;
extern s32 saved_held_item_word;

/* Clear the root and linked object flags, saving and resetting D_80081484 when the root flag is set. */
void clear_player_linked_action_flags(void) {
    ActorRecord *root;
    S_80094E34_1 *linkedObject;
    s32 savedGlobalValue;
    s32 rootFlags;

    root = dungeon_actor_ring_anchor;
    if (root->flags1C & ACTOR_CARRYING) {
        linkedObject = ((PlayerRecord *)root)->unk_124;
        if (linkedObject != 0) {
            linkedObject->unk_1C = (s32)(linkedObject->unk_1C & ACTOR_LIFTED_CLEAR_MASK);
        }
        rootFlags = root->flags1C;
        savedGlobalValue = held_item_record;
        held_item_record = 0;
        root->flags1C = rootFlags & 0xFFEFFFFF;
        saved_held_item_word = savedGlobalValue;
    }
}
