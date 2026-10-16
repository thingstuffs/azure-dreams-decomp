#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801714B0_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_801714B0_0;   /* entity in dungeonUpdateLinkedFacingSprite */

typedef struct S_801714B0_1 {
    u8 pad_00[0x94];
    s16 unk_94;
} S_801714B0_1;   /* arg0 in dungeonUpdateLinkedFacingSprite */


extern void *D_80174CDC[3];

extern void selectIndirectTableEntry(void *, u8, s8);
extern void func_800478B8(void *);

/* Updates the record's directional selection and flag from the entity's facing. */
void dungeonUpdateLinkedFacingSprite(S_801714B0_1 *state, void *unused, Rec_D_80082E80 *record)
{
    S_801714B0_0 *entity;
    u8 *direction_flags;
    s16 calculated_direction;
    s32 direction;

    entity = (u8 *)D_80174CDC[0] + 0x20;
    func_800478B8(record);
    if (D_80174CDC[0] != 0) {
        calculated_direction =
            ((gameWork.view.viewAngle + entity->unk_2A + 0x100) >> 9) & 7;
        direction = calculated_direction;

        if (state->unk_94 != direction) {
            selectIndirectTableEntry(record,
                record->unk_2C.as_pu8[direction],
                record->unk_04.as_s8);
            state->unk_94 = calculated_direction;
        }

        direction_flags = dirSpriteFlag;
        if (direction_flags[direction] != 0) {
            record->unk_14.at00_u16.v |= 1;
        } else {
            record->unk_14.at00_u16.v &= 0xFFFE;
        }
    }
}
