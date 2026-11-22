#include "common.h"
#include "town/player.h"
#include "shared/entity.h"
#include "town/player/scene_action_setup.h"
#include "town/player/state.h"

typedef struct S_8009A18C_0 {
    u8 pad_00[0x4];
    void (*unk_04)(struct TownObjectRecord *, ObjectPosition *, struct SpriteFrameState *);
} S_8009A18C_0;   /* arg0 in initialize_player_data_reference */

/* Initializes the data reference and state value. */
void initialize_player_data_reference(S_8009A18C_0 *data_ref, ObjectPosition *position) {
    data_ref->unk_04 = &advance_player_state;
    position->velocity_z = -10 * 0x10000;
}
