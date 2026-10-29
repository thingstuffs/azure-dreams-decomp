#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "town/minigame/keima.h"
#include "engine/graphics.h"
#include "engine/texture.h"
#include "town/minigame.h"

typedef struct S_800211C4_0 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800211C4_0;   /* arg0 in update_directional_record */

typedef struct S_800211C4_2 {
    u8 pad_00[0x20];
    s16 unk_20;
} S_800211C4_2;   /* arg1_hold in update_directional_record */

/* Update the record for its current direction and set its direction flag. */
void update_directional_record(KeimaPathActor *orientation, void *state_ptr, SpriteFrameState *record) {
    u8 *flags_page;
    void *flags_base;
    s32 direction;
    u8 *direction_data;
    s32 angle_sector;
    u16 angle;
    u16 flags;
    S_800211C4_2 *state = state_ptr;

    angle = (orientation->facing.u + 0x2000) & 0xFFF;
    orientation->facing.u = angle;
    angle_sector = (s32)(g_game_work.view.camera_rotation.parts.viewAngle + angle + 0x100) >> 9;
    direction = angle_sector & 7;
    if (record->flags & 0x6000) {
        select_sprite_entry(record, *((u8 *)*(s32 *)&record->frameTable + direction), 0);
    }
    if (state->unk_20 == direction) {
        flags_page = (u8 *)0x80070000;
    } else {
        direction_data = record->frameTable;
        if (direction_data != 0) {
            select_indirect_table_entry(record, direction_data[direction], record->unk_04);
        }
        state->unk_20 = direction;
        flags_page = (u8 *)0x80070000;
    }
    flags_base = flags_page - 0x3308;
    direction_data = dir_sprite_flag + direction;
    if (direction_data[0] != 0) {
        flags = record->flags | 1;
    } else {
        flags = record->flags & 0xFFFE;
    }
    record->flags = flags;
}
