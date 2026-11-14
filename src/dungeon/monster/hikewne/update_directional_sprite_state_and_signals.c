#include "engine/graphics/select_sprite_entry_api.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"
#include "records/Rec_func_8017360C_arg0.h"
#include "dungeon/monster/hikewne_frames.h"

extern s32 update_actor_transform_from_parent(void *, void *, void *, void *);

#include "dungeon/monster/hikewne.h"

/*
 * Alternates Hikewne's idle frames, updates its parent-relative motion, and restores its callback
 * after a floor trap.
 */
void update_directional_sprite_state_and_signals(ActorRecord *controller, void *update_arg, SpriteFrameState *sprite, ActorRecord *actor)
{
    u8 *direction_table;

    direction_table = sprite->frameTable;
    if (direction_table == hikewne_direction_frames) {
        if (*(u16 *)&sprite->unk_04 == 0x103) {
            (sprite->frameTable) = hikewne_alt_direction_frames;
            select_sprite_entry(
                sprite,
                hikewne_alt_direction_frames[
                    ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
    } else if (direction_table == hikewne_alt_direction_frames) {
        if (*(u16 *)&sprite->unk_04 == 0x103) {
            (sprite->frameTable) = hikewne_direction_frames;
            select_sprite_entry(
                sprite,
                hikewne_direction_frames[
                    ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
    }

    if (update_actor_transform_from_parent(controller, update_arg, sprite, actor) != 0) {
        if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
            controller->unk_8C.byte_ptr = update_hikewne_actor_behavior;
        }
    } else if ((*(u8 **)&sprite->frameTable == hikewne_frame_set_2) &&
               !(actor->flags1C & (ACTOR_MP_EMPTY | ACTOR_ASLEEP))) {
        (sprite->frameTable) = hikewne_direction_frames;
        select_sprite_entry(
            sprite,
            hikewne_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
    }
}

/* MECHANISM: Four call-live arguments naturally occupy s2/s3/s0/s1 and make
   the 0x28 frame; the apparent callees are local CFG joins. Duplicated direct
   E0/E8 update arms cross-jump into one suffix with a1-held byte-table bases. */
