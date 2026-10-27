#include "common.h"
#include "town/player.h"
#include "shared/entity.h"
#include "town/player/scene_action_setup.h"

typedef struct S_8009A18C_0 {
    u8 pad_00[0x4];
    void (*unk_04)(struct Rec_func_80094268_arg0 *, EntityRec *, void *);
} S_8009A18C_0;   /* arg0 in initialize_player_data_reference */

typedef struct S_8009A18C_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8009A18C_1;   /* arg1 in initialize_player_data_reference */

/* Initializes the data reference and state value. */
void initialize_player_data_reference(S_8009A18C_0 *data_ref, S_8009A18C_1 *state) {
    data_ref->unk_04 = &advance_player_state;
    state->unk_14 = 0xFFF60000;
}
