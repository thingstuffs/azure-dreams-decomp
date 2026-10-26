/* Actor directional action and its file-private helper. */
#include "common.h"
#include "dungeon/actor/motion.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "engine/graphics.h"
/* extern */
static void apply_actor_delta_and_cap_value(void *unused_0, void *unused_1, void *unused_2, u8 *record);
extern void apply_clamped_actor_value_delta(void *arg);

/* Starts action 7 with directional frames when ready; otherwise applies the pending actor delta. */
s32 begin_ready_actor_directional_action(void *entity, void *context, void *sprite_in, u8 *direction_frames) {
    Rec_func_800AA258_arg2 *sprite = sprite_in;
    if (((Rec_func_800A9E70_arg0 *)entity)->unk_64 > 0) {
        apply_actor_delta_and_cap_value(entity, context, sprite, entity);
        return 0;
    }
    g_dungeon_status.pending_display_owner = (void *) ((s8 *) entity - 0x20);
    ((Rec_func_800A9E70_arg0 *)entity)->unk_9A.as_s8 = 7;
    ((Rec_func_800A9E70_arg0 *)entity)->unk_9B.as_s8 = 0;
    ((Rec_func_800A9E70_arg0 *)entity)->unk_8C = 0;
    if (direction_frames != 0) {
        if (!(((Rec_func_800A9E70_arg0 *)entity)->unk_1C & 0x20)) {
            sprite->unk_2C.as_pu8 = direction_frames;
            select_sprite_entry(sprite, *(direction_frames + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle
                + ((Rec_func_800A9E70_arg0 *)entity)->unk_2A + 0x100) >> 9) & 7)), 0);
        }
    }
    return 1;
}

/*
 * Applies the actor value delta, then caps byte 0x28 at the limit in byte 0x29; the first three
 * arguments are unused.
 */
static void apply_actor_delta_and_cap_value(void *unused_0, void *unused_1, void *unused_2, u8 *record) {
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
