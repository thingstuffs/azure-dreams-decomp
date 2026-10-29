#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "records/Rec_D_80082E80.h"
#include "engine/texture.h"
#include "slus.h"

typedef struct S_801714B0_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_801714B0_0;   /* entity in update_linked_facing_sprite */

typedef struct S_801714B0_1 {
    u8 pad_00[0x94];
    s16 unk_94;
} S_801714B0_1;   /* arg0 in update_linked_facing_sprite */

/* Updates the record's directional selection and flag from the entity's facing. */
void update_linked_facing_sprite(S_801714B0_1 *state, void *unused, SpriteFrameState *record)
{
    ActorRecord *entity;
    u8 *direction_flags;
    s16 calculated_direction;
    s32 direction;

    entity = (void *)(D_80174CDC + 1);
    advance_sprite_animation_and_textures(record);
    if (D_80174CDC != 0) {
        calculated_direction =
            ((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7;
        direction = calculated_direction;

        if (state->unk_94 != direction) {
            select_indirect_table_entry(record,
                (*(u8 * *)&record->frameTable)[direction],
                record->unk_04);
            state->unk_94 = calculated_direction;
        }

        direction_flags = dir_sprite_flag;
        if (direction_flags[direction] != 0) {
            record->flags |= 1;
        } else {
            record->flags &= 0xFFFE;
        }
    }
}
