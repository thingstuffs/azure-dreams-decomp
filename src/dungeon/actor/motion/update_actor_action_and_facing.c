#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

extern void func_8003DB94(void *sprite, void *ptr, s32 value);
extern void clear_slots_of_type(void *actor, s32 value);
extern void reset_actor_motion_at_sprite_tile(void *state, void *motion, void *sprite, void *actor);
extern void handle_actor_commands_and_facing(void);
extern void apply_clamped_actor_value_delta(void *actor);

extern void *D_800DD274[8];

/* Refresh the directional sprite and advance the actor state when sprite flags are set. */
void update_actor_action_and_facing_2(Rec_func_8008ACDC_arg0 *state, EntityRec *motion, SpriteFrameState *sprite, EntityRec *actor)
{
    s32 tracked_addr;

    if (state->unk_9B.as_u8 == 0) {
        apply_clamped_actor_value_delta(actor);
        state->unk_9B.as_u8++;
    }

    if (sprite->flags & 0xE000) {
        sprite->frameTable = D_800DD274;
        func_8003DB94(
            sprite,
            D_800DD274[
                ((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);

        tracked_addr = ((s32)g_dungeon_status.unk_10);
        if (tracked_addr == (u32)((u8 *)actor - 0x20)) {
            g_dungeon_status.unk_10 = tracked_addr & 0x7FFFFFFF;
        }

        if (actor->unk_28 == 0) {
            actor->unk_28 = 0;
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            clear_slots_of_type(actor, 10);
            reset_actor_motion_at_sprite_tile(state, motion, sprite, actor);
            return;
        }

        state->unk_96.as_s16 = 8;
        state->unk_8C.as_pv = handle_actor_commands_and_facing;
    }
}
