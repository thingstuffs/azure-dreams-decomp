#include "common.h"
#include "engine/graphics/select_sprite_entry_api.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "records/Rec_func_801724B0_arg0.h"
#include "shared/entity.h"
#include "dungeon/monster/baloon.h"

typedef struct S_80047784 S_80047784;

struct SpriteFrameState;
extern u8 D_800E2360;

/* Initializes state and configures the target using an angle-indexed table entry. */
void start_baloon_facing_pose(ActorRecord *state, ObjectPosition *unused, SpriteFrameState *target, ActorRecord *angleSource) {
    state->action_id = 0x10;
    state->action_phase = 0;
    target->frameTable = &D_800E2360;
    select_sprite_entry(target, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + angleSource->facing + 0x100) >> 9) & 7) + &D_800E2360),
        0);
    state->unk_AA = 0;
}
