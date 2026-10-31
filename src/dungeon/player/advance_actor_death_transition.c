#include "engine/resource.h"
#include "slus.h"
#include "shared/dungeon_actor_callbacks.h"
#include "shared/sprite_frame_state.h"
#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "dungeon/player/item.h"
#include "dungeon/item.h"

extern u8 dungeon_button_latch[9];
void snapshot_inventory_and_familiars(void *input_state);
extern u8 D_800E0672[17];

   /* input in advance_actor_death_transition */

typedef struct S_8008E0C4_2 {
    u8 unk_00;
} S_8008E0C4_2;   /* D_800E3CD0 in advance_actor_death_transition */

/* Waits for the death animation and delay, then changes scenes or restores player input in state 0x10. */
void advance_actor_death_transition(ActorRecord *context, void *unused, SpriteFrameState *input, ActorRecord *entity) {
    GameWork *work;
    u16 remaining;
    s32 state;

    work = &g_game_work;
    state = context->action_phase.u;
    switch (state) {
    case 0:
        if (input->flags & 0xE000) {
            adjust_source_value_and_finalize(entity, D_800E0672);
            context->action_timer.u = 0x80;
            context->action_phase.u++;
        }
        break;

    case 1:
        remaining = context->action_timer.u - 1;
        context->action_timer.u = remaining;
        if ((remaining << 0x10) > 0) {
            break;
        }
        if (*(u16 *)0x80013714 & 4) {
            if (((S_8008E0C4_2 *)dungeon_button_latch)->unk_00 == 0) {
                ((S_8008E0C4_2 *)dungeon_button_latch)->unk_00 = state;
                request_scene_dispatch_state(3);
                break;
            }
        } else {
            snapshot_inventory_and_familiars(context);
            snapshot_inventory_familiar_records();
            runtime_dispatch_state.flags16 = 0xC000;
            request_scene_state_with_parameters(6, 0, 0, 0, 0xC000);
            context->action_phase.u++;
            break;
        }
        break;

    case 2:
        break;

    case 0x10:
        if (input->flags & 0xE000) {
            entity->hp = entity->max_hp;
            entity->facing = 0x400 - ((((u16)work->view.camera_rotation.parts.viewAngle) + 0x100) & 0xE00);
            context->unk_8C.ptr_ptr =handle_player_input;
            g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
        }
        break;
    }
}
