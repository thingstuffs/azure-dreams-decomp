#include "common.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"
#include "dungeon/player/object.h"


extern s32 prepare_directional_attack();
extern s32 apply_camera_offset_and_select_target(void *object_addr, void *source_pos, s32 helper_arg, s32 slot_value);
extern void begin_actor_exclusive_action();


/* Start the actor action and reset its state when ready, or dispatch the alternate action. */
void begin_actor_action(Rec_func_800A9E70_arg0 *state, ObjectPosition *world_pos, s32 tile_pos, EntityRec *actor)
{
    if (state->unk_B5 == 0) {
        actor->unk_71 &= 0x7F;
        if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 16) == 0)) {
            apply_camera_offset_and_select_target((u8 *)actor - 0x20, world_pos, 8, 0x300);
            if ((try_claim_dungeon_action_slot(actor) << 16) == 0) {
                state->unk_8C = 0;
                state->unk_9A.as_s8 = 0x11;
                state->unk_9B.as_s8 = 0;
                state->unk_96.as_s16 = 0;
                actor->unk_6D--;
                state->unk_98 |= 8;
                prepare_directional_attack(actor, tile_pos, actor->facing, 1, 0);
                actor->unk_84 = 0x7C;
                actor->unk_85 = 0;
                return;
            }
        }
    } else {
        begin_actor_exclusive_action(state, world_pos, tile_pos, 1, 1);
    }
}
