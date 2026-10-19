/* Actor directional action and its file-private helper. */
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_func_800AA258_arg2.h"
M2C_UNK func_80047784();
/* extern */
static void apply_actor_delta_and_cap_value();
extern void apply_clamped_actor_value_delta(void *arg);

s32 begin_ready_actor_directional_action(void *entity, M2C_UNK context, Rec_func_800AA258_arg2 *sprite, s32 direction_frames) {
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
            func_80047784(sprite, *((u8 *) direction_frames + (((s32) (g_game_work.view.viewAngle
                + ((Rec_func_800A9E70_arg0 *)entity)->unk_2A + 0x100) >> 9) & 7)), 0);
        }
    }
    return 1;
}

static void apply_actor_delta_and_cap_value(s32 unused_0, s32 unused_1, s32 unused_2, u8 *record) {
    u8 limit;

    (void)unused_0;
    (void)unused_1;
    (void)unused_2;
    apply_clamped_actor_value_delta(record);
    limit = record[0x29];
    if (limit < record[0x28]) {
        record[0x28] = limit;
    }
}
