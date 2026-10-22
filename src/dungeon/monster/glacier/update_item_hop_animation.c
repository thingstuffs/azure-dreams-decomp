#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80172AD8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    u8 pad_A0[0x4];
    s32 unk_A4;
} S_80172AD8_0;   /* arg0 in update_item_hop_animation */

extern void select_sprite_entry(void *, s16, s16);
extern s32 func_800644B8(s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void on_actor_status_updated(void *);
extern void spend_actor_mp(void *, s32);
extern s32 check_actor_floor_trap(void *, void *);

extern u8 D_801714B8;
extern u8 D_801760BC;
extern u8 D_801760C4;

/* Updates the actor's hop animation and finishes the timed movement at its destination tile. */
void update_item_hop_animation(void *action, void *motion, void *sprite, void *actor)
{
    s32 direction_aux;
    s32 state;
    s32 move_frames;
    s32 target_x;
    s32 position_component;
    s32 height;
    s32 height_offset;
    s32 frame_count;
    s32 action_timer;
    s32 actor_flags;
    DungeonGlobalStatus *global_base;

    state = ((S_80172AD8_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(((SpriteFrameState *)sprite)->flags & 0x6000)) {
            break;
        }
        ((SpriteFrameState *)sprite)->frameTable = &D_801760BC;
        select_sprite_entry(
            sprite,
            *(&D_801760BC +
              (((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7)),
            0);
        ((S_80172AD8_0 *)action)->unk_98 |= 8;
        ((ActorRecord *)actor)->flags1C &= 0xF7FFFFFF;
        ((S_80172AD8_0 *)action)->unk_9E.s = 5;
        ((S_80172AD8_0 *)action)->unk_A4 = 0;
        ((S_80172AD8_0 *)action)->unk_9B++;
                        /* fallthrough */
    case 1:
        ((S_80172AD8_0 *)action)->unk_90 -= ((S_80172AD8_0 *)action)->unk_A4;
        ((SpriteFrameState *)sprite)->scale_x = 0xC00;
        ((SpriteFrameState *)sprite)->scale_y = 0x1400;
        move_frames = ((S_80172AD8_0 *)action)->unk_9E.s;
        if (move_frames != 0) {
            target_x = ((SpriteFrameState *)sprite)->unk_24;
            position_component = ((EntityRec *)motion)->x.w.i;
            target_x <<= 6;
            position_component -= 0x20;
            ((EntityRec *)motion)->unk_0C = ((target_x - position_component) << 16) / move_frames;

            position_component = ((EntityRec *)motion)->y.w.i - 0x20;
            ((EntityRec *)motion)->unk_10 =
                (((((SpriteFrameState *)sprite)->unk_25 << 6) - position_component) << 16) /
                ((S_80172AD8_0 *)action)->unk_9E.s;
            ((S_80172AD8_0 *)action)->unk_A4 =
                (-func_800644B8(((S_80172AD8_0 *)action)->unk_9E.s * 0x199)) << 9;
        }

        height = ((S_80172AD8_0 *)action)->unk_90;
        height_offset = ((S_80172AD8_0 *)action)->unk_A4;
        frame_count = ((S_80172AD8_0 *)action)->unk_9E.u;
        height += height_offset;
        frame_count -= 1;
        ((S_80172AD8_0 *)action)->unk_9E.u = frame_count;
        ((S_80172AD8_0 *)action)->unk_90 = height;
        if ((frame_count << 16) < 0) {
            ((S_80172AD8_0 *)action)->unk_90 = 0;
            ((S_80172AD8_0 *)action)->unk_98 &= 0xFFF7;
            ((ActorRecord *)actor)->flags1C |= 0x08000000;
            ((S_80172AD8_0 *)action)->unk_9B++;
        }
                        /* fallthrough */
    case 2:
        if (((ActorRecord *)actor)->flags1C & 0x08000000) {
            ((S_80172AD8_0 *)action)->unk_98 &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
            ((SpriteFrameState *)sprite)->scale_x = 0x1400;
            ((SpriteFrameState *)sprite)->scale_y = 0xC00;
            ((SpriteFrameState *)sprite)->frameTable = &D_801760C4;
            select_sprite_entry(
                sprite,
                *(&D_801760C4 +
                  (((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7)),
                0);
            ((S_80172AD8_0 *)action)->unk_9B++;
        }
        break;
    case 3:
        ((SpriteFrameState *)sprite)->scale_x = 0x1000;
        ((SpriteFrameState *)sprite)->scale_y = 0x1000;
        break;
    }

    action_timer = ((S_80172AD8_0 *)action)->unk_96 - 1;
    ((S_80172AD8_0 *)action)->unk_96 = action_timer;
    if ((action_timer << 16) > 0) {
        return;
    }

    ((EntityRec *)motion)->flags14 = 0;
    ((EntityRec *)motion)->unk_10 = 0;
    ((EntityRec *)motion)->unk_0C = 0;
    set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
    ((SpriteFrameState *)sprite)->scale_x = 0x1000;
    ((SpriteFrameState *)sprite)->scale_y = 0x1000;
    spend_actor_mp(actor, 4);
    advance_status_timers(actor);

    global_base = &g_dungeon_status;
    if (global_base->activity_counts.parts.pending_movement_count != 0) {
        (*(u16 *)&global_base->activity_counts.parts.pending_movement_count)--;
    }

    actor_flags = ((ActorRecord *)actor)->flags1C;
    if (actor_flags & 0x2000) {
        if (((ActorRecord *)actor)->action_flags & ACTOR_ACTION_PENDING) {
            ((ActorRecord *)actor)->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            ((ActorRecord *)actor)->facing = get_rounded_facing_and_rounding_flag(
                ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &direction_aux);
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        ((S_80172AD8_0 *)action)->unk_8C = &D_801714B8;
        on_actor_status_updated(actor);
    }
}
