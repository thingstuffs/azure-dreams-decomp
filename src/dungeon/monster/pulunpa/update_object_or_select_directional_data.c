#include "common.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "records/Rec_D_80082E80.h"

extern s32 update_actor_transform_from_parent(Rec_func_800A9E70_arg0 *state, ObjectPosition *position, Rec_D_80082E80 *tile, void *actor);

extern void select_sprite_entry(void *, u8, s32);

extern u8 pulunpa_action_resume_address[];
extern u8 pulunpa_variant_action_address[];
extern u8 D_801762C8[];
#include "dungeon/monster/pulunpa.h"
extern u8 D_80176328[];
extern u8 pulunpa_frame_set_3[];

/* Updates object state or selects a source table entry from the target direction. */
/* Updates Pulunpa's parent-relative motion and floor traps, then restores the idle frames for its normal
 * or alternate form. */
void update_object_or_select_directional_data(void *object_arg, void *context, void *source_arg, void *target_arg) {
    void *object = object_arg;
    SpriteFrameState *source= source_arg;
    void *target = target_arg;
    void *state_table;

    if (update_actor_transform_from_parent(object_arg, context, source_arg, target_arg) != 0) {
        if ((check_actor_floor_trap(source, target) << 0x10) > 0) {
            if (*(u8 *)((u8 *)object + 0xA7) != 0) {
                *(void **)((u8 *)object + 0x8C) = pulunpa_variant_action_address;
            } else {
                *(void **)((u8 *)object + 0x8C) = pulunpa_action_resume_address;
            }
        }
        return;
    }

    state_table = source->frameTable;
    if (state_table == pulunpa_direction_frames) {
        if (*(s32 *)((u8 *)target + 0x1C) & 0x208) {
            return;
        }
        source->frameTable = D_801762C8;
        select_sprite_entry(source, D_801762C8[((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)target + 0x2A) + 0x100) >> 9) & 7],
            0);
    } else if (state_table == pulunpa_frame_set_3) {
        if (*(s32 *)((u8 *)target + 0x1C) & 0x208) {
            return;
        }
        source->frameTable = D_80176328;
        select_sprite_entry(source, D_80176328[((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)target + 0x2A) + 0x100) >> 9) & 7],
            0);
    } else {
        return;
    }

}

