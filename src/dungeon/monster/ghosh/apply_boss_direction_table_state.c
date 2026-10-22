/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

typedef struct S_80170A54_0 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_80170A54_0;   /* base in apply_boss_direction_table_state */

typedef struct S_80170A54_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80170A54_1;   /* object in apply_boss_direction_table_state */

typedef struct S_80170A54_2 {
    u16 unk_00;
} S_80170A54_2;   /* arg0 in apply_boss_direction_table_state; pointer addresses record offset 0x2 */



void texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(); /* extern */
extern void *primary_actor_record[3];
extern u8 resident_globals_page[];

/* Applies a direction-indexed table entry in state 2 and sets record and global flags. */
void apply_boss_direction_table_state(void *record_data) {
    S_80170A54_1 *active_object = (S_80170A54_1 *)primary_actor_record[0];
    TileObject *state_data = &reference_tile_object;


    if (state_data->unk_004 == 2) {
        u8 direction_entry;
        direction_entry = ((u8 *)state_data->frame_table)[
                 (((s32) (g_game_work.view.camera_rotation.parts.viewAngle +
                          active_object->unk_2A +
                          0x100) >> 9) & 7)];
        texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(state_data, direction_entry,
            4, 1);
        ((S_80170A54_2 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_80170A54_2 *)((u8 *)record_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
