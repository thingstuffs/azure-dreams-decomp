#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_func_800AA258_arg2.h"

typedef struct S_80047784 S_80047784;

void select_sprite_entry(S_80047784 *object, s16 table_index, s16 entry_index);         /* extern */
void apply_actor_delta_and_cap_value();         /* extern */


/* Set the entity to state 7 and select its directional sprite frame when ready. */
s32 begin_ready_actor_directional_action(void *entity, s32 context, Rec_func_800AA258_arg2 *sprite, s32 direction_frames) {
    if (((Rec_func_800A9E70_arg0 *)entity)->unk_64 > 0) {
        apply_actor_delta_and_cap_value(entity, context, sprite, entity);
        return 0;
    }
    g_dungeon_status.unk_10 = (void *) ((s8 *) entity - 0x20);
    ((Rec_func_800A9E70_arg0 *)entity)->unk_9A.as_s8 = 7;
    ((Rec_func_800A9E70_arg0 *)entity)->unk_9B.as_s8 = 0;
    ((Rec_func_800A9E70_arg0 *)entity)->unk_8C = 0;
    if (direction_frames != 0) {
        if (!(((Rec_func_800A9E70_arg0 *)entity)->unk_1C & 0x20)) {
            sprite->unk_2C.as_s32 = direction_frames;
            select_sprite_entry(sprite, *((u8 *) direction_frames + (((s32) (g_game_work.view.viewAngle
                + ((Rec_func_800A9E70_arg0 *)entity)->unk_2A + 0x100) >> 9) & 7)), 0);
        }
    }
    return 1;
}
