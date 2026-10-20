#include "dungeon/monster/troll/create_tinted_sprite_effect_supplied_position.h"
#include "shared/sprite_frame_state.h"

/* Animate movement to the target tile and finalize the actor when the timer expires. */
void create_tinted_sprite_effect_supplied_position(T_8017406C_S_8017406C_0 *animation, EntityRec *motion, SpriteFrameState *tile, EntityRec *actor)
{
    s32 state;
    s32 arc_ticks;
    s32 target_x;
    s32 world_x;
    s32 height;
    s32 arc_offset;
    s32 world_y;
    s32 next_arc_ticks;
    s32 ticks_left;
    s32 actor_flags;
    s32 coord_result;
    DungeonGlobalStatus *global_base;

    state = animation->unk_9B;
    switch (state) {
    case 0:
        animation->unk_98 |= 8;
        actor->flags1C &= 0xF7FFFFFF;
        animation->unk_9E.s = 5;
        animation->unk_A0 = 0;
        animation->unk_9B++;
                        /* fall through */
    case 1:
        arc_ticks = animation->unk_9E.s;
        animation->unk_90 -= animation->unk_A0;
        if (arc_ticks != 0) {
            target_x = tile->unk_24;
            world_x = motion->x.w.i;
            target_x <<= 6;
            world_x -= 0x20;

            motion->unk_0C =
                ((target_x - world_x) << 16) / arc_ticks;

            world_y = motion->y.w.i;
            world_y -= 0x20;
            motion->unk_10 =
                (((tile->unk_25 << 6) - world_y) << 16) /
                animation->unk_9E.s;

            animation->unk_A0 =
                (-func_800644B8(animation->unk_9E.s * 0x199)) << 10;
        }

        height = animation->unk_90;
        arc_offset = animation->unk_A0;
        next_arc_ticks = animation->unk_9E.u;
        height += arc_offset;
        next_arc_ticks -= 1;
        animation->unk_9E.u = next_arc_ticks;
        animation->unk_90 = height;
        if ((next_arc_ticks << 16) < 0) {
            animation->unk_90 = 0;
            animation->unk_98 &= 0xFFF7;
            actor->flags1C |= 0x08000000;
            animation->unk_9B++;
        }
                        /* fall through */
    case 2:
        if (actor->flags1C & 0x08000000) {
            animation->unk_98 &= 0xFFF7;
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            set_record_integer_tile_center(motion, tile->unk_24, tile->unk_25);
            animation->unk_9B++;
        }
        break;
    default:
        break;
    }

    ticks_left = animation->unk_96 - 1;
    animation->unk_96 = ticks_left;
    if ((ticks_left << 16) > 0) {
        return;
    }

    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    set_record_integer_tile_center(motion, tile->unk_24, tile->unk_25);
    reduce_actor_food_meter(actor, 4);
    advance_status_timers(actor);

    global_base = &g_dungeon_status;
    if (global_base->unk_08 != 0) {
        (*(u16 *)&global_base->unk_08)--;
    }

    actor_flags = actor->flags1C;
    if (actor_flags & 0x2000) {
        if (actor->unk_46 & 0x8000) {
            actor->unk_46 &= 0x7FFF;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            actor->facing = get_rounded_facing_and_rounding_flag(
                tile->unk_24,
                tile->unk_25,
                D_80082E80.tileX,
                D_80082E80.tileY,
                &coord_result);
        }
    }
    if ((check_actor_floor_trap(tile, actor) << 16) > 0) {
        animation->unk_8C = update_actor_behavior;
        on_actor_status_updated(actor);
    }
}
