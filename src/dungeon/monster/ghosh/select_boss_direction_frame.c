/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"


typedef struct S_80170A54_2 {
    u16 unk_00;
} S_80170A54_2;   /* arg0 in select_boss_direction_frame; pointer addresses record offset 0x2 */



#include "engine/texture.h"
#include "dungeon/monster/ghosh.h"

/* Applies a direction-indexed table entry in state 2 and sets record and global flags. */
void select_boss_direction_frame(void *record_data) {
    ActorRecord *active_object = primary_actor_record;
    TileObject *state_data = &reference_tile_object;


    if (state_data->frame_index == 2) {
        u8 direction_entry;
        direction_entry = ((u8 *)state_data->frame_table)[
                 (((s32) (g_game_work.view.camera_rotation.parts.viewAngle +
                          active_object->facing +
                          0x100) >> 9) & 7)];
        texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(state_data, direction_entry,
            4, 1);
        ((S_80170A54_2 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_80170A54_2 *)((u8 *)record_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
