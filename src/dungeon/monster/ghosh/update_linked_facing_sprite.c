#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801714B0_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_801714B0_0;   /* entity in update_linked_facing_sprite */

typedef struct S_801714B0_1 {
    u8 pad_00[0x94];
    s16 unk_94;
} S_801714B0_1;   /* arg0 in update_linked_facing_sprite */

extern void *D_80174CDC[3];

extern void select_indirect_table_entry(void *, u8, s8);
extern void func_800478B8(void *);

/* Updates the record's directional selection and flag from the entity's facing. */
void update_linked_facing_sprite(S_801714B0_1 *state, void *unused, SpriteFrameState *record)
{
    S_801714B0_0 *entity;
    u8 *direction_flags;
    s16 calculated_direction;
    s32 direction;

    entity = (u8 *)D_80174CDC[0] + 0x20;
    func_800478B8(record);
    if (D_80174CDC[0] != 0) {
        calculated_direction =
            ((g_game_work.view.viewAngle + entity->unk_2A + 0x100) >> 9) & 7;
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
