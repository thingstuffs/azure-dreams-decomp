#include "common.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"
#include "records/Rec_func_8017360C_arg0.h"

extern void select_sprite_entry(void *, u8, s32);
extern s32 update_actor_transform_from_parent(s32, s32, void *, void *);


extern u8 D_801714D4;
extern u8 D_801740E0[];
#include "dungeon/monster/hikewne.h"
extern u8 D_80174158[];

/* Updates the directional sprite state and signals the controller after the actor update. */
/* Alternates Hikewne's idle frames, updates its parent-relative motion, and restores its callback after a
 * floor trap. */
void update_directional_sprite_state_and_signals(s32 controller, s32 update_arg, SpriteFrameState *sprite, ActorRecord *actor)
{
    u8 *direction_table;

    direction_table = *(u8 **)&sprite->frameTable;
    if (direction_table == D_801740E0) {
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
            (sprite->frameTable) = D_801740E0;
            select_sprite_entry(
                sprite,
                D_801740E0[
                    ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
    }

    if (update_actor_transform_from_parent(controller, update_arg, sprite, actor) != 0) {
        if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
            ((Rec_func_8017360C_arg0 *)controller)->unk_8C.as_pu8 = &D_801714D4;
        }
    } else if ((*(u8 **)&sprite->frameTable == D_80174158) &&
               !(actor->flags1C & 0x208)) {
        (sprite->frameTable) = D_801740E0;
        select_sprite_entry(
            sprite,
            D_801740E0[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
    }
}

/* MECHANISM: Four call-live arguments naturally occupy s2/s3/s0/s1 and make
   the 0x28 frame; the apparent callees are local CFG joins. Duplicated direct
   E0/E8 update arms cross-jump into one suffix with a1-held byte-table bases. */
